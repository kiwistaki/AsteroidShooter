#include "NoeudPositionDepart.h"

NoeudPositionDepart::NoeudPositionDepart(const std::string& type) : NoeudAbstrait(type) {
	// MODeLE TEMPORAIRE
	modele_.charger("media/PositionDepart.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudPositionDepart::NoeudPositionDepart(const NoeudPositionDepart& src) : NoeudAbstrait(src) {
	modele_.charger("media/PositionDepart.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudPositionDepart::~NoeudPositionDepart() {
}

void NoeudPositionDepart::animer(float dt) {
	NoeudAbstrait::animer(dt);
}

void NoeudPositionDepart::afficherConcret() const {
	glColor3f(1.0f, 0.0f, 0.0f); // Rouge
	
	glPushMatrix();
		if (selectionne_) {		
			// On desactive les textures pour changer la couleur
			glDisable(GL_TEXTURE_2D);

			// XOR avec la couleur en dessous (pour que l'on voit toujours le rectangle)
			glLogicOp(GL_XOR);
			glEnable(GL_COLOR_LOGIC_OP);

			glColor3f(1.0f, 1.0f, 1.0f);
			boiteEnglobanteOrientee_.afficher();

			glDisable(GL_COLOR_LOGIC_OP);

			glEnable(GL_TEXTURE_2D); // Reactivation des textures

			glColor4f(0.0f, 0.85f, 0.0f, 0.5f);
		}

		/// Transformation par rapport a l'objet lui-meme
		glTranslatef(position_.x, position_.y, position_.z);
		glRotatef(angleRotation_, axeRotation_.x, axeRotation_.y, axeRotation_.z);
		glScalef(taille_.x, taille_.y, taille_.z);

		modele_.dessiner();
	glPopMatrix();
}