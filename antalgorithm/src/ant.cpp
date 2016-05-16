#include "ant.h"

#ifndef CMATH
#define CMATH
#include <cmath>
#endif // CMATH

#ifndef STRING
#define STRING
#include <string>
#endif // STRING

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif // IOSTREAM

#ifndef STDLIB
#define STDLIB
#include <stdlib.h> /* srand, rand */
#endif // STDLIB

// Constructor / Destructor

ant::ant(datas& d):donnees(d)
{
    vector<int> indicesVillesAVisiterTemp;
    indicesVillesAVisiterTemp.clear();
    for(int i = 1 ; i< (int)d.getNomsVilles().size(); i++)
    {
        indicesVillesAVisiterTemp.push_back(i);
    }

    vector<int> indicesVillesVisitees2;
    indicesVillesVisitees2.clear();
    indicesVillesVisitees2.push_back(0);

    indicesVillesAVisiter=indicesVillesAVisiterTemp;
    indicesVillesVisitees=indicesVillesVisitees2;

    distanceParcourue = 0;
    currentPos=0;
}

ant::~ant(){}

// Getters

vector<int> ant::getIndicesVillesVisitees() const {return this->indicesVillesVisitees;}
vector<int> ant::getIndicesVillesAVisiter() const {return this->indicesVillesAVisiter;}
int ant::getDistanceParcourue() const {return this->distanceParcourue;}
int ant::getCurrentPos() const {return this->currentPos;}

// Methods

void ant:: initialiser()
{
    indicesVillesAVisiter.clear();
    for(int i = 1 ; i< (int) this->donnees.getNomsVilles().size(); i++)
    {
        indicesVillesAVisiter.push_back(i);
    }
    indicesVillesVisitees.clear();
    indicesVillesVisitees.push_back(0);

    distanceParcourue = 0;
    currentPos=0;
}

/** \brief Méthode ajoutant une nouvelle ville à indicesVillesAVisiter
 * \param a Indice de la ville à ajouter
 * \return void
 */
void ant::pushNouvelleVille(const int a) {this->indicesVillesAVisiter.push_back(a);}

/** \brief Méthode permettant de trouver la prochaine ville à visiter.
 * \details On fonctionne dans cette méthode avec des probabilités. On calcul la probabilité d'aller de la position courrante à toutes les autres villes non visitées.
 * Une fois que l'on a calculé toutes les probabilités, on effectue une roulette - à la manière d'un algorithme génétique. On additionne les probabilités de toutes les villes,
 * ce qui va créer un intervalle [0;1]. On va alors choisir un nombre aléatoire dans cet intervalle [0;1], et prendre la ville dont la probabilité se situe à cet endroit dans l'intervalle.
 * \return int Indice de la ville choisie
 *
 */
int ant::chercherProchaineVille()
{
    vector<float> probas ;

    float denominateur=0;

    int indV=currentPos;
    float alpha=donnees.getAlpha();
    float beta=donnees.getBeta();

   // Calcul des probabilité d'aller de la ville currPos aux villes i

    for (int i = 0 ; i < (int)indicesVillesAVisiter.size() ; i++)
    {
        float a = donnees.getPheromones()[currentPos][indicesVillesAVisiter.at(i)];
        int b = donnees.getDistances()[currentPos][indicesVillesAVisiter.at(i)];
        float c =  (float ) 1/b;
        denominateur+= (float) (pow(a,alpha) * pow (c,beta));
    }

    for (int i = 0 ; i < (int) indicesVillesAVisiter.size() ; i++)
    {
        float a = donnees.getPheromones()[currentPos][indicesVillesAVisiter.at(i)];
        int b = donnees.getDistances()[currentPos][indicesVillesAVisiter.at(i)];
        float c =  (float ) 1/b;
        float proba= (float) ((pow(a,alpha)) * (pow (c,beta)))/denominateur;

        probas.push_back(proba);

       // cout << "Proba : "<< proba << " ; Ville : " <<  indicesVillesAVisiter.at(i) << endl;
    }

    // On effectue une roulette une fois toutes les probabilités calculées

        float random = ((float) rand()) / (float) RAND_MAX;
        float cont=0;
        int k=0;
        while (cont<random && k< (int) probas.size())
        {
            cont+= probas[k];
            k++;
        }
        --k;

        indV=indicesVillesAVisiter.at(k);

    return indV;
}

/** \brief Méthode de dépose des phéromones
 * \details On modifie ici les pheromonesParIteration puisque l'on dépose des phéromones uniquement à la fin d'une itération.
 * \return void
 */
void ant::deposerPheromone()
{
    for (int i=0 ; i < (int) indicesVillesVisitees.size() -1  ; i++)
    {
        float b = (float) 1/distanceParcourue;
        donnees.setPheromonesParIteration(indicesVillesVisitees.at(i),indicesVillesVisitees.at(i+1),b);
        donnees.setPheromonesParIteration(indicesVillesVisitees.at(i+1),indicesVillesVisitees.at(i),b);
    }
}

/** \brief Méthode donnant l'ordre à une fourmi d'avancer
 * \param indVille Ville dans laquelle la fourmi doit aller
 * \details Cet ordre se traduit simplement par le fait d'ajouter la ville en paramètre au vecteur indicesVillesVisitees et de l'enlever au vecteur indicesVillesAVisiter.
 * \return void
 */
void ant::avancerVille( const int indVille)
{
    indicesVillesVisitees.push_back(indVille);
    distanceParcourue = distanceParcourue + donnees.getDistances()[currentPos][indVille];
    for (int j= 0 ; j <  (int) indicesVillesAVisiter.size() ; j++)
    {
        if (indVille == indicesVillesAVisiter.at(j))
        {
            indicesVillesAVisiter.erase(indicesVillesAVisiter.begin()+j);
        }
    }
    currentPos=indVille;
}

ostream& operator<< (ostream &res, const ant & fourmi )
{
    res << "Indices des villes à visiter : "  << endl;
    for (int j= 0 ; j < (int) fourmi.indicesVillesAVisiter.size() ; j++)
    {
        int a=fourmi.indicesVillesAVisiter[j];
        res << "- " << a << endl;
    }
    res << "Indices des villes visitées : " << endl;
    for (int j= 0 ; j < (int)fourmi.indicesVillesVisitees.size() ; j++)
    {
        res  << "- " << fourmi.indicesVillesVisitees[j] << endl;
    }
    res  << "Distance parcourue : " << fourmi.distanceParcourue << endl << "Position  actuelle : " << fourmi.currentPos << endl;
    return res;
}


