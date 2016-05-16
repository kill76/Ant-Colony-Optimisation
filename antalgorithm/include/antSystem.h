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
    int getMeilleureSolution() const;
    vector<int> getMeilleurTrajet() const;

    // Methods
    void run(const int);

private:
    vector<ant*> population;

    vector<int> meilleurTrajet;
    int meilleureSolution;

    datas& dat;
};

#endif // ANTSYSTEM_H
