<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Table de hachage](#table-de-hachage)
	- [Complexité temporelle](#complexité-temporelle)
	- [Notation](#notation)
	- [Lois](#lois)
		- [Exemple avec un String](#exemple-avec-un-string)


<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Table de hachage



## Complexité temporelle
n correspond au nombre noeuds dans l'arbre.

| Algorithme | Complexité |
| :---: | :---: |
| Recherche | O (1) |
| Insertion | O (1) |
| Acceder | –* |
\* Dans une table de hachage, l’ordre des éléments est indéfini, rendant l’accès aléatoire inapplicable, du moins pas en temps mieux que O(n).

## Notation
| Étiquette | Signification |
| :---: | :---: |
| N | Le taille N du tableau  |
|  |  |
|  |  |

## Lois
`h2 (y) = y mod N` 

### Exemple avec un String 
```
N = 10 
Dictionnaire<string, string> d;
d["INF1120"] = "Programmation I"; // "INF1120".hash()=23247
d["INF1132"] = "Mathematiques pour l'informatique"; // "INF1132".hash()=54248
d["INF2120"] = "Programmation II"; // "INF2120".hash()=93717
d["INF3105"] = "Structures de donnees et algorithmes"; // "INF3105".hash()=52238
d["INF4230"] = "Intelligence artificielle"; // "INF4230".hash()=21349
```
`23247 mod 10 = 7` on le place dans la case 7 du tableau 