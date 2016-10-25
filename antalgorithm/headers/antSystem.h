#ifndef ANTSYSTEM_H
#define ANTSYSTEM_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif // VECTOR

#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif // IOSTREAM

#include "ant.h"

class antSystem
{
public:
    // Constructor / Destructor
    antSystem(const int, datas&);
    virtual ~antSystem();

    // Getters
    int getBestSolution() const;
    vector<int> getBestPath() const;

    // Methods
    void run(const int);

private:
    vector<ant*> population;

    vector<int> bestPath;
    int bestSolution;

    datas& data;
};

#endif // ANTSYSTEM_H
