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
    // Entrée des paramètre via un fichier de données

    string nomfic="";
    bool OK=false ;

    while (!OK)
    {
        cout << "Indiquez le chemin absolu du fichier de donnée :" << endl;
        cin >> nomfic;
        ifstream fic(nomfic.c_str(), ios::in);
        if (fic)
        {
            OK=true;
            fic.close();
        }
        else cerr << "Impossible d'ouvrir le fichier ! Recommencez !" << endl << endl;
    }

    ifstream fichier(nomfic.c_str(), ios::in);

    int nbVille = 0;
    vector<vector<int> > distances;
    vector<int> ligne;
    vector<string> villes;
    int nbIter =0;
    int nbAnt =0;
    float alpha=0;
    float beta=0;
    float evaporation=0;

    fichier>>nbVille;
    cout << "Données initiales " << endl << "-----------------" << endl;
    cout <<  "Nombre de villes : " << nbVille << endl;
    for (int i = 0 ; i < nbVille ; i++)
    {
        for (int j = 0 ; j < nbVille; j++)
        {
            int tmp;
            fichier >> tmp;
            ligne.push_back(tmp);
        }
        distances.push_back(ligne);
        ligne.clear();
    }

    for (int k = 0 ; k < nbVille ; k++)
    {
        string tmp;
        fichier >> tmp;
        villes.push_back(tmp);
    }
    fichier >> nbIter;
    fichier >> nbAnt;
    fichier >> alpha;
    fichier >> beta;
    fichier >> evaporation;

    fichier.close();

    cout << "Nombre d'itération : "<< nbIter << endl << "Nombre de fourmis : " << nbAnt << endl << "Alpha : " << alpha << endl << "Beta : " << beta << endl << "Evap. Rate : " << evaporation << endl <<endl;

    cout << "Matrice des distances :" << endl;
    for (int i = 0 ; i < nbVille ; i++)
    {
        for (int j = 0 ; j < nbVille; j++)
        {
            cout << " " << distances[i][j];
        }
        cout << endl;
    }
    cout << endl;

    cout << "Liste des villes : " << endl;
    for (int i = 0 ; i < nbVille ; i++)
    {
        cout << "- " << villes[i] << endl;
    }

    cout << "---------------------------" << endl;

    // Initialisation des classes et lancement de l'algorithme

    datas probleme(distances,villes,alpha,beta,evaporation);
    antSystem syst(nbAnt, probleme);
    syst.run(nbIter);

    // Affichage de la solution

    cout << "---------------------------" << endl << "Meilleure Distance : " << syst.getMeilleureSolution() << endl;
    cout << "Meilleur Trajet : ";
    vector<string> villesOrdonnee;
    villesOrdonnee= probleme.chercherVilleViaIndice(syst.getMeilleurTrajet());
    cout << villesOrdonnee[0];
    for (int i = 1 ; i < (int) villesOrdonnee.size() ; i++)
    {
        cout << " -> " << villesOrdonnee[i];
    }

}
