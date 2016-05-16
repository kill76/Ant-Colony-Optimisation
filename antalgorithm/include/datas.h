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
    vector<string> getNomsVilles() const;
    vector<vector<float> > getPheromones() const;
    vector<vector<float> > getPheromonesParIteration() const;
    vector<vector<int> > getDistances() const;
    float getAlpha() const;
    float getBeta() const;
    void setPheromonesParIteration (const int,const int ,const float);

    // Methods
    void evaporate();
    vector<string> chercherVilleViaIndice(vector<int>);
private:
    vector<vector<float> > pheromonesParIteration;
    vector<vector<float> > pheromones;
    vector<vector<int> > distances;
    vector<string>  nomsVilles;
    float alpha;
    float beta ;
    float evaporation;
};

#endif // DATAS_H
