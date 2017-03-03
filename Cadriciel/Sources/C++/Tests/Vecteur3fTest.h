//////////////////////////////////////////////////////////////////////////////
/// @file Vecteur3fTest.h
/// @author The FloppyDisketeers
/// @date 2014-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef VECTEUR3F_TEST_H
#define VECTEUR3F_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../../Commun/Utilitaire/Vecteur.h"

/**
 * @class Vecteur3fTest
 * @brief Test qui s'assure que les operations importantes d'un vecteur mathematique sont
 *        fonctionnelles
 */
class Vecteur3fTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(Vecteur3fTest);
	CPPUNIT_TEST(testProduitScalaire);
	CPPUNIT_TEST(testProduitVectoriel);
	CPPUNIT_TEST(testReflexion);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

		/**
		 * Effectue un produit scalaire entre deux vecteurs
		 */
		void testProduitScalaire();

		/**
		 * Effectue un produit vectoriel entre deux vecteur
		 */
		void testProduitVectoriel();

		/**
		 * Effectue la reflexion d'un vecteur par rapport a une normale
		 */
		void testReflexion();
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////