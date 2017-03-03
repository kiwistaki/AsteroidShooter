//////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireSon.cpp
/// @author FloppyDisketeers
/// @date 2014-01-25
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "GestionnaireSon.h"

SINGLETON_DECLARATION_CPP(GestionnaireSon);


GestionnaireSon::GestionnaireSon()
{
	FMOD_System_Create(&system_);
	FMOD_System_Init(system_, 32, FMOD_INIT_NORMAL, NULL);

	loadSounds();
}

GestionnaireSon::~GestionnaireSon()
{
	FMOD_Sound_Release(collisionProj_);
	FMOD_Sound_Release(collisionAutre_);
	FMOD_Sound_Release(portail_);
	FMOD_Sound_Release(tir_);
	FMOD_Sound_Release(collision_);
	FMOD_Sound_Release(acceleration_);
	FMOD_Sound_Release(explosionStation_);
	FMOD_Sound_Release(explosionAsteroide_);

	FMOD_Sound_Release(musique1_);

	FMOD_System_Close(system_);
	FMOD_System_Release(system_);
}

void GestionnaireSon::jouerMusique()
{
	FMOD_Sound_SetLoopCount(musique1_, -1);

	FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, musique1_, 0, &canal1_);
	FMOD_Channel_SetVolume(canal1_, 0.90f);
}

void GestionnaireSon::arreterMusique()
{
	FMOD_Channel_SetPaused(canal1_, 1);
}

void GestionnaireSon::jouerSon(int son)
{
	// EXPLOAST, EXPLOSTAT, TIRVAISSEAU, SONPORTAIL, SONBONUSACC, COLLISION ...
	switch (son)
	{
	case EXPLOAST:
		FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, explosionAsteroide_, false, NULL);
		break;

	case EXPLOSTAT:
		FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, explosionStation_, false, NULL);
		break;

	case TIRVAISSEAU:
		FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, tir_, false, NULL);
		break;

	case SONPORTAIL:
		FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, portail_, true, &canal4_);
		FMOD_Channel_SetVolume(canal4_, 0.70f);
		FMOD_Channel_SetPaused(canal4_, false);
		break;

	case SONBONUSACC:
		FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, acceleration_, false, NULL);
		break;

	case COLLISION:
		FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, collision_, true, &canal2_);
		FMOD_Channel_SetVolume(canal2_, 0.50f);
		FMOD_Channel_SetPaused(canal2_, false);
		break;

	case COLLISIONAUTRE:
		FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, collisionAutre_, false, NULL);
		break;

	case COLLISIONPROJ:
		FMOD_System_PlaySound(system_, FMOD_CHANNEL_FREE, collisionProj_, true, &canal3_);
		FMOD_Channel_SetVolume(canal3_, 0.15f);
		FMOD_Channel_SetPaused(canal3_, false);
		break;

	default:
		break;
	}
}

void GestionnaireSon::loadSounds()
{
	// Musique 
	FMOD_System_CreateSound(system_, "sons/HeroicDisketeerFleetGo.wav", FMOD_SOFTWARE | FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATESTREAM, 0, &musique1_);
	// ExplosionAsteroide
	FMOD_System_CreateSound(system_, "sons/explosion_medium.mp3", FMOD_CREATESAMPLE ,0 , &explosionAsteroide_);
	// Tir
	FMOD_System_CreateSound(system_, "sons/scifi054.wav", FMOD_CREATESAMPLE ,0 , &tir_);
	// BonusAcc
	FMOD_System_CreateSound(system_, "sons/Power_Up_Ray-Mike_Koenig-800933783.wav", FMOD_CREATESAMPLE ,0 , &acceleration_);
	// ExplosionStation
	FMOD_System_CreateSound(system_, "sons/large_explosion.mp3", FMOD_CREATESAMPLE ,0 , &explosionStation_);
	// Portail
	FMOD_System_CreateSound(system_, "sons/Switch19-intermed-5280_hifi.mp3", FMOD_CREATESAMPLE ,0 , &portail_);
	// CollisionAst
	FMOD_System_CreateSound(system_, "sons/Metal Impact Hollow-SoundBible.com-583611978.wav", FMOD_CREATESAMPLE ,0 , &collision_);
	// CollisionVaisseau
	FMOD_System_CreateSound(system_, "sons/metal_garbage_dumpster.mp3", FMOD_CREATESAMPLE ,0 , &collisionAutre_);
	// CollisionProjectile
	FMOD_System_CreateSound(system_, "sons/impact_metal_tin_lid_on_tin_002.mp3", FMOD_CREATESAMPLE ,0 , &collisionProj_);
}

void GestionnaireSon::update()
{
	FMOD_System_Update(system_);
}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////