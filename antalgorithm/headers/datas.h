#ifndef DATAS_H
#define DATAS_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif // VECTOR

#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif // IOSTREAM

#ifndef STD
#define STD
using namespace std;
#endif // STD

class datas
{
public:
    // Constructor / Destructor
    datas(const vector<vector<int> > , const vector<string> , const float , const float, const float);
    virtual ~datas();

    // Getters / Setters
    vector<string> getNamesOfCities() const;
    vector<vector<float> > getPheromones() const;
    vector<vector<float> > getPheromonesByIteration() const;
    vector<vector<int> > getDistances() const;
    float getAlpha() const;
    float getBeta() const;
    void setPheromonesByIteration (const int,const int ,const float);

    // Methods
    void evaporate();
    vector<string> findCityUsingIndex(vector<int>);
private:
    vector<vector<float> > pheromonesByIteration;
    vector<vector<float> > pheromones;
    vector<vector<int> > distances;
    vector<string>  namesOfCities;
    float alpha;
    float beta ;
    float evaporation;
};

#endif // DATAS_H
