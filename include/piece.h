#pragma once
#include "../include/echiquier.h"
#include "../include/enum.h"
#include <iostream>
using namespace std;

/**
 * @brief Classe correspondant à la piece
 */
class Piece {
  public:
    /**
     * @brief Variable correspondant au type de la pièce
     */
    NomPiece nom;
    /**
     * @brief Variable correspondant à la couleur de la pièce
     */
    Couleur couleur;
    /**
     * @brief Variable correspondant au code unicode de la pièce qui sera
     * affiché dans le terminal
     */
    string nom_affiche;
    /**
     * @brief Variable correspondant à la position de la pièce
     */
    Square square;
    /**
     * @brief Variable indiquant si la pièce a déjà été déplacée
     */
    bool deplace = false;
    /**
     * @brief Variable indiquant si la pièce peux roquer
     */
    bool is_roque = false;
    /**
     * @brief Variable indiquant si la pièce à déjà été roquée
     */
    bool roqued = false;
    /**
     * @brief Variable indiquant si le dernier déplacement du pion est un
     * avancement de 2 cases
     */
    bool is_last_move_2 = false;
    /**
     * @brief Variable indiquant si le prochain deplacement est une prise en
     * passant
     */
    bool en_passant = false;

    /**
     * @brief Constructeur par défaut
     */
    Piece(Couleur couleur, string nom_affiche, Square square);

    /**
     * @brief Constructeur de copie
     */
    Piece(const Piece &piece);

    /**
     * @brief Fonction permettant de cloner un objet Piece
     * @return un objet Piece
     */
    virtual Piece *clone() = 0;

    /**
     * @brief Destructeur
     */
    virtual ~Piece();

    /**
     * @brief Fonction qui affiche toutes les pièces de l'echiquier dans le
     * terminal
     */
    void affiche();

    /**
     * @brief Fonction qui verifie si le deplacement d'une piece est possible
     * @param case_origine la case de depart
     * @param case_destination la case d'arrivée
     * @param echiquier[8][8] la piece à déplacer
     * @param ask_usr si on veut interroger l'utilisateur (par exemple lors de
     * la promotion pour la nouvelle piece)
     * @return true si le deplacement est possible, false sinon
     */
    virtual bool est_mouvement_legal(Square case_origine,
                                     Square case_destination,
                                     Piece *echiquier[8][8],
                                     bool ask_usr = true) = 0;

    /**
     * @brief Fonction qui verifie si le roque est possible
     * @param echiquier[8][8] la piece à déplacer
     * @param petit_roque booléen qui indique si le roque à vérifier est un
     * petit roque ou un grand roque
     * @return true si le roque est possible, false sinon
     */
    virtual bool roque(Piece *echiquier[8][8], bool petit_roque) {
        (void)echiquier;
        (void)petit_roque;
        return false;
    }

    /**
     * @brief Fonction qui renvoie un Square de la position d'une pièce
     * @return un Square
     */
    Square get_pos();

    /**
     * @brief Fonction qui renvoie la couleur d'une piece
     * @return la couleur de la piece
     */
    Couleur get_couleur();
};

class Tour : public Piece {
  public:
    /**
     * @brief Constructeur par défaut
     */
    Tour(Couleur couleur, string nom_affiche, Square square);

    /**
     * @brief Constructeur de copie
     */
    Tour(const Tour &tour);
    Tour *clone();

    // Fonction annexes
    bool est_mouvement_legal(Square case_origine, Square case_destination,
                             Piece *echiquier[8][8], bool ask_usr = true);
};

class Cavalier : public Piece {
  public:
    /**
     * @brief Constructeur par défaut
     */
    Cavalier(Couleur couleur, string nom_affiche, Square square);

    /**
     * @brief Constructeur de copie
     */
    Cavalier(const Cavalier &cavalier);
    Cavalier *clone();

    // Fonction annexes
    bool est_mouvement_legal(Square case_origine, Square case_destination,
                             Piece *echiquier[8][8], bool ask_usr = true);
};

class Fou : public Piece {
  public:
    /**
     * @brief Constructeur par défaut
     */
    Fou(Couleur couleur, string nom_affiche, Square square);

    /**
     * @brief Constructeur de copie
     */
    Fou(const Fou &fou);
    Fou *clone();

    // Fonction annexes
    bool est_mouvement_legal(Square case_origine, Square case_destination,
                             Piece *echiquier[8][8], bool ask_usr = true);
};

class Dame : public Piece {
  public:
    /**
     * @brief Constructeur par défaut
     */
    Dame(Couleur couleur, string nom_affiche, Square square);

    /**
     * @brief Constructeur de copie
     */
    Dame(const Dame &dame);
    Dame *clone();

    // Fonction annexes
    bool est_mouvement_legal(Square case_origine, Square case_destination,
                             Piece *echiquier[8][8], bool ask_usr = true);
};

class Roi : public Piece {
  public:
    /**
     * @brief Constructeur par défaut
     */
    Roi(Couleur couleur, string nom_affiche, Square square);

    /**
     * @brief Constructeur de copie
     */
    Roi(const Roi &roi);
    Roi *clone();

    // Fonction annexes
    bool est_mouvement_legal(Square case_origine, Square case_destination,
                             Piece *echiquier[8][8], bool ask_usr = true);
    bool roque(Piece *echiquier[8][8], bool petit_roque);
};

class Pion : public Piece {
  public:
    /**
     * @brief Constructeur par défaut
     */
    Pion(Couleur couleur, string nom_affiche, Square square);

    /**
     * @brief Constructeur de copie
     */
    Pion(const Pion &pion);
    Pion *clone();

    // Fonction annexes
    bool est_mouvement_legal(Square case_origine, Square case_destination,
                             Piece *echiquier[8][8], bool ask_usr = true);

    /**
     * @brief Fonction permettant la promotion d'un pion ie le changement de
     * pièce
     * @param case_origine la case de depart (qui est aussi la case finale car
     * on traite le promotion parès le déplacement du pion)
     * @param echiquier[8][8] le pion à déplacer
     */
    void promotion(Square case_origine, Piece *echiquier[8][8]);
};