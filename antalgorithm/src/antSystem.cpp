#include "antSystem.h"
#include "ant.h"

// Constructor / Destructor

antSystem::antSystem(const int nbAnt, datas& data):data(data)
{
    vector<ant*> pop;
    pop.clear();
    for (int i = 0 ; i <nbAnt; i++)
    {
        pop.push_back(new ant(data));
    }

    vector<int> tmpBestPath;
    for (int i = 0 ; i <nbAnt; i++)
    {
        tmpBestPath.push_back(i);
    }
    bestPath=tmpBestPath;
    population=pop;

    bestSolution= 999999999;

}

antSystem::~antSystem()
{
    for (std::vector<ant*>::iterator it = population.begin() ; it != population.end(); ++it)
    {
        delete *it;
    }
}

// Getters

int antSystem::getBestSolution() const {return this->bestSolution;}
vector<int> antSystem::getBestPath() const {return this->bestPath;}

// Methods


/*
    Main method of the algorithm.
*/
void antSystem::run(const int nbOfIterations)
{

    for (int k= 0 ; k < nbOfIterations ; k++)
    {
        cout << "---------------------------" << endl;
        cout << "Iteration : " << k+1 << endl;
        for (int i = 0 ; i<(int) population.size(); i++)
        {
            cout << "Ant : " << i+1 << endl;
            bool chang = false;
            ant* a = population.at(i);
           // cout << (*a);
            while (!(a->getIndexesOfCitiesToVisit().empty()))
            {
                int tmp = (a)->findNextCity();

                (a)->moveToNextCity(tmp);
               // cout << "---------------------------" << endl <<"Progress of the ant : " << "index of the chosen city : " << tmp << endl << (*a) << endl;
               // Uncomment to see the whole process of the algorithm


               /* The following instructions add the starting city to the city to visit once all the others were visited,
                  if it had not be done already. We do this to answer correctly to the TSP.
               */
               //*************************************************************
                if ((a->getIndexesOfCitiesToVisit().empty()) && chang == false)
                {
                    a->pushNewCity(0);
                    chang = true;
                }
                //*************************************************************

            }
            int distance = a->getDistanceTravelled();

            if (distance < bestSolution)
            {
                bestSolution=distance;
                bestPath= a->getIndexesOfCitiesVisited();
            }
            (a)->dropPheromone();
            (a)->initialize();
        }
        if (k%10 == 0) {this->data.evaporate();};
        /*
            We chose to evaporate the pheromones each 10 iteration in order to have a solution biased quite heavily by the pheromones
            This can be chosen as variable defined by the user in a next version of this program.
        */
    }
}
