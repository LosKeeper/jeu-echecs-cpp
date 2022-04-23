#include <regex>

/**
 * @brief fonction verifiant que la saiaie est correcte ([a-h][1-8])
 * @param cmd l'entrée saisie par l'utilisateur
 * @return true si la saisie est correcte, false sinon
 */
bool saisie_correcte(string const &cmd);

/**
 * @brief fonction verifiant que la saisie est correcte en cas de petit roque
 * (O|o|0)*2
 * @param cmd l'entrée saisie par l'utilisateur
 * @return true si la saisie est correcte, false sinon
 */
bool saisie_correcte_petitroque(string const &cmd);

/**
 * @brief fonction verifiant que la saisie est correcte en cas de grand roque
 * (O|o|0)*3
 * @param cmd l'entrée saisie par l'utilisateur
 * @return true si la saisie est correcte, false sinon
 */
bool saisie_correcte_grandroque(string const &cmd);