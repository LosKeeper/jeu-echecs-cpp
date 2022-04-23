#pragma once
#include "../include/enum.h"
#include "../include/piece.h"
#include <iostream>
#include <vector>
using namespace std;
#define NBCOL 8

/**
 * @brief Fonction genrant les mouvements possibles d'une pièce
 * @param piece la pièce dont on veut générer les mouvements
 * @param echiquier l'echiquier sur lequel on veut générer les mouvements
 * @return un vecteur de Move contenant les mouvements possibles (Atteignable si
 * la case est atteignable, Prenable si une piece est prenable sur une case
 * atteignable, non_atteignable sinon)
 */
vector<vector<Move>> generate_mvt(Piece *piece, Piece *echiquier[8][8]);

/**
 * @brief Classe correspondant au jeu en cours
 */
class Jeu {
  public:
    /**
     * @brief Variable correspondant à l'echiquier
     */
    Echiquier echiquier;
    /**
     * @brief Variable correspondant à la couleur de la prochaine pièce à
     * déplacer
     */
    Couleur couleur_a_deplacer;
    /**
     * @brief Variable indiquant si le jeu est en échec
     */
    bool en_echec = false;

    /**
     * @brief Constructeur par défaut
     */
    Jeu();

    /**
     * @brief Constructeur de copie
     * @param jeu le jeu à copier
     */
    Jeu(const Jeu &jeu);

    /**
     * @brief Surcharge de l'operateur =
     * @param jeu le jeu à copier
     * @return le jeu copié
     */
    Jeu &operator=(const Jeu &jeu);

    /**
     * @brief Fonction qui verifie si un echec est present sur la partie
     * @param echiquier l'echiquier sur lequel on veut verifier l'echec
     * @param print si on veut afficher la presence d'un echec dans le terminal
     * @return true si l'echec est present, false sinon
     */
    bool echec(Echiquier echiquier, bool print = true);

    /**
     * @brief Fonction qui verifie la presence d'un echec sur la partie mais
     * pour une seule couleur
     * @param echiquier l'echiquier sur lequel on veut verifier l'echec
     * @param print si on veut afficher la presence d'un echec dans le terminal
     * @return true si l'echec est present, false sinon
     */
    bool echec_mat(Echiquier echiquier, bool print = true);

    /**
     * @brief Fonction qui verifie si un echec et mat est present sur la
     * partie
     * @param print si on veut afficher l'echec et mat dans le terminal
     * @return true si l'echec et mat est present, false sinon
     */
    bool mat(bool print = true);

    /**
     * @brief Fonction qui verifie si une partie est finie en verifiant la
     * présence des 2 rois
     * @param echiquier l'echiquier sur lequel on veut verifier la fin de la
     * partie
     * @return true si la partie est finie, false sinon
     */
    bool partie_finie(Echiquier echquier);

    /**
     * @brief Fonction qui affiche l'echiquier dans le terminal
     */
    void affiche();

    /**
     * @brief Fonction qui affiche l'echiquier dans le terminal de facon
     * canonique ie la position de toutes les pieces sur une seule ligne
     */
    void affichage_canonique();

    /**
     * @brief Fonction qui permet de modifier l'attribut Square de chaque piece
     * avec sa nouvelle position (utile en cas de undo ou si oubli de changer
     * l'attribut de position de la pièce)
     */
    void repositionner_pieces();

    /**
     * @brief Fonction qui deplace une piece sur l'echiquier
     * @param orig la position de depart
     * @param dest la position d'arrivee
     */
    void deplace(string orig, string dest);

    /**
     * @brief Fonction qui deplace une piece sur l'echiquier en cas de roque
     * @param petit_roque indique si le roque est un petit roque
     * @param print si on veut afficher le roque dans le terminal
     * @return true si le roque est possible et deplace les pièces en
     * conséquence, false sinon
     */
    bool deplace_roque(bool petit_roque, bool print = true);

    /**
     * @brief Fonction qui affiche toutes les pièces mangées
     */
    void affiche_pieces();
};