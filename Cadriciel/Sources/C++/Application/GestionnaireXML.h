//////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireXML.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_GESTIONNAIREXML_H__
#define __APPLICATION_GESTIONNAIREXML_H__

#include <iostream>
#include <list>
#include <string>
#include "../../../Commun/Utilitaire/Singleton.h"
#include "Carte.h"
#include "ConfigScene.h"
#include "tinyxml.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
/// @class GestionnaireXML
/// @brief Classe qui s'occupe de la gestion des cartes et des fichiers XML
///        C'est une classe singleton
///
/// @author FloppyDisketeers
/// @date 2014-01-21
///////////////////////////////////////////////////////////////////////////
class GestionnaireXML : public Singleton<GestionnaireXML>
{
	SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(GestionnaireXML);

public:
	/// Constructeur par defaut
					GestionnaireXML();

	/// Destructeur
					~GestionnaireXML();

	/// Methode qui permet de sauvegarder une carte
	/// @param nom		Le nom de la carte a sauvegarder
	/// @param carte	La carte a sauvegarder
	void			sauvegarderCarte(const string nom, Carte& carte) const;

	/// Methode qui permet de charger une zone de jeu
	/// @param nom Le nom de la carte a charger
	Carte*			chargerCarte(const string nom);

	/// Methode qui retourne le nom de la carte par defaut
	/// @return Le nom de la carte par defaut
	string			getNomCarteDefaut() const;

	/// Methode qui cree la carte par defaut
	/// @return La carte chargee par defaut
	Carte*			chargerCarteDefaut();

	/// Methode qui cree la carte de campagne par defaut
	/// @return La carte de campagne par defaut
	Carte*			chargerCarteCampagneDefaut();
		 	/**
	 * Sauvegarde le fichier de configuration du jeu. Le fichier créer s'appelle "configuration.xml"
	 * @param toucheJoueur1Propulsion La touche utilisée par le joueur 1 pour la propulsion
	 * @param toucheJoueur1TournerGauche La touche utilisée par le joueur 1 pour tourner à gauche
	 * @param toucheJoueur1TournerDroite La touche utilisée par le joueur 1 pour tourner à droite
	 * @param toucheJoueur1Manoeuvre La touche utilisée par le joueur 1 pour effectuer une manoeuvre
	 * @param toucheJoueur1Tir La touche utilisée par le joueur 1 pour tirer
	 * @param toucheJoueur2Propulsion La touche utilisée par le joueur 2 pour la propulsion
	 * @param toucheJoueur2TournerGaughe La touche utilisée par le joueur 2 pour tourner à gauche
	 * @param toucheJoueur2TournerDroite La touche utilisée par le joueur 2 pour tourner à droite
	 * @param toucheJoueur2Manoeuvre La touche utilisée par le joueur 2 pour effectuer une manoeuvre
	 * @param toucheJoueur2Tir La touche utilisée par le joueur 2 pour tirer
	 * @param dureeJeu La durée, en seconde, d'une partie
	 * @param pointsDeVieStation Les points de vie des stations dans une partie
	 */
	void			sauvegarderConfiguration(int toucheJoueur1Propulsion, int toucheJoueur1TournerGauche,
											 int toucheJoueur1TournerDroite, int toucheJoueur1Manoeuvre,
											 int toucheJoueur1Tir, int toucheJoueur2Propulsion,
											 int toucheJoueur2TournerGauche, int toucheJoueur2TournerDroite,
											 int toucheJoueur2Manoeuvre, int toucheJoueur2Tir,
											 double dureeJeu, int pointsDeVieStation,
											 bool apparitionAsteroide, bool changementMode, bool eclairage,
											 bool cibleJoueur, bool cadreDepart, bool zonePassage,
											 bool attractionPort) const;

	/**
	 * Lie le fichier de configuration du jeu et retourne les valeurs sauvegardées
	 * @param toucheJoueur1Propulsion La touche utilisée par le joueur 1 pour la propulsion
	 * @param toucheJoueur1TournerGauche La touche utilisée par le joueur 1 pour tourner à gauche
	 * @param toucheJoueur1TournerDroite La touche utilisée par le joueur 1 pour tourner à droite
	 * @param toucheJoueur1Manoeuvre La touche utilisée par le joueur 1 pour effectuer une manoeuvre
	 * @param toucheJoueur1Tir La touche utilisée par le joueur 1 pour tirer
	 * @param toucheJoueur2Propulsion La touche utilisée par le joueur 2 pour la propulsion
	 * @param toucheJoueur2TournerGaughe La touche utilisée par le joueur 2 pour tourner à gauche
	 * @param toucheJoueur2TournerDroite La touche utilisée par le joueur 2 pour tourner à droite
	 * @param toucheJoueur2Manoeuvre La touche utilisée par le joueur 2 pour effectuer une manoeuvre
	 * @param toucheJoueur2Tir La touche utilisée par le joueur 2 pour tirer
	 * @param dureeJeu La durée, en seconde, d'une partie
	 * @param pointsDeVieStation Les points de vie des stations dans une partie
	 */
	void			chargerConfiguration(int& toucheJoueur1Propulsion, int& toucheJoueur1TournerGauche,
										 int& toucheJoueur1TournerDroite, int& toucheJoueur1Manoeuvre,
										 int& toucheJoueur1Tir, int& toucheJoueur2Propulsion,
										 int& toucheJoueur2TournerGauche, int& toucheJoueur2TournerDroite,
										 int& toucheJoueur2Manoeuvre, int& toucheJoueur2Tir,
										 double& dureeJeu, int& pointsDeVieStation, bool& apparitionAsteroide,
										 bool& changementMode, bool& eclairage, bool& cibleJoueur,
										 bool& cadreDepart, bool& zonePassage, bool& attractionPort, bool& fichierExiste) const;

	void			sauvegarderConfigCampagne(bool modeCoop, bool joueur2Virtuel, vector<string> listeCarte);

	void			chargerConfigCampagne(bool& modeCoop, bool& joueur2Virtuel, bool& fichier, vector<string>& listeCarte);

private:
	/// Methode qui permet de lire des elements d'un fichier XML
	void			lireXML(TiXmlNode& noeud, Carte& carte) const;
	/// Methode qui permet de creer un fichier XML
	void			creerXML(TiXmlNode& noeud, Carte& carte) const;

	/// Nom de la carteDefaut
	const string	nomCarteDefaut_; 

	/// Nom de la carteDefaut
	const string	nomCampagneDefaut_; 

	/// Nom du fichier de configuration
	const string	nomFichierConfig_;
};

#endif // __APPLICATION_GESTIONNAIREXML_H__
 
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////