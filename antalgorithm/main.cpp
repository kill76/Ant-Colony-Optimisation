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

#include <fstream>
#include "datas.h"
#include "antSystem.h"


int main(int argc, char **argv)
{
    // We use a data file to enter the parameter of the algorithm
    //*************************************************************
    string filePath="";
    bool OK=false ;

    while (!OK)
    {
        cout << "Enter the absolute file path :" << endl;
        cin >> filePath;
        ifstream tmpFile(filePath.c_str(), ios::in);
        if (tmpFile)
        {
            OK=true;
            tmpFile.close();
        }
        else cerr << "Impossible to open the file, make sure the path is correct." << endl << endl;
    }
    //*************************************************************

    // Declaration of the parameters
    //*************************************************************
    ifstream file(filePath.c_str(), ios::in);

    int nbOfCities = 0;
    vector<vector<int> > distances;
    vector<int> line;
    vector<string> cities;
    int nbOfIterations =0;
    int nbOfAnts =0;
    float alpha=0;
    float beta=0;
    float evaporation=0;
    //*************************************************************


    // As we know how the file is written, we can directly read it to give a value to each parameter
    //*************************************************************
    file>>nbOfCities;
    cout << "Initial data " << endl << "-----------------" << endl;
    cout << "Number of cities : " << nbOfCities << endl;
    for (int i = 0 ; i < nbOfCities ; i++)
    {
        for (int j = 0 ; j < nbOfCities; j++)
        {
            int tmp;
            file >> tmp;
            line.push_back(tmp);
        }
        distances.push_back(line);
        line.clear();
    }

    for (int k = 0 ; k < nbOfCities ; k++)
    {
        string tmp;
        file >> tmp;
        cities.push_back(tmp);
    }

    file >> nbOfIterations;
    file >> nbOfAnts;
    file >> alpha;
    file >> beta;
    file >> evaporation;

    file.close();
    //*************************************************************


    // We print on the screen the value of the parameters read
    //*************************************************************
    cout << "Number of iteration : "<< nbOfIterations << endl << "Number of ants : " << nbOfAnts << endl << "Alpha : " << alpha << endl << "Beta : " << beta << endl << "Evap. Rate : " << evaporation << endl <<endl;

    cout << "Distance matrix :" << endl;
    for (int i = 0 ; i < nbOfCities ; i++)
    {
        for (int j = 0 ; j < nbOfCities; j++)
        {
            cout << " " << distances[i][j];
        }
        cout << endl;
    }
    cout << endl;

    cout << "List of cities : " << endl;
    for (int i = 0 ; i < nbOfCities ; i++)
    {
        cout << "- " << cities[i] << endl;
    }

    cout << "---------------------------" << endl;
    //*************************************************************

    // Initialization of the problem and launch of the algorithm
    //*************************************************************
    datas problem(distances,cities,alpha,beta,evaporation);
    antSystem syst(nbOfAnts, problem);
    syst.run(nbOfIterations);
    //*************************************************************

    // Printing of the solution on the screen
    //*************************************************************

    cout << "---------------------------" << endl << "Best solution : " << syst.getBestSolution() << endl;
    cout << "Best path: ";
    vector<string> orderedCities;
    orderedCities= problem.findCityUsingIndex(syst.getBestPath());
    cout << orderedCities[0];
    for (int i = 1 ; i < (int) orderedCities.size() ; i++)
    {
        cout << " -> " << orderedCities[i];
    }
    //*************************************************************

}
