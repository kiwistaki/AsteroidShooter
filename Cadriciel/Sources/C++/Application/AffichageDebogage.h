//////////////////////////////////////////////////////////////////////////////
/// @file AffichageDebogage.h
/// @author Vincent Longpre
/// @date 2014-02-25
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _AFFICHAGE_DEBOGAGE_H_
#define _AFFICHAGE_DEBOGAGE_H_

#include <string>
#include "aiVector3D.h"
#include "../Arbre/Noeuds/NoeudPortail.h"
#include "../Arbre/Noeuds/NoeudAsteroide.h"
#include "../ElementObjet/VaisseauVirtuel.h"
#include "Carte.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
/// @class AffichageDebogage
/// @brief Classe permettant d'afficher a l'ecran et a la console des
///			informations concernant la partie en cours. Cette classe
///			implémente le patron singleton.
///
/// @author Vincent Longpre
/// @date 2014-02-25
///////////////////////////////////////////////////////////////////////////
class AffichageDebogage
{
public:
	// Permet d'obtenir l'instance unique de la classe
	static AffichageDebogage* obtenirInstance();

	// Permet d'afficher a la console une informations horodatee concernant
	// l'apparition d'un asteroide
	// @param position La position d'apparition de l'asteroide
	// @param vitesse La vitesse de l'asteroide
	// @param taille La taille de l'asteroide
	void afficherApparitionAsteroide(aiVector3D position, aiVector3D vitesse, unsigned int taille) const;

	// Permet d'afficher a la console une information horodatee concernant
	// le changement le mode du joueur virtuel
	// @param mode Le mode dans lequel le joueur virtuel se trouve
	void afficherChangementModeJoueurVirtuel(Mode mode) const;

	// Permet d'afficher a la console une information horodatee concernant le
	// changement d'etat d'un element de l'eclairage
	// @param typeLumiere Le type de lumiere qui vient d'etre modifiee
	// @param etatActuel L'etat de la lumiere
	void afficherModificationEclairage(unsigned int typeLumiere, bool etatActuel) const;

	// Permet d'afficher le rayon d'attraction des portails
	// @param nPortail Le portail autour duquel afficher son rayon
	void afficherRayonAttraction(const NoeudPortail* nPortail) const;

	// Permet d'afficher l'asteroide cible du joueur virtuel
	void afficherAsteroideCibleJoueurVirtuel(const NoeudAsteroide* nAsteroide) const;

	// Permet d'afficher la zone de passage des asteroides
	void afficherZonePassage(const Carte* carte) const;

	// Permet d'afficher le cadre de depart
	void afficherCadreDepart(const Carte* carte) const;

	// Permet de determiner si l'apparition d'un asteroide est affiche a la console
	// @param affichage Si l'on doit afficher ou non
	void setAfficherApparitionAsteroide(bool affichage);

	// Permet de determiner si le changement de mode du joueur virtuel est affiche a la console
	// @param affichage Si l'on doit afficher ou non
	void setAfficherChangementModeJoueurVirtuel(bool affichage);

	// Permet de determiner si la modification de l'eclairage est affichee a la console
	// @param affichage Si l'on doit afficher ou non
	void setAfficherModificationEclairage(bool affichage);

	// Permet de determiner si le rayon d'attraction des portails est affiche
	// @param affichage Si l'on doit afficher ou non
	void setAfficherRayonAttraction(bool affichage);

	// Permet de determiner si l'asteroide cible du joueur virtuel est affiche ou non
	// @param affichage Si l'on doit afficher ou non
	void setAfficherAsteroideCible(bool affichage);

	// Permet de determiner si la zone de passage des asteroides est affichee
	// @param affichage Si la zone doit etre affichee ou non
	void setAfficherZonePassage(bool affichage);

	// Permet de determiner si le cadre de depart est affiche ou non
	// @param affichage Si le cadre doit etre affiche ou non
	void setAfficherCadreDepart(bool affichage);

private:
	// Constructeur prive
	AffichageDebogage();

	// Destructeur prive
	~AffichageDebogage();

	// Permet d'obtenir une chaine de caractere representant le temps courant
	// @return La chaine de caractere representant le temps courant (HH:MM:ss:mm)
	string obtenirTempsCourant() const; 

	// Instance statique unique de la classe
	static AffichageDebogage* instance_;

	// Booleens de config qui determine si certaines sorties a la console
	// doivent etre affichees ou non
	bool afficherApparitionAsteroide_;
	bool afficherChangementModeJoueurVirtuel_;
	bool afficherModificationEclairage_;

	// Booleens de config qui determine si certains elements de debogages
	// OpenGL doivent etre affiches ou non
	bool afficherRayonAttraction_;
	bool afficherAsteroideCible_;
	bool afficherZonePassage_;
	bool afficherCadreDepart_;
};

#endif // _AFFICHAGE_DEBOGAGE_H_

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////