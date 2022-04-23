#include "../include/enum.h"
#include <iostream>
using namespace std;

std::ostream &operator<<(std::ostream &os, Couleur couleur) {
    switch (couleur) {
    case Couleur::Blanc:
        return os << "Blanc";
    case Couleur::Noir:
        return os << "Noir";
    default:
        return os << "inconnu";
    }
}

Couleur operator!(Couleur couleur) {
    return couleur == Couleur::Blanc ? Couleur::Noir : Couleur::Blanc;
}

std::ostream &operator<<(std::ostream &os, NomPiece nom) {
    switch (nom) {
    case NomPiece::cavalier:
        return os << "cavalier";
    case NomPiece::tour:
        return os << "tour";
    case NomPiece::fou:
        return os << "fou";
    case NomPiece::dame:
        return os << "dame";
    case NomPiece::roi:
        return os << "roi";
    case NomPiece::pion:
        return os << "pion";
    default:
        return os << "inconnu";
    }
}