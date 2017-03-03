//////////////////////////////////////////////////////////////////////////////
/// @file JeuAbstrait.cpp
/// @author FloppyDisketeers
/// @date 2014-01-28
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#include "JeuAbstrait.h"

#include "../FacadeModele.h"
#include "../../Arbre/ArbreRenduINF2990.h"

JeuAbstrait::JeuAbstrait(Carte& carte, vue::Vue* vue) : carte_(carte), vue_(vue) {
	mouseX_  = mouseY_ = lastMouseX_ = lastMouseY_ = 0;
	boutton_ = -1;
	touche_  = -1;
	pourcentageDeplacement_ = 0.1f;
}

JeuAbstrait::~JeuAbstrait() {
}

void JeuAbstrait::recevoirInputs(int mouseX, int mouseY, int boutton, int touche, int scroll) {
	// La derniere position de la souris 
	lastMouseX_ = mouseX_;
	lastMouseY_ = mouseY_;
	// La derniere touche du clavier
	previousTouche_ = touche_;

	// Une fois la derniere position attribuee, la position courante peut etre assignee
	mouseX_  = mouseX;
	mouseY_  = mouseY;

	boutton_ = boutton;
	touche_  = touche;
	scroll_  = scroll;
}

void JeuAbstrait::setCarte(Carte& carte) {
	carte_ = carte;
}

void JeuAbstrait::setVue(vue::Vue* vue) {
	vue_ = vue;
}

void JeuAbstrait::setPourcentageDeplacement(bool estOrtho){

	if(estOrtho){
		pourcentageDeplacement_ = 0.1f;
	}else{
		pourcentageDeplacement_ = -10.0f;
	}

}

void JeuAbstrait::update(float deltaT){
	// Si le boutton droite de la souris est appuye on deplace.
	if(boutton_ == 3){
		vue_->deplacerXY( Vecteur2i(mouseX_-lastMouseX_, mouseY_-lastMouseY_) );
	// Evite d'avoir un deplacement avec la souris en plus d'un deplacement avec le clavier.
	// Priorise le bouton quand il n'y a pas de commande.
	} else 	{
		// Liste des entiers correspondant aux fleches
		// haut = 38;  gauche = 37;  bas = 40;  droite = 39
		if(previousTouche_!=touche_)
		{
			switch(touche_)
			{
			case 38:
				vue_->deplacerXY( 0.0,  -pourcentageDeplacement_ );
				break;
			case 40:
				vue_->deplacerXY( 0.0, pourcentageDeplacement_ );
				break;
			case 37:
				vue_->deplacerXY( pourcentageDeplacement_, 0.0 );
				break;
			case 39:
				vue_->deplacerXY(  -pourcentageDeplacement_, 0.0 );
				break;
			default:
				break;
			}
		}
	}
}