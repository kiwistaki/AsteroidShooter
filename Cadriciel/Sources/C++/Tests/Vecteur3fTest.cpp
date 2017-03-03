////////////////////////////////////////////////////////////////////////////////////
/// @file Vecteur3fTest.cpp
/// @author The FloppyDisketeers
/// @date 2014-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////
#include "Vecteur3fTest.h"

#include "Utilitaire.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Vecteur3fTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vecteur3fTest::setUp()
///
/// Effectue l'initialisation prealable a l'execution de l'ensemble des
/// cas de tests de cette suite de tests (si necessaire).
/// 
/// Aucun objet a initialiser
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Vecteur3fTest::setUp() {
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vecteur3fTest::tearDown()
///
/// Effectue les operations de finalisation necessaires suite a l'execution
/// de l'ensemble des cas de tests de cette suite de tests (si necessaire).
/// 
/// Aucun objet a detruire
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Vecteur3fTest::tearDown() {
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vecteur3fTest::testProduitScalaire()
///
/// Cas de test: Tester si le produit scalaire fonctionne correctement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Vecteur3fTest::testProduitScalaire() {
	Vecteur3f u(1.0f, 2.0f, 3.0f);
	Vecteur3f v(4.0f, 5.0f, 6.0f);

	float dot = produitScalaire(u, v);

	CPPUNIT_ASSERT(dot == 32.0f);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vecteur3fTest::testProduitVectoriel()
///
/// Cas de test: Tester si le produit vectoriel fonctionne correctement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Vecteur3fTest::testProduitVectoriel() {
	Vecteur3f u(1.0f, 0.0f, 0.0f);
	Vecteur3f v(0.0f, 1.0f, 0.0f);

	Vecteur3f w = produitVectoriel(u, v);

	CPPUNIT_ASSERT(w == Vecteur3f(0.0f, 0.0f, 1.0f));
	
	w = produitVectoriel(v, u);

	CPPUNIT_ASSERT(w == Vecteur3f(0.0f, 0.0f, -1.0f));

	u[0] = -1.0f;
	u[1] =  7.0f;
	u[2] =  4.0f;

	v[0] = -5.0f;
	v[1] =  8.0f;
	v[2] =  4.0f;

	w = produitVectoriel(u, v);

	CPPUNIT_ASSERT(w == Vecteur3f(-4.0f, -16.0f, 27.0f));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vecteur3fTest::testReflexion()
///
/// Cas de test: Tester si la reflexion fonctionne correctement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Vecteur3fTest::testReflexion() {
	Vecteur3f u(1.0f, -1.0f, 0.0f);
	Vecteur3f n(0.0f, 1.0f, 0.0f);

	Vecteur3f r = calculerReflexion(u, n);

	CPPUNIT_ASSERT(r == Vecteur3f(1.0f, 1.0f, 0.0f));
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////