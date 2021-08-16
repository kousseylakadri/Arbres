/* UQAM / Département d'informatique
   INF3105 - Structures de données et algorithmes
   Squelette pour classe générique Tableau<T> pour le TP1 et Lab3.

   AUTEUR(S):
    1) Nom + Code permanent du l'étudiant.e 1
    2) Nom + Code permanent du l'étudiant.e 2
*/

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>
#include <iostream>

template <class T>
class Tableau {

public:
    Tableau(int capacite_initiale = 4);
    Tableau(const Tableau&);
    ~Tableau();

    // Ajouter un element à la fin
    void ajouter(const T& element);
    // Vider le tableau
    void vider();
    // Retourne le nombre d'éléments dans le tableau
    int taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void inserer(const T& element, int index = 0);

    // Enlève l'element à position index. Les éléments après index sont décalés d'une position après.
    void enlever(int index = 0);

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int chercher(const T& element);

    // Redimensionne le tableau
    void redimensionner(int newCapacite);

    const T&
    operator[](int index) const;
    T& operator[](int index);

    bool operator==(const Tableau<T>& autre) const;
    Tableau<T>& operator=(const Tableau<T>& autre);

private:
    T* elements;
    int nbElements;
    int capacite;
};

// ---------- Définitions -------------

template <class T>
Tableau<T>::Tableau(int capacite_)
{
    elements = new T[capacite_];
    capacite = capacite_;
    nbElements = 0;
}

template <class T>
Tableau<T>::Tableau(const Tableau& autre)
{
    elements = new T[autre.capacite];
    capacite = autre.capacite;
    nbElements = autre.nbElements;
    for (int i = 0; i < capacite; i++)
        elements[i] = autre.elements[i];
}

template <class T>
Tableau<T>::~Tableau()
{
    delete[] elements;
}

template <class T>
int Tableau<T>::taille() const
{
    return nbElements;
}

template <class T>
void Tableau<T>::ajouter(const T& item)
{
    if (nbElements == capacite)
        redimensionner(capacite * 2);
    elements[nbElements++] = item;
}

template <class T>
void Tableau<T>::redimensionner(int newCapacite)
{
    T* temp = new T[newCapacite];
    for (int i = 0; i < capacite; i++)
        temp[i] = elements[i];
    delete[] elements;
    capacite = newCapacite;
    elements = temp;
}

template <class T>
void Tableau<T>::inserer(const T& element, int index)
{
    if (nbElements == capacite)
        redimensionner(capacite * 2);
    for (int i = nbElements; i > index; --i)
        elements[i] = elements[i - 1];
    elements[index] = element;
    ++nbElements;
}

template <class T>
void Tableau<T>::enlever(int index)
{
    for (int i = index; i < nbElements - 1; ++i)
        elements[i] = elements[i + 1];
    --nbElements;
}

template <class T>
int Tableau<T>::chercher(const T& element)
{
    int index = -1;

    for (int i = 0; i < nbElements; i++) {
        if (elements[i] == element)
            index = i;
    }

    return index;
}

template <class T>
void Tableau<T>::vider()
{
    nbElements = 0;
    capacite = 1;
    delete[] elements;
}

template <class T>
const T& Tableau<T>::operator[](int index) const
{
    return elements[index];
}

template <class T>
T& Tableau<T>::operator[](int index)
{
    return elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator=(const Tableau<T>& autre)
{
    if (this == &autre)
        return *this;

    nbElements = autre.nbElements;
    if (capacite < autre.capacite) {
        delete[] elements;
        capacite = autre.capacite;
        elements = new T[capacite];
    }
    for (int i = 0; i < nbElements; i++)
        elements[i] = autre[i];
    return *this;
}

template <class T>
bool Tableau<T>::operator==(const Tableau<T>& autre) const
{
    bool equals = true;
    if (nbElements == autre.nbElements)
        for (int i = 0; i < nbElements; i++) {
            if (!(elements[i] == autre.elements[i]))
                equals = false;
        }
    else
        equals = false;
    return equals;
}

#endif //define _TABLEAU___H_
