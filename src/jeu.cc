#include "../include/jeu.h"
#include "../include/debug.h"
#include "../include/echiquier.h"
#include "../include/piece.h"
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

vector<vector<Move>> generate_mvt(Piece *piece, Piece *echiquier[8][8]) {
    // Initialise le tableau des mouvements possibles
    vector<vector<Move>> mvt;
    for (int i = 0; i < NBCOL; i++) {
        vector<Move> ligne;
        for (int j = 0; j < NBCOL; j++) {
            ligne.push_back(Move::non_atteignable);
        }
        mvt.push_back(ligne);
    }

    Piece *piece_c = piece->clone();

    for (int i = 0; i < NBCOL; i++) {
        for (int j = 0; j < NBCOL; j++) {
            if (piece_c->est_mouvement_legal(piece_c->square, Square(i, j),
                                             echiquier, false)) {
                if (echiquier[i][j]) {
                    mvt[i][j] = Move::prenable;
                } else {
                    mvt[i][j] = Move::atteignable;
                }
            } else {
                mvt[i][j] = Move::non_atteignable;
            }
        }
    }
    delete piece_c;
    return mvt;
};

bool Jeu::echec(Echiquier echiquier, bool print) {
    Piece *pieces_c[8 * NBCOL];
    int z = 0;
    for (int k = 0; k < NBCOL; k++) {
        for (int l = 0; l < NBCOL; l++) {
            if (echiquier.echiquier[k][l]) {
                pieces_c[z] =
                    echiquier.echiquier[k][l]
                        ->clone(); // On clone les pieces car le fonction
                                   // est_mouvement_legal modifie des varaibles
                                   // des pieces et on ne veut pas que les
                                   // pieces soient modifiees
                DEB(cout << "-> (fct echec)Piece " << pieces_c[z]->nom_affiche
                         << " sur la case " << pieces_c[z]->square.to_string()
                         << endl);
                for (int i = 0; i < NBCOL; i++) {
                    for (int j = 0; j < NBCOL; j++) {
                        DEB(cout << "   => Test de deplacement sur la case "
                                 << Square(i, j).to_string() << endl);
                        if (pieces_c[z]->est_mouvement_legal(
                                Square(k, l), Square(i, j), echiquier.echiquier,
                                false)) {
                            DEB(cout << "       ==> Deplacement possible"
                                     << endl);
                            if (echiquier.echiquier[i][j] &&
                                echiquier.echiquier[i][j]->couleur !=
                                    pieces_c[z]->couleur &&
                                echiquier.echiquier[i][j]->nom ==
                                    NomPiece::roi) {
                                if (print) {
                                    cout << "-> Mise en echec de la piece"
                                         << echiquier.echiquier[i][j]
                                                ->nom_affiche
                                         << " par la piece"
                                         << pieces_c[z]->nom_affiche
                                         << " sur la case "
                                         << pieces_c[z]->square.to_string()
                                         << endl;
                                }
                                return true;
                            }
                        }
                    }
                }
                delete pieces_c[z];
                z++;
            }
        }
    }
    return false;
}

bool Jeu::echec_mat(Echiquier echiquier, bool print) {
    Piece *pieces_c[8 * NBCOL];
    int z = 0;
    for (int k = 0; k < NBCOL; k++) {
        for (int l = 0; l < NBCOL; l++) {
            if (echiquier.echiquier[k][l] &&
                echiquier.echiquier[k][l]->couleur == couleur_a_deplacer) {
                pieces_c[z] =
                    echiquier.echiquier[k][l]->clone(); // On clone
                                                        // les pieces
                                                        // car le
                                                        // fonction
                                                        // est_mouvement_legal
                                                        // modifie
                                                        // des varaibles
                                                        // des pieces et
                                                        // on ne veut
                                                        // pas que les
                                                        // pieces soient
                                                        // modifiees
                DEB(cout << "-> (fct echec_mat)Piece "
                         << pieces_c[z]->nom_affiche << " sur la case "
                         << pieces_c[z]->square.to_string() << endl);
                for (int i = 0; i < NBCOL; i++) {
                    for (int j = 0; j < NBCOL; j++) {
                        DEB(cout << "   => Test de deplacement sur la case "
                                 << Square(i, j).to_string() << endl);
                        if (pieces_c[z]->est_mouvement_legal(
                                pieces_c[z]->square, Square(i, j),
                                echiquier.echiquier, false)) {
                            DEB(cout << "       ==> Deplacement possible"
                                     << endl);
                            if (echiquier.echiquier[i][j] &&
                                echiquier.echiquier[i][j]->couleur !=
                                    pieces_c[z]->couleur &&
                                echiquier.echiquier[i][j]->nom ==
                                    NomPiece::roi) {
                                if (print) {
                                    cout << "-> Mise en echec de la piece"
                                         << echiquier.echiquier[i][j]
                                                ->nom_affiche
                                         << " par la piece"
                                         << pieces_c[z]->nom_affiche
                                         << " sur la case "
                                         << pieces_c[z]->square.to_string()
                                         << endl;
                                }
                                return true;
                            }
                        }
                    }
                }
                delete pieces_c[z];
                z++;
            }
        }
    }
    return true;
}

bool Jeu::mat(bool print) {
    DEB(cout << "-> Vérification du mat " << endl);
    Echiquier *echiquier_c =
        echiquier
            .clone_echiquier_piece(); // On clone l'echiquier et on clone chaque
                                      // piece de l'echiquier car la fonction
                                      // est_mouvement_legal modifie des
                                      // variables des pieces et on ne veut pas
                                      // que les pieces soient modifiees
    Echiquier *echiquier_deplace;
    for (int i = 0; i < NBCOL; i++) {
        for (int j = 0; j < NBCOL; j++) {
            if (echiquier_c->echiquier[i][j] &&
                echiquier_c->echiquier[i][j]->couleur == !couleur_a_deplacer) {
                DEB(cout << "-> (fct mat)Piece "
                         << echiquier_c->echiquier[i][j]->nom_affiche
                         << " sur la case "
                         << echiquier_c->echiquier[i][j]->square.to_string()
                         << endl);
                for (int k(0); k < NBCOL; k++) {
                    for (int l(0); l < NBCOL; l++) {
                        echiquier_deplace =
                            echiquier_c->clone_echiquier_piece();
                        DEB(cout
                            << "    => Test déplacement de la piece "
                            << echiquier_deplace->echiquier[i][j]->nom_affiche
                            << " sur la case "
                            << echiquier_deplace->echiquier[i][j]
                                   ->square.to_string()
                            << " vers la case " << Square(k, l).to_string()
                            << endl);
                        if (echiquier_deplace->echiquier[i][j]
                                ->est_mouvement_legal(
                                    Square(i, j), Square(k, l),
                                    echiquier_deplace->echiquier, false)) {
                            DEB(cout << "       => Déplacement de la piece "
                                     << echiquier_deplace->echiquier[i][j]
                                            ->nom_affiche
                                     << " sur la case "
                                     << echiquier_deplace->echiquier[i][j]
                                            ->square.to_string()
                                     << " vers la case "
                                     << Square(k, l).to_string() << " possible"
                                     << endl);
                            echiquier_deplace->deplace(
                                echiquier_deplace->echiquier[i][j],
                                Square(i, j), Square(k, l), false);
                            DEB(cout
                                << "-> Pièce déplacée sur le nouvel echiquier :"
                                << endl);
                            DEB(echiquier_deplace->affiche());
                            if (partie_finie(*echiquier_deplace)) {
                                if (print)
                                    cout << "-> Echec et mat" << endl;

                                echiquier_deplace->delete_pieces();
                                delete echiquier_deplace;
                                echiquier_c->delete_pieces();
                                delete echiquier_c;
                                return true;
                            }
                            if (echec_mat(*echiquier_deplace, false) == false) {
                                DEB(cout << "-> Plus d'échec" << endl);
                                echiquier_deplace->delete_pieces();
                                delete echiquier_deplace;
                                echiquier_c->delete_pieces();
                                delete echiquier_c;
                                return false;
                            }
                        }
                    }
                }
                echiquier_deplace->delete_pieces();
            }
        }
    }
    if (print)
        cout << "-> Echec et mat" << endl;

    echiquier_deplace->delete_pieces();
    delete echiquier_deplace;
    echiquier_c->delete_pieces();
    delete echiquier_c;
    return true;
}

bool Jeu::partie_finie(Echiquier echiquier) {
    bool roiBlanc = false;
    bool roiNoir = false;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (echiquier.echiquier[i][j]) {
                if (echiquier.echiquier[i][j]->nom == NomPiece::roi) {
                    switch (echiquier.echiquier[i][j]->couleur) {
                    case Couleur::Blanc:
                        roiBlanc = true;
                        break;
                    case Couleur::Noir:
                        roiNoir = true;
                        break;
                    }
                }
            }
        }
    }
    return !(roiBlanc && roiNoir);
}

void Jeu::repositionner_pieces() {
    for (int i(0); i < NBCOL; i++) {
        for (int j(0); j < NBCOL; j++) {
            if (echiquier.echiquier[i][j]) {
                echiquier.echiquier[i][j]->square = Square(i, j);
            }
        }
    }
}

// Constructeur
Jeu::Jeu() {
    echiquier = Echiquier();
    couleur_a_deplacer = Couleur::Blanc;
}

// Constructeur de copie
Jeu::Jeu(const Jeu &jeu) {
    echiquier = jeu.echiquier;
    couleur_a_deplacer = jeu.couleur_a_deplacer;
}

// Surcharge de l'operateur =
Jeu &Jeu::operator=(const Jeu &jeu) {
    echiquier = jeu.echiquier;
    couleur_a_deplacer = jeu.couleur_a_deplacer;
    return *this;
}

void Jeu::affiche() { echiquier.affiche(); }

void Jeu::affichage_canonique() { echiquier.affichage_canonique(); }

void Jeu::deplace(string orig, string dest) {
    Square origine(orig);
    Square destination(dest);

    if (!echiquier.echiquier[origine.ligne][origine.colonne]) {
        cerr << "Pas de pièces sur la case "
                "selectionnée !"
             << endl;
    }

    else if (echiquier.echiquier[origine.ligne][origine.colonne]->couleur !=
             couleur_a_deplacer) {
        cerr << "Ce n'est pas au tour de la pièce " << couleur_a_deplacer
             << " d'être jouée !" << endl;
    }

    else if (echiquier.echiquier[origine.ligne][origine.colonne]
                 ->est_mouvement_legal(origine, destination,
                                       echiquier.echiquier)) {

        echiquier.deplace(echiquier.echiquier[origine.ligne][origine.colonne],
                          origine, destination);

        couleur_a_deplacer = !couleur_a_deplacer;

    } else {
        cerr << "Mouvement illégal !" << endl;
    }
}

bool Jeu::deplace_roque(bool petit_roque, bool print) {
    if (petit_roque) {
        switch (couleur_a_deplacer) {
        case Couleur::Blanc:
            if (echiquier.echiquier[0][4]) {
                if (echiquier.echiquier[0][4]->roque(echiquier.echiquier,
                                                     true)) {
                    if (print)
                        cout << "Petit roque blanc" << endl;
                    couleur_a_deplacer = !couleur_a_deplacer;
                    return true;
                }
            }
            if (print)
                cerr << "Erreur petit roque blanc" << endl;
            return false;

        case Couleur::Noir:
            if (echiquier.echiquier[7][4]) {
                if (echiquier.echiquier[7][4]->roque(echiquier.echiquier,
                                                     true)) {
                    if (print)
                        cout << "Petit roque noir" << endl;
                    couleur_a_deplacer = !couleur_a_deplacer;
                    return true;
                }
            }
            if (print)
                cerr << "Erreur petit roque noir" << endl;
            return false;
        }
    } else {
        switch (couleur_a_deplacer) {
        case Couleur::Blanc:
            if (echiquier.echiquier[0][4]) {
                if (echiquier.echiquier[0][4]->roque(echiquier.echiquier,
                                                     false)) {
                    if (print)
                        cout << "Grand roque blanc" << endl;
                    couleur_a_deplacer = !couleur_a_deplacer;
                    return true;
                }
            }
            if (print)
                cerr << "Erreur grand roque blanc" << endl;
            return false;

        case Couleur::Noir:
            if (echiquier.echiquier[7][4]) {
                if (echiquier.echiquier[7][4]->roque(echiquier.echiquier,
                                                     false)) {
                    if (print)
                        cout << "Grand roque noir" << endl;
                    couleur_a_deplacer = !couleur_a_deplacer;
                    return true;
                }
            }
            if (print)
                cerr << "Erreur grand roque noir" << endl;
            return false;
        }
    }
    return false;
}

void Jeu::affiche_pieces() {
    cout << "Les pièces mangées sont : ";
    for (auto nom : echiquier.pieces_mangee) {
        cout << nom << " | ";
    }
    cout << endl;
}