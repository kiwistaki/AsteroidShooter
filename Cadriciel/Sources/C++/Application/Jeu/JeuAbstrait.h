//////////////////////////////////////////////////////////////////////////////
/// @file JeuAbstrait.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_JEUABSTRAIT_H__
#define __APPLICATION_JEUABSTRAIT_H__

#include <vector>
#include "../Carte.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
/// @class JeuAbstrait
/// @brief Classe abstraite representant les fonctionalites de bases
///		   des differents modes de jeux.
///
/// @author FloppyDisketeers
/// @date 2014-01-21
///////////////////////////////////////////////////////////////////////////
class JeuAbstrait
{
public:
	/**
	* Constructeur par parametres
	* @param vue	La vue du jeu
	* @param carte	La carte contenant tous les elements du jeu
	*/
					JeuAbstrait(Carte& carte, vue::Vue* vue);
	/**
	* Destructeur
	*/
	virtual			~JeuAbstrait();

	/**
	* Permet de definir la carte a utiliser
	* @param carte La carte a utiliser
	*/
	void			setCarte(Carte& carte);

	/**
	* Permet d'obtenir la carte utilisee
	*/
	Carte&			getCarte() const;

	/**
	* Permet de modifier la vue apres l'initialisation d'un mode de jeu
	*/
	void			setVue(vue::Vue* vue);
	
	/**
	* Mise a jour
	* @param deltaT Le temps en secondes depuis la dernière frame
	*/
	virtual void	update(float deltaT);

	/**
	 * Methode qui recoit les inputs necessaires (clavier, souris, ecran)
	 * @param mouseX	Position en X de la souris
	 * @param mouseY	position en Y de la souris
	 * @param boutton	Boutton clique avec la souris
	 * @param touche	Touche appuyee avec la souris
	 */
	void			recevoirInputs(int mouseX, int mouseY, int boutton, int touche, int scroll);

	virtual void setPourcentageDeplacement(bool estOrtho);

protected:
	/// La carte qui contient tous les objets
	Carte&			carte_;

	/** La vue du jeu */
	vue::Vue*		vue_;

	/** Position en X de la souris */
	int				mouseX_;

	/** Position en Y de la souris */
	int				mouseY_;

	/** Derniere position en X de la souris */
	int				lastMouseX_;

	/** Derniere position en Y de la souris */
	int				lastMouseY_;

	/** Boutton presentement clique avec la souris */
	int				boutton_;

	/** Touche presentement appuye avec le clavier */
	int				touche_;
	
	/** Touche precedente appuye avec le clavier */
	int				previousTouche_;

	/** Scroll avec la souris */
	int				scroll_;

	
	float pourcentageDeplacement_;
};

#endif // __APPLICATION_JEUABSTRAIT_H__