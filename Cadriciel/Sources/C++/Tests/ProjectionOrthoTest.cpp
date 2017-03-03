////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.cpp
/// @author FloppyDisketeers
/// @date 2014-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ProjectionOrthoTest.h"
#include "../../../Commun/Utilitaire/Utilitaire.h"
#include "../../../Commun/Utilitaire/Droite3D.h"
#include "../../../Commun/Utilitaire/Plan3D.h"

#define RATIO (16.0f/9.0f)

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( ProjectionOrthoTest );


////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::setUp()
///
/// Effectue l'initialisation prealable a l'execution de l'ensemble des
/// cas de tests de cette suite de tests (si necessaire).
/// 
/// Si certains objets doivent etre construits, il est conseille de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::setUp()
{
	projOrtho_ = new vue::ProjectionOrtho( 0,	  100,	// Cloture X
										   0,	  200,	// Cloture Y
										 -10,	   10,	// Z Avant Arriere
									   0.10f,	20.0f,	// ZoomInMax, ZoomOutMax
									   0.05f,			// IncrementZoom
										-500,	 1000,	// Fenetre X
										-1000,   1000);	// Fenetre Y
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::tearDown()
///
/// Effectue les operations de finalisation necessaires suite a l'execution
/// de l'ensemble des cas de tests de cette suite de tests (si necessaire).
/// 
/// Si certains objets ont ete alloues a l'initialisation, ils doivent etre
/// desalloues, et il est conseille de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::tearDown()
{
	delete projOrtho_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testZoomerInOut()
///
/// Cas de test: Tester si on effectue le meme nombre de zoom in
///				 et de zoom out, on revient a la situation de depart.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomerInOut()
{
	Vecteur4 fenetreAvantZoom;
	projOrtho_->obtenirCoordonneesFenetreVirtuelle(fenetreAvantZoom[0], fenetreAvantZoom[1], 
												   fenetreAvantZoom[2], fenetreAvantZoom[3]);
	Vecteur2 pointCentralAvantZoom( (fenetreAvantZoom[0]+fenetreAvantZoom[1])/2.0f, 
									(fenetreAvantZoom[2]+fenetreAvantZoom[3])/2.0f );

	for(int i=0; i<10; ++i){
		projOrtho_->zoomerOut();
	}

	for(int i=0; i<10; ++i){
		projOrtho_->zoomerIn();
	}

	Vecteur4 fenetreApresZoom;
	projOrtho_->obtenirCoordonneesFenetreVirtuelle(fenetreApresZoom[0], fenetreApresZoom[1], 
												   fenetreApresZoom[2], fenetreApresZoom[3]);
	Vecteur2 pointCentralApresZoom( (fenetreApresZoom[0]+fenetreApresZoom[1])/2.0f, 
									(fenetreApresZoom[2]+fenetreApresZoom[3])/2.0f );

	// Verifier que l'on zoom toujours dans le centre
	CPPUNIT_ASSERT(pointCentralAvantZoom==pointCentralApresZoom);
	// 4 car taille du vecteur est de 4 et on veut verifier les 4 bounds.
	for(int i = 0; i < 4; ++i){
		CPPUNIT_ASSERT( abs(fenetreAvantZoom[i]-fenetreApresZoom[i]) < utilitaire::EPSILON );
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::ajusterRapportAspect()
///
/// Cas de test: S'assurer que le rapport d'aspect est respecte.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::ajusterRapportAspect()
{
	// Dans l'instanciation d'une projection orthogonale, ajusterRapportAspect()
	// sera appele, donc il ne reste qu'a verifier les rapports.
	Vecteur4 fenetreVirtuelle;
	Vecteur2i cloture( projOrtho_->obtenirDimensionCloture() );
	projOrtho_->obtenirCoordonneesFenetreVirtuelle(fenetreVirtuelle[0], fenetreVirtuelle[1], 
												   fenetreVirtuelle[2], fenetreVirtuelle[3]);
	
	double rapportFenetre( (fenetreVirtuelle[1]-fenetreVirtuelle[0])/(fenetreVirtuelle[3]-fenetreVirtuelle[2]) );
	double rapportCloture( (double)cloture[0]/(double)cloture[1] );	
	
	// Si le ratio de la fenetre et le ratio de la cloture sont equivalentes,
	// alors le ratio entre ces deux devraient etre le meme, donc equivalent a 1.
	CPPUNIT_ASSERT( abs(1.0f-(rapportFenetre/rapportCloture) < utilitaire::EPSILON) );
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testRedimensionFenetre()
///
/// Cas de test: s'assurer que le rapport entre les tailles des clotures
///				 les tailles des fenetres reste toujours pareil.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testRedimensionFenetre()
{
	// Puisque Java nous envoie toujours les dimensions de la cloture dans 
	// le bon rapport d'aspect, on suppose que l'on obtient des parametres 
	// avec le bon rapport d'aspect, il ne reste qu'a verifier si le rapport
	// entre la fenetre et la cloture reste pareil.
	for(int largeurCloture = 200; largeurCloture < 1080; ++largeurCloture)
	{
		int hauteurCloture = (int)(largeurCloture/RATIO);
		projOrtho_->redimensionnerFenetre( Vecteur2i(0, 0), Vecteur2i(largeurCloture, hauteurCloture) );

		// Meme code que le test d'ajustement de rapport d'aspect.
		Vecteur4 fenetreVirtuelle;
		Vecteur2 cloture( projOrtho_->obtenirDimensionCloture() );
		projOrtho_->obtenirCoordonneesFenetreVirtuelle(fenetreVirtuelle[0], fenetreVirtuelle[1], 
													   fenetreVirtuelle[2], fenetreVirtuelle[3]);
	
		double rapportFenetre( (fenetreVirtuelle[1]-fenetreVirtuelle[0])/(fenetreVirtuelle[3]-fenetreVirtuelle[2]) );
		double rapportCloture( (double)cloture[0]/(double)cloture[1] );	

		// On verifie si la difference est inferieure a 1%, qui est une limite acceptable.
		CPPUNIT_ASSERT( (abs(1.0f-rapportFenetre/rapportCloture) < (1.0f/100.0f)) );
	}
}

	
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////