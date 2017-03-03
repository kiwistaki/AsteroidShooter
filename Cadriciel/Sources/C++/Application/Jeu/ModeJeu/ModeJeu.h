//////////////////////////////////////////////////////////////////////////////
/// @file ModeJeu.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_MODEJEU_H__
#define __APPLICATION_MODEJEU_H__

#include <map>
#include "../JeuAbstrait.h"
#include "../../Carte.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
/// @class ModeJeu
/// @brief Classe contenant les fonctionalites en lien avec le gameplay
///		   (une partie est en cours), donc la zone de jeu a ete chargee
///		   et le(s) joueur(s) puvent controler leur vaisseau. La minuterie
///		   part, les animations, la physique du jeu et les regles sont
///		   appliquees. 
///		   La barre de menus devient visible seulement lorsque la partie
///		   est en pause (bouton "ESC"). Les deux options de la barres de
///		   menus sont : retourner au menu principal et changer de camera.
///		   "Backspace" reinitialise la partie
///		   Les modes suivent le command pattern.
///
/// @author FloppyDisketeers
/// @date 2014-01-21
///////////////////////////////////////////////////////////////////////////
class ModeJeu : public JeuAbstrait
{
public:
	/// Constructeur par parametres
	/// @param carte La carte avec laquelle jouer
	/// @param vue Le viewport
						ModeJeu(Carte& carte, vue::Vue* vue);
	/// Destructeur
	virtual				~ModeJeu();

	/// Update recoit les informations et laisse le jeu analyser les donnees
	virtual void		update(float deltaT);

	/// Methode qui s'occupe de la logique des vaisseaux Joueurs
	void				logiqueVaisseaux(float deltaT);

	/// Methode qui definit le mode et la position des joueurs
	virtual void		traitementInitial();

	/// Enumerations des commandes 
	enum ListeCommandes	{ PAUSE, REINITIALISER, NOMBRECOMMANDES };

private:
	/// Etat de la commandes
	enum ListeCommandes	commandeCourante_;
	enum ListeCommandes commandePrecendente_;

	/// Pointeur vers les 2 vaisseaux
	Vaisseau			*joueur_1;
	Vaisseau			*joueur_2;

	/// Pointeur vers la maps de commandes des joueurs map<Commandes, touche>
	map<int,int>	    *commandesJoueur_;

	/// Bool pour la manoeuvre
	bool				manoeuvreJoueur1_;
	bool				manoeuvreJoueur2_;

protected:
	/// Attribut pour la duree de jeu
	float				tempsJeu_;
};

#endif // __APPLICATION_MODEJEU_H__