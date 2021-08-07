Monceau (Heap)
==============

* Le but c'est de pouvoir y extraire l'élément plus petit en temps :math:`\in 
  O(1)`
* Données linéaires et partiellment ordonnées
* Liste d'opérations simple
    * Inserer un élément
    * Accéder le premier élément
    * Supprime le premier élément

Un monceau: représentation graphique et en mémoire:

.. digraph:: exemple_arbre_monceau
    
    2 -> 4 -> 7;
    2 -> 6 -> 9;
    4 -> 8;
    
|  [0] | [1] |[2]  |[3]  | [4] | [5] |
| :--- |:---:|:---:|:--- |:---:|:---:|
|   2  |   4 |  6  |  7  |  8  |   9 |


Détails
-------

Un monceau peut être représenté avec un `arbre binaire`_ où:

* la racine est l'element le plus petit (ou avec la plus haute priorité)
* l'arbre est **complet**: il n'y à aucun trous à gauche (il doit avoir une
  meilleur façon de le dire)
* chaque noeud est toujours plus petit de ses descendants

Un monceau peut être implémenté avec une **liste_** où:

* la racine est à l'indice 0 de la liste
* l'ordonnencement des elements dans la liste suit le `parcour en largeur`__ de
  l'arbre
* pour trouver les **enfants** d'un noeud : gauche : :math:`2i + 1` et droite :
  :math:`2i + 2`
* pour trouver le **parent** d'un noeud: :math:`(i-1)/2` (sauf pour i=0)

__ parcours_

Insertion
`````````

1. Inserer l'élément à la fin de la liste (*O(1)*). Ceci est analogue à 
   insérer le nouveau noeud dans la prochaine place disponible (en allant de
   gauche à droite de façon complète) dans l'arbre.
2. Tant que le nouveau élement est plus petit que son parent (et l'élément
   n'est pas à la racine, bien sûr): l'echanger de place avec son parent.

Dans le pire cas, **l'insertion se fait en** :math:`O(\log n)`, car on insère à
la fin du tableau (:math:`O(1)` {ammorti}) et dans le pire cas il faut
remmonter le nouveau élément jusqu'à la racine (:math:`O(\log n)`).

Suppresion de l'élément prioritaire
```````````````````````````````````

1. On mémorise le premier élément (indice 0)
2. On transfert le dernier élément à la place du premier (bye bye premier
   élément)
3. Tant que cet élément est plus grand que ses deux enfants, on l'échange de
   place avec le plus petit des deux enfants 

Priorité
````````

Le monceau est utilisé pour implémenter la **liste de priorité**, qui place
l'élément le plus prioritaire au début. Le concept de priorité permet de 
pouvoir definir une base autre que < ou > pour comparer les éléments.
