//////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstraitTest.h
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDABSTRAITTEST_H
#define _TESTS_NOEUDABSTRAITTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "NoeudVaisseau.h"
#include "ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstraitTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        methodes de la classe NoeudAbstrait
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class NoeudAbstraitTest : public CppUnit::TestFixture
{

	// =================================================================
	// Declaration de la suite de tests et des methodes de tests
	//
	// Important, vous devez definir chacun de vos cas de tests a l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas execute !
	// =================================================================
  CPPUNIT_TEST_SUITE( NoeudAbstraitTest );/*
  CPPUNIT_TEST( testPositionRelative );
  CPPUNIT_TEST( testType );
  CPPUNIT_TEST( testEtat );
  CPPUNIT_TEST( testSelection );
  CPPUNIT_TEST( testEnfants );
  CPPUNIT_TEST( testAjout );*/
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

	/// Cas de test: ecriture/lecture de la position relative
	void testPositionRelative();

	/// Cas de test: type de noeud
	void testType();

	/// Cas de test: definition/obtention de l'etat (booleens) du noeud
	void testEtat();

	/// Cas de test: definition/obtention des etats de selection du noeud
	void testSelection();

	/// Cas de test: s'assurer que le noeud abstrait n'a pas d'enfant
	void testEnfants();

	/// Cas de test: s'assurer qu'il est impossible d'ajouter un enfant
	void testAjout();

private:
	/// Instance d'un noeud abstrait
	NoeudVaisseau* noeud;
};

#endif // _TESTS_NOEUDABSTRAITTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////