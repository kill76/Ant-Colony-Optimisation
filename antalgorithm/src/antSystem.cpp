#include "antSystem.h"
#include "ant.h"

// Constructor / Destructor

antSystem::antSystem(const int nbAnt, datas& donnees):dat(donnees)
{
    vector<ant*> pop;
    pop.clear();
    for (int i = 0 ; i <nbAnt; i++)
    {
        pop.push_back(new ant(donnees));
    }

    vector<int> meilleurTrajet2;
    for (int i = 0 ; i <nbAnt; i++)
    {
        meilleurTrajet2.push_back(i);
    }
    meilleurTrajet=meilleurTrajet2;
    population=pop;

    meilleureSolution= 999999999;

}

antSystem::~antSystem()
{
    for (std::vector<ant*>::iterator it = population.begin() ; it != population.end(); ++it)
    {
        delete *it;
    }
}

// Getters

int antSystem::getMeilleureSolution() const {return this->meilleureSolution;}
vector<int> antSystem::getMeilleurTrajet() const {return this->meilleurTrajet;}

// Methods

/** \brief Méthode principale de l'algorithme
 * \details C'est dans cette méthode que l'on déroule l'algorithme défini dans la partie "Presentation de l'algorithme" du rapport.
 * \param nbIter Le nombre d'itération (=temps) que les fourmi doivent parcourir le graphe.
 * \return void
 *
 */
void antSystem::run(const int nbIter)
{

    for (int k= 0 ; k < nbIter ; k++)
    {
        cout << "---------------------------" << endl;
        cout << "Itération : " << k+1 << endl;
        for (int i = 0 ; i<(int) population.size(); i++)
        {
            cout << "Fourmi : " << i+1 << endl;
            bool chang = false;
            ant* a = population.at(i);
           // cout << (*a);
            while (!(a->getIndicesVillesAVisiter().empty()))
            {
                int tmp = (a)->chercherProchaineVille();

                (a)->avancerVille(tmp);
               // cout << "---------------------------" << endl <<"Avancement de la fourmi : " << "indice de la ville choisie : " << tmp << endl << (*a) << endl;
                if ((a->getIndicesVillesAVisiter().empty()) && chang == false)  // Ce bloc permet d'ajouter la ville de depart aux villes à visiter, une fois que toutes
                {                                                               // les autres l'ont été, si cela n'a pas déjà été fait une fois. On cela pour pouvoir
                    a->pushNouvelleVille(0);                                    // répondre correctement au probleme du voyageur de commerce.
                    chang = true;
                }
            }
            int distance = a->getDistanceParcourue();

            if (distance < meilleureSolution)
            {
                meilleureSolution=distance;
                meilleurTrajet= a->getIndicesVillesVisitees();
            }
            (a)->deposerPheromone();
            (a)->initialiser();
        }
        if (k%10 == 0) {this->dat.evaporate();};      // Nous avons choisis d'évaporer les phéromones toutes les 10 itérations afin
                                                      // d'obtenir des resultats assez biaisés par les pheromones.
    }
}
