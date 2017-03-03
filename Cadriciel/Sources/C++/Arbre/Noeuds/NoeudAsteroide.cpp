#include "NoeudAsteroide.h"

#include "../Modeles/GestionnaireAsteroide.h"
#include "../../Application/AffichageDebogage.h"

NoeudAsteroide::NoeudAsteroide(const std::string& type) : NoeudAbstrait(type), estCible_(false) {
	unsigned int liste;
	GestionnaireAsteroide::getInstance()->getModeleAsteroide(liste, rayon_);
	modele_.setDisplayList(liste);
	angleX_ = 0.0f;
    angleY_ = 0.0f;
    angleZ_ = 0.0f;
}

NoeudAsteroide::NoeudAsteroide(const NoeudAsteroide& src) : NoeudAbstrait(src), estCible_(false) {
	unsigned int liste;
	GestionnaireAsteroide::getInstance()->getModeleAsteroide(liste, rayon_);
	modele_.setDisplayList(liste);
	angleX_ = 0.0f;
    angleY_ = 0.0f;
    angleZ_ = 0.0f;
}

NoeudAsteroide::~NoeudAsteroide() {
}

void NoeudAsteroide::setCible(bool estCible)
{
	estCible_ = estCible;
}

void NoeudAsteroide::animer(float dt) {
	NoeudAbstrait::animer(dt);
}

void NoeudAsteroide::afficherConcret() const {
	glColor3f(0.37f, 0.3f, 0.26f); // Rendre plus visible
		
	glPushMatrix();
		/// Transformation par rapport a l'objet lui-meme
		glTranslatef(position_.x, position_.y, position_.z);

		glRotatef(angleX_, 1.0f, 0.0f, 0.0f);
		glRotatef(angleY_, 0.0f, 1.0f, 0.0f);
		glRotatef(angleZ_, 0.0f, 0.0f, 1.0f);

		glScalef(taille_.x, taille_.y, taille_.z);

		modele_.dessiner();
	glPopMatrix();

	if (estCible_)
		AffichageDebogage::obtenirInstance()->afficherAsteroideCibleJoueurVirtuel(this);
}

void NoeudAsteroide::setRayon(float rayon)
{
	rayon_ = rayon;
}

float NoeudAsteroide::getRayon() const
{
	return rayon_;
}