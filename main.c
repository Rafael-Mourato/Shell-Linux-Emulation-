#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LEN 256
#define MAX_ARGS_LEN 64

void run_command(char *args[]) {
    int pid = fork();

    if (pid == 0) {
        execvp(args[0], args);

        printf("Erro: Comando %s não encontrado.\n", args[0]);
        exit(1);
    }
    else if (pid > 0) {
        wait(NULL);
    }
    else {
        printf("Erro ao criar o processo filho.\n");
    }
}

void help_command() {

    printf("\n=========================================================\n");
    printf("                  EMULATION SHELL LINUX                   \n");
    printf("=========================================================\n");
    printf("Esta shell permite executar uma selecao de comandos Linux.\n\n");
    printf("Comandos disponíveis: \n");
    printf("  > ajuda      - Mostra um menu com todos os comandos disponíveis.\n");
    printf("  > sai        - Termina a execução desta shell.\n");
    printf("  > lista      - lista ficheiros e diretorios.\n");
    printf("  > quem       - Mostra quem está no sistema.\n");
    printf("  > processos  - Mostra os processos ativos.\n");
    printf("  > manual     - Mostra a documentacao do sistema.\n");
    printf("  > limpa      - Limpa o ecra do terminal.\n\n");

}

int main(void) {

    char entry[MAX_COMMAND_LEN];
    char *args[MAX_ARGS_LEN];

    bool running = true;

    do {

        printf("shell_emulation> ");

        if (fgets(entry, MAX_COMMAND_LEN, stdin) == NULL) {
            break;
        }

        entry[strcspn(entry, "\n")] = '\0';

        int i = 0;
        args[i] = strtok(entry, " ");

        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if (args[0] == NULL) {
            continue;
        }

        if (strcmp(args[0], "ajuda") == 0) {
            help_command();
        } else if (strcmp(args[0], "sai") == 0) {
            printf("A sair...\n");
            running = false;
        } else if (strcmp(args[0], "quem") == 0) {
            args[0] = "who";
            run_command(&args[0]);

        } else if (strcmp(args[0], "lista") == 0) {
            args[0] = "ls";
            run_command(&args[0]);

        } else if (strcmp(args[0], "processos") == 0) {
            args[0] = "ps";
            run_command(&args[0]);

        } else if (strcmp(args[0], "manual") == 0) {

            args[0] = "man";

            if (args[1] != NULL) {
                if (strcmp(args[1], "quem") == 0) {
                    args[1] = "who";
                } else if (strcmp(args[1], "lista") == 0) {
                    args[1] = "ls";
                } else if (strcmp(args[1], "processos") == 0) {
                    args[1] = "ps";
                }  else if (strcmp(args[1], "manual") == 0) {
                    args[1] = "man";
                }
            }

            run_command(args);

        } else if (strcmp(args[0], "limpa") == 0) {
            args[0] = "clear";
            run_command(&args[0]);

        } else {
            printf("Comando nao reconhecido.\n");
        }

    } while (running);

    return 0;
}
