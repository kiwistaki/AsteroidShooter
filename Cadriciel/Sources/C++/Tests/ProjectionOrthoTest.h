
//////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.h
/// @author FloppyDisketeers
/// @date 2014-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_PROJECTIONORTHOTEST_H
#define _TESTS_PROJECTIONORTHOTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../../../Commun/Utilitaire/Vue/Vue.h"
#include "../../../Commun/Utilitaire/Vue/VueOrtho.h"
#include "../../../Commun/Utilitaire/Vue/ProjectionOrtho.h"


///////////////////////////////////////////////////////////////////////////
/// @class ProjectionOrthoTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        methodes de la classe ProjectionOrtho
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class ProjectionOrthoTest : public CppUnit::TestFixture
{

	// =================================================================
	// Declaration de la suite de tests et des methodes de tests
	//
	// Important, vous devez definir chacun de vos cas de tests a l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas execute !
	// =================================================================
  CPPUNIT_TEST_SUITE( ProjectionOrthoTest );
  {
	  CPPUNIT_TEST( testZoomerInOut );
	  CPPUNIT_TEST( ajusterRapportAspect );
	  CPPUNIT_TEST( testRedimensionFenetre );
  }
  CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Methodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement a effectuer pour initialiser cette suite de tests
	void		setUp();

	/// Traitement a effectuer pour 'finaliser' cette suite de tests
	void		tearDown();


	// =================================================================
	// Definissez ici les differents cas de tests...
	// =================================================================

	/// Cas de test: zoomer in out avec le scroll de la souris
	void		testZoomerInOut();

	/// Cas de test: definition/obtention de l'etat (booleens) du noeud
	void		ajusterRapportAspect();

	/// Cas de test: definition/obtention de l'etat (booleens) du noeud
	void		testRedimensionFenetre();

private:
	/// Instance de la la classe Projection Ortho.
	vue::ProjectionOrtho* projOrtho_;
};

#endif // _TESTS_PROJECTIONORTHOTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////