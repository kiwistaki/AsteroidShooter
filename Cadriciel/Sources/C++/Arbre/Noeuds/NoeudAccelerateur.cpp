#include "NoeudAccelerateur.h"


NoeudAccelerateur::NoeudAccelerateur(const std::string& type) : NoeudAbstrait(type) {
	// MODeLE TEMPORAIRE
	modele_.charger("media/Accelerateur.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);

	estActif_ = true;
}

NoeudAccelerateur::~NoeudAccelerateur() {
}

NoeudAccelerateur::NoeudAccelerateur(const NoeudAccelerateur& src) : NoeudAbstrait(src) {
	modele_.charger("media/Accelerateur.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);

	estActif_ = true;
}

void NoeudAccelerateur::animer(float dt) {
	NoeudAbstrait::animer(dt);
}

void NoeudAccelerateur::afficherConcret() const {
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		if (selectionne_) {	
			// On desactive les textures pour changer la couleur
			glDisable(GL_TEXTURE_2D);

			// XOR avec la couleur en dessous (pour que l'on voit toujours le
			// rectangle)
			glLogicOp(GL_XOR);
			glEnable(GL_COLOR_LOGIC_OP);

			glColor3f(1.0f, 1.0f, 1.0f);
			boiteEnglobanteOrientee_.afficher();

			glDisable(GL_COLOR_LOGIC_OP);

			glEnable(GL_TEXTURE_2D);

			glColor4f(0.0f, 0.85f, 0.0f, 0.5f);
		}

		if (!estActif_) {
			glDisable(GL_LIGHTING);
			glColor4f(1.0f, 0.0f, 0.0f, 0.5f); // Rouge
			glEnable(GL_BLEND);
		}

		/// Transformation par rapport a l'objet lui-meme
		glTranslatef(position_.x, position_.y, position_.z);
		glRotatef(angleRotation_, axeRotation_.x, axeRotation_.y, axeRotation_.z);
		glScalef(taille_.x, taille_.y, taille_.z);

		modele_.dessiner();

		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPopAttrib();
}