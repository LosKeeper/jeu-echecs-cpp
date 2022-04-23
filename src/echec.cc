#include <iostream>
#include <ostream>
#include <pthread.h>
#include <thread>
#include <vector>
using namespace std;

/**
 * @brief NBCOL correspond à la taille de l'échiquier sur une colonne (qui est
 * aussi la meme sur une ligne)
 */
#define NBCOL 8

#include "../include/debug.h"
#include "../include/echec.h"
#include "../include/interruption.h"
#include "../include/jeu.h"

int main() {
    signal(SIGTSTP, signal_handler);
    signal(SIGINT, signal_handler);
    Jeu monjeu;
    Jeu ancienjeu;
    string mouvement;
    bool stop(false);
    monjeu.affiche();
    do {
        thread lecteur(lecture_entree_terminal, ref(mouvement));
        cout << monjeu.couleur_a_deplacer;
        cout << " : Coup (eg. e2e4) ? ";
        lecteur.join();
        if (gSignalStatus == 1) {
            monjeu = ancienjeu;
            gSignalStatus = 0;
            monjeu.repositionner_pieces();
            goto fin_affichage;
        } else if (gSignalStatus == 2) {
            stop = true;
            gSignalStatus = 0;
            goto fin_affichage;
        }
        if (mouvement != "/quit" && mouvement != "/pieces") {
            ancienjeu = monjeu;
            if (saisie_correcte(mouvement)) {
                // découper case origine et destination
                string orig = mouvement.substr(0, 2);
                string dest = mouvement.substr(2, 2);
                monjeu.deplace(orig, dest);
            } else if (saisie_correcte_petitroque(mouvement)) {
                monjeu.deplace_roque(true);
            } else if (saisie_correcte_grandroque(mouvement)) {
                monjeu.deplace_roque(false);
            } else {
                cerr << "Entrée incorrect" << endl;
            }
            monjeu.repositionner_pieces();
            monjeu.en_echec = false;
            DEB(cout << "-> Vérification de l'échec" << endl);
            if (monjeu.echec(monjeu.echiquier)) {
                monjeu.en_echec = true;
                if (monjeu.mat()) {
                    cout << "-> Victoire du joueur "
                         << !monjeu.couleur_a_deplacer << endl
                         << "=>Appuyer sur CTRL+C ou entrez \"/quit\" "
                            "pour quitter le programme"
                         << endl;
                }
            }
            lecteur.~thread();
        fin_affichage:;
            monjeu.affiche();
        } else if (mouvement == "/pieces") {
            monjeu.affiche_pieces();
        } else
            stop = true;
    } while (!stop && !monjeu.partie_finie(monjeu.echiquier));
    monjeu.affichage_canonique();
    exit(EXIT_SUCCESS);
}

bool saisie_correcte(string const &cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd, mouvmtpattern);
}

bool saisie_correcte_petitroque(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

bool saisie_correcte_grandroque(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}
