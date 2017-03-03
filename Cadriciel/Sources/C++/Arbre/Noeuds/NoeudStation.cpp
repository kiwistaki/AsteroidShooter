#include "NoeudStation.h"
#include "../../AffichageTexte/FreeType.h"
#include "../../Application/FacadeModele.h"

NoeudStation::NoeudStation(const std::string& type) : NoeudAbstrait(type) {
	modele_.charger("media/Station.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudStation::NoeudStation(const NoeudStation& src) : NoeudAbstrait(src) {
	modele_.charger("media/Station.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudStation::~NoeudStation() {
}

void NoeudStation::animer(float dt) {
	NoeudAbstrait::animer(dt);
}

void NoeudStation::afficherConcret() const {
	NoeudAbstrait::afficherConcret();
}

void NoeudStation::afficherVie(const int& nbVie) const
{
	GLint	 viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLdouble winX, winY, winZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

	Phont& monPhont = FacadeModele::obtenirInstance()->phontVie_;

	// 1.2f*moitieHauteur pour faire un bon decalage
	gluProject(this->position_[0]-24, this->position_[1]-this->boiteEnglobanteOrientee_.getMoitieHauteur()-60, 
		this->position_[2]-this->boiteEnglobanteOrientee_.getMoitieHauteur(), modelview, projection, viewport, &winX, &winY, &winZ);

	int coinMaxX, coinMaxY;
	FacadeModele::obtenirInstance()->obtenirVue()->obtenirCoinsMax(coinMaxX, coinMaxY);
	monPhont.print(coinMaxX, coinMaxY, (GLuint) winX, (GLuint) winY, true, "%2.2i", nbVie );
}