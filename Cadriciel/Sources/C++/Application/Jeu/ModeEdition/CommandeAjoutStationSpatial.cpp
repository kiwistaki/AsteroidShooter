#include "CommandeAjoutStationSpatial.h"
#include "../../../ElementObjet/Station.h"
#include "../../FacadeModele.h"

CommandeAjoutStationSpatial::CommandeAjoutStationSpatial(const vue::Vue& vue, Carte& carte) : vue_(vue), carte_(carte)
{
	type_ = STATION;
	mouseClicked_ = false;
}

CommandeAjoutStationSpatial::~CommandeAjoutStationSpatial()
{
}

void CommandeAjoutStationSpatial::executer(int mouseX, int mouseY, int boutton, int touche)
{
	// Si le joueur click (gauche) dans la carte
	if (boutton == 1) {
		if(!mouseClicked_) {
			clickedPositionX_ = mouseX;
			clickedPositionY_ = mouseY;
		}
		mouseClicked_ = true;

	} else if (boutton == -1 && mouseClicked_) {
		if((mouseX >= (clickedPositionX_ - 3) && mouseX <= (clickedPositionX_ + 3)) && (mouseY >= (clickedPositionY_ - 3) && mouseY <= (clickedPositionY_ + 3))) {
			Vecteur3 positionVirtuelle;
			vue_.convertirClotureAVirtuelle(clickedPositionX_, clickedPositionY_, positionVirtuelle);
			// On cree l'objet simplement lorsque l'utilisateur relache le boutton gauche de la souris
			if (validerPosition(positionVirtuelle))
			{
				Station* s = new Station();
				s->setPositionActuelle(positionVirtuelle);
				carte_.ajouterElement(s);
			}
		}
		mouseClicked_ = false;

	}

	Vecteur3 positionSouris;
	vue_.convertirClotureAVirtuelle(mouseX, mouseY, positionSouris);

	if (!validerPosition(positionSouris)) {
		afficheCurseurRouge(Vecteur3(mouseX, mouseY));
	}
}

bool CommandeAjoutStationSpatial::validerPosition(Vecteur3& position)
{
	float haut = (float) carte_.getZoneJeuY()[1]; // Bordure du haut
	float bas = (float) carte_.getZoneJeuY()[0]; // Bordure du bas
	float gauche = (float) carte_.getZoneJeuX()[0]; // Bordure de gauche
	float droite = (float) carte_.getZoneJeuX()[1]; // Bordure de droite

	bool okHaut = position[1] < haut; // Si element plus bas que le haut
	bool okBas = position[1] > bas; // Si element plus haut que le bas
	bool okGauche = position[0] > gauche; // Si element a droite de la gauche
	bool okDroite = position[0] < droite; // Si element a gauche de la droite

	if (okHaut && okBas && okGauche && okDroite)
		return true;
	else
		return false;
}

void CommandeAjoutStationSpatial::afficheCurseurRouge(const Vecteur3& positionSouris) const {
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glTranslatef((GLfloat)positionSouris[0], (GLfloat)positionSouris[1], 0.0f);
		glScalef(0.5f, 0.5f, 0.5f);

		// On desactive les textures, sinon on arrive pas a bien afficher.
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex2i(-10,  18);
			glVertex2i(-18,  10);
			glVertex2i( 12, -20);
			glVertex2i( 20, -12);

			glVertex2i(-18, -12);
			glVertex2i(-10, -20);
			glVertex2i( 20,  10);
			glVertex2i( 12,  18);
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glPopAttrib();
}