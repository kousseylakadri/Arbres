/* #include ... */

#include <iostream> // pour std::cout 
#include <string>   // pour std::string 
#include <vector>
using namespace std;
class Graphe{
  public:
    void ajouterSommet(string s); // allègement «const string&» ==> «string».
    void ajouterArete(string d, string a, int poids);
    int  mystere(string orig, string dest) const;
  private:
    struct Sommet;
    struct Arete{
        const Sommet* arrivee;
        int poids;
    };
    struct Sommet{
        string nom;
        vector<Arete> as; // arêtes sortantes
        mutable bool envisite=false;
    };
    vector<Sommet> sommets;
    int getIndice(string nom) const;
    int mystere2(const Sommet*orig, const Sommet*dest, int l=0) const;
};
void Graphe::ajouterSommet(string nom){
    Sommet s;
    s.nom=nom;
    sommets.push_back(s);
}
int Graphe::getIndice(string nom) const{
    for(int i=0;i<sommets.size();i++)
        if(sommets[i].nom==nom)
            return i;
    return -1;
}
void Graphe::ajouterArete(string depart, string arrivee, int p){
    Arete a { &(sommets[getIndice(arrivee)]), p };
    sommets[getIndice(depart)].as.push_back(a);
}
int Graphe::mystere(string orig, string dest) const{
    return mystere2(&(sommets[getIndice(orig)]), &(sommets[getIndice(dest)]));
}
int Graphe::mystere2(const Sommet*orig, const Sommet*dest, int longueur) const{
    if(orig==dest)
        return longueur;
    int minl = 1000; // 1000, est-ce un bon choix ?
    if(orig->envisite)
        return minl;
    orig->envisite=true;  //marque le sommet "en visite"
    for(vector<Arete>::const_iterator i=orig->as.begin();i!=orig->as.end();++i){
        int l2 = mystere2(i->arrivee, dest, longueur + i->poids);
        if(l2 < minl)
            minl = l2;
    }
    orig->envisite=false; //démarque le sommet "en visite"
    return minl;
}
int main(){
    //Exemple d'usage de Graphe
    Graphe g;
    g.ajouterSommet("a"); g.ajouterSommet("b");
    g.ajouterSommet("c"); g.ajouterSommet("d");
    g.ajouterArete("a","b",2); g.ajouterArete("a","c",6);
    g.ajouterArete("b","c",3); g.ajouterArete("c","a",3);
    cout << g.mystere("a", "c") << endl
         << g.mystere("d", "c") << endl;
}