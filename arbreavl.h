#if !defined(__ARBREAVL_H__)
#define __ARBREAVL_H__
#include <cassert>
#include "pile.h"

template <class T>
class ArbreAVL
{
  public:
    ArbreAVL();
    ArbreAVL(const ArbreAVL &);
    ~ArbreAVL();

    // Annonce l'existence d'une classe Iterateur.
    class Iterateur;

    void inserer(const T &);
    bool contient(const T &) const;
    bool vide() const;
    void vider();
    bool afficher() const;
    void enlever(const T &); // non requis pour le TP2.
    int hauteur() const;

    // Fonctions pour obtenir un itérateur (position dans l'arbre)
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const T &) const;
    Iterateur rechercherEgalOuSuivant(const T &) const;
    Iterateur rechercherEgalOuPrecedent(const T &) const;

    // Accès aux éléments de l'arbre via un intérateur.
    const T &operator[](const Iterateur &) const;
    T &operator[](const Iterateur &);

    // Copie d'un arbre AVL.
    ArbreAVL &operator=(const ArbreAVL &);

  private:
    struct Noeud
    {
        Noeud(const T &);
        T contenu;
        int equilibre;
        Noeud *gauche,
            *droite;
    };
    Noeud *racine;

    // Fonctions internes
    bool inserer(Noeud *&, const T &);
    void rotationGaucheDroite(Noeud *&);
    void rotationDroiteGauche(Noeud *&);
    void vider(Noeud *&);
    void copier(const Noeud *, Noeud *&) const;
    const T &max(Noeud *) const;
    bool afficher(Noeud *courant, int profondeur = 0, int etat = 0) const;
    bool enlever(Noeud *&, const T &e);

  public:
    // Sera présenté à la semaine #7
    class Iterateur
    {
      public:
        Iterateur(const ArbreAVL &a);
        Iterateur(const Iterateur &a);
        Iterateur(const ArbreAVL &a, Noeud *c);

        operator bool() const;
        bool operator!() const;
        bool operator==(const Iterateur &) const;
        bool operator!=(const Iterateur &) const;

        const T &operator*() const;

        Iterateur &operator++();
        Iterateur operator++(int);
        Iterateur &operator=(const Iterateur &);

      private:
        const ArbreAVL &arbre_associe;
        Noeud *courant;
        Pile<Noeud *> chemin;

        friend class ArbreAVL;
    };
};

//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T &c)
    : contenu(c), equilibre(0), gauche(NULL), droite(NULL)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL()
    : racine(NULL)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T> &autre)
    : racine(NULL)
{
    copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    vider(racine);
}

template <class T>
bool ArbreAVL<T>::contient(const T &element) const
{
    Noeud *racineTemp = racine;

    while (racineTemp != nullptr && racineTemp->contenu != element)
    {
        if (racineTemp->contenu > element)
            racineTemp = racineTemp->gauche;
        else
            racineTemp = racineTemp->droite;
    }

    if (racineTemp == nullptr)
        return false;
    else
        return true;
}

template <class T>
void ArbreAVL<T>::inserer(const T &element)
{
    inserer(racine, element);
}

template <class T>
bool ArbreAVL<T>::inserer(Noeud *&noeud, const T &element)
{
    if (noeud == NULL)
    {
        noeud = new Noeud(element);
        return true;
    }
    if (element < noeud->contenu)
    {
        if (inserer(noeud->gauche, element))
        {
            noeud->equilibre++;
            if (noeud->equilibre == 0)
                return false;
            if (noeud->equilibre == 1)
                return true;
            assert(noeud->equilibre == 2);
            if (noeud->gauche->equilibre == -1)
                rotationDroiteGauche(noeud->gauche);
            rotationGaucheDroite(noeud);
        }
        return false;
    }
    else if (element > noeud->contenu)
    {
        if (inserer(noeud->droite, element))
        {
            noeud->equilibre--;
            if (noeud->equilibre == 0)
                return false;
            if (noeud->equilibre == -1)
                return true;
            assert(noeud->equilibre == -2);
            if (noeud->droite->equilibre == 1)
                rotationGaucheDroite(noeud->droite);
            rotationDroiteGauche(noeud);
        }
        return false;
    }

    // element == noeud->contenu
    noeud->contenu = element;
    return false;
}

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud *&racinesousarbre)
{
    Noeud *temp = racinesousarbre->gauche;
    int ea = temp->equilibre;
    int eb = racinesousarbre->equilibre;
    int neb = -(ea > 0 ? ea : 0) - 1 + eb;
    int nea = ea + (neb < 0 ? neb : 0) - 1;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud *&racinesousarbre)
{
    Noeud *temp = racinesousarbre->droite;
    int ea = temp->equilibre;
    int eb = racinesousarbre->equilibre;
    int neb = -(ea < 0 ? ea : 0) + 1 + eb;
    int nea = ea + (neb > 0 ? neb : 0) + 1;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
bool ArbreAVL<T>::afficher() const
{
    printf("\n");
    if (racine != nullptr)
        afficher(racine);
    else
        printf("Vide");
    printf("\n");
}

template <class T>
bool ArbreAVL<T>::afficher(Noeud *courant, int profondeur, int etat) const
{
    if (courant->droite)
        afficher(courant->droite, profondeur + 1, 1);

    for (int i = 0; i < profondeur; i++)
        printf("          ");

    if (etat == 1) // gauche
        std::cout << "┌───────";
    else if (etat == 2) // droite
        std::cout << "└───────";

    std::cout << "[" << courant->contenu << "]:" << courant->equilibre << std::endl;

    if (courant->gauche)
        afficher(courant->gauche, profondeur + 1, 2);
}

template <class T>
bool ArbreAVL<T>::vide() const
{
    return racine == nullptr;
}

template <class T>
void ArbreAVL<T>::vider()
{
    vider(racine);
}

template <class T>
void ArbreAVL<T>::vider(Noeud *&noeud)
{
    if (noeud == nullptr)
        return;

    vider(noeud->gauche);
    vider(noeud->droite);

    delete noeud;
}

template <class T>
void ArbreAVL<T>::copier(const Noeud *source, Noeud *&noeud) const
{
    if (source == nullptr)
    {
        noeud = nullptr;
        return;
    }

    noeud = new Noeud(source->contenu);
    noeud->equilibre = source->equilibre;

    if (source->gauche != nullptr)
        copier(source->gauche, noeud->gauche);

    if (source->droite != nullptr)
        copier(source->droite, noeud->droite);
}

template <class T>
int ArbreAVL<T>::hauteur() const
{
    // À compléter.
    return 0;
}

template <class T>
const T &ArbreAVL<T>::max(Noeud *n) const
{
    // À compléter.
}

// L'enlèvement est optionnel (non requise pour le TP2)
template <class T>
void ArbreAVL<T>::enlever(const T &element)
{
    enlever(racine, element);
}

template <class T>
bool ArbreAVL<T>::enlever(Noeud *&noeud, const T &element)
{
    if (element < noeud->contenu)
    {
        if (enlever(noeud->gauche, element))
        {
            // ...
        }
    }
    else if (element > noeud->contenu)
    {
        // ...
    }
    else if (element == noeud->contenu)
    {
        if (noeud->gauche == NULL && noeud->droite == NULL)
        {
            delete noeud;
            noeud = NULL;
            return true;
        }
        else
        {
            // ...
            return true;
        }
    }
}

//----------------------- OPERATEURS ----------------------------//
template <class T>
const T &ArbreAVL<T>::operator[](const Iterateur &iterateur) const
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
T &ArbreAVL<T>::operator[](const Iterateur &iterateur)
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
ArbreAVL<T> &ArbreAVL<T>::operator=(const ArbreAVL &autre)
{
    if (this == &autre)
        return *this;
    vider();
    copier(autre.racine, racine);
    return *this;
}

//----------------------- ITERATEURS ----------------------------//
template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL &a)
    : arbre_associe(a), courant(NULL)
{
}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur &a)
    : arbre_associe(a.arbre_associe)
{
    courant = a.courant;
    chemin = a.chemin;
}

// Pré-incrément
template <class T>
typename ArbreAVL<T>::Iterateur &ArbreAVL<T>::Iterateur::operator++()
{
    // À compléter.
    return *this;
}

// Post-incrément
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int)
{
    Iterateur copie(*this);
    operator++();
    return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const
{
    return courant != NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const
{
    return courant == NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur &o) const
{
    assert(&arbre_associe == &o.arbre_associe);
    return courant == o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur &o) const
{
    assert(&arbre_associe == &o.arbre_associe);
    return courant != o.courant;
}

template <class T>
const T &ArbreAVL<T>::Iterateur::operator*() const
{
    assert(courant != NULL);
    return courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur &ArbreAVL<T>::Iterateur::operator=(const Iterateur &autre)
{
    assert(&arbre_associe == &autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}

//----------------------- ITERATEURS ----------------------------//
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
    Iterateur iter(*this);
    iter.courant = racine;
    if (iter.courant != NULL)
        while (iter.courant->gauche != NULL)
        {
            iter.chemin.empiler(iter.courant);
            iter.courant = iter.courant->gauche;
        }
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{
    return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T &e) const
{
    Iterateur iter(*this);
    Noeud *n = racine;
    while (n)
    {
        if (e < n->contenu)
        {
            iter.chemin.empiler(n);
            n = n->gauche;
        }
        else if (n->contenu < e)
            n = n->droite;
        else
        {
            iter.courant = n;
            return iter;
        }
    }
    iter.chemin.vider();
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T &e) const
{
    Iterateur iter(*this);
    // À compléter.
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T &e) const
{
    // À compléter.
    return Iterateur(*this);
}

#endif