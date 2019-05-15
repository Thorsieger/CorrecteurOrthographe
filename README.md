# Correcteur orthographique

>  Réalisation d’un analyseur de fichier pour compter les mots non reconnus par rapport à un dictionnaire.

## Principe

Ce programme permet de détecter dans un texte tous les mots mal orthographiés. Il accepte différents alphabets (latin, cyrillique, japonais ...). Il se base sur le dictionnaire que l'utilisateur donne et compte le nombre de mots non reconnus dans le fichier testé. Le programme n'est pas sensible à la casse mais gère les accents et caractères spéciaux.

## Installation

* Téléchargez tous les fichiers du projet
* Ouvrir un terminal à l'emplacement des fichiers
* Installer gcc (si nécessaire) ou modifiez le file makefile pour utiliser le compilateur de votre choix
* Tapez "make" dans le terminal (cela va créer l'exécutable "compteur_erreurs")

## Utilisation

* Lancer le programme ( ./compteur_erreurs)

* Donnez le nom du dictionnaire/texte que vous souhaitez utiliser (le nom ne doit pas contenir d'espaces):
    * Soit en donnant le chemin absolu du fichier : (/home/usr/chemin/fichier/dico.txt)
    * Soit en plaçant le dictionnaire à l'emplacement de l'exécutable et en entrant simplement son nom
    * Soit en utilisant les 3 dictionnaires disponibles (words/american-english ou words/french ou words/brithish-english)

* Vous pouvez ensuite modifier les caractères de séparation d'un texte (points, virgules, etc. ) en appuyant sur [Y] ou conserver la liste déja disponible.

* Il vous faut maintenant donner le nom du fichier à corriger. (soit chemin absolu, soit fichier placé dans le répertoire de l'exécutable). Ici encore le nom du fichier ne doit pas contenir d'espaces.

**Le programme vous indique les mots non reconnus et les comptabilises**

* Vous pouvez maintenant soit quitter le programme soit relancer une analyse d'un autre fichier.

*Pour changer de dictionnaire il vous faudra relancer le programme.*

*Il est également possible de lancer le programme avec les fichiers en paramètres. Lancer la commande suivante : ./compteur_erreurs [chemin dictionnaire] [chemin ficher à analyser].*
