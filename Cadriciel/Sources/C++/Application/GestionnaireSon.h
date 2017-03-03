//////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireSon.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_GESTIONNAIRESON_H__
#define __APPLICATION_GESTIONNAIRESON_H__

#include <iostream>

#include "../../../Commun/Externe/FMOD/include/fmod.h"
#include "../../../Commun/Externe/FMOD/include/fmod.hpp"
#include "../../../Commun/Externe/FMOD/include/fmod_codec.h"
#include "../../../Commun/Externe/FMOD/include/fmod_dsp.h"
#include "../../../Commun/Externe/FMOD/include/fmod_memoryinfo.h"
#include "../../../Commun/Externe/FMOD/include/fmod_errors.h"
#include "../../../Commun/Externe/FMOD/include/fmod_output.h"

#include "../../../Commun/Utilitaire/Singleton.h"

using namespace std;

enum Son { EXPLOAST, EXPLOSTAT, TIRVAISSEAU, SONPORTAIL, SONBONUSACC, COLLISION, COLLISIONAUTRE, COLLISIONPROJ };

/**
 * @class GestionnaireSon
 * @brief Classe qui se charge des sons
 *
 * @author FloppyDisketeers
 * @date 2014-01-21
 */
class GestionnaireSon : public Singleton<GestionnaireSon>
{
	SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(GestionnaireSon);

public:
	/// Constructeur
	GestionnaireSon();

	/// Destructeur
	~GestionnaireSon();

	/// Methode qui permet de joueur la musique en boucle
	void jouerMusique();

	/// Methode qui permet d'arrêter la musique 
	void arreterMusique();

	/**
	 * Methode qui permet de jouer divers sons
	 * @param int son : le son que l'on veut faire jouer
	 */
	void jouerSon(int son);

	/// Update du gestionnaire de son
	void update();

private:
	/// Methode qui charge les sons
	void loadSounds();

	/// System qui gère le son
	FMOD_SYSTEM *system_;

	/// Les differents cannaux
	FMOD_CHANNEL *canal1_;
	FMOD_CHANNEL *canal2_;
	FMOD_CHANNEL *canal3_;
	FMOD_CHANNEL *canal4_;
	FMOD_CHANNEL *canal5_;

	/// Les différents sons
	FMOD_SOUND *musique1_;
	FMOD_SOUND *explosionAsteroide_;
	FMOD_SOUND *explosionStation_;
	FMOD_SOUND *acceleration_;
	FMOD_SOUND *portail_;
	FMOD_SOUND *tir_;
	FMOD_SOUND *collision_;
	FMOD_SOUND *collisionAutre_;
	FMOD_SOUND *collisionProj_;
};

#endif
 
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////