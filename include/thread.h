#pragma once
#include <csignal>
#include <iostream>
#include <pthread.h>
#include <thread>

/**
 * @brief Variable globale indiquant l'id du thread qui lit l'entrée dans le
 * terminal
 */
pthread_t tid_lecteur;

/**
 * @brief Fonction qui s'occupe des interruptions pour l thread de lecture
 */
void signal_lecteur(int signal) {
    if (signal == SIGUSR1) {
        pthread_exit(NULL);
    }
}

/**
 * @brief Fonction qui lit l'entrée dans le terminal
 * @param mouvment la chaine de caractère contenant le contenu rentré par
 * l'utilisateur
 */
void lecture_entree_terminal(std::string &mouvement) {
    tid_lecteur = pthread_self();
    signal(SIGUSR1, signal_lecteur);
    std::cin.clear();
    std::cin >> mouvement;
    pthread_exit(NULL);
}
