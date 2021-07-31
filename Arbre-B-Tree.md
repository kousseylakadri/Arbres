<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Arbre B d’ordre m](#arbre-b-dordre-m)
  - [Complexité temporelle](#complexité-temporelle)
  - [Propriétés](#propriétés)
  - [Notation](#notation)
  - [Insertion](#insertion)
    - [Exemple 1 : Insertion de l’arbre B d’ordre 4](#exemple-1-insertion-de-larbre-b-dordre-4)
  - [Enlèvement](#enlèvement)
    - [Exemple 17 18 0](#exemple-17-18-0)
  - [Recherche](#recherche)
    - [Exemple Recherche de 23](#exemple-recherche-de-23)
  - [Nombre de clé dans un Arbre B d’ordre m, et de hauteur h](#nombre-de-clé-dans-un-arbre-b-dordre-m-et-de-hauteur-h)
    - [Exemple avec m = 100 et h = 2](#exemple-avec-m--100-et-h--2)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Arbre B d’ordre m

Un arbre B d’ordre m, aussi appelé arbre B(m/2, m), 12 est un arbre équilibré.

- `max d'enfant : m`
- `max de cle : m-1`
- `min d'enfant : [m/2]`
- `min de cle : [m/2]-1`

## Complexité temporelle
n correspond au nombre noeuds dans l'arbre.

| Algorithme | Complexité |
| :---: | :---: |
| Recherche | O(log n) |
| Insertion | O(log n) |
| Supression | O(log n) |

## Propriétés
1. Tous les nœuds ont au plus m enfants.
2. Les nœuds intérieurs stockent une liste de clés triées ⟨k0,k1,···⟩ et des pointeurs vers les enfants;
3. Le nombre de clés dans un nœud est égale au nombre d’enfants moins un ;
4. Tous les nœuds intérieurs (autres que les feuilles et la racine) ont au moins ⌊ m2 ⌋ enfants ;
5. Toutes les feuilles sont à distance égale de la racine.
6. Tous les éléments accessibles depuis le i-ème enfants sont supérieurs à la clé ki−1 et inférieurs à la clé ki.


## Notation
| Étiquette | Signification |
| :---: | :---: |
| K | Cle(un noeud k valeurs) |
| m | Un arbre-B d'ordre |
| P | Pointeur |

## Insertion
  
1. on recherche la feuille où devrait se trouver l’élément e ;
2. une fois la feuille trouvée, on insère l’élément dans la feuille trouvée; l’unique exception est l’insertion du premier élément où la racine doit être créée;
3. si la capacité du nœud n’est pas dépassée (un nœud contient au plus m − 1 clés), l’opération est terminée ;
4. si la capacité est dépassée, on scinde le nœud en deux, et on remonte la clé médiane vers le nœud parent ;
5. si le nœud parent dépasse sa capacité, on le scinde à nouveau, et ce, jusqu’à temps de remonter à la racine ;
6. enfin, dans le cas où la capacité de la racine est dépassée, une nouvelle racine est créée.


### Exemple 1 : Insertion de l’arbre B d’ordre 4

![Insertion](./Images/Insertion-1.png)

![Insertion](./Images/Insertion-2.png)

## Enlèvement

L’enlèvement d’un élément e fonctionne comme suit :
- on recherche la feuille où se trouve l’élément e et on y enlève e ; 
- si le nombre de clés devient inférieur à ⌊m/2⌋ :
  - si les deux nœuds frères ont un nombre de clés supérieur à ⌊m/2⌋, on peut emprunter une clé d’un frère et ou d'un pere ;
  - sinon, on fusionne le nœud avec l’un de ses frères ;
- lors d’une fusion, on descend une clé du nœud parent et on répète l’étape 2 sur ce dernier.
  
### Exemple 17 18 0

![Enlèvement](./Images/enlevement.png)

## Recherche

La recherche d’un élément e dans un arbre B se fait comme suit :
- le nœud de départ est la racine ;
- on recherche la plus grande clé ki dans le nœud courant tel quel ki <= e ;
- si ki = e, alors l’élément a été trouvé ;
- sinon, le i-ème nœud enfant devient le nœud courant et on répète l’étape 2 de la procédure ; 
- si on ne trouve pas la clé dans une feuille, alors l’élément e n’existe pas dans l’arbre.  

  
### Exemple Recherche de 23

![Recherche](./Images/reherche.png)

## Nombre de clé dans un Arbre B d’ordre m, et de hauteur h
- Nb clés min = 2*(m+1) h  - 1
- Nb clés max = (2*m+1) h+1 - 1
  
### Exemple avec m = 100 et h = 2

- Nb clés min = 20401 et 
- Nb clés max =8 120 600
