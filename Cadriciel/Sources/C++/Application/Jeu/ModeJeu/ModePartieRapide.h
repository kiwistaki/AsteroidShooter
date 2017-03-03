//////////////////////////////////////////////////////////////////////////////
/// @file ModePartieRapide.h
/// @author FloppyDisketeers
/// @date 2014-03-11
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_MODEPARTIERAPIDE_H__
#define __APPLICATION_MODEPARTIERAPIDE_H__

#include "ModeJeu.h"

/**
 * @class ModePartieRapide
 * @brief Cette classe implemente le mode de jeu partie rapide
 * @author FloppyDisketeers
 */
class ModePartieRapide : public ModeJeu {
public:
	/// Constructeur
	/// @param carte La carte avec laquelle jouer
	/// @param vue Le viewport
	ModePartieRapide(Carte& carte, vue::Vue* vue);

	/// Destructeur
	~ModePartieRapide();

	/// Update recoit les informations et laisse le jeu analyser les donnees
	/// @param deltaT Le temps depuis la derniere frame affichee
	virtual void update(float deltaT);

private:
};

#endif // __APPLICATION_MODEPARTIERAPIDE_H__