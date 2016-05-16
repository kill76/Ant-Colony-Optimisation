#include "datas.h"

// Constructor / Destructor

datas::datas(const vector<vector<int> > dist , const vector<string> nV, const float a , const float b, const float e )
{
    distances=dist;
    nomsVilles= nV;
    vector<vector<float> > pheromones2;
    vector<float> tmp;
    for (int j= 0 ; j< (int) nV.size(); j++)
    {
        tmp.push_back(1);
    }
    for (int i = 0 ; i < (int)nV.size(); i++)
    {
        pheromones2.push_back(tmp);
    }

    pheromones=pheromones2;
    pheromonesParIteration=pheromones;

    alpha =a;
    beta= b;
    evaporation=e;
}

datas::~datas(){}

// Getters / Setter

vector<string> datas::getNomsVilles() const {return this->nomsVilles;}
vector<vector<float> >  datas::getPheromones() const {return this->pheromones;}
vector<vector<int> > datas::getDistances() const {return this->distances;}
float datas::getAlpha() const {return this->alpha;}
float datas::getBeta() const {return this->beta;}
vector<vector<float> > datas::getPheromonesParIteration() const {return this->pheromonesParIteration;}

void datas::setPheromonesParIteration(const int i, const int j,  const float value)
{
    this->pheromonesParIteration[i][j]+= value;
}

// Methods

/** \brief Méthode d'évaporation des phéromones
 * \details On évapore les phéromones selon la formule inscrite dans les règles de l'algorithme.
 * \return void
 */
void datas::evaporate()
{
    for (int i=0; i<int(nomsVilles.size()); i++)
        for (int j=0; j<(int)nomsVilles.size(); j++)
        {
            float a = this->pheromonesParIteration[i][j];
            pheromones[i][j] = float(pheromones[i][j]*(1-evaporation) + a);  // Formule donné dans les règles de l'algorithme
            pheromones[j][i] = pheromones[i][j];
        }
}

/** \brief Méthode permettant de retrouver une liste de nom de ville à partir de leurs indices initiaux.
 * \param indsVille Vecteur d'indices de villes
 * \details Cette méthode est surtout utilisée pour retrouver les noms des villes visitées par une fourmi afin de pouvoir afficher correctement le trajet parcouru.
 * \return vector<string> Vecteur des noms des villes correspondantes
 *
 */
vector<string> datas::chercherVilleViaIndice(vector<int> indsVille)
{
    vector<string> villesOrdonnee;
    for (int i = 0 ; i<(int)indsVille.size(); i++)
    {
        villesOrdonnee.push_back(this->nomsVilles.at(indsVille.at(i)));
    }

    return villesOrdonnee;
}


