#ifndef ANT_H
#define ANT_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif // VECTOR

#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif // IOSTREAM
#include "datas.h"

#ifndef STD
#define STD
using namespace std;
#endif // STD

class ant
{
public:
     // Constructor / Destructor
    ant(datas& d);
    virtual ~ant();

    // Getters
    vector<int> getIndicesVillesVisitees() const;
    vector<int> getIndicesVillesAVisiter() const;
    int getDistanceParcourue() const;
    int getCurrentPos() const;

    // Methods
    void pushNouvelleVille (const int);

    int chercherProchaineVille();
    void avancerVille( const int);
    void deposerPheromone();
    void initialiser();

    // Override
    friend std::ostream& operator<< (std::ostream &, const ant &);
private:
    vector<int>  indicesVillesVisitees;
    vector<int>  indicesVillesAVisiter;

    int distanceParcourue;
    int currentPos;

    datas& donnees;

};

#endif // ANT_H
