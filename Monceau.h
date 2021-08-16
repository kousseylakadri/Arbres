/*
  Monceau à l'aide d'un tableau
  Permet de représenter des arbres binaires sans pointeurs :
  - L'enfant de gauche est assis à 2n
  - L'enfant de droite est assis à 2n + 1
  - Le parent est assis à l'étage (n/2)
*/

#ifndef Monceau_H
#define Monceau_H

#include <vector>
#include <string>

class Monceau {
  std::vector<int> queue_;
  unsigned    int  size_;

  // Appelé par insert()
  // Si la valeur du parent est supérieure à la valeur actuelle
  //   l'élément actuel bouillonne jusqu'à ce que nous atteignions la racine
  void bubbleUp  (int idx);
    // Appelé par delete()
  // Si le courant est supérieur aux enfants
  //   l'élément courant descend jusqu'à ce qu'il n'y ait plus d'enfants
  void bubbleDown(int idx);
  // Utilisé par bubbleDown()
  //   Récupère l'index de la valeur min
  //   entre 3 indices donnés au tableau de tas.
  int getMinIdx  (int aIdx, int bIdx, int cIdx);

public:
  Monceau();
  ~Monceau() {};
  bool              isEmpty   () const;
  int               size      () const;
  void              clear     ();
  int               getItem   (unsigned int idx) const;
  int               parent    (unsigned int idx) const;
  int               child     (unsigned int idx) const;
  int               find      (unsigned int idx, int val) const;
  void              insert    (int val);
  void              remove    (int val);
  void              makeMonceau  (int array[], int size);
  void              makeMonceau  (std::vector<int> &input);
  int               extractMin(); // Supprime et renvoie la valeur min
  std::vector<int>  MonceauSort  (); //O(n log n)
  std::string       toString  () const;
};

#endif