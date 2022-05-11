#include <SDL2/SDL.h>
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

void draw_rectangle_fill(SDL_Renderer *renderer, const SDL_Rect &rectangle,
                         const SDL_Color &color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (auto y = rectangle.y; y < rectangle.y + rectangle.h; y++) {
        for (auto x = rectangle.x; x < rectangle.x + rectangle.w; x++) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window =
        SDL_CreateWindow("Echec", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    // Make all the 64 cases of the chessboard with a rectangle of size 10x10
    SDL_Rect rect[NBCOL][NBCOL];
    for (int i = 0; i < NBCOL; i++) {
        for (int j = 0; j < NBCOL; j++) {
            rect[i][j].x = i * 100;
            rect[i][j].y = j * 100;
            rect[i][j].w = 100;
            rect[i][j].h = 100;
            // Draw in brown for pair of lines and in white for impair of lines
            if ((i + j) % 2 == 0) {
                printf("%d %d\n", i, j);
                draw_rectangle_fill(renderer, rect[i][j], {100, 100, 100, 255});
            } else {
                draw_rectangle_fill(renderer, rect[i][j], {255, 255, 255, 255});
            }
        }
    }
    SDL_RenderPresent(renderer);

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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

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
