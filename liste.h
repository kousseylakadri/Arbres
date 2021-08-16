/*
  INF3105 - Structures de données et algorithmes
  UQAM / Département d'informatique

  Liste simplement chaînée.

  À compléter.
*/

#if !defined(__LISTE_H__)
#define __LISTE_H__

#include <assert.h>

// Déclaration

template <class T>
class Liste {
public:
    class Iterateur;

    Liste();
    ~Liste();

    bool estVide() const;
    void vider();

    bool operator==(const Liste&) const;

    const Liste& operator=(const Liste&);

    T& operator[](const Iterateur&);
    const T& operator[](const Iterateur&) const;

    // Les fonctions insérer retournent un Itérateur sur la position de l'objet inséré.
    // La fonction enlever retourne un Iterateur sur la position suivante de l'objet enlevé.
    Iterateur inserer(const T&, const Iterateur&);
    Iterateur enlever(const Iterateur&);

    Iterateur inserer_debut(const T&);
    Iterateur inserer_fin(const T&);
    void enlever_debut();

    Iterateur debut() const; // Iterateur sur le début.
    Iterateur fin() const; // Iterateur sur la fin. La fin est la position suivante du dernier élément.

    Iterateur trouver(const T&) const; // Retourne un itérateur sur le premier élément cherchée. S'il n'existe pas, retourne fin().

private:
    class Cellule {
    public:
        Cellule(const T& c, Cellule* s = NULL)
            : suivante(s)
        {
            contenu = c;
        }
        T contenu;
        Cellule* suivante;
    };

public:
    class Iterateur {
    public:
        Iterateur(const Iterateur&);
        Iterateur(const Liste&);

        operator bool() const; // retourne vrai si l'itérateur n'est pas rendu à la fin. Permet de faire while(iter)
        bool operator!() const; // retourne faux si l'itérateur n'est pas rendu à la fin
        bool operator==(const Iterateur&) const; // compare deux itérateur (deux "positions")
        bool operator!=(const Iterateur&) const; // !compare deux itérateur (deux "positions")

        Iterateur operator++(int); // post-incrément (passe au suivant)
        Iterateur& operator++(); // pré-incrément (passe au suivant)

        //T& operator*(); // Pourquoi est-ce une mauvaise idée? Qu'arrive-t-il si la liste est constante?
        const T& operator*() const; // déférencement

        Iterateur& operator=(const Iterateur&); // affecte l'itérateur à la valeur d'un autre

    private:
        Cellule* precedente; // pointeur sur la Cellule précédente de la position courante
        const Liste& liste; // référence sur la Liste associée à l'itérateur courant (pour des fins de robustesse).
        friend class Liste;
    };

private:
    Liste(const Liste&);

    Cellule* derniere;
};

/*
 Puisque Liste<T> est une classe générique, toutes ses définitions doivent être
 inclues après les déclarations. On peut quand même séparer les déclarations et
 les définitions en deux fichiers (liste.h et liste.hcc), à condition d'inclure le
 deuxième (liste.hcc) à la fin du premier (liste.h). Ainsi, un fichier source
 (.cc, .cpp, c++) qui inclut liste.h inclura indirectement aussi liste.hcc.
*/
//#include "liste.hcc"

// Implémentation des constructeurs, destructeurs et fonctions
template <class T>
Liste<T>::Liste()
{
    derniere = NULL;
}

template <class T>
Liste<T>::~Liste()
{
    vider();
}

template <class T>
bool Liste<T>::estVide() const
{
    return derniere == NULL;
}

template <class T>
void Liste<T>::vider()
{
    // À compléter.
    // Requis pour la tâche 3.
}

template <class T>
const Liste<T>& Liste<T>::operator=(const Liste<T>& autre)
{
    // À compléter.
    return *this;
}

template <class T>
T& Liste<T>::operator[](const Iterateur& i)
{
    assert(&i.liste == this);
    assert(i.precedente != NULL);
    return i.precedente->suivante->contenu;
}

template <class T>
const T& Liste<T>::operator[](const Iterateur& i) const
{
    assert(&i.liste == this);
    assert(i.precedente != NULL);
    return i.precedente->suivante->contenu;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer(const T& e, const Iterateur& i)
{
    // À compléter.
    return fin();
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer_debut(const T& e)
{
    // À compléter.
    return fin();
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer_fin(const T& e)
{
    // À compléter.
    // Requis pour la tâche 3.
    return fin();
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::enlever(const Iterateur& i)
{
    // À compléter.
    return fin();
}

template <class T>
void Liste<T>::enlever_debut()
{
    // À compléter.
    // Requis pour la tâche 3.
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::debut() const
{
    return Iterateur(*this);
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::fin() const
{
    Iterateur iter(*this);
    iter.precedente = NULL;
    return iter;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::trouver(const T& e) const
{
    // À compléter.
    // Probablement non requis pour la tâche #3.
    return fin();
}

template <class T>
bool Liste<T>::operator==(const Liste& autre) const
{
    if (this == &autre)
        return true;
    // À compléter.
    return false;
}

//----------------------------------------------------//
template <class T>
Liste<T>::Iterateur::Iterateur(const Iterateur& i)
    : liste(i.liste)
{
    precedente = i.precedente;
}

template <class T>
Liste<T>::Iterateur::Iterateur(const Liste<T>& l)
    : liste(l)
{
    precedente = l.derniere;
}

template <class T>
bool Liste<T>::Iterateur::operator!() const
{
    return precedente == NULL;
}

template <class T>
Liste<T>::Iterateur::operator bool() const
{
    return precedente != NULL;
}

template <class T>
bool Liste<T>::Iterateur::operator==(const Iterateur& autre) const
{
    return precedente == autre.precedente
        && &liste == &autre.liste;
}

template <class T>
bool Liste<T>::Iterateur::operator!=(const Iterateur& autre) const
{
    return precedente != autre.precedente
        || &liste != &autre.liste;
}

// operator ++ () est le pré-incrément
template <class T>
typename Liste<T>::Iterateur& Liste<T>::Iterateur::operator++()
{
    precedente = precedente->suivante;
    if (precedente == liste.derniere)
        precedente = NULL;
    return *this;
}

// operator ++ (int) est le post-incrément
template <class T>
typename Liste<T>::Iterateur Liste<T>::Iterateur::operator++(int)
{
    Iterateur temp(*this);
    precedente = precedente->suivante;
    if (precedente == liste.derniere)
        precedente = NULL;
    return temp;
}

template <class T>
const T& Liste<T>::Iterateur::operator*() const
{
    return liste[*this];
}

template <class T>
typename Liste<T>::Iterateur& Liste<T>::Iterateur::operator=(const Iterateur& autre)
{
    assert(&liste == &autre.liste);
    precedente = autre.precedente;
    return *this;
}

#endif
