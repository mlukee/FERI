#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "common.h"

volatile int alarm_diff = 0;   // globalna spremenljivka za casovno razliko
volatile int sigint_flag = 0;  // globalna spremenljivka za prekinitev
volatile int sigterm_flag = 0; // globalna spremenljivka za prekinitev

void sig_handler(int signum) // funkcija za obdelavo signalov
{
    if (signum == SIGALRM) // ce je signal SIGALRM
        alarm(alarm_diff); //  nastavi alarm na casovno razliko

    if (signum == SIGINT)  // ce je signal SIGINT
        sigint_flag = 1;   // nastavi sigint_flag na 1
    if (signum == SIGTERM) // ce je signal SIGTERM
        sigterm_flag = 1;  // nastavi sigterm_flag na 1
}

int main(int argc, char **argv)
{
    if (argc != 2)
    { // ce ni podan argument
        fprintf(stderr, "Manjka obvezni argument.\n");
        return EXIT_FAILURE;
    }

    double razlika_casov = 0;     // spremenljivka za casovno razliko
    signal(SIGALRM, sig_handler); // nastavi obdelavo signala SIGALRM
    signal(SIGINT, sig_handler);  // nastavi obdelavo signala SIGINT
    signal(SIGTERM, sig_handler); // nastavi obdelavo signala SIGTERM

    struct job_node *job_list = read_job_list(argv[1]); // prebere datoteko

    struct job_node *job_node = job_list; // nastavi job_node na prvi element seznama

    while (job_node != NULL) // dokler ni konec seznama
    {
        time_t current_time = time(NULL);                       // trenutni cas
        razlika_casov = difftime(job_node->time, current_time); // casovna razlika med trenutnim casom in casom iz datoteke
        if (razlika_casov <= 0)                                 // ce je casovna razlika manjsa ali enaka 0
        {
            if (sigint_flag == 1 || sigterm_flag == 1) // ce je bil prekinjen prekini zanko
                break;
            system(job_node->cmd); // izvedi ukaz
        }
        if (razlika_casov > 0) // ce je casovna razlika vecja od 0
        {
            if (job_node->next != NULL) // ce je naslednji element seznam ni NULL
            {
                alarm_diff = difftime(job_node->next->time, job_node->time); // casovna razlika med trenutnim casom in casom iz datoteke
                alarm(razlika_casov);                                        // nastavi alarm na casovno razliko
                pause();                                                     // počakaj na signal
                if (sigint_flag == 1 || sigterm_flag == 1)                   // ce je bil prekinjen prekini zanko
                    break;
                system(job_node->cmd); // izvedi ukaz
            }
            else
            {
                alarm(razlika_casov);                      // nastavi alarm na casovno razliko
                pause();                                   // počakaj na signal
                if (sigint_flag == 1 || sigterm_flag == 1) // ce je bil prekinjen prekini zanko
                    break;
                system(job_node->cmd); // izvedi ukaz
            }
        }

        job_node = job_node->next; // prehodi na naslednji element seznama
    }
    while (job_node != NULL) // ce je bil prekinjen izpisi preostanek seznama
    {
        printf("%ld %s\n", job_node->time, job_node->cmd);
        job_node = job_node->next;
    }

    free_job_list(job_list); // osvobodi seznam

    return EXIT_SUCCESS;
}
