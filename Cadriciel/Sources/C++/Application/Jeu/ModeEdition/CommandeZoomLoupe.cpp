/**
* @file CommandeZoomLoupe.cpp
* @author The FloppyDisketeers
* @date 2014-02-04
* @version 1.0
*
* @addtogroup inf2990 INF2990
* @{
*/

#include "CommandeZoomLoupe.h"

#include "../../../ElementObjet/ElementJeuAbstrait.h"


/**
* @interface CommandeZoomLoupe
* 
* 
*/
////////////////////////////////////////////////////////////////////////
///
/// @fn CommandeZoomLoupe::CommandeZoomLoupe(const vue::Vue& vue)
///
/// L'interface CommandeZoomLoupe permet de zoomer en creant
/// un rectangle elastique en mode edition.
///
/// @param[in] vue   : Permet de convertir les coordonnees dans la bonne cloture
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
CommandeZoomLoupe::CommandeZoomLoupe(vue::Vue& vue) : vue_(vue)
{
	mouseClicked_  = false;
	modeRectangle_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CommandeZoomLoupe::executer(int mouseX, int mouseY, int boutton, int touche)
///
/// Cette fonction execute les operations necessaires en fonction des parametres d'entrees
/// 
/// @param[in] mouseX   : coordonnee de la souris en x.
/// @param[in] mousey   : coordonnee de la souris en y.
/// @param[in] boutton	: bouton de la souris appuye.
/// @param[in] touche   : touche du clavier appuyee.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CommandeZoomLoupe::executer(int mouseX, int mouseY, int boutton, int touche)
{
	mouseX_ = mouseX;
	mouseY_ = mouseY;
	
	// Si clique gauche de la souris.
	if (boutton == 1) 
	{
		
		// Si l'etat precedent n'etait pas clique, le coin initial du rectangle sera defini.
		if (!mouseClicked_) {
			clickedPositionX_ = mouseX;
			clickedPositionY_ = mouseY;

			// Sert seulement a l'affichage du rectangle elastique
			vue_.convertirClotureAVirtuelle(mouseX, mouseY, coinInitialRectangle_);
			
			coinInitialRectangleNonVirtuelle_[0] = mouseX;
			coinInitialRectangleNonVirtuelle_[1] = mouseY;
		}
		mouseClicked_ = true;

		// Definition d'un clic: si le clic reste a ± 3 pixels du point clique,
		// alors on effectue une selection ponctuelle. Sinon, on fais une
		// selection elastique.
		if ((mouseX >= (clickedPositionX_ - 3) && mouseX <= (clickedPositionX_ + 3)) &&
			(mouseY >= (clickedPositionY_ - 3) && mouseY <= (clickedPositionY_ + 3)))
		{
			modeRectangle_ = false;
		}
		else
		{
			modeRectangle_ = true;

			// Variation de distance par rapport au premier clic du rectangle
			int dx = clickedPositionX_ - mouseX_;
			int dy = clickedPositionY_ - mouseY_;
			
			// Conditions pour le rectangle elastique
			if (dx != 0 && dy != 0 && (abs(dx) > 3 || abs(dy) > 3))
			{
				// Sert seulement a afficher le rectangle elastique
				vue_.convertirClotureAVirtuelle(mouseX_, mouseY_, coinCourantRectangle_);
			
				coinCourantRectangleNonVirtuelle_[0] = mouseX_;
				coinCourantRectangleNonVirtuelle_[1] = mouseY_;

				afficherRectangleElastique(coinInitialRectangle_, coinCourantRectangle_);
			}
		}
	}
	else
	{
		// Si le mode precedent etait en mode rectangle, il sera possible d'effectuer un zoom
		if(modeRectangle_)
		{
			//Vecteur2i coin1(coinInitialRectangle_[0], coinInitialRectangle_[1]);
			//Vecteur2i coin2(coinCourantRectangle_[0], coinCourantRectangle_[1]);
			Vecteur2 coin1(coinInitialRectangleNonVirtuelle_[0], coinInitialRectangleNonVirtuelle_[1]);
			Vecteur2 coin2(coinCourantRectangleNonVirtuelle_[0], coinCourantRectangleNonVirtuelle_[1]);
			
			// Si bouton ALT(int 18) pas appuye
			if(touche == 18){
				vue_.zoomerOutElastique(coin1, coin2);
			} else {
				vue_.zoomerInElastique(coin1, coin2);
			}
			modeRectangle_ = false;
		}
		mouseClicked_ = false;
	}
	
}

void CommandeZoomLoupe::afficherRectangleElastique(const Vecteur3& pointClique,
												   const Vecteur3& pointSouris)
{
	// On desactive les textures, sinon on arrive pas a bien afficher.
	glDisable(GL_TEXTURE_2D);

	parametresPointillee_.commencer();

	// On desactive le depth test pour affiche par dessus tout
	glDisable(GL_DEPTH_TEST);

	// XOR avec la couleur en dessous
	glLogicOp(GL_XOR);
	glEnable(GL_COLOR_LOGIC_OP);

	glPushMatrix();
		glBegin(GL_LINE_LOOP);
			glVertex2i((int)pointClique[0], (int)pointClique[1]);
			glVertex2i((int)pointClique[0], (int)pointSouris[1]);
			glVertex2i((int)pointSouris[0], (int)pointSouris[1]);
			glVertex2i((int)pointSouris[0], (int)pointClique[1]);
		glEnd();
	glPopMatrix();

	glDisable(GL_COLOR_LOGIC_OP);
	glEnable(GL_DEPTH_TEST);

	parametresPointillee_.finir();

	glEnable(GL_TEXTURE_2D);
}