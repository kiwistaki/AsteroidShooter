////////////////////////////////////////////////////////////////////////////////////
/// @file TestVaisseau.cpp
/// @author FloppyDisketeers
/// @date 2014-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "TestVaisseau.h"
#include "aiVector3D.h"
#include "GestionnaireXML.h"

#include "../Application/FacadeModele.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( TestVaisseau );

////////////////////////////////////////////////////////////////////////
///
/// @fn void TestVaisseau::setUp()
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
void TestVaisseau::setUp()
{
	FacadeModele::obtenirInstance()->initialiser();
	FacadeModele::obtenirInstance()->initialiserModeEdition();
	element_ = new VaisseauJoueur();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TestVaisseau::tearDown()
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
void TestVaisseau::tearDown()
{
	delete element_;
	FacadeModele::obtenirInstance()->libererInstance();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TestVaisseau::testAngle()
///
/// Cas de test: Ajoute un angle a l'element et
/// s'assurer que l'angle est le bon.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TestVaisseau::testAngle()
{
	float angle = 90.0;
	element_->setAngle(angle);

	CPPUNIT_ASSERT(element_->getAngle() == angle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TestVaisseau::testPosition()
///
/// Cas de test: Ajoute une position de depart et une position actuelle a 
/// l'element et s'assurer qu'elles sont bonnes.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TestVaisseau::testPosition()
{
	aiVector3D position = (1.9f,2.0f,2.1f);
	element_->setPositionActuelle(position);
	element_->setPositionDepart(position);

	// Test pour la position actuelle
	CPPUNIT_ASSERT(element_->getPositionActuelle().x == position.x);
	CPPUNIT_ASSERT(element_->getPositionActuelle().y == position.y);
	CPPUNIT_ASSERT(element_->getPositionActuelle().z == position.z);
	// Test pour la position de depart
	CPPUNIT_ASSERT(element_->getPositionDepart().x == position.x);
	CPPUNIT_ASSERT(element_->getPositionDepart().y == position.y);
	CPPUNIT_ASSERT(element_->getPositionDepart().z == position.z);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TestVaisseau::testAxe()
///
/// Cas de test: Ajoute un axe a 
/// l'element et s'assurer qu'il est bon.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TestVaisseau::testAxe()
{
	Vecteur3f axe = (0.0f, 1.0f, 0.0f);
	element_->setAxe( axe );

	//Test sur chaque composante du vecteur
	CPPUNIT_ASSERT(element_->getAxe().x == axe[0]);
	CPPUNIT_ASSERT(element_->getAxe().y == axe[1]);
	CPPUNIT_ASSERT(element_->getAxe().z == axe[2]);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TestVaisseau::testVitesse()
///
/// Cas de test: Ajoute une vitesse a 
/// l'element et s'assurer qu'elle est bonne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TestVaisseau::testVitesse()
{
	aiVector3D directionVitesse = ( 1.0f, 2.0f, 3.0f);
	element_->setDirectionVitesse( directionVitesse );

	//Test sur chaque composante du vecteur
	CPPUNIT_ASSERT(element_->getDirectionVitesse().x == directionVitesse.x);
	CPPUNIT_ASSERT(element_->getDirectionVitesse().y == directionVitesse.y);
	CPPUNIT_ASSERT(element_->getDirectionVitesse().z == directionVitesse.z);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TestVaisseau::testId()
///
/// Cas de test: Ajoute un id a 
/// l'element et s'assurer qu'il est bon.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TestVaisseau::testId()
{
	unsigned int id = 22;
	element_->setId( id );

	CPPUNIT_ASSERT( element_->getId() == id);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TestVaisseau::testPoids()
///
/// Cas de test: Ajoute un poids a 
/// l'element et s'assurer qu'il est bon.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TestVaisseau::testPoids()
{
	float poids = 22;
	element_->setPoids( poids);

	CPPUNIT_ASSERT( element_->getPoids() == poids);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void TestVaisseau::testTaille()
///
/// Cas de test: Ajoute une taille a 
/// l'element et s'assurer qu'elle est bonne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void TestVaisseau::testTaille()
{
	aiVector3D taille = ( 1.0f, 2.0f, 3.0f);
	element_->setTaille( taille );

	//Test sur chaque composante du vecteur
	CPPUNIT_ASSERT(element_->getTaille().x == taille.x);
	CPPUNIT_ASSERT(element_->getTaille().y == taille.y);
	CPPUNIT_ASSERT(element_->getTaille().z == taille.z);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////