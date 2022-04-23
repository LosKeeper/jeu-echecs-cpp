#pragma once
#include <ostream>

/**
 * @brief Classe indiquant l'etat d'une case de l'echiquier
 */
enum class Move { non_atteignable, atteignable, prenable };

/**
 * @brief Classe indiquant la couleur d'une piece
 */
enum class Couleur { Blanc, Noir };

/**
 * @brief Surchage de l'operateur ! pour passer d'une couleur à l'autre
 * @param couleur la couleur
 * @return la couleur inversee
 */
Couleur operator!(Couleur couleur);

/**
 * @brief Surchage de l'operateur << pour afficher la couleur
 * @param os le flux d'entrée
 * @param couleur la couleur
 * @return La couleur sur le flux d'entrée
 */
std::ostream &operator<<(std::ostream &os, Couleur couleur);

// Classe indiquant le type de la pièce
enum class NomPiece { tour, cavalier, fou, dame, roi, pion };

/**
 * @brief Surchage de l'operateur << pour afficher le type de la pièce
 * @param os le flux d'entrée
 * @param nomPiece le type de la pièce
 * @return Le type de la pièce sur le flux d'entrée
 */
std::ostream &operator<<(std::ostream &os, NomPiece nom);