#include "NoeudVaisseau.h"

NoeudVaisseau::NoeudVaisseau(const std::string& type) : NoeudAbstrait(type), joueur1_(true) {
	modele_.charger("media/Vaisseau.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudVaisseau::NoeudVaisseau(const NoeudVaisseau& src) : NoeudAbstrait(src), joueur1_(true) {
	modele_.charger("media/Vaisseau.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudVaisseau::~NoeudVaisseau() {
}

void NoeudVaisseau::animer(float dt) {
	NoeudAbstrait::animer(dt);
}

void NoeudVaisseau::afficherConcret() const {
	if (joueur1_) {
		glColor3f(1.0f, 0.0f, 0.0f); // Joueur 1 rouge
	} else {
		glColor3f(0.0f, 0.0f, 1.0f); // Joueur 2 bleu
	}

	glPushMatrix();
		/// Transformation par rapport a l'objet lui-meme
		glTranslatef(position_.x, position_.y, position_.z);
		glRotatef(angleRotation_, axeRotation_.x, axeRotation_.y, axeRotation_.z);
		glScalef(taille_.x, taille_.y, taille_.z);

		modele_.dessiner();
	glPopMatrix();
}