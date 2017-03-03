#include "NoeudProjectile.h"

NoeudProjectile::NoeudProjectile(const std::string& type) : NoeudAbstrait(type) {
	modele_.charger("media/Projectile.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudProjectile::NoeudProjectile(const NoeudProjectile& src) : NoeudAbstrait(src) {
	modele_.charger("media/Projectile.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudProjectile::~NoeudProjectile() {
}

void NoeudProjectile::animer(float dt) {
	NoeudAbstrait::animer(dt);
}

void NoeudProjectile::afficherConcret() const {
	NoeudAbstrait::afficherConcret();
	/*
	glPushMatrix();
		glLoadMatrixf((float*)&transformation_);
		objetTemporaire( 12.0f, 0.0f, 0.0f, 1.0f );	
	glPopMatrix();*/
}