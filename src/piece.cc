#include "../include/piece.h"
#include <iostream>
using namespace std;

// Constructeur
Piece::Piece(Couleur couleur, string nom_affiche, Square square)
    : couleur(couleur), nom_affiche(nom_affiche), square(square){};

// Constructeur de copie
Piece::Piece(const Piece &piece)
    : couleur(piece.couleur), nom_affiche(piece.nom_affiche),
      square(piece.square){};

// Destructeur
Piece::~Piece(){};

// Fonctions annexes
void Piece::affiche() { cout << nom_affiche; }
Square Piece::get_pos() { return square; }
Couleur Piece::get_couleur() { return couleur; }

Tour::Tour(Couleur couleur, string nom_affiche, Square square)
    : Piece(couleur, nom_affiche, square) {
    nom = NomPiece::tour;
};
Tour::Tour(const Tour &tour) : Piece(tour) { nom = NomPiece::tour; };
Tour *Tour::clone() { return new Tour(*this); }
bool Tour::est_mouvement_legal(Square case_origine, Square case_destination,
                               Piece *echiquier[8][8], bool ask_usr) {
    (void)ask_usr;
    // Test si la destinatin est dans l'echiquier
    if ((case_destination.ligne < 0 || case_destination.ligne >= NBCOL) ||
        (case_destination.colonne < 0 || case_destination.colonne >= NBCOL)) {
        return false;
    }

    // Test si destination est une piece et si de meme couleur
    if (echiquier[case_destination.ligne][case_destination.colonne]) {
        if (echiquier[case_destination.ligne][case_destination.colonne]
                ->couleur == this->couleur) {
            return false;
        }
    }

    if (case_destination.ligne == case_origine.ligne &&
        case_destination.colonne !=
            case_origine.colonne) { // depacement sur colonne

        for (int i = min(case_origine.colonne, case_destination.colonne) + 1;
             i < max(case_origine.colonne, case_destination.colonne); i++) {
            // Test si personnage sur le chemin
            if (echiquier[case_destination.ligne][i]) {
                return false;
            }
        }
        return true;
    }
    if (case_destination.colonne == case_origine.colonne &&
        case_destination.ligne != case_origine.ligne) { // deplacement sur ligne

        for (int i = min(case_origine.ligne, case_destination.ligne) + 1;
             i < max(case_origine.ligne, case_destination.ligne); i++) {
            // Test si personnage sur le chemin
            if (echiquier[i][case_destination.colonne]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Cavalier::Cavalier(Couleur couleur, string nom_affiche, Square square)
    : Piece(couleur, nom_affiche, square) {
    nom = NomPiece::cavalier;
};
Cavalier::Cavalier(const Cavalier &cavalier) : Piece(cavalier) {
    nom = NomPiece::cavalier;
};
Cavalier *Cavalier::clone() { return new Cavalier(*this); }
bool Cavalier::est_mouvement_legal(Square case_origine, Square case_destination,
                                   Piece *echiquier[8][8], bool ask_usr) {
    (void)ask_usr;
    // Test si la destinatin est dans l'echiquier
    if ((case_destination.ligne < 0 || case_destination.ligne >= NBCOL) ||
        (case_destination.colonne < 0 || case_destination.colonne >= NBCOL)) {
        return false;
    }

    // Test si destination est une piece et si de meme couleur
    if (echiquier[case_destination.ligne][case_destination.colonne]) {
        if (echiquier[case_destination.ligne][case_destination.colonne]
                ->couleur == this->couleur) {
            return false;
        }
    }

    if (case_destination.ligne == case_origine.ligne + 2 &&
        case_destination.colonne == case_origine.colonne + 1) {
        return true;
    } else if (case_destination.ligne == case_origine.ligne + 2 &&
               case_destination.colonne == case_origine.colonne - 1) {
        return true;
    } else if (case_destination.ligne == case_origine.ligne + 1 &&
               case_destination.colonne == case_origine.colonne - 2) {
        return true;
    } else if (case_destination.ligne == case_origine.ligne - 1 &&
               case_destination.colonne == case_origine.colonne - 2) {
        return true;
    } else if (case_destination.ligne == case_origine.ligne - 2 &&
               case_destination.colonne == case_origine.colonne + 1) {
        return true;
    } else if (case_destination.ligne == case_origine.ligne - 2 &&
               case_destination.colonne == case_origine.colonne - 1) {
        return true;
    } else if (case_destination.ligne == case_origine.ligne + 1 &&
               case_destination.colonne == case_origine.colonne + 2) {
        return true;
    } else if (case_destination.ligne == case_origine.ligne - 1 &&
               case_destination.colonne == case_origine.colonne + 2) {
        return true;
    } else {
        return false;
    }
}

Fou::Fou(Couleur couleur, string nom_affiche, Square square)
    : Piece(couleur, nom_affiche, square) {
    nom = NomPiece::fou;
};
Fou::Fou(const Fou &fou) : Piece(fou) { nom = NomPiece::fou; };
Fou *Fou::clone() { return new Fou(*this); }
bool Fou::est_mouvement_legal(Square case_origine, Square case_destination,
                              Piece *echiquier[8][8], bool ask_usr) {
    (void)ask_usr;
    // Test si la destinatin est dans l'echiquier
    if ((case_destination.ligne < 0 || case_destination.ligne >= NBCOL) ||
        (case_destination.colonne < 0 || case_destination.colonne >= NBCOL)) {
        return false;
    }

    // Test si destination est une piece et si de meme couleur
    if (echiquier[case_destination.ligne][case_destination.colonne]) {
        if (echiquier[case_destination.ligne][case_destination.colonne]
                ->couleur == this->couleur) {
            return false;
        }
    }
    // On regarde si le mouvement est bien en diagonale
    if (abs(case_destination.colonne - case_origine.colonne) -
            abs(case_destination.ligne - case_origine.ligne) !=
        0) {
        return false;
    } else { // Cas ou le mouvement est bien en diagonale
        // On verifie qu'il n'y a pas d'obstacles sur le mouvement
        int NbDeplacement =
            abs(case_destination.colonne - case_origine.colonne);

        if (case_destination.ligne > case_origine.ligne &&
            case_destination.colonne > case_origine.colonne) {
            for (int i = 1; i < NbDeplacement; i++) {
                if (echiquier[case_origine.ligne + i]
                             [case_origine.colonne + i]) {
                    return false;
                }
            }
        } else if (case_destination.ligne > case_origine.ligne &&
                   case_destination.colonne < case_origine.colonne) {
            for (int i = 1; i < NbDeplacement; i++) {
                if (echiquier[case_origine.ligne + i]
                             [case_origine.colonne - i]) {
                    return false;
                }
            }
        } else if (case_destination.ligne < case_origine.ligne &&
                   case_destination.colonne > case_origine.colonne) {
            for (int i = 1; i < NbDeplacement; i++) {
                if (echiquier[case_origine.ligne - i]
                             [case_origine.colonne + i]) {
                    return false;
                }
            }
        } else if (case_destination.ligne < case_origine.ligne &&
                   case_destination.colonne < case_origine.colonne) {
            for (int i = 1; i < NbDeplacement; i++) {
                if (echiquier[case_origine.ligne - i]
                             [case_origine.colonne - i]) {
                    return false;
                }
            }
        }
    }
    return true;
}

Dame::Dame(Couleur couleur, string nom_affiche, Square square)
    : Piece(couleur, nom_affiche, square) {
    nom = NomPiece::dame;
};
Dame::Dame(const Dame &dame) : Piece(dame) { nom = NomPiece::dame; };
Dame *Dame::clone() { return new Dame(*this); }
bool Dame::est_mouvement_legal(Square case_origine, Square case_destination,
                               Piece *echiquier[8][8], bool ask_usr) {
    (void)ask_usr;
    // Test si la destinatin est dans l'echiquier
    if ((case_destination.ligne < 0 || case_destination.ligne >= NBCOL) ||
        (case_destination.colonne < 0 || case_destination.colonne >= NBCOL)) {
        return false;
    }

    // Test si destination est une piece et si de meme couleur
    if (echiquier[case_destination.ligne][case_destination.colonne]) {
        if (echiquier[case_destination.ligne][case_destination.colonne]
                ->couleur == this->couleur) {
            return false;
        }
    }
    if (abs(case_destination.colonne - case_origine.colonne) -
            abs(case_destination.ligne - case_origine.ligne) ==
        0) { // Cas ou le mouvement est bien en diagonale
        // On verifie qu'il n'y a pas d'obstacles sur le mouvement
        int NbDeplacement =
            abs(case_destination.colonne - case_origine.colonne);

        if (case_destination.ligne > case_origine.ligne &&
            case_destination.colonne > case_origine.colonne) {
            for (int i = 1; i < NbDeplacement; i++) {
                if (echiquier[case_origine.ligne + i]
                             [case_origine.colonne + i]) {
                    return false;
                }
            }
            return true;
        } else if (case_destination.ligne > case_origine.ligne &&
                   case_destination.colonne < case_origine.colonne) {
            for (int i = 1; i < NbDeplacement; i++) {
                if (echiquier[case_origine.ligne + i]
                             [case_origine.colonne - i]) {
                    return false;
                }
            }
            return true;
        } else if (case_destination.ligne < case_origine.ligne &&
                   case_destination.colonne > case_origine.colonne) {
            for (int i = 1; i < NbDeplacement; i++) {
                if (echiquier[case_origine.ligne - i]
                             [case_origine.colonne + i]) {
                    return false;
                }
            }
            return true;
        } else if (case_destination.ligne < case_origine.ligne &&
                   case_destination.colonne < case_origine.colonne) {
            for (int i = 1; i < NbDeplacement; i++) {
                if (echiquier[case_origine.ligne + i]
                             [case_origine.colonne - i]) {
                    return false;
                }
            }
            return true;
        }
    } else if (case_destination.ligne == case_origine.ligne &&
               case_destination.colonne !=
                   case_origine.colonne) { // depacement sur colonne

        for (int i = min(case_origine.colonne, case_destination.colonne) + 1;
             i < max(case_origine.colonne, case_destination.colonne); i++) {
            // Test si personnage sur le chemin
            if (echiquier[case_destination.ligne][i] != nullptr) {
                return false;
            }
        }
        return true;
    } else if (case_destination.colonne == case_origine.colonne &&
               case_destination.ligne !=
                   case_origine.ligne) { // deplacement sur ligne

        for (int i = min(case_origine.ligne, case_destination.ligne) + 1;
             i < max(case_origine.ligne, case_destination.ligne); i++) {
            // Test si personnage sur le chemin
            if (echiquier[i][case_destination.colonne] != nullptr) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Roi::Roi(Couleur couleur, string nom_affiche, Square square)
    : Piece(couleur, nom_affiche, square) {
    nom = NomPiece::roi;
};
Roi::Roi(const Roi &roi) : Piece(roi) { nom = NomPiece::roi; };
Roi *Roi::clone() { return new Roi(*this); }
bool Roi::est_mouvement_legal(Square case_origine, Square case_destination,
                              Piece *echiquier[8][8], bool ask_usr) {
    (void)ask_usr;
    // Test si la destinatin est dans l'echiquier
    if ((case_destination.ligne < 0 || case_destination.ligne >= NBCOL) ||
        (case_destination.colonne < 0 || case_destination.colonne >= NBCOL)) {
        return false;
    }

    // Test si destination est une piece et si de meme couleur
    if (echiquier[case_destination.ligne][case_destination.colonne]) {
        if (echiquier[case_destination.ligne][case_destination.colonne]
                ->couleur == this->couleur) {
            return false;
        }
    }
    if (abs(case_destination.colonne - case_origine.colonne) >= 2 ||
        abs(case_destination.ligne - case_origine.ligne) >= 2) {
        return false;
    }
    this->is_roque = true;
    return true;
}

bool Roi::roque(Piece *echiquier[8][8], bool petit_roque) {
    if (this->deplace || this->roqued) {
        return false;
    }
    switch (this->couleur) {
    case Couleur::Blanc:
        // Petit roque blanc
        if (echiquier[0][7] && petit_roque) {
            if (echiquier[0][6] == nullptr && echiquier[0][5] == nullptr &&
                echiquier[0][7]->deplace == false) {
                echiquier[0][6] = echiquier[0][4];
                echiquier[0][6]->deplace = true;
                echiquier[0][4] = nullptr;
                echiquier[0][5] = echiquier[0][7];
                echiquier[0][5]->deplace = true;
                echiquier[0][7] = nullptr;
                this->roqued = true;
                return true;
            }
        }
        // Grand roque blanc
        else if (echiquier[0][0] && !petit_roque) {
            if (echiquier[0][1] == nullptr && echiquier[0][2] == nullptr &&
                echiquier[0][3] == nullptr &&
                echiquier[0][0]->deplace == false) {
                echiquier[0][2] = echiquier[0][4];
                echiquier[0][2]->deplace = true;
                echiquier[0][4] = nullptr;
                echiquier[0][3] = echiquier[0][0];
                echiquier[0][3]->deplace = true;
                echiquier[0][0] = nullptr;
                this->roqued = true;
                return true;
            }
        }
        break;

    case Couleur::Noir:
        // Petit roque noir
        if (echiquier[7][7] && petit_roque) {
            if (echiquier[7][6] == nullptr && echiquier[7][5] == nullptr &&
                echiquier[7][7]->deplace == false) {
                echiquier[7][6] = echiquier[7][4];
                echiquier[7][6]->deplace = true;
                echiquier[7][4] = nullptr;
                echiquier[7][5] = echiquier[7][7];
                echiquier[7][5]->deplace = true;
                echiquier[7][7] = nullptr;
                this->roqued = true;
                return true;
            }
        }
        // Grand roque noir
        else if (echiquier[7][0] && !petit_roque) {
            if (echiquier[7][1] == nullptr && echiquier[7][2] == nullptr &&
                echiquier[7][3] == nullptr &&
                echiquier[7][0]->deplace == false) {
                echiquier[7][2] = echiquier[7][4];
                echiquier[7][2]->deplace = true;
                echiquier[7][4] = nullptr;
                echiquier[7][3] = echiquier[7][0];
                echiquier[7][3]->deplace = true;
                echiquier[7][0] = nullptr;
                this->roqued = true;
                return true;
            }
        }
        break;
    }
    return false;
}

Pion::Pion(Couleur couleur, string nom_affiche, Square square)
    : Piece(couleur, nom_affiche, square) {
    nom = NomPiece::pion;
};
Pion::Pion(const Pion &pion) : Piece(pion) { nom = NomPiece::pion; };
Pion *Pion::clone() { return new Pion(*this); }
bool Pion::est_mouvement_legal(Square case_origine, Square case_destination,
                               Piece *echiquier[8][8], bool ask_usr) {
    // Test si la destinatin est dans l'echiquier
    if ((case_destination.ligne < 0 || case_destination.ligne >= NBCOL) ||
        (case_destination.colonne < 0 || case_destination.colonne >= NBCOL)) {
        return false;
    }

    // Test si destination est une piece et si de meme
    // couleur
    if (echiquier[case_destination.ligne][case_destination.colonne]) {
        if (echiquier[case_destination.ligne][case_destination.colonne]
                ->couleur == this->couleur) {
            return false;
        }
    }
    switch (echiquier[case_origine.ligne][case_origine.colonne]->couleur) {
    case Couleur::Blanc:
        // Prise en diagonale vers l'avant
        if (case_destination.ligne - case_origine.ligne == 1 &&
            abs(case_destination.colonne - case_origine.colonne) == 1) {
            if (echiquier[case_destination.ligne][case_destination.colonne]) {
                if (echiquier[case_destination.ligne][case_destination.colonne]
                        ->couleur !=
                    echiquier[case_origine.ligne][case_origine.colonne]
                        ->couleur) {
                    return true;
                } else {
                    return false;
                }
            } else if (echiquier[case_origine.ligne]
                                [case_destination.colonne] &&
                       echiquier[case_origine.ligne][case_destination.colonne]
                           ->is_last_move_2 &&
                       echiquier[case_origine.ligne][case_destination.colonne]
                               ->couleur != Couleur::Blanc) {
                this->en_passant = true;
                this->is_last_move_2 = false;
                return true;
            } else {
                return false;
            }

            // Si piece a la destination
        } else if (echiquier[case_destination.ligne]
                            [case_destination.colonne]) {
            return false;

            // Si deplacement de 2 vers l'avant
        } else if (case_destination.ligne - case_origine.ligne == 2 &&
                   case_destination.colonne - case_origine.colonne == 0) {
            if (case_destination.ligne > 4) {
                return false;
            } else {
                this->is_last_move_2 = true;
                return true;
            }

            // Si deplacement de 1 vers l'avant
        } else if (case_destination.ligne - case_origine.ligne == 1 &&
                   case_destination.colonne - case_origine.colonne == 0) {
            if (ask_usr)
                promotion(case_origine, echiquier);
            this->is_last_move_2 = false;
            return true;
        }

        return false;

    case Couleur::Noir:
        // Prise en diagonale vers l'avant
        if (case_origine.ligne - case_destination.ligne == 1 &&
            abs(case_destination.colonne - case_origine.colonne) == 1) {
            if (echiquier[case_destination.ligne][case_destination.colonne] !=
                nullptr) {
                if (echiquier[case_destination.ligne][case_destination.colonne]
                        ->couleur !=
                    echiquier[case_origine.ligne][case_origine.colonne]
                        ->couleur) {
                    this->is_last_move_2 = false;
                    return true;
                } else {
                    return false;
                }
            } else if (echiquier[case_origine.ligne]
                                [case_destination.colonne] &&
                       echiquier[case_origine.ligne][case_destination.colonne]
                           ->is_last_move_2 &&
                       echiquier[case_origine.ligne][case_destination.colonne]
                               ->couleur != Couleur::Noir) {
                this->en_passant = true;
                this->is_last_move_2 = false;
                return true;
            } else {
                return false;
            }

            // Si piece a la destination
        } else if (echiquier[case_destination.ligne]
                            [case_destination.colonne]) {
            return false;

            // Si deplacement de 2 vers l'avant
        } else if (case_origine.ligne - case_destination.ligne == 2 &&
                   case_destination.colonne - case_origine.colonne == 0) {
            if (case_destination.ligne < 3) {
                return false;
            } else {
                this->is_last_move_2 = true;
                return true;
            }

            // Si deplacement de 1 vers l'avant
        } else if (case_origine.ligne - case_destination.ligne == 1 &&
                   case_destination.colonne - case_origine.colonne == 0) {
            if (ask_usr)
                promotion(case_origine, echiquier);
            this->is_last_move_2 = false;
            return true;
        }

        return false;
    }
    return false;
}
void Pion::promotion(Square case_origine, Piece *echiquier[8][8]) {
debut_boucle:;
    char nouvelle_piece;
    switch (echiquier[case_origine.ligne][case_origine.colonne]->couleur) {
    case Couleur::Blanc:
        if (case_origine.ligne == 6) {
            cout << "Choississez la nouvele piece qui remplacera le pion : "
                    "( Q = Reine , R = Tour , B = Fou , K = Cavalier )";
            cin >> nouvelle_piece;
            switch (nouvelle_piece) {
            case 'R':
                delete (echiquier[case_origine.ligne][case_origine.colonne]);
                echiquier[case_origine.ligne][case_origine.colonne] =
                    new Tour(Couleur::Blanc, " \u2656 ",
                             Square(case_origine.ligne, case_origine.colonne));
                break;

            case 'K':
                delete (echiquier[case_origine.ligne][case_origine.colonne]);
                echiquier[case_origine.ligne][case_origine.colonne] =
                    new Cavalier(
                        Couleur::Blanc, " \u2658 ",
                        Square(case_origine.ligne, case_origine.colonne));
                break;

            case 'B':
                delete (echiquier[case_origine.ligne][case_origine.colonne]);
                echiquier[case_origine.ligne][case_origine.colonne] =
                    new Fou(Couleur::Blanc, " \u2657 ",
                            Square(case_origine.ligne, case_origine.colonne));
                break;

            case 'Q':
                delete (echiquier[case_origine.ligne][case_origine.colonne]);
                echiquier[case_origine.ligne][case_origine.colonne] =
                    new Dame(Couleur::Blanc, " \u2655 ",
                             Square(case_origine.ligne, case_origine.colonne));
                break;

            default:
                cout << "Mauvaise piece selectionnée !" << endl;
                goto debut_boucle;
                break;
            }
        } else {
            return;
        }
        break;

    case Couleur::Noir:
        if (case_origine.ligne == 1) {
            cout << "Choississez la nouvele piece qui remplacera le pion : "
                    "( Q = Reine , R = Tour , B = Fou , K = Cavalier )";
            cin >> nouvelle_piece;
            switch (nouvelle_piece) {
            case 'R':
                delete (echiquier[case_origine.ligne][case_origine.colonne]);
                echiquier[case_origine.ligne][case_origine.colonne] =
                    new Tour(Couleur::Noir, " \u265C ",
                             Square(case_origine.ligne, case_origine.colonne));
                break;

            case 'K':
                delete (echiquier[case_origine.ligne][case_origine.colonne]);
                echiquier[case_origine.ligne][case_origine.colonne] =
                    new Cavalier(
                        Couleur::Noir, " \u265E ",
                        Square(case_origine.ligne, case_origine.colonne));
                break;

            case 'B':
                delete (echiquier[case_origine.ligne][case_origine.colonne]);
                echiquier[case_origine.ligne][case_origine.colonne] =
                    new Fou(Couleur::Noir, " \u265D ",
                            Square(case_origine.ligne, case_origine.colonne));
                break;

            case 'Q':
                delete (echiquier[case_origine.ligne][case_origine.colonne]);
                echiquier[case_origine.ligne][case_origine.colonne] =
                    new Dame(Couleur::Noir, " \u265B ",
                             Square(case_origine.ligne, case_origine.colonne));
                break;

            default:
                cout << "Mauvaise piece selectionnée !" << endl;
                goto debut_boucle;
                break;
            }
        } else {
            return;
        }
        break;

    default:
        cout << "Mauvaise piece selectionnée !" << endl;
        goto debut_boucle;
        break;
    }
}