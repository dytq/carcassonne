#include "Paysan.hpp"
#include "Chevalier.hpp"

Paysan::Paysan(Joueur * joueur, Noeud * noeud)
{
    Meeple::joueur = joueur;
    Meeple::noeud = noeud;

}

bool est_complet(std::list<Noeud*> ville_marque, Noeud * noeud_courant)
{
    if(noeud_courant == nullptr) {
        return false;
    }

    bool etat_complet = true;
    int i;
    for(i = 0; i <  noeud_courant->get_nbr_voisins(); i++)
    {
        Noeud * noeud_voisin = noeud_courant->noeud_fils(nullptr, i);

        if(std::find(ville_marque.begin(), ville_marque.end(), noeud_voisin) == ville_marque.end())
        {
            ville_marque.push_back(noeud_voisin);
            etat_complet = est_complet(ville_marque, noeud_courant);
        }
    }
    return etat_complet;
}

/**
 * Algoritme de comptage pour un Paysan
 *
 * On fait un parcours en profondeur du réseau:
 * - Si on a un près alors on fait les vérifications necessaire (si il y un meeple on l'ajoute dans la map Joueur/Meeple)
 * - Si on a une ville:
 *  - On regarde si elle a été traité,
 *  - Si oui on passe au noeud suivant
 *  - Sinon on regarde si c'est une ville complète et on ajoute les points
 * */
bool Paysan::compter_points(int status_du_jeu, std::map<Joueur *, std::list<Meeple *>> mapJoueurListeMeeple, int *score)
{
    if(status_du_jeu == STATUS_EN_COURS)
    {
        return false;
    }

    std::list<Noeud *> ville_marque;

    Noeud * noeud_courant = this->noeud;
    // manque le parcour du graphe noeud
    if(noeud_courant->get_type_element() == Noeud::VILLE &&
       std::find(ville_marque.begin(), ville_marque.end(), noeud_courant) == ville_marque.end())
    {
        if(est_complet(ville_marque, noeud_courant))
        {
            *score = *score + POINTS_PAYSANS;
        }
    }

    return true;
}