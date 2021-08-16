/*  INF3105 - Structures de données et algorithmes
    Lab 11 -- Graphes / Représentations et algorithmes de base
    http://ericbeaudry.uqam.ca/INF3105/lab11/
*/
#if !defined(__GRAPHE_H__)
#define __GRAPHE_H__

#include <queue>
#include <map>
#include <set>
#include <iostream>

using namespace std;

// Le type S est le type utilisé pour identifier les sommets
template <class S>
class Graphe
{
  public:
    // Interface public pour créer le graphe.
    void ajouterSommet(const S &s);
    void ajouterAreteOrientee(const S &s1, const S &s2);
    void ajouterAreteNonOrientee(const S &s1, const S &s2);

    // Interface public pour les requêtes de base.
    void parcoursRechercheProfondeur(const S &s) const;
    void parcoursProfondeurRec(const S &s) const;
    void parcoursRechercheLargeur(const S &s) const;
    void parcoursLargeurRec(const S &s) const;
    void extraireComposantesConnexes() const;
    void resetVisite() const;

  private:
    struct Sommet
    {
        mutable bool estVisite;
        set<S> voisins; // ensemble des sommets accessibles via les arêtes sortantes du sommet.
    };
    map<S, Sommet> sommets; // identification --> sommet
};

template <class S>
void Graphe<S>::ajouterSommet(const S &s)
{
    sommets[s] = Sommet();
}

// Doit ajouter les 2 arêtes orientées : s1->s2 et s2->s1;
template <class S>
void Graphe<S>::ajouterAreteNonOrientee(const S &s1, const S &s2)
{
    ajouterAreteOrientee(s1, s2);
    ajouterAreteOrientee(s2, s1);
}

// Doit uniquement ajouter s1->s2.
template <class S>
void Graphe<S>::ajouterAreteOrientee(const S &s1, const S &s2)
{
    sommets[s1].voisins.insert(s2);
}

template <class S>
void Graphe<S>::parcoursRechercheProfondeur(const S &s) const
{
    resetVisite();
    parcoursProfondeurRec(s);
    cout << endl;
}

template <class S>
void Graphe<S>::parcoursProfondeurRec(const S &s) const
{
    sommets.at(s).estVisite = true;
    cout << s << " ";

    for (const S &voisin : sommets.at(s).voisins)
    {
        if (!sommets.at(voisin).estVisite)
            parcoursProfondeurRec(voisin);
    }
}

template <class S>
void Graphe<S>::parcoursRechercheLargeur(const S &s) const
{
    resetVisite();

    queue<S> file;
    sommets.at(s).estVisite = true;
    file.push(s);

    while (!file.empty())
    {
        S elem = file.front();
        file.pop();
        cout << elem << " ";

        for (const S &voisin : sommets.at(elem).voisins)
        {
            if (!sommets.at(voisin).estVisite)
            {
                sommets.at(voisin).estVisite = true;
                file.push(voisin);
            }
        }
    }

    cout << endl;
}

template <class S>
void Graphe<S>::extraireComposantesConnexes() const
{
    resetVisite();
    std::cout << "{ ";
    for (const auto &pair : sommets)
    {
        if (pair.second.estVisite)
            continue;
        std::cout << "{ ";
        std::queue<S> file;
        pair.second.estVisite = true;
        file.push(pair.first);
        while (!file.empty())
        {
            S elem = file.front();
            file.pop();
            std::cout << elem << " ";
            const Sommet &sommet = sommets.at(elem);

            for (const S &voisin : sommet.voisins)
                if (!sommets.at(voisin).estVisite)
                {
                    sommets.at(voisin).estVisite = true;
                    file.push(voisin);
                }
        }
        std::cout << "}";
    }
    std::cout << " }" << std::endl;
}

template <class S>
void Graphe<S>::resetVisite() const
{
    for (auto &pair : sommets)
        pair.second.estVisite = false;
}

#endif
