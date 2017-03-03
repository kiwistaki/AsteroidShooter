#include "NoeudBarriere.h"

NoeudBarriere::NoeudBarriere(const std::string& type) : NoeudAbstrait(type) {
	// MODeLE TEMPORAIRE
	modele_.charger("media/Barriere.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudBarriere::NoeudBarriere(const NoeudBarriere& src) : NoeudAbstrait(src) {
	modele_.charger("media/Barriere.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudBarriere::~NoeudBarriere() {
}

void NoeudBarriere::animer(float dt) {
	NoeudAbstrait::animer(dt);
}

void NoeudBarriere::afficherConcret() const {
	NoeudAbstrait::afficherConcret();
}