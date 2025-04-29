
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_redir
{
    char *file;
    char *type;
    struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
    char **args;
    t_redir *redirs;
} t_cmd;

typedef struct s_data
{
    int fd1[2];
    int *pid;
    int nb_cmds;
} t_data;

void apply_redirection(t_redir *redir)
{
    while (redir)
    {
        int fd;
        if (redir->type[0] == '>')
        {
            fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redir->type[0] == '<')
        {
            fd = open(redir->file, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        redir = redir->next;
    }
}

void wait_all_pids(t_data *data)
{
    for (int i = 0; i < data->nb_cmds; i++)
        waitpid(data->pid[i], NULL, 0);
}

void exec_multi_cmd(t_data *data, t_cmd *cmds)
{
    pipe(data->fd1);
    int i = 0;

    while (i < data->nb_cmds)
    {
        data->pid[i] = fork();
        if (data->pid[i] < 0)
        {
            perror("fork");
            exit(1);
        }
        if (data->pid[i] == 0)
        {
            if (i == 0)
                dup2(data->fd1[1], STDOUT_FILENO);
            else if (i == data->nb_cmds - 1)
                dup2(data->fd1[0], STDIN_FILENO);

            close(data->fd1[0]);
            close(data->fd1[1]);

            apply_redirection(cmds[i].redirs);

            // Debug print
            printf("Process %d launching: ", i);
            for (int k = 0; cmds[i].args[k]; k++)
                printf("[%s] ", cmds[i].args[k]);
            printf("\n");

            execvp(cmds[i].args[0], cmds[i].args);
            perror("execvp");
            exit(1);
        }
        i++;
    }
    close(data->fd1[0]);
    close(data->fd1[1]);
    wait_all_pids(data);
}

int count_args(char **av)
{
    int count = 0;
    while (av[count] && strcmp(av[count], "|") != 0 && strcmp(av[count], "<") != 0 && strcmp(av[count], ">") != 0)
        count++;
    return count;
}

void stock_cmds(t_cmd *cmds, char **av, int nb_cmds)
{
    int i = 0;
    int cmd_i = 0;

    while (cmd_i < nb_cmds)
    {
        while (av[i] && (strcmp(av[i], "<") == 0 || strcmp(av[i], ">") == 0))
        {
                t_redir *new_redir = malloc(sizeof(t_redir));
                new_redir->type = strdup(av[i]);
                new_redir->file = strdup(av[i + 1]);
                new_redir->next = cmds[cmd_i].redirs;
                cmds[cmd_i].redirs = new_redir;
                i += 2;
        }
        int nb_args = count_args(av + i);
        char **args_tmp = malloc(sizeof(char *) * (nb_args + 1));
        int arg_i = 0;

        while (arg_i < nb_args)
        {
            args_tmp[arg_i] = strdup(av[i]);
            arg_i++;
            i++;
        }
        args_tmp[arg_i] = NULL;
        cmds[cmd_i].args = args_tmp;
        cmds[cmd_i].redirs = NULL;
        if (av[i])
            i++;
        cmd_i++;
    }
}

int main(int ac, char **av)
{
    if (ac < 5)
    {
        printf("Usage: ./minishell < Makefile cmd | cmd > file\n");
        return 1;
    }

    t_data *data = malloc(sizeof(t_data));
    data->nb_cmds = 2;
    data->pid = malloc(sizeof(int) * 2);
    t_cmd *cmds = malloc(sizeof(t_cmd) * 2);

    stock_cmds(cmds, av + 1, 2);
    exec_multi_cmd(data, cmds);

    return 0;
}
