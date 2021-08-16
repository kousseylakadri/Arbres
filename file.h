/*
  INF3105 - Structures de donn?es et algorithmes
  UQAM / D?partement d'informatique
*/

#if !defined(__FILE_H__)
#define __FILE_H__

template <class T>
class File {
public:
    File();
    ~File();

    void enfiler(const T&);
    T defiler();
    void defiler(T&);
    bool vide() const { return queue == NULL; }

private:
    class Cellule {
    public:
        Cellule(const T& e, Cellule* c = NULL);
        T element;
        Cellule* suivante;
    };

    Cellule* queue;
};

/*
 Puisque File<T> est une classe g?n?rique, toutes ses d?finitions doivent ?tre
 inclues apr?s les d?clarations. On peut quand m?me s?parer les d?clarations et
 les d?finitions en deux fichiers (file.h et file.hcc), ? condition d'inclure le
 deuxi?me (file.hcc) ? la fin du premier (file.h). Ainsi, un fichier source
 (.cc, .cpp, c++) qui inclut file.h inclura indirectement aussi file.hcc.

*/

//#include "file.hcc"
/**** D?but des d?finitions pouvant ?tre mises dans file.hcc. ****/

// Les deux directives suivante sont utiles lorsqu'un fichier file.hcc est utilis?.
#if !defined(__FILE_HCC__)
#define __FILE_HCC__

#include <assert.h>

template <class T>
File<T>::File()
{
    queue = NULL;
}

template <class T>
File<T>::~File()
{
    while (!vide())
        defiler();
}

template <class T>
File<T>::Cellule::Cellule(const T& e, Cellule* c)
    : element(e)
    , suivante(c)
{
}

template <class T>
void File<T>::enfiler(const T& e)
{
    if (queue == NULL) {
        queue = new Cellule(e);
        queue->suivante = queue;
    } else {
        queue = queue->suivante = new Cellule(e, queue->suivante);
    }
}

template <class T>
T File<T>::defiler()
{
    assert(queue != NULL);

    Cellule* aEnlever = queue->suivante;
    if (queue == queue->suivante)
        queue = NULL;
    else
        queue->suivante = aEnlever->suivante;

    T result = aEnlever->element;
    delete aEnlever;
    return result;
}

template <class T>
void File<T>::defiler(T& r)
{
    // ? compl?ter.
}

// Ce #endif est utile si mis dans file.hcc
#endif
/**** Fin des d?finitions pouvant ?tre mises dans file.hcc. ****/

#endif
