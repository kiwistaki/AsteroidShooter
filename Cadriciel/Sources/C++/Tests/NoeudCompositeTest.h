//////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.h
/// @author The FloppyDisketeers
/// @date 2014-02-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef NOEUDCOMPOSITE_TEST_H
#define NOEUDCOMPOSITE_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../../Commun/Utilitaire/Vecteur.h"
#include "../Arbre/Noeuds/NoeudComposite.h"
#include "../Arbre/Noeuds/NoeudAbstrait.h"

/**
 * @class NoeudCompositeTest
 * @brief Test qui s'assure que les operations importantes d'un noeud composite sont
 *        fonctionnelles
 */
class NoeudCompositeTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NoeudCompositeTest);
	CPPUNIT_TEST( testAjouter );
	CPPUNIT_TEST( testChercher );
	CPPUNIT_TEST( testCalculerProfondeur );
	CPPUNIT_TEST( testEffacer );
	CPPUNIT_TEST( testObtenirNombreEnfant );
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

		void testCalculerProfondeur();
		void testChercher();
		void testAjouter();
		void testEffacer();
		void testObtenirNombreEnfant();

private:
	NoeudComposite* noeud_;

};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////