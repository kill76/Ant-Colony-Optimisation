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

ant::ant(datas& data):data(data)
{
    vector<int> tmpIndexesOfCitiesToVisit;
    tmpIndexesOfCitiesToVisit.clear();
    for(int i = 1 ; i< (int)data.getNamesOfCities().size(); i++)
    {
        tmpIndexesOfCitiesToVisit.push_back(i);
    }

    vector<int> tmpIndexesOfCitiesVisited;
    tmpIndexesOfCitiesVisited.clear();
    tmpIndexesOfCitiesVisited.push_back(0);

    indexesOfCitiesToVisit=tmpIndexesOfCitiesToVisit;
    indexesOfCitiesVisited=tmpIndexesOfCitiesVisited;

    distanceTravelled = 0;
    currentPosition=0;
}

ant::~ant(){}

// Getters

vector<int> ant::getIndexesOfCitiesVisited() const {return this->indexesOfCitiesVisited;}
vector<int> ant::getIndexesOfCitiesToVisit() const {return this->indexesOfCitiesToVisit;}
int ant::getDistanceTravelled() const {return this->distanceTravelled;}
int ant::getCurrentPosition() const {return this->currentPosition;}

// Methods

void ant:: initialize()
{
    indexesOfCitiesToVisit.clear();
    for(int i = 1 ; i< (int) this->data.getNamesOfCities().size(); i++)
    {
        indexesOfCitiesToVisit.push_back(i);
    }

    indexesOfCitiesVisited.clear();
    indexesOfCitiesVisited.push_back(0);

    distanceTravelled = 0;
    currentPosition=0;
}

/*
    Add a new city to the indexesOfCitiesToVisit vector.
*/
void ant::pushNewCity(const int aCity) {this->indexesOfCitiesToVisit.push_back(aCity);}

 /*
    Method to find the next city to visit.
    We use probabilities to do so. We compute the probability to go from the current position to each the other cities.
    Once done, we use a roulette : we sum all the probability thus creating a [0;1] interval.
    Then we will pick a random number in this interval and chose the city whose probability is at this number in the interval.

    Example:
    If we have 3 cities of respective probability 0.2,0.3,0.5 then the interval is divided in 3 parts : 0 to 0.2 ; 0.2 to 0.5 ; 0.5 to 1.
    If the random number is 0.4356, we will thus chose the 2nd city.
 */
int ant::findNextCity()
{
    vector<float> probabilities ;

    float denominator=0;

    int cityIndex=currentPosition;
    float alpha=data.getAlpha();
    float beta=data.getBeta();

    // Compute the probabilities to go from the city currentPosition to the cities i
    //*************************************************************
    for (int i = 0 ; i < (int)indexesOfCitiesToVisit.size() ; i++)
    {
        float a = data.getPheromones()[currentPosition][indexesOfCitiesToVisit.at(i)];
        int b = data.getDistances()[currentPosition][indexesOfCitiesToVisit.at(i)];
        float c =  (float ) 1/b;
        denominator+= (float) (pow(a,alpha) * pow (c,beta));
    }

    for (int i = 0 ; i < (int) indexesOfCitiesToVisit.size() ; i++)
    {
        float a = data.getPheromones()[currentPosition][indexesOfCitiesToVisit.at(i)];
        int b = data.getDistances()[currentPosition][indexesOfCitiesToVisit.at(i)];
        float c =  (float ) 1/b;
        float probability= (float) ((pow(a,alpha)) * (pow (c,beta)))/denominator;

        probabilities.push_back(probability);

       // cout << "Probability : "<< probability << " ; City : " <<  indexesOfCitiesToVisit.at(i) << endl;
       // Uncomment to see the whole process of the algorithm
    }
    //*************************************************************

    // We do the "roulette" once the probabilities calculated
    //*************************************************************
        float random = ((float) rand()) / (float) RAND_MAX;
        float counter=0;
        int k=0;
        while (counter<random && k< (int) probabilities.size())
        {
            counter+= probabilities[k];
            k++;
        }
        --k;
    //*************************************************************

        cityIndex=indexesOfCitiesToVisit.at(k);

    return cityIndex;
}

/*
    Method to deposit pheromones on the graph.

    We only alter the PheromonesByIteration as we deposit the pheromones only at the end of an iteration.
*/
void ant::dropPheromone()
{
    for (int i=0 ; i < (int) indexesOfCitiesVisited.size() -1  ; i++)
    {
        float b = (float) 1/distanceTravelled;
        data.setPheromonesByIteration(indexesOfCitiesVisited.at(i),indexesOfCitiesVisited.at(i+1),b);
        data.setPheromonesByIteration(indexesOfCitiesVisited.at(i+1),indexesOfCitiesVisited.at(i),b);
    }
}

/*
    Method telling an ant to go to the next city

    It is in fact simple : we add the cityIndex to the indexesOfCitiesVisited vector and remove it from indexesOfCitiesToVisit.
    Of course, we also modify the distanceTravelled and the currentPosition of the ant.
*/
void ant::moveToNextCity( const int cityIndex)
{
    indexesOfCitiesVisited.push_back(cityIndex);
    distanceTravelled = distanceTravelled + data.getDistances()[currentPosition][cityIndex];
    for (int j= 0 ; j <  (int) indexesOfCitiesToVisit.size() ; j++)
    {
        if (cityIndex == indexesOfCitiesToVisit.at(j))
        {
            indexesOfCitiesToVisit.erase(indexesOfCitiesToVisit.begin()+j);
        }
    }
    currentPosition=cityIndex;
}

ostream& operator<< (ostream &res, const ant & ant )
{
    res << "Indexes of the cities to visit : "  << endl;
    for (int j= 0 ; j < (int) ant.indexesOfCitiesToVisit.size() ; j++)
    {
        int a=ant.indexesOfCitiesToVisit[j];
        res << "- " << a << endl;
    }
    res << "Indexes of the visited cities : " << endl;
    for (int j= 0 ; j < (int)ant.indexesOfCitiesVisited.size() ; j++)
    {
        res  << "- " << ant.indexesOfCitiesVisited[j] << endl;
    }
    res  << "Distance travelled : " << ant.distanceTravelled << endl << "Current position : " << ant.currentPosition << endl;
    return res;
}


