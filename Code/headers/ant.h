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
    ant(datas&);
    virtual ~ant();

    // Getters
    vector<int> getIndexesOfCitiesVisited() const;
    vector<int> getIndexesOfCitiesToVisit() const;
    int getDistanceTravelled() const;
    int getCurrentPosition() const;

    // Methods
    void pushNewCity (const int);

    int findNextCity();
    void moveToNextCity( const int);
    void dropPheromone();
    void initialize();

    // Override
    friend std::ostream& operator<< (std::ostream &, const ant &);
private:
    vector<int>  indexesOfCitiesVisited;
    vector<int>  indexesOfCitiesToVisit;

    int distanceTravelled;
    int currentPosition;

    datas& data;

};

#endif // ANT_H
