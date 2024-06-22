#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

// ============================== DEFINITION DES CLASSES =======================================
class Cellule
{
private:
    bool vivant;

public:
    Cellule(bool);
    Cellule();

    bool get_bool() { return vivant; };
    void set_bool(bool a) { vivant = a; };

    bool test_de_vie(int);
    int number_of_friends();
};
Cellule::Cellule()
{
    vivant = 0;
}
Cellule::Cellule(bool a)
{
    vivant = a;
}
bool Cellule::test_de_vie(int nb_cellules_autours)
{
    if (vivant == false && nb_cellules_autours == 3)
    {
        vivant = true;
    }
    if (vivant == true && nb_cellules_autours < 2 || nb_cellules_autours > 3)
    {
        vivant = false;
    }

    return vivant;
}

class Grille
{
private:
    int longueur;
    int largeur;
    Cellule **element;

public:
    Grille(int, int);
    ~Grille();

    int get_longueur() { return longueur; };
    int get_largeur() { return largeur; };
    Cellule get_element(int i, int j) { return element[i][j]; };
    bool get_etat(int i, int j) { return element[i][j].get_bool(); };
    void set_etat(int i, int j, bool a) { element[i][j].set_bool(a); };
};
Grille::Grille(int xmax, int ymax)
{
    longueur = xmax;
    largeur = ymax;
    // rempli chaques carreaux avec une cellule
    Cellule **elem = new Cellule *[longueur + 2];
    for (int i = 0; i < longueur + 2; i++)
    {
        elem[i] = new Cellule[largeur + 2];
    }
    element = elem;
}
Grille::~Grille()
{
    for (int i = 0; i < longueur; i++)
    {
        delete[] element[i];
    }
    delete[] element;
}

// ============================== FONCTION MAIN =======================================
int main()
{
    ofstream fichier("jeu_vie.txt");
    ofstream fichier2("resultats.txt");
    // true = 1
    int longueur = 50; // nombre de carreaux selon x
    int largeur = 50;  // nombre de carreaux selon y
    int t_max = 1000;   // nombre de tours
    int t = 0;

    Grille grille_passe(longueur, largeur);
    Grille grille_present(longueur, largeur);
    int nb_cellules = 0;

    // permet de générer un nombre aléatoire (soit 1 soit 0)
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);

    // C.I.
    for (int i = 1; i <= longueur; i++)
    {
        for (int j = 1; j <= largeur; j++)
        {
            int random_number = distrib(gen);
            grille_passe.set_etat(i, j, random_number);

            if (grille_passe.get_etat(i, j) == 1)
            {
                fichier << i - 0.5 << "  " << j - 0.5 << endl;
                nb_cellules++;
            }
        }
    }
    fichier << endl
            << endl;
    fichier2 << nb_cellules << "  " << t << endl;

    for (t = 1; t <= t_max; t++)
    {
        nb_cellules = 0;

        for (int i = 1; i <= longueur; i++)
        {
            for (int j = 1; j <= largeur; j++)
            {
                int nb_friends = grille_passe.get_etat(i + 1, j) + grille_passe.get_etat(i + 1, j + 1) + grille_passe.get_etat(i + 1, j - 1) + grille_passe.get_etat(i - 1, j) + grille_passe.get_etat(i - 1, j + 1) + grille_passe.get_etat(i - 1, j - 1) + grille_passe.get_etat(i, j + 1) + grille_passe.get_etat(i, j - 1);
                // cout << i << "  " << j << "  " << nb_friends << endl;

                bool test = grille_passe.get_element(i, j).test_de_vie(nb_friends);

                grille_present.set_etat(i, j, test);

                if (grille_present.get_etat(i, j) == 1)
                {
                    fichier << i + 0.5 << "  " << j + 0.5 << endl;
                    nb_cellules++;
                }

                
            }
        }
        grille_passe = grille_present;
        fichier << endl
                << endl;
        fichier2 << nb_cellules << "  " << t << endl;
    }

    fichier.close();
    fichier2.close();
    return 0;
}