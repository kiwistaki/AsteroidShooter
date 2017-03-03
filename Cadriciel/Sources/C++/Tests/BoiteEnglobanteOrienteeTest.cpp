//////////////////////////////////////////////////////////////////////////////
/// @file BoiteEnglobanteOrientee.cpp
/// @author The FloppyDisketeers
/// @date 2014-02-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#include "BoiteEnglobanteOrienteeTest.h"

#include "../../Commun/Utilitaire/Vecteur.h"
#include "../../Commun/Externe/assimp/include/aiVector3D.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BoiteEnglobanteOrienteeTest);

void BoiteEnglobanteOrienteeTest::setUp() {
}

void BoiteEnglobanteOrienteeTest::tearDown() {
}

void BoiteEnglobanteOrienteeTest::testCalculerCollision() {
	// Deux boites l'une dans l'autre
	math::BoiteEnglobanteOrientee obb1(Vecteur3f(0.0f, 0.0f, 0.0f), Vecteur3f(10.0f, 10.0f, 0.0f));
	math::BoiteEnglobanteOrientee obb2(Vecteur3f(0.0f, 0.0f, 0.0f), Vecteur3f(10.0f, 10.0f, 0.0f));

	CPPUNIT_ASSERT(obb1.calculerCollision(obb2));

	// On les separe
	obb2.update(aiVector3D(15.0f, 0.0f, 0.0f), 0.0f, aiVector3D(1.0f, 1.0f, 1.0f));

	CPPUNIT_ASSERT(!obb1.calculerCollision(obb2));

	// On en oriente un a -90 degre
	obb2.update(aiVector3D(15.0f, 0.0f, 0.0f), -90.0f, aiVector3D(1.0f, 1.0f, 1.0f));

	// Il ne devrait pas encore collisioner car ils sont separes et que la rotation l'a
	// plus deplace vers la droite
	CPPUNIT_ASSERT(!obb1.calculerCollision(obb2));

	// On redeplace la boite
	obb2.update(aiVector3D(5.0f, 0.0f, 0.0f), 90.0f, aiVector3D(1.0f, 1.0f, 1.0f));

	CPPUNIT_ASSERT(obb1.calculerCollision(obb2));
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////