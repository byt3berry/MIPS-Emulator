# Projet CS351 (2022-2023): Émulateur MIPS

---
title: Projet CS351 (2022-2023): Émulateur MIPS
author: Cocagne_Strainovic
date: 18/10/2022
---

## Rendu 1

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Vérifié que `make test-cli` ne renvoie pas d'erreur.
  - [x] Vérifié que `make tests` se plaint sur le nombre d'instructions et pas
      sur l'existence des fichiers de sortie.
  - [x] Vu que les soumissions se font avec `make tar`.


## Rendu 2

(Une dizaine de lignes devrait suffire à chaque fois)

* Comment avez-vous choisi de programmer l'analyse de texte (dont la lecture
des opérandes entières) ?

[Nous récupérons chaque ligne une par une, si le premier caractère de la ligne 
est un "#" (commentaire) ou un saut de ligne (ligne vide), on ignore la ligne.
Ensuite, à partir de cette ligne nous récupérons l'opérateur ("ADD", "SUB", 
"J", ...), son format (qui sert à savoir le nombre de paramètres à récupérer, 
l'ordre dans lequel il faut les récupérer dans la ligne et les écrire dans le 
code hexadécimal), le nombre de paramètres, les paramètres, l'OPcode (pour les 
types I et J) ou le func (pour le type R), et enfin l'ordre des paramètres.
Toutes ces informations sont stockées dans une structure "Instruction". Pour 
finir, le code hexadécimal qui sera affiché dans la console ou stocké dans un 
fichier est créé puis utilisé.]

* Avez-vous vu des motifs récurrents émerger ? Avez-vous "factorisé" ces motifs
pour éviter de les répéter ? Si non, serait-ce difficile ?

[On remarque plusieurs types de récurrence. Premièrement il existe trois 
catégories d'instruction, la catégorie R ("Register type"), I ("Immediate type") 
et J ("Jump type"),chaque catégorie possède son propre format codage binaire.
Ensuite on trouve 8 façons différentes d'écrire une instruction 
(ex : "%s $%d, %d($%d)", "%s $%d, $%d, %d", ...), chacune de ces façons facilite
la récupération des paramètres pour chaque ligne. Enfin on trouve 13 ordres 
de paramètres, c'est à dire l'ordre dans lequel les paramètres vont être écrits 
dans le codage binaire de l'instruction (ex : pour ADDI : premier sortie = deuxième entré,
deuxième sortie = premier entré, troisième sortie = troisième entrée). Sans 
factoriser les instructions parmis ces motifs, il faudrait prendre chaque 
instruction au cas par cas pour récupérer ses paramètres et générer le codage 
binaire.]

* Comment avez-vous procédé pour écrire les tests ? Étes-vous confiant·e·s que
toutes les instructions gérées sont couvertes ? 

[Le premier fichier de test comporte une ligne par instruction, ainsi chaque 
instruction est testée, le deuxième fichier test les limites du code : 
nombre trop grands, utilisations de registre à la place d'immédiat et inversement, 
tentative de modification du registre $zero. Nous avons utilisé les fichiers tests 
pour vérifier que chaque instruction renvoyais les bons codes binaires, nous avons 
en plus utilisé un programme permettant d'assembler du code MIPS pour vérifier que 
nos codes binaires étaient justes. De plus, si le code détècte un problème dans une 
instruction (ex : opération qui n'existe pas, registre à la place d'immédiat ou 
inversement, ...), l'instruction est remplacée par l'instruction NOP qui ne fait 
rien. Le code s'est révélé fonctionnel lorque nous l'avons mit à l'épreuve de nos 
tests.]

* Quelle a été votre expérience avec l'utilisation et la compréhension de la
documentation (ie. des annexes) ?

[L'annexe 1 est très clair et explique bien les différents formats d'instruction
R, I et J ainsi que l'utilisation et l'appel des registres. L'annexe 2 à été utile 
pour récupérer les valeurs des OPcode et func, mais aussi pour identifier les formats 
d'entrée des paramètres dans les instructions et de sortie des paramètres dans les 
codages binaires. Cette annexe nous a aussi servi pour comprendre les opérations 
que faisait chaque instruction, même si quelques explications sont compliquées à 
comprendre pour les non iniciés (ex : pour LUI : GPR[rt] <-- immediate || 0^16), 
internet à été très utile quant à la compréhension de ces notations.]

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Implémenté la traduction pour des instructions de toutes les catéories
      (calcul, comparaisons, sauts, HI/LO, mémoire)
  - [x] Implémenté la traduction pour toutes les instructions de l'annexe 2
  - [x] Pris en compte les cas particuliers : valeurs négatives, hors limites,
      noms d'instructions ou opérandes invalides...


## Rendu 3

(10/15 lignes devrait suffire à chaque fois)

* Quelle structure en modules planifiez-vous d'utiliser pour l'émulateur ?

[Nous avons huit modules différents :
 - "modes.h" : Les fonctions pour lancer les différents modes de lecture
 - "read.h" : Les fonctions pour lire les fichiers en fonction du mode de lecture
 - "analyse.h" : Fonctions pour extraire les données utiles de chaques instruction
 - "Instruction.h" : Gestion des objets du type Instruction
 - "execute.h" : Les fonctions pour éxecuter les instructions
 - "registers.h" : Les fonctions pour gérer les registres (lecture, écriture)
 - "fonctionModes.h" : Les fonctions lancées après le choix du mode d'éxecutions
 - "utils.h" : Les fonctions de conversion ou d'édition de chaines de caractères
 - "constantes.h" : Les constantes pour clarifier le code]

* Quelles seront les fonctions principales de chaque module ?

[Les fichiers et leurs fonctions principales :
 - "modes.h" : "modeInteractif", "modeAutoPasAPas", "modeAuto" en fonction du mode 
de lecture
 - "read.h" : "readLine", récupère une ligne dans le fichier à lire, appelle la 
fonction d'analyse
 - "analyse.h" : "analyseLine" récupère les différents paramètres de chaque
instruction : opérateur, OPcode, registres ou immédiats
 - "Instruction.h" : "setOutput" appelle les fonctions qui vont générer le code
hexadécimal de l'instruction en distinguant le format (R, I ou J)
 - "execute.h" : Pas encore implémenté, on aura une fonction qui déterminera 
l'opération à effectuer sur les registres : addition, soustraction, ...
 - "registers.h" : "setValueToRegister" et "getValueFromRegister" pour écrire et lire
les registres
 - "utils.h" : "decToBin", "binToHex", "complementA2", et d'autres fonctions annexes
 - "constantes.h" : Aucunes fonctions ici, seulement des constantes]

* Quels avantages voyez vous à cette structure (à comparer à un unique fichier)?

[Plusieurs modules permettent de structurer le code, le rendent ergonomique, 
facile à parcourir et à débogger si nécessaire. Les fonctions sont regroupées
en fonction de leurs objectifs, au lieu de faire de grandes fonctions, on essaye
de les diviser en plus petites, plus simples et réutilisables, afin de factoriser
le code.]


## Rendu 4

* Avez-vous réussi à suivre la structure prévue au rendu 3 ? Quelles
modifications ont été nécessaires ? Rétrospectivement, est-ce que cette
structure était bien prévue ?

[COMPLÉTER ICI]

* Avez-vous compris le fonctionnement de chaque instruction à partir de la
documentation fournie ? Si non, quels sont les points obscurs ?

[COMPLÉTER ICI]

* Quels exemples de programmes avez-vous choisi pour tester le calcul ? Les
comparaisons et sauts ? La mémoire ?

[COMPLÉTER ICI]

* Le sujet spécifie-t-il tous les détails nécessaires pour bien implémenter la
mémoire ? Quels choix avec-vous faits ?

[COMPLÉTER ICI]

* Reste-t-il des bugs que vous avez découverts et pas corrigés ?

[COMPLÉTER ICI]

* D'autres remarques sur votre programme ?

[COMPLÉTER ICI]

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :**
  - [ ] Implémenté l'émulation de toutes les instructions gérées par le rendu 2.
  - [ ] Implémenté l'émulation de toutes les instructions.
  - [ ] Tous vos tests qui passent.
  - [ ] Vérifié que vos tests couvrent toutes les instructions émulées.
  - [ ] Testé les cas particuliers : valeurs négatives, overflows...
  - [ ] Testé les cas d'erreur : division par zéro, sauts invalides...
  - [ ] Un port fonctionnel de DOOM pour votre émulateur.

* Des retours sur le projet en général ?

[COMPLÉTER ICI]
