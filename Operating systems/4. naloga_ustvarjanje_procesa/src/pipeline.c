#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int execute_pipeline(char ***cmd_list, int input_fd, int output_fd, int err_fd)
{
    int output_trenutni_fd = -1;
    int return_status = 0;
    int naslednji_fd = -1;
    while(cmd_list[0] != 0) // gre skozi vrstice v cmd_list
    {
        if ((cmd_list + 1)[0] != 0) // ce ni zadni proces
        {
            int pipe_fd[2]; // pipe_fd[0], pipe_fd[1], pipe
            if (pipe(pipe_fd) == -1)
            {
                perror("napaka pri kreiranju pipe!");
                return 1;
            }
            naslednji_fd = pipe_fd[0];
            output_trenutni_fd = pipe_fd[1];
        }

        int pid = fork();
        // 0...input
        // 1...output
        // 2...error
        switch (pid)
        {
        case -1:
            perror("Napaka pri ustvarjanju procesa!");
            return -1;
            break;
        case 0:
            if ((cmd_list + 1)[0] == 0) // ce je zadnji proces
            {
                output_trenutni_fd = output_fd;
            }
            if (dup2(output_trenutni_fd, STDOUT_FILENO) == -1)
            {
                perror("Napaka pri STDOUT_FILENO!");
                return -1;
            }
            close(output_trenutni_fd);

            if (dup2(input_fd, STDIN_FILENO) == -1)
            {
                perror("Napaka pri STDIN_FILENO!");
                return -1;
            }
            if (dup2(err_fd, STDERR_FILENO) == -1)
            {
                perror("Napaka pri STDERR_FILENO!");
                return -1;
            }
            close(err_fd);
            close(input_fd);
            execvp(cmd_list[0][0], cmd_list[0]);
            perror("Napaka pri zaganjanju procesa!");
            return -1;
            break;
        default:
            close(input_fd);
            if ((cmd_list + 1)[0] != 0) // ce je zadnji proces
            {
                close(output_trenutni_fd);
            }
            input_fd = naslednji_fd;
            int status;
            waitpid(pid, &status, 0);
            if (return_status == 0)
            {
                if (WIFEXITED(status))
                {
                    return_status = WEXITSTATUS(status);
                }
                else
                {
                    return_status = 255;
                }
            }
            break;
        }
        cmd_list += 1;
    }
    return return_status;
}
