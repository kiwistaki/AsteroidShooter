//////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireAnimation.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_GESTIONNAIREANIMATION_H__
#define __APPLICATION_GESTIONNAIREANIMATION_H__

#include <iostream>

#include "../ElementObjet/Station.h"
#include "../ElementObjet/Asteroide.h"
#include "../../../Commun/Utilitaire/Singleton.h"
#include "../../../Commun/Externe/FreeImage/include/FreeImage.h"

using namespace std;


class GestionnaireAnimation : public Singleton<GestionnaireAnimation>
{
	SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(GestionnaireAnimation);

public:
	/// Constructeur
	GestionnaireAnimation();

	/// Destructeur
	~GestionnaireAnimation();

	/// Afficher Animation de station qui explose
	void animationStation();

	void animationAsteroid1();

	void animationAsteroid2();

	void animer(int compteur, float x, float y, float rayon);

	/// Getter
	bool getAnimationStationEnCours(){ return animationStationEnCours_;}
	void setAnimationStationEnCours(bool valeur);

	bool getAnimationAsteroid1EnCours(){ return animationAsteroid1EnCours_;}
	void setAnimationAsteroid1EnCours(bool valeur);
	bool getAnimationAsteroid2EnCours(){ return animationAsteroid2EnCours_;}
	void setAnimationAsteroid2EnCours(bool valeur);

	float getPositionStationX(){ return xStation_;}
	void setPositionStationX(float x);
	float getPositionStationY(){ return yStation_;}
	void setPositionStationY(float y);

	float getPositionAsteroid1X(){ return xAsteroid1_;}
	void setPositionAsteroid1X(float x);
	float getPositionAsteroid1Y(){ return yAsteroid1_;}
	void setPositionAsteroid1Y(float y);

	float getPositionAsteroid2X(){ return xAsteroid2_;}
	void setPositionAsteroid2X(float x);
	float getPositionAsteroid2Y(){ return yAsteroid2_;}
	void setPositionAsteroid2Y(float y);

	void setRayonStation(float r){ rayonStation_ = r; }
	float getRayonStation(){ return rayonStation_; }

	void setRayonAsteroide1(float r){ rayonAsteroide1_ = r; }
	float getRayonAsteroide1(){ return rayonAsteroide1_; }

	void setRayonAsteroide2(float r){ rayonAsteroide2_ = r; }
	float getRayonAsteroide2(){ return rayonAsteroide2_; }

	void interrompreAnimation();

	static int compteurStation_;
	static int compteurAsteroid1_;
	static int compteurAsteroid2_;

private:
	float xStation_, yStation_;
	float xAsteroid1_, yAsteroid1_;
	float xAsteroid2_, yAsteroid2_;

	float rayonStation_;
	float rayonAsteroide1_;
	float rayonAsteroide2_;

	int largeurPixel_, hauteurPixel_;
	GLuint textureID_;
	FIBITMAP *bitmap_;

	bool animationStationEnCours_;
	bool animationAsteroid1EnCours_;
	bool animationAsteroid2EnCours_;
};
#endif
 
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////