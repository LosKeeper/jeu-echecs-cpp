#include "../include/echiquier.h"
#include "../include/piece.h"
#include <iostream>
using namespace std;
#include <string>

// Constructeurs
Square::Square(string algb) {
    colonne = (int)algb[0] - 97;
    ligne = (int)algb[1] - 49;
}
Square::Square(int ligne, int colonne) : ligne(ligne), colonne(colonne){};

// Fonctions annexes
string Square::to_string() {
    char algb[3];
    algb[0] = (char)(colonne + 97);
    algb[1] = (char)(ligne + 49);
    algb[2] = '\0';
    return algb;
}

void Echiquier::alloc_mem_echiquier() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            echiquier[i][j] = nullptr;
        }
    }
}

void Echiquier::deplace(Piece *piece, Square orig, Square dest, bool print) {
    if (piece->en_passant) {
        switch (piece->couleur) {
        case Couleur::Blanc:
            piece->square = dest;
            piece->deplace = true;
            piece->en_passant = false;
            echiquier[dest.ligne][dest.colonne] =
                echiquier[orig.ligne][orig.colonne];
            echiquier[orig.ligne][orig.colonne] = nullptr;
            pieces_mangee.push_back(
                echiquier[orig.ligne][dest.colonne]->nom_affiche);
            delete echiquier[orig.ligne][dest.colonne];
            echiquier[orig.ligne][dest.colonne] = nullptr;
            return;

        case Couleur::Noir:
            piece->square = dest;
            piece->deplace = true;
            piece->en_passant = false;
            echiquier[dest.ligne][dest.colonne] =
                echiquier[orig.ligne][orig.colonne];
            echiquier[orig.ligne][orig.colonne] = nullptr;
            pieces_mangee.push_back(
                echiquier[orig.ligne][dest.colonne]->nom_affiche);
            delete echiquier[orig.ligne][dest.colonne];
            echiquier[orig.ligne][dest.colonne] = nullptr;
            return;
        }
    }
    if (echiquier[dest.ligne][dest.colonne]) {
        pieces_mangee.push_back(
            echiquier[dest.ligne][dest.colonne]->nom_affiche);
        delete echiquier[dest.ligne][dest.colonne];
    }
    piece->square = dest;
    piece->deplace = true;
    echiquier[dest.ligne][dest.colonne] = piece;
    if (print)
        cout << "-> déplacement de "
             << echiquier[dest.ligne][dest.colonne]->nom_affiche << endl;
    echiquier[orig.ligne][orig.colonne] = nullptr;
}

void Echiquier::pose_piece(Piece *piece, Square square) {
    echiquier[square.ligne][square.colonne] = piece;
}

// constructeur
Echiquier::Echiquier() {

    alloc_mem_echiquier(); //  alloue un tableau
                           //  équivalent à un Piece
                           //  *[8][8]
                           //     en initialisant les
                           //     cases à nullptr et
                           //     alloue des vecteurs
                           //     piecesb, piecesn,
                           //     pionsb
    // Constructeur (Couleur,nom_affiché, case)
    piecesb[0] = new Tour(Couleur::Blanc, " \u2656 ", Square(0, 0));
    piecesb[1] = new Cavalier(Couleur::Blanc, " \u2658 ", Square(0, 1));
    piecesb[2] = new Fou(Couleur::Blanc, " \u2657 ", Square(0, 2));
    piecesb[3] = new Dame(Couleur::Blanc, " \u2655 ", Square(0, 3));
    piecesb[4] = new Roi(Couleur::Blanc, " \u2654 ", Square(0, 4));
    piecesb[5] = new Fou(Couleur::Blanc, " \u2657 ", Square(0, 5));
    piecesb[6] = new Cavalier(Couleur::Blanc, " \u2658 ", Square(0, 6));
    piecesb[7] = new Tour(Couleur::Blanc, " \u2656 ", Square(0, 7));
    piecesn[0] = new Tour(Couleur::Noir, " \u265C ", Square(7, 0));
    piecesn[1] = new Cavalier(Couleur::Noir, " \u265E ", Square(7, 1));
    piecesn[2] = new Fou(Couleur::Noir, " \u265D ", Square(7, 2));
    piecesn[3] = new Dame(Couleur::Noir, " \u265B ", Square(7, 3));
    piecesn[4] = new Roi(Couleur::Noir, " \u265A ", Square(7, 4));
    piecesn[5] = new Fou(Couleur::Noir, " \u265D ", Square(7, 5));
    piecesn[6] = new Cavalier(Couleur::Noir, " \u265E ", Square(7, 6));
    piecesn[7] = new Tour(Couleur::Noir, " \u265C ", Square(7, 7));

    // allocation des pions
    for (unsigned char i(0); i < NBCOL; i++) {
        pionsb[i] = new Pion(Couleur::Blanc, " \u2659 ", Square(1, i));
        pionsn[i] = new Pion(Couleur::Noir, " \u265F ", Square(6, i));
    }
    // Pose des pieces en position initiale
    // pose des pieces blanches
    for (unsigned char i(0); i < NBCOL; i++) {
        // met à jour le tableau echiquier, à la case
        // donnée par la position courante de la pièce
        // obtenue avec piecesb[i]->get_pos(), avec le
        // pointeur vers la pièce (piecesb[i])
        pose_piece(piecesb[i], piecesb[i]->get_pos());
        pose_piece(piecesn[i], piecesn[i]->get_pos());
        pose_piece(pionsn[i], pionsn[i]->get_pos());
        pose_piece(pionsb[i], pionsb[i]->get_pos());
    }
}

void Echiquier::affiche() {

    string space5 = string(5, ' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     "
            "g    "
            " h    "
         << endl;
    cout << "  "
            "+-----+-----+-----+-----+-----+-----+-----"
            "+---"
            "--+"
         << endl;
    for (int i(NBCOL - 1); i >= 0; i--) {
        cout << i + 1 << " "; // numérotation ligne dans affichage
        for (int j(0); j < NBCOL; j++) {
            cout << "|";
            if (echiquier[i][j]) {
                cout << "\u0020"; // U+0020 est un esapce
                                  // utf-8 taille police
                echiquier[i][j]->affiche();
                cout << "\u0020";
            } else
                cout << space5; // 2 ascii spaces
        }
        cout << "|\n  "
                "+-----+-----+-----+-----+-----+-----+-"
                "----"
                "+-----+";
        cout << endl;
    }
}

void Echiquier::affichage_canonique() {
    cout << endl;
    for (int i(0); i < NBCOL; i++) {
        for (int j(0); j < NBCOL; j++) {
            if (echiquier[i][j]) {
                switch (echiquier[i][j]->couleur) {
                case Couleur::Blanc:
                    cout << "w";
                    break;
                case Couleur::Noir:
                    cout << "b";
                    break;
                }
                switch (echiquier[i][j]->nom) {
                case NomPiece::pion:
                    cout << "P";
                    break;
                case NomPiece::tour:
                    cout << "R";
                    break;
                case NomPiece::fou:
                    cout << "B";
                    break;
                case NomPiece::cavalier:
                    cout << "N";
                    break;
                case NomPiece::dame:
                    cout << "Q";
                    break;
                case NomPiece::roi:
                    cout << "K";
                    break;
                }
            }
            cout << ",";
        }
    }
    cout << endl;
}

Echiquier *Echiquier::clone_echiquier_piece() {
    Echiquier *echiquier_clone = new Echiquier();
    for (int i(0); i < NBCOL; i++) {
        for (int j(0); j < NBCOL; j++) {
            if (echiquier[i][j]) {
                echiquier_clone->pose_piece(echiquier[i][j]->clone(),
                                            Square(i, j));
            } else {
                echiquier_clone->echiquier[i][j] = nullptr;
            }
        }
    }
    return echiquier_clone;
}

void Echiquier::delete_pieces() {
    for (int i(0); i < NBCOL; i++) {
        for (int j(0); j < NBCOL; j++) {
            if (echiquier[i][j]) {
                delete echiquier[i][j];
                echiquier[i][j] = nullptr;
            }
        }
    }
}
