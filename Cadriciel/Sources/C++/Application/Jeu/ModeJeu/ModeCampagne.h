//////////////////////////////////////////////////////////////////////////////
/// @file ModeCampagne.h
/// @author FloppyDisketeers
/// @date 2014-03-11
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _APPLICATION_MODECAMPAGNE_H_
#define _APPLICATION_MODECAMPAGNE_H_

#include <queue>
#include <vector>

#include "ModeJeu.h"
#include "ComparateurCartes.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
/// @class ModeCampagne
/// @brief Classe qui implemente le comportement du mode campagne
///
/// @author Vincent Longpre
/// @date 2014-03-11
///////////////////////////////////////////////////////////////////////////
class ModeCampagne : public ModeJeu {
public:
	/// Constructeur
	/// @param carte La carte avec laquelle jouer
	/// @param vue Le viewport
	ModeCampagne(Carte& carte, vue::Vue* vue, vector<string> cartes, bool modeCoop, bool joueur2Virtuel);
	
	/// Destructeur
	virtual ~ModeCampagne();

	/// Update recoit les informations et laisse le jeu analyser les donnees
	/// @param deltaT Le temps depuis la derniere frame affichee
	virtual void update(float deltaT);

	/// Methode qui place la prochaine carte a jouer
	/// @param modeCoop S'il y a plusieurs joueurs
	/// @param joueur2Virtuel Si le 2e joueur est virtuel
	void prochaineCarte(bool modeCoop, bool joueur2Virtuel);

private:
	/// File de priorite contenant les cartes a utiliser pour la campagne
	priority_queue<string, vector<string>, ComparateurCartes> file_;
};

#endif // _APPLICATION_MODECAMPAGNE_H_