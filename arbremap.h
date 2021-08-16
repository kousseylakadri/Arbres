/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique ArbreMap<K,V> pour le Lab8 et le TP2.

   AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#if !defined(__ARBREMAP_H__)
#define __ARBREMAP_H__

#include "arbreavl.h"

template <class K, class V>
class ArbreMap
{
    class Entree
    {
      public:
        Entree(const K &c) : cle(c), valeur() {}
        K cle;
        V valeur;
        bool operator<(const Entree &e) const { return cle < e.cle; }
        bool operator>(const Entree &e) const { return cle > e.cle; }
    };
    ArbreAVL<Entree> entrees;

  public:
    class Iterateur
    {
      public:
        Iterateur(const ArbreMap &a) : iter(a.entrees.debut()) {}
        Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}
        operator bool() const { return iter.operator bool(); };
        bool operator!() const;

        Iterateur &operator++();
        Iterateur operator++(int);

        const K &cle() const;
        const V &valeur() const;
        V &valeur();

      private:
        typename ArbreAVL<Entree>::Iterateur iter;
    };
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const K &cle) const;
    Iterateur rechercherEgalOuSuivant(const K &cle) const;
    Iterateur rechercherEgalOuPrecedent(const K &cle) const;
    const V &operator[](const Iterateur &iter) const;
    V &operator[](const Iterateur &iter);

    bool contient(const K &) const;
    void enlever(const K &);
    bool vide() const;
    void vider();
    const V &operator[](const K &) const;
    V &operator[](const K &);
};

template <class K, class V>
void ArbreMap<K, V>::vider()
{
    entrees.vider();
}

template <class K, class V>
bool ArbreMap<K, V>::vide() const
{
    return entrees.vide();
}

template <class K, class V>
void ArbreMap<K, V>::enlever(const K &c)
{
    // À compléter
}

template <class K, class V>
bool ArbreMap<K, V>::contient(const K &cle) const
{
    Entree entree(cle);
    return entrees.contient(entree);
}

template <class K, class V>
const V &ArbreMap<K, V>::operator[](const K &c) const
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
    return entrees[iter].valeur;
}

template <class K, class V>
V &ArbreMap<K, V>::operator[](const K &c)
{
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(Entree(c));
    if (!iter)
    {
        entrees.inserer(Entree(c));
        iter = entrees.rechercher(c);
    }
    return entrees[iter].valeur;
}

template <class K, class V>
typename ArbreMap<K, V>::Iterateur &ArbreMap<K, V>::Iterateur::operator++()
{
    // À compléter.
    return *this;
}

//------------------------ ITERATEURS -------------------------//
template <class K, class V>
const K &ArbreMap<K, V>::Iterateur::cle() const
{
    return (*iter).cle;
}

template <class K, class V>
const V &ArbreMap<K, V>::Iterateur::valeur() const
{
    return (*iter).valeur;
}

template <class K, class V>
V &ArbreMap<K, V>::Iterateur::valeur()
{
    return const_cast<V &>((*iter).valeur);
}

template <class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::debut() const
{
    // return Iterateur(∗this);
}

template <class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::fin() const
{
    return Iterateur(entrees.fin());
}

template <class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::rechercher(const K &cle) const
{
    return Iterateur(entrees.rechercher(cle));
}

template <class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::rechercherEgalOuSuivant(const K &cle) const
{
    return Iterateur(entrees.rechercherEgalOuSuivant(cle));
}

template <class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::rechercherEgalOuPrecedent(const K &cle) const
{
    return Iterateur(entrees.rechercherEgalOuPrecedent(cle));
}

#endif
