////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author The FloppyDisketeers
/// @date 2014-02-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////
#include "NoeudCompositeTest.h"

#include "Utilitaire.h"

CPPUNIT_TEST_SUITE_REGISTRATION(NoeudCompositeTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
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
void NoeudCompositeTest::setUp() {
	noeud_ = new NoeudComposite("Noeud Composite");
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::tearDown()
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
void NoeudCompositeTest::tearDown() {
	noeud_->vider();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testCalculerProfondeur()
///
/// Cas de test: Calculer la profondeur de l'arbre de noeud en ajoutant 
/// un noeud abstrait au vecteur de noeud abstrait.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testCalculerProfondeur(){
	NoeudAbstrait* noeudAbstrait = new NoeudAbstrait("Noeud Abstrait");
	noeud_->ajouter(noeudAbstrait);
	CPPUNIT_ASSERT( noeud_->calculerProfondeur() == 2 );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testChercher()
///
/// Cas de test: Ajoute un noeud abstrait au conteneur d'enfants et
/// ensuite verifie que celui-ci se retrouve dans le conteneur en faisant
/// une recherche avec son nom.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testChercher(){
	NoeudAbstrait* noeudAbstrait = new NoeudAbstrait("Noeud Abstrait");
	noeud_->ajouter(noeudAbstrait);
	CPPUNIT_ASSERT( noeud_->chercher("Noeud Abstrait") == noeudAbstrait );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testAjouter()
///
/// Cas de test: Ajoute un noeud abstrait au conteneur d'enfants et
/// ensuite verifie que celui-ci se retrouve dans le conteneur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testAjouter(){
	NoeudAbstrait* noeudAbstrait = new NoeudAbstrait("Noeud Abstrait");
	noeud_->ajouter(noeudAbstrait);
	CPPUNIT_ASSERT( noeud_->getEnfants()[0] == noeudAbstrait );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEffacer()
///
/// Cas de test: Ajoute un noeud abstrait au conteneur d'enfants et
/// ensuite verifie que celui-ci ne se retrouve pas dans le conteneur
/// apres sa suppression.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacer(){
	NoeudAbstrait* noeudAbstrait = new NoeudAbstrait("Noeud Abstrait");
	noeud_->ajouter(noeudAbstrait);
	noeud_->effacer(noeudAbstrait);
	CPPUNIT_ASSERT( noeud_->chercher("Noeud Abstrait") == 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testObtenirNombreEnfant()
///
/// Cas de test: Ajoute un noeud abstrait au conteneur d'enfants et
/// ensuite vérifie le nombre d'enfant que le conteneur contient.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testObtenirNombreEnfant(){
	NoeudAbstrait* noeudAbstrait = new NoeudAbstrait("Noeud Abstrait");
	noeud_->ajouter(noeudAbstrait);
	CPPUNIT_ASSERT( noeud_->obtenirNombreEnfants() == 1 );
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////