//////////////////////////////////////////////////////////////////////////////
/// @file BoiteEnglobanteOrientee.h
/// @author The FloppyDisketeers
/// @date 2014-02-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef BOITE_ENGLOBANTE_ORIENTEE_TEST_H
#define BOITE_ENGLOBANTE_ORIENTEE_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../../Commun/Utilitaire/BoiteEnglobanteOrientee.h"

/**
 * @class BoiteEnglobanteOrienteeTest
 * @brief Test qui s'assure que les operations effectuees sur les boites englobantes orientees
 * sont fonctionnelles.
 */
class BoiteEnglobanteOrienteeTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(BoiteEnglobanteOrienteeTest);
	CPPUNIT_TEST(testCalculerCollision);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

		/**
		 * S'assure que la collision entre deux boites fonctionnent
		 * correctement
		 */
		void testCalculerCollision();
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////