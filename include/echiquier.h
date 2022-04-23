#pragma once
#include <string>
#include <vector>
using namespace std;

#define NBCOL 8

class Piece;

/**
 * @brief Classe corespondant à la localisation de la pièce sur l'échiquier
 */
class Square {
  public:
    /**
     * @brief Variable correspondant au numéro de ligne
     */
    int ligne;

    /**
     * @brief Variable correspondant au numéro de colonne
     */
    int colonne;

    /**
     * @brief Constructeur avec en argument une chaine de caractères
     * @param algb la chaine de caractères
     * @return un objet Square
     */
    Square(string algb);

    /**
     * @brief Constructeur avec en argument deux entiers
     * @param ligne l'entier représentant la ligne
     * @param colonne l'entier représentant la colonne
     * @return un objet Square
     */
    Square(int ligne, int colonne);

    // Fonctions annexes
    /**
     * @brief Fonction qui convertit un objet Square en chaine de caractères
     * @return la chaine de caractères
     */
    string to_string();
};

/**
 * @brief Classe corespondant à l'échiquier
 */
class Echiquier {
  public:
    /**
     * @brief Variable correspondant à l'echiquier
     */
    Piece *echiquier[8][8];
    /**
     * @brief Variable correspondant aux pièces blanches
     */
    Piece *piecesb[8];
    /**
     * @brief Variable correspondant aux pièces noires
     */
    Piece *piecesn[8];
    /**
     * @brief Variable correspondant aux pions blancs
     */
    Piece *pionsb[NBCOL];
    /**
     * @brief Variable correspondant aux pions noirs
     */
    Piece *pionsn[NBCOL];
    /**
     * @brief Vecteur contenant toutes les pieces mangées
     */
    vector<string> pieces_mangee;

    /**
     * @brief Constructeur par défaut
     */
    Echiquier();

    // Fonctions annexes
    /**
     * @brief Fonction qui clone un objet Echiquier en clonant aussi les pièces
     * présentes sur l'echiquier
     */
    Echiquier *clone_echiquier_piece();

    /**
     * @brief Fonction qui initialise les cases de l'echiquier à nullptr
     */
    void alloc_mem_echiquier();

    /**
     * @brief Fonction qui déplace une pièce sur l'echiquier
     * @param piece la pièce à déplacer
     * @param orig la position de départ
     * @param dest la position d'arrivée
     * @param print si vrai, affiche le déplacement dans le terminal
     */
    void deplace(Piece *piece, Square orig, Square dest, bool print = true);

    /**
     * @brief Fonction qui pose une pièce sur l'echiquier
     * @param piece la pièce à poser
     * @param square la position de la pièce
     */
    void pose_piece(Piece *piece, Square square);

    /**
     * @brief Fonction qui affiche l'echiquier dans le terminal
     */
    void affiche();

    /**
     * @brief Fonction qui affiche l'echiquier sous forme canonique (affiche la
     * position des pièces sur une seule ligne)
     */
    void affichage_canonique();

    /**
     * @brief Fcontion qui permet de supprimer les pieces contenues sur
     * l'echiquier et le reinitialise
     */
    void delete_pieces();
};