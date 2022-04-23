# <img src="assets/icon.png" alt="icon" width="6%"/> Jeu d'échecs 
[![version](https://img.shields.io/badge/version-1.0.1-blue.svg)](https://github.com/LosKeeper/jeu-echecs-cpp)
[![compiler](https://img.shields.io/badge/compiler-g++-red.svg)](https://github.com/LosKeeper/jeu-echecs-cpp/blob/main/Makefile)
[![license](https://img.shields.io/badge/license-GPL_3.0-yellow.svg)](https://github.com/LosKeeper/jeu-echecs-cpp/blob/main/LICENSE)
[![author](https://img.shields.io/badge/author-LosKeeper-blue)](https://github.com/LosKeeper)
> Il s'agit d'un projet de jeu d'échecs codée en C++ qui se joue en 1vs1 dans le terminal.


   1. [Compilation](#compilation)
      1. [Installation](#installation)
      2. [Debug](#debug)
      3. [Documentation](#documentation)
      4. [Tests](#tests)
   2. [Exécution](#exécution)
      1. [Démarrage](#démarrage)
      2. [Fonctionnement du jeu](#fonctionnement-du-jeu)
         1. [Déplacements classiques](#déplacements-classiques)
         2. [Roque](#roque)
         3. [Promotion](#promotion)
         4. [En passant](#en-passant)
         5. [Détection de l'échec](#détection-de-léchec)
         6. [Détection de l'échec et mat](#détection-de-léchec-et-mat)
         7. [Annuler le dernier coup](#annuler-le-dernier-coup)
      3. [Afficher les pièces mangées](#afficher-les-pièces-mangées)
      4. [Fin de partie](#fin-de-partie)
      5. [Entrées possibles](#entrées-possibles)
   3. [Fonctions demandées implémentées](#fonctions-demandées-implémentées)
   4. [Fonctions supplémentaires](#fonctions-supplémentaires)
   5. [Conception du programme](#conception-du-programme)
   6. [Futures améliorations](#futures-améliorations)

## Compilation

### Installation

Pour compiler le programme, on utilisera le makefile associé à ce projet grâce à la commande : 
```c
make
```
> Le programme sera ainsi compilé et placé dans le dossier `bin`.

### Debug

On peut compiler le programme en mode débug afin d'obtenir plus d'informations sur les différents passages dans les différentes fonctions (en particulier pour la détection de l'échec et mat). Pour cela, on compilera le programme en utilisant la commande :
```bash
make debug
```
> Les commandes de debug seront affichées en vert dans le terminal (indication sur les recherches de mouvements en cours et les fonction en cours d'utilisation)

### Documentation

Pour générer la documentation associée au programme, on utilisera la commande :
```bash
make doc
```
> On s'assurera au préalable d'avoir installé `graphviz` pour pouvoir compiler la documentation en ayant des graphques pour la représentation des classes :  `sudo apt install graphviz`

Ainsi sera généré un dossier html et sera automatiquement ouverte dans le navigateur par défaut la documentation mais sinon on y accédera par exemple grâce à la commande :
```bash
firefox html/index.html
```
### Tests

Pour tester le programme avec les fichiers de tests fournis, on utilisera la commande :
```bash
make tests
```
> Le programme sera compilé et testé et les résultats seront affichés dans le terminal.

## Exécution

### Démarrage

Pour démarrer le programme, on utilisera la commande 
```bash
./bin/echecs
```

### Fonctionnement du jeu

Une fois le programme démarré, il affichera l'échiquier initial et attendra la saisie d'un coup. Il est aussi indiqué la couleur de la pièce à déplacer.
#### Déplacements classiques

- Le programme attends une entrée dans le terminal la forme d'une chaîne de caractères du type `a2a3` avec `a2` étant la case de départ et `a3` la case d'arrivée.
#### Roque

- Le programme attendra une entrée dans le terminal la forme d'une chaîne de caractères du type `O-O` ou `O-O-O` pour le roque.

#### Promotion

- Lorsqu'un pion arrive à la dernière ligne, il peut alors se transformer soit en dame, soit en fou, soit en tour, soit en cavalier. Le programme attendra une entrée dans le terminal avec un caractère correspondant à la nouvelle pièce souhaitée.
#### En passant

- Lorsqu'un pion arrive à la case d'un pion adverse qui a fait precedemment un double saut, il peut alors faire un en passant c'est-à-dire manger la pièce adverse et se déplacer de 1 en diagonale dans la direction de la pièce adverse.

#### Détection de l'échec

- A chaque fin de tour, on détecte la présence d'un roi en échec et si c'est la cas on en informe le joueur dans le terminal.

#### Détection de l'échec et mat

- En cas d'échec, on vérifie alors s'il s'agit uniquement d'un échec ou bien s'il s'agit d'un échec et mat et dans ce cas on en informe le joueur dans le terminal.

#### Annuler le dernier coup

- Si par erreur vous avez mal joué et souhaitez rejouer votre dernier coup, vous pouvez revenir en arriere en faisant un `CTRL+Z` et rejouer votre coup.

>Pour cette commande, le programme utilise un thread séparé uniquement pour la lecture dans le terminal qui sera tué lors de la réception d'un signal car `cin` est bloquant.

### Afficher les pièces mangées

Pour afficher toutes les pièces déjà mangées, il suffit d'entrer `/pieces` et ainsi sera affichée la liste de toutes les pièces mangées.

### Fin de partie

Le programme affichera un message de fin de partie si la partie est terminée. Si l'on souhaite quiter le programme, il suffit d'entrer la commande `/exit` ou bien en faisant un `CTRL+C`.

### Entrées possibles

  
| Entrée              | Action                        |
| ------------------- | ----------------------------- |
| `a2a3`              | Déplace la pièce `a2` en `a3` |
| `o-o`               | Petit roque                   |
| `o-o-o`             | Grand roque                   |
| `/quit` ou `CTRL+C` | Arrête du programme           |
| `CTRL+Z`            | Annule le dernier coup        |
| `/pieces`           | Affiche les pièces mangées    |
## Fonctions demandées implémentées

- [Base](#déplacements-classiques)
- Prise
- Pions
- Obstacle
- [Prise en passant](#en-passant)
- [Echec](#détection-de-léchec)
- [Roque](#roque)
- [Promotion](#promotion)
- [Mat](#détection-de-léchec-et-mat)

## Fonctions supplémentaires

- [Annulation du dernier coup](#annuler-le-dernier-coup)
- [Affichage des pièces mangées](#afficher-les-pièces-mangées)

## Conception du programme

Le programme est composé de plusieurs fichiers correspondants chacun à des classes. J'ai déjà commencé par réaliser les différentes classes avec leurs méthodes et attributs. Ainsi on a les classes :
- `Echiquier` : qui contient toutes les pièces du jeu
- `Piece` : qui contient les attributs et méthodes communes à toutes les pièces.
  - `Pion` : qui contient les attributs et méthodes communes à tous les pions.
  - `Fou` : qui contient les attributs et méthodes communes à tous les fou.
  - `Tour` : qui contient les attributs et méthodes communes à tous les tours.
  - `Cavalier` : qui contient les attributs et méthodes communes à tous les cavaliers.
  - `Dame` : qui contient les attributs et méthodes communes à toutes les dames.
  - `Roi` : qui contient les attributs et méthodes communes à tous les rois.
> Toutes ces classes héritent de la classe `Piece`.
- `Square` : qui contient les attributs et méthodes communes à toutes les cases.
- `Jeu` : qui contient les attributs et méthodes communes à tout le programme.

Ensuite, j'ai implémenté les fonctions demandées comme l'affichage tout d'abord puis ensuite la fonction de verification de mouvement légaux qui est virtuelle (car elle est différent pour chaque pièce). J'ai ensuite implémenté la fonction de déplacement en accord avec la fonction de mouvement légaux puis la fonction de prise. Pours les roques, j'avais commencé par implémenter les roques sans l'entrée du type `o-o-o` cependant cela rendait le roque obligatoire c'est pourquoi je suis revenu à la méthode de roque avec l'entrée du type `o-o-o` comme demandée. J'ai ensuite implémenté la promotion pour les pions et la prise en passant en m'y reprenant à plusieures fois. Enfin, j'ai réalisé la fonction de détection de l'échec et de l'échec et mat qui copie l'echiquier et qui teste l'échec après le déplacement de toute les pièces. J'ai aussi implémenté des fonctions supplémentaires comme l'arrêt du programme et l'annulation du dernier coup en utilisant des signaux. Cela a été rendu possible grâce a l'utilisation de `thread` qui permet de lancer un thread séparé pour la lecture dans le terminal et qui sera tué lors de la réception d'un signal car `cin` est bloquant. Il y a aussi la possibilité d'afficher les différentes pièces mangées grace à la commande `/pieces`. Le plus compliqué a été d'implémenter le fonction d'échec et mat c'est pourquoi il y a une règle `debug` dans le makefile qui affiche les différentes pièces testées lors de l'échec et mat. La fonction pat n'a pas été implémentée car trop compliqué sachant que pour chaque pat il y a détection de l'échec et de l'échec et mat. Le programme passe les différents tests fournis dans le sujet comme on peut le voir en executant la commande `make test`.

## Futures améliorations

- Multithreading pour le recherche d'échec et mat
- Vraie interface graphique
