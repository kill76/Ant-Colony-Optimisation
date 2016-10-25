#include "datas.h"

// Constructor / Destructor

datas::datas(const vector<vector<int> > dist , const vector<string> citiesNames, const float a , const float b, const float e )
{
    distances=dist;
    namesOfCities= citiesNames;
    vector<vector<float> > tmpPheromones;
    vector<float> tmp;
    for (int j= 0 ; j< (int) citiesNames.size(); j++)
    {
        tmp.push_back(1);
    }
    for (int i = 0 ; i < (int)citiesNames.size(); i++)
    {
        tmpPheromones.push_back(tmp);
    }

    pheromones=tmpPheromones;
    pheromonesByIteration=pheromones;

    alpha =a;
    beta= b;
    evaporation=e;
}

datas::~datas(){}

// Getters / Setter

vector<string> datas::getNamesOfCities() const {return this->namesOfCities;}
vector<vector<float> >  datas::getPheromones() const {return this->pheromones;}
vector<vector<int> > datas::getDistances() const {return this->distances;}
float datas::getAlpha() const {return this->alpha;}
float datas::getBeta() const {return this->beta;}
vector<vector<float> > datas::getPheromonesByIteration() const {return this->pheromonesByIteration;}

void datas::setPheromonesByIteration(const int i, const int j,  const float value)
{
    this->pheromonesByIteration[i][j]+= value;
}

// Methods

/*
    Method to evaporate the pheromones.
*/
void datas::evaporate()
{
    for (int i=0; i<int(namesOfCities.size()); i++)
        for (int j=0; j<(int)namesOfCities.size(); j++)
        {
            float a = this->pheromonesByIteration[i][j];
            pheromones[i][j] = float(pheromones[i][j]*(1-evaporation) + a);  // Formule donné dans les règles de l'algorithme
            pheromones[j][i] = pheromones[i][j];
        }
}

/*
    This method allow us to find the names of the cities according to their index.

    This is mainly use to find the names of cities visited by an ant in order to print correctly the path it travelled.
*/
vector<string> datas::findCityUsingIndex(vector<int> citiesIndexes)
{
    vector<string> orderedCities;
    for (int i = 0 ; i<(int)citiesIndexes.size(); i++)
    {
        orderedCities.push_back(this->namesOfCities.at(citiesIndexes.at(i)));
    }

    return orderedCities;
}


