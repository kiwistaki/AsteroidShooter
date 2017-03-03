//////////////////////////////////////////////////////////////////////////////
/// @file ConfigSceneTest.h
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_CONFIGSCENETEST_H
#define _TESTS_CONFIGSCENETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ConfigScene.h"
#include "GestionnaireXML.h"

///////////////////////////////////////////////////////////////////////////
/// @class ConfigSceneTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        methodes de la classe ConfigScene
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class ConfigSceneTest : public CppUnit::TestFixture
{

	// =================================================================
	// Declaration de la suite de tests et des methodes de tests
	//
	// Important, vous devez definir chacun de vos cas de tests a l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas execute !
	// =================================================================
   CPPUNIT_TEST_SUITE( ConfigSceneTest );
   CPPUNIT_TEST( testSauvegardeChargement );/*
   CPPUNIT_TEST( testTaille );
   CPPUNIT_TEST( testRotation );*/
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

	/// Cas de test: sauvegarde et chargement XML d'une carte
	void testSauvegardeChargement();

	/// Cas de test: sauvegarde et chargment correct de la taille d'un element
	void testTaille();

	/// Cas de test: sauvegarde et chargment correct de la rotation d'un element
	void testRotation();

private:
	/// Instance d'une carte
	Carte *carte_;

	/// Nom de la carte a sauvegarder/enregistrer
	string nom_;
};

#endif // _TESTS_CONFIGSCENETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
