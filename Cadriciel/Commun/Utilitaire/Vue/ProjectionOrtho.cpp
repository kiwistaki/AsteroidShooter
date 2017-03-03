////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/gl.h>
#include "ProjectionOrtho.h"
#include "Camera.h"
#include "VueOrtho.h"

#define RATIO (16.0f/9.0f)

namespace vue 
{
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] xMinCloture   : coordonnee minimale en @a x de la clôture.
	/// @param[in] xMaxCloture   : coordonnee maximale en @a x de la clôture.
	/// @param[in] yMinCloture   : coordonnee minimale en @a y de la clôture.
	/// @param[in] yMaxCloture   : coordonnee maximale en @a y de la clôture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arriere (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arriere (en @a z).
	/// @param[in] xMinFenetre   : coordonnee minimale en @a x de la fenetre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonnee maximale en @a x de la fenetre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonnee minimale en @a y de la fenetre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonnee maximale en @a y de la fenetre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant,  double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double xMinFenetre, double xMaxFenetre,
		double yMinFenetre, double yMaxFenetre) :
	Projection(xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false) ,
		xMinFenetre_(xMinFenetre),
		xMaxFenetre_(xMaxFenetre),
		yMinFenetre_(yMinFenetre),
		yMaxFenetre_(yMaxFenetre)
	{
		premiereRedimensionnement_ = true;
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'increment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn() 
	{
		double longueurFenetreXChCote( (xMaxFenetre_-xMinFenetre_)/2.0f );
		double longueurFenetreYChCote( (yMaxFenetre_-yMinFenetre_)/2.0f );
		Vecteur2 pointCentreCourrant( (xMaxFenetre_+xMinFenetre_)/2.0f, (yMaxFenetre_+yMinFenetre_)/2.0f );
		
		// Le facteur de zoom est le rapport entre le rapport de la fenetre et de la cloture
		// Ce rapport doit etre superieur afin de pouvoir continuer a zoomer in
		// Si le prochain zoom donne un rapport plus grand que le zoom minimal
		if( ( (xMaxFenetre_-xMinFenetre_-(2.0*longueurFenetreXChCote*incrementZoom_))/(xMaxCloture_-xMinCloture_) ) > zoomInMax_ ) // pour empecher d'avoir un zoom qui inverse les min et max.
		{
			xMinFenetre_ = pointCentreCourrant[0]-longueurFenetreXChCote/(1.0+incrementZoom_);
			xMaxFenetre_ = pointCentreCourrant[0]+longueurFenetreXChCote/(1.0+incrementZoom_);
			yMinFenetre_ = pointCentreCourrant[1]-longueurFenetreYChCote/(1.0+incrementZoom_);
			yMaxFenetre_ = pointCentreCourrant[1]+longueurFenetreYChCote/(1.0+incrementZoom_);
		}
		else
		{
			xMinFenetre_ = pointCentreCourrant[0] - ((double)xMaxCloture_-(double)xMinCloture_)/2.0f*zoomInMax_;
			xMaxFenetre_ = pointCentreCourrant[0] + ((double)xMaxCloture_-(double)xMinCloture_)/2.0f*zoomInMax_;
			yMinFenetre_ = pointCentreCourrant[1] - ((double)yMaxCloture_-(double)yMinCloture_)/2.0f*zoomInMax_;
			yMaxFenetre_ = pointCentreCourrant[1] + ((double)yMaxCloture_-(double)yMinCloture_)/2.0f*zoomInMax_;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'increment de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut() 
	{
		double longueurFenetreXChCote( (xMaxFenetre_-xMinFenetre_)/2.0f );
		double longueurFenetreYChCote( (yMaxFenetre_-yMinFenetre_)/2.0f );
		Vecteur2 pointCentreCourrant( (xMaxFenetre_+xMinFenetre_)/2.0f, (yMaxFenetre_+yMinFenetre_)/2.0f );

		// Si le prochain zoom out respecte encore la limite, on peut le faire, sinon on l'etabli a la taille avec le bon rapport
		if( ( (xMaxFenetre_-xMinFenetre_+(2.0*longueurFenetreXChCote*incrementZoom_))/(xMaxCloture_-xMinCloture_) ) < zoomOutMax_ )
		{
			xMinFenetre_ = pointCentreCourrant[0]-longueurFenetreXChCote*(1.0+incrementZoom_);
			xMaxFenetre_ = pointCentreCourrant[0]+longueurFenetreXChCote*(1.0+incrementZoom_);
			yMinFenetre_ = pointCentreCourrant[1]-longueurFenetreYChCote*(1.0+incrementZoom_);
			yMaxFenetre_ = pointCentreCourrant[1]+longueurFenetreYChCote*(1.0+incrementZoom_);
		}
		else
		{
			xMinFenetre_ = pointCentreCourrant[0] - ((double)xMaxCloture_-(double)xMinCloture_)/2.0f*zoomOutMax_;
			xMaxFenetre_ = pointCentreCourrant[0] + ((double)xMaxCloture_-(double)xMinCloture_)/2.0f*zoomOutMax_;
			yMinFenetre_ = pointCentreCourrant[1] - ((double)yMaxCloture_-(double)yMinCloture_)/2.0f*zoomOutMax_;
			yMaxFenetre_ = pointCentreCourrant[1] + ((double)yMaxCloture_-(double)yMinCloture_)/2.0f*zoomOutMax_;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( const Vecteur2i& coinMin, const Vecteur2i& coinMax )
	///
	/// Permet d'ajuster les coordonnees de la fenetre virtuelle en fonction
	/// d'un redimensionnement de la fenetre.
	///
	/// L'agrandissement de la fenetre virtuelle est proportionnel a
	/// l'agrandissement de la clotûre afin que les objets gardent la meme
	/// grandeur apparente lorsque la fenetre est redimensionnee.
	///
	/// @param[in]  coinMin : Coin contenant les coordonnees minimales de la
	///                       nouvelle clôture
	/// @param[in]  coinMax : Coin contenant les coordonnees maximales de la
	///                       nouvelle clôture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre( const Vecteur2i& coinMin,
		const Vecteur2i& coinMax )
	{
		/*
		 L'image va etre modifie des le depart etant donne que le xMaxCloture est
		 initialement d'une taille quelconque et qu'il sera redimensionne puisqu'on
		 le canvas possede une taille differente de l'initialisation, le redimensionnement
		 sera effectue.
		 
		 Lorsque le canvas grossit, la cloture devient plus grande, alors il faut
		 grossir les parametres de la fenetre (qui est utilise dans glOrtho) afin
		 que nous puissions voir plus d'informations dans notre viewport et que
		 l'image reste de la meme taille.
		*/

		double pourcentageGrossissement = ((double)coinMax[0]-(double)coinMin[0])/((double)xMaxCloture_-(double)xMinCloture_);
		
		Vecteur2 pointCentreCourrant( (xMaxFenetre_+xMinFenetre_)/2.0f, (yMaxFenetre_+yMinFenetre_)/2.0f );


		// Quantite de fenetre a ajouter ou retirer des deux cote de la fenetre actuelle.
		double nouveauLargeurFenetre = ((double)xMaxFenetre_-(double)xMinFenetre_)*pourcentageGrossissement;
		double nouveauHauteurFenetre = ((double)yMaxFenetre_-(double)yMinFenetre_)*pourcentageGrossissement;

		// Puisque Java envoie les coordonnees ayant deja les bonnes proportions, 
		// il n'est pas necessaire d'effectuer les calculs pour maintenir le ratio.
		// Effectuer operation si le Canvas change de dimension.
		if(pourcentageGrossissement != 1)
		{		
			// Le premier redimensionnement cause probleme, donc juste empecher de changer la 
			// fenetre lorsque c'est le premier reimensionnement
			xMinFenetre_ = pointCentreCourrant[0] - nouveauLargeurFenetre/2.0f;
			xMaxFenetre_ = pointCentreCourrant[0] + nouveauLargeurFenetre/2.0f;
			yMinFenetre_ = pointCentreCourrant[1] - nouveauHauteurFenetre/2.0f;
			yMaxFenetre_ = pointCentreCourrant[1] + nouveauHauteurFenetre/2.0f;
		
			xMinCloture_ = coinMin[0];
			xMaxCloture_ = coinMax[0];
			yMinCloture_ = coinMin[1];
			yMaxCloture_ = coinMax[1];
		
			glViewport( xMinCloture_, yMinCloture_, xMaxCloture_, yMaxCloture_ );
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::appliquer() const
	///
	/// Cette fonction permet d'appliquer la fenetre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les proprietes de la
	/// fenetre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::appliquer() const
	{
		glOrtho(xMinFenetre_, xMaxFenetre_,	yMinFenetre_, yMaxFenetre_,	zAvant_, zArriere_ );
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn( const Vecteur2i& coin1, const Vecteur2i& coin2)
	///
	/// Permet de faire un zoom in sur un rectangle determine par deux coins.
	/// Ainsi la region delimitee par le rectangle deviendra la fenetre
	/// virtuelle.  La fenetre resultante est ajustee pour respecter le rapport
	/// d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxieme coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn( const Vecteur2i& coin1, const Vecteur2i& coin2 ) 
	{
		Vecteur2 coin1Virtuelle;
		Vecteur2 coin2Virtuelle;

		ProjectionOrtho::convertirClotureAVirtuelle(coin1[0], coin1[1], coin1Virtuelle[0], coin1Virtuelle[1]);
		ProjectionOrtho::convertirClotureAVirtuelle(coin2[0], coin2[1], coin2Virtuelle[0], coin2Virtuelle[1]);

		// Verifier la direction du rectangle
		double largeurRectangle( abs(coin2Virtuelle[0]-coin1Virtuelle[0]) );
		double hauteurRectangle( abs(coin2Virtuelle[1]-coin1Virtuelle[1]) );

		Vecteur2 nouveauPointCentral( (coin2Virtuelle[0]+coin1Virtuelle[0])/2.0f, (coin2Virtuelle[1]+coin1Virtuelle[1])/2.0f );

		// Si le rectangle depasse les limites de la cloture
		if( coin2Virtuelle[0] < xMinFenetre_ || coin2Virtuelle[0] > xMaxFenetre_ ||
			coin2Virtuelle[1] < yMinFenetre_ || coin2Virtuelle[1] > yMaxFenetre_ ){
			return;
		}

		// Si le rectangle dessine est plus petit que la limite inferieur
		// de la fenetre que nous pouvons voir, limiter les dimensions
		// Un ET (&&), car le rectangle sera utilise avec la plus grosse valeur de largeur ou hauteur
		if( (largeurRectangle/((float)xMaxCloture_-(float)xMinCloture_) < zoomInMax_) && 
			(hauteurRectangle/((float)yMaxCloture_-(float)yMinCloture_) < zoomInMax_) )
		{
			xMinFenetre_ = nouveauPointCentral[0] - ( (xMaxCloture_-xMinCloture_)/2.0f )*zoomInMax_;
			xMaxFenetre_ = nouveauPointCentral[0] + ( (xMaxCloture_-xMinCloture_)/2.0f )*zoomInMax_;
			yMinFenetre_ = nouveauPointCentral[1] - ( (yMaxCloture_-yMinCloture_)/2.0f )*zoomInMax_;
			yMaxFenetre_ = nouveauPointCentral[1] + ( (yMaxCloture_-yMinCloture_)/2.0f )*zoomInMax_;
			
			return;
		}
		
		// Effectuer le zoom selon quel cote est plus grand que l'autre
		if( largeurRectangle > hauteurRectangle )
		{
			xMinFenetre_ = nouveauPointCentral[0] - (largeurRectangle/2.0f);
			xMaxFenetre_ = nouveauPointCentral[0] + (largeurRectangle/2.0f);
			yMinFenetre_ = nouveauPointCentral[1] - (largeurRectangle/2.0f)/RATIO;
			yMaxFenetre_ = nouveauPointCentral[1] + (largeurRectangle/2.0f)/RATIO;
		}
		else
		{
			xMinFenetre_ = nouveauPointCentral[0] - (hauteurRectangle/2.0f)*RATIO;
			xMaxFenetre_ = nouveauPointCentral[0] + (hauteurRectangle/2.0f)*RATIO;
			yMinFenetre_ = nouveauPointCentral[1] - (hauteurRectangle/2.0f);
			yMaxFenetre_ = nouveauPointCentral[1] + (hauteurRectangle/2.0f);
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut( const Vecteur2i& coin1, const Vecteur2i& coin2)
	///
	/// Permet de faire un zoom out sur un rectangle delimite par deux coins.
	/// Ainsi la fenetre virtuelle avant le zoom sera placee a l'interieur de
	/// la region delimite par le rectangle.  La fenetre resultante est ajustee
	/// pour respecter le rapport d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxieme coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerOut( const Vecteur2i& coin1, const Vecteur2i& coin2 ) 
	{
		Vecteur2 coin1Virtuelle;
		Vecteur2 coin2Virtuelle;

		ProjectionOrtho::convertirClotureAVirtuelle(coin1[0], coin1[1], coin1Virtuelle[0], coin1Virtuelle[1]);
		ProjectionOrtho::convertirClotureAVirtuelle(coin2[0], coin2[1], coin2Virtuelle[0], coin2Virtuelle[1]);

		// Conserver le pointCentral avant la transformation
		Vecteur2 ancienCentreFenetre( (xMaxFenetre_+xMinFenetre_)/2.0f, (yMaxFenetre_+yMinFenetre_)/2.0f );
		
		double largeurFenetre( xMaxFenetre_-xMinFenetre_ );
		double hauteurFenetre( yMaxFenetre_-yMinFenetre_ );
	
		// Si le rectangle depasse les limites de la cloture
		if( coin2Virtuelle[0] < xMinFenetre_ || coin2Virtuelle[0] > xMaxFenetre_ ||
			coin2Virtuelle[1] < yMinFenetre_ || coin2Virtuelle[1] > yMaxFenetre_ ){
			return;
		}

		double pourcentageChangementClotureX( (xMaxCloture_-xMinCloture_)/abs((float)coin2[0]-(float)coin1[0]) );
		double pourcentageChangementClotureY( (yMaxCloture_-yMinCloture_)/abs((float)coin2[1]-(float)coin1[1]) );
		
		// Si le rectangle doit contenir trop de pixels de la fenetre actuelle juste limite l'operation
		// Condition ||, mais je ne sais pas pourquoi (verifier si le grandissement suivant cause un depassement)
		// LE RATIO DANS LE IF EST PEUT-ETRE A ENLEVER
		if( ((pourcentageChangementClotureX*(xMaxFenetre_-xMinFenetre_)/(xMaxCloture_-xMinCloture_)) > zoomOutMax_) || 
			((pourcentageChangementClotureY*(yMaxFenetre_-yMinFenetre_)/(yMaxCloture_-yMinCloture_)) > zoomOutMax_/RATIO) )
		{
			// Le decalage dans le cas 
			// Il faut faire l'ajout du centre ici
			xMinFenetre_ = - ( (xMaxCloture_-xMinCloture_)/2.0f )*zoomOutMax_;
			xMaxFenetre_ = + ( (xMaxCloture_-xMinCloture_)/2.0f )*zoomOutMax_;
			yMinFenetre_ = - ( (yMaxCloture_-yMinCloture_)/2.0f )*zoomOutMax_;
			yMaxFenetre_ = + ( (yMaxCloture_-yMinCloture_)/2.0f )*zoomOutMax_;
		}
		else
		{
			// Effectuer un zoom avec le plus petit cote du rectangle, donc celui qui cause le plus de zoomm out
			if (pourcentageChangementClotureX > pourcentageChangementClotureY)
			{
				xMinFenetre_ = -largeurFenetre*pourcentageChangementClotureX/2.0f;
				xMaxFenetre_ = +largeurFenetre*pourcentageChangementClotureX/2.0f;
				yMinFenetre_ = -hauteurFenetre*pourcentageChangementClotureX/2.0f;
				yMaxFenetre_ = +hauteurFenetre*pourcentageChangementClotureX/2.0f;
			}				   
			else			   
			{				   
				xMinFenetre_ = -largeurFenetre*pourcentageChangementClotureY/2.0f;
				xMaxFenetre_ = +largeurFenetre*pourcentageChangementClotureY/2.0f;
				yMinFenetre_ = -hauteurFenetre*pourcentageChangementClotureY/2.0f;
				yMaxFenetre_ = +hauteurFenetre*pourcentageChangementClotureY/2.0f;
			}
		}
		
		// Avoir le nouveau point de la fenetre avec la nouvelle grandeur de fenetre 
		// A faire apres la modification des xMin/MaxFenetre sinon le decalage sera different
		Vecteur2 nouveauCentreFenetre;
		// Convertir le point central de la cloture dans la fenetre virtuelle
		ProjectionOrtho::convertirClotureAVirtuelle( (coin2[0]+coin1[0])/2, (coin2[1]+coin1[1])/2, 
													  nouveauCentreFenetre[0], nouveauCentreFenetre[1] );
		// Calculer le decalage du point central de la cloture converti en virtuelle avec l'ancien fenetre
		Vecteur2 decalageDuFenetre( nouveauCentreFenetre[0]-ancienCentreFenetre[0], nouveauCentreFenetre[1]-ancienCentreFenetre[1] );
		
		// Effectuer le decalage, un moins pour deplacer dans le sens contraire
		xMinFenetre_ -= decalageDuFenetre[0];
		xMaxFenetre_ -= decalageDuFenetre[0];
		yMinFenetre_ -= decalageDuFenetre[1];
		yMaxFenetre_ -= decalageDuFenetre[1];
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater( double deplacementX, double deplacementY )
	///
	/// Permet de deplacer la fenetre virtuelle en @a x et en @a y.  Les
	/// deplacement doivent etre exprimes en proportion de la fenetre virtuelle.
	///
	/// @param[in]  deplacementX : le deplacement en @a x (en pourcentage).
	/// @param[in]  deplacementY : le deplacement en @a y (en pourcentage).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater( double deplacementX, double deplacementY )
	{
		double largeurFenetre( xMaxFenetre_-xMinFenetre_ );
		double hauteurFenetre( yMaxFenetre_-yMinFenetre_ );

		xMinFenetre_ += largeurFenetre*deplacementX/2.0f;
		xMaxFenetre_ += largeurFenetre*deplacementX/2.0f;
		yMinFenetre_ += largeurFenetre*deplacementY/2.0f;
		yMaxFenetre_ += largeurFenetre*deplacementY/2.0f;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater(const Vecteur2i& deplacement)
	///
	/// Permet de translater la fenetre virtuelle en fonction d'un deplacement
	/// en coordonnees de clôture.
	///
	/// @param[in]  deplacement : Le deplacement en coordonnees de clôture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater( const Vecteur2i& deplacement )
	{
		// Le deplacement en y dans le canvas est l'inverse du deplacement de cloture d'ou le -deplacement[1]
		Vecteur2 deplacementEnCloture( deplacement[0], -deplacement[1]);
		
		double largeurFenetre( xMaxFenetre_-xMinFenetre_ );
		double hauteurFenetre( yMaxFenetre_-yMinFenetre_ );
		
		// Rapport entre le decalage de cloture selon la grandeur de la cloture actuelle
		float pourcentageDeplacementClotureX( (float)deplacementEnCloture[0]/((float)xMaxCloture_-(float)xMinCloture_) );
		float pourcentageDeplacementClotureY( (float)deplacementEnCloture[1]/((float)yMaxCloture_-(float)yMinCloture_) );

		// Ne pas diviser la largeur par 2. Je ne sais pas pourquoi il ne faut pas le faire.
		xMinFenetre_ -= largeurFenetre*pourcentageDeplacementClotureX;
		xMaxFenetre_ -= largeurFenetre*pourcentageDeplacementClotureX;
		yMinFenetre_ -= hauteurFenetre*pourcentageDeplacementClotureY;
		yMaxFenetre_ -= hauteurFenetre*pourcentageDeplacementClotureY;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::centrerSurPoint( const Vecteur2i& pointCentre )
	///
	/// Permet de centrer la fenetre virtuelle sur un point de l'ecran. Le
	/// point de l'ecran est convertit en coordonnees virtuelles et il devient
	/// le centre de la fenetre virtuelle.
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::centrerSurPoint( const Vecteur2i& pointCentre ) 
	{
		Vecteur2 pointCentreCourrant( (xMaxFenetre_+xMinFenetre_)/2.0f, (yMaxFenetre_+yMinFenetre_)/2.0f );
		Vecteur2 decalageParRapportCentre( pointCentre[0]-pointCentreCourrant[0], pointCentre[1]-pointCentreCourrant[1] );
		
		xMinFenetre_ += decalageParRapportCentre[0];
		xMaxFenetre_ += decalageParRapportCentre[0];
					 
		yMinFenetre_ += decalageParRapportCentre[1];
		yMaxFenetre_ += decalageParRapportCentre[1];	
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonnees de la fenetre virtuelle en fonction
	/// de la clôture de facon a ce que le rapport d'aspect soit respecte.
	/// Les tailles des fenetres sont entierement overwrited.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect() 
	{
		if( ((float)xMaxCloture_-(float)xMinCloture_)/((float)yMaxCloture_-(float)yMinCloture_) != RATIO)
		{
			xMaxCloture_ = 0;
			xMaxCloture_ = (int)(((float)yMaxCloture_-(float)yMinCloture_)*RATIO);
		}
		
		xMinFenetre_ = -((float)yMaxFenetre_-(float)yMinFenetre_)/2.0f*RATIO;
		xMaxFenetre_ =  ((float)yMaxFenetre_-(float)yMinFenetre_)/2.0f*RATIO;
		yMinFenetre_ = -((float)yMaxFenetre_-(float)yMinFenetre_)/2.0f;
		yMaxFenetre_ =  ((float)yMaxFenetre_-(float)yMinFenetre_)/2.0f;

/*
		xMinFenetre_ = -((float)xMaxCloture_-(float)xMinCloture_);
		xMaxFenetre_ =  ((float)xMaxCloture_-(float)xMinCloture_);
		yMinFenetre_ = -((float)yMaxCloture_-(float)yMinCloture_);
		yMaxFenetre_ =  ((float)yMaxCloture_-(float)yMinCloture_);
*/
		
	}				 


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::convertirClotureAVirtuelle( int i, int j, double& x, double& y ) const 
	///
	/// Permet de calculer les coordonnees dans l'espace virtuel d'un point
	/// specifie en coordonnees d'affichage.  Utilise le calcul des rapports.
	///
	/// @param[in]  i : coordonnee @a i du point dans l'espace d'affichage.
	/// @param[in]  j : coordonnee @a j du point dans l'espace d'affichage.
	/// @param[out] x : coordonnee @a x du point dans l'espace virtuel.
	/// @param[out] y : coordonnee @a y du point dans l'espace virtuel.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::convertirClotureAVirtuelle( int i,
		int j,
		double& x,
		double& y ) const
	{
		// Transformer j dans les coordonnes cartesien du viewport.
		j = yMaxCloture_ - j;

		// Effectuer un calcul de rapport pour voir la position en pourcentage par rapport 
		// au point (0,0) et decaler par rapport a l'endroit minimale de la fenetre
		x = (double)xMinFenetre_ + (double)i/((double)xMaxCloture_-(double)xMinCloture_)*((double)xMaxFenetre_-(double)xMinFenetre_);
		y = (double)yMinFenetre_ + (double)j/((double)yMaxCloture_-(double)yMinCloture_)*((double)yMaxFenetre_-(double)yMinFenetre_);
	}


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
