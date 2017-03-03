//////////////////////////////////////////////////////////////////////////////
/// @file TestVaisseau.h
/// @author FloppyDisketeers
/// @date 2014-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_VAISSEAU_H
#define _TESTS_VAISSEAU_H

#include <cppunit/extensions/HelperMacros.h>
#include "../ElementObjet/VaisseauJoueur.h"
#include "../Arbre/ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class TestVaisseau
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        methodes de la classe ConfigScene
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class TestVaisseau : public CppUnit::TestFixture
{

	// =================================================================
	// Declaration de la suite de tests et des methodes de tests
	//
	// Important, vous devez definir chacun de vos cas de tests a l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas execute !
	// =================================================================
   CPPUNIT_TEST_SUITE( TestVaisseau );
   CPPUNIT_TEST(  testAngle );
   CPPUNIT_TEST(  testVitesse );
   CPPUNIT_TEST(  testPosition );
   CPPUNIT_TEST(  testAxe );
   CPPUNIT_TEST(  testId );
   CPPUNIT_TEST(  testPoids );
   CPPUNIT_TEST(  testTaille );
   CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Methodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement a effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement a effectuer pour 'finaliser' cette suite de tests
	void tearDown();

	// =================================================================
	// Definissez ici les differents cas de tests...
	// =================================================================

	void testAngle();
	void testPosition();
	void testAxe();
	void testVitesse();
	void testId();
	void testPoids();
	void testTaille();

private:
	Vaisseau* element_;
	ArbreRenduINF2990* arbreRendu_;
};

#endif // _TESTS_VAISSEAU_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////