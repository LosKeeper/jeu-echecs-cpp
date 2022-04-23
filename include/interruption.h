#pragma once
#include "../include/thread.h"
#include <csignal>
#include <unistd.h>

/**
 * @brief Variable globale indiquant si une interruption est à traiter
 */
namespace {
volatile sig_atomic_t gSignalStatus = 0;
}

/**
 * @brief Fonction traitant une interruption
 * @param sig le numéro de l'interruption
 */
void signal_handler(int signal) {
    switch (signal) {
        // Si CTRL+C on ferme le programme
    case SIGINT:
        cout << endl << "Terminaison par CTRL-C" << endl;
        gSignalStatus = 2;
        pthread_kill(tid_lecteur, SIGUSR1);
        break;

        // Si CTRL+Z on ferme le thread s'occupant de la lecture et on
        // positionne la variable globale à 1
    case SIGTSTP:
        cout << endl << "Dernier coup annulé" << endl;
        gSignalStatus = 1;
        pthread_kill(tid_lecteur, SIGUSR1);
        break;
    }
}