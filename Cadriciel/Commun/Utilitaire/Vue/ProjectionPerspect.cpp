#include <windows.h>
#include <GL/gl.h>
#include <GL/GLU.h>
#include "ProjectionPerspect.h"
#include "Camera.h"
#include "VuePerspect.h"

#define RATIO (16.0f/9.0f)

namespace vue {

	ProjectionPerspect::ProjectionPerspect( int xMinCloture, int xMaxCloture,
											int yMinCloture, int yMaxCloture,
											double zAvant,  double zArriere,
											double zoomInMax, double zoomOutMax,
											double incrementZoom,
											double xMinFenetre, double xMaxFenetre,
											double yMinFenetre, double yMaxFenetre) :
											Projection( xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
														zAvant, zArriere,
														zoomInMax, zoomOutMax, incrementZoom, true) ,
											xMinFenetre_(xMinFenetre),
											xMaxFenetre_(xMaxFenetre),
											yMinFenetre_(yMinFenetre),
											yMaxFenetre_(yMaxFenetre)


	{
		premiereRedimensionnement_ = true;
		ajusterRapportAspect();
	}

	/// Zoom in, c'est-a-dire un grossissement. - Pas défini pour la projection en perspective
	void ProjectionPerspect::zoomerIn(){
		//
	}

    /// Zoom out, c'est-a-dire un rapetissement. - Pas défini pour la projection en perspective
    void ProjectionPerspect::zoomerOut(){
		//
	}

	
    /// Modification de la clôture.
    void ProjectionPerspect::redimensionnerFenetre( const Vecteur2i& coinMin, const Vecteur2i& coinMax )	{
	
		double pourcentageGrossissement = ((double)coinMax[0]-(double)coinMin[0])/((double)xMaxCloture_-(double)xMinCloture_);
		
		Vecteur2 pointCentreCourrant( (xMaxFenetre_+xMinFenetre_)/2.0f, (yMaxFenetre_+yMinFenetre_)/2.0f );


		// Quantite de fenetre a ajouter ou retirer des deux cote de la fenetre actuelle.
		double nouveauLargeurFenetre = ((double)xMaxFenetre_-(double)xMinFenetre_)*pourcentageGrossissement;
		double nouveauHauteurFenetre = ((double)yMaxFenetre_-(double)yMinFenetre_)*pourcentageGrossissement;

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

	void ProjectionPerspect::ajusterRapportAspect() 
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
	
	}

    /// Application de la projection.
    void ProjectionPerspect::appliquer() const {
		gluPerspective(30.0, RATIO, zAvant_, zArriere_);
		
	}



};