////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstraitTest.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudAbstraitTest.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( NoeudAbstraitTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::setUp()
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
void NoeudAbstraitTest::setUp()
{
	noeud = new NoeudVaisseau(ArbreRenduINF2990::NOM_VAISSEAU);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::tearDown()
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
void NoeudAbstraitTest::tearDown()
{
	delete noeud;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testPositionRelative()
///
/// Cas de test: ecriture/lecture de la position relative
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testPositionRelative()
{
	noeud->assignerPositionRelative(Vecteur3(2.2, 3.3, 4.4));

	Vecteur3 vecteur = noeud->obtenirPositionRelative();

	CPPUNIT_ASSERT( utilitaire::EGAL_ZERO(vecteur[0] - 2.2) );
	CPPUNIT_ASSERT( utilitaire::EGAL_ZERO(vecteur[1] - 3.3) );
	CPPUNIT_ASSERT( utilitaire::EGAL_ZERO(vecteur[2] - 4.4) );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testType()
///
/// Cas de test: type de noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testType()
{
	CPPUNIT_ASSERT( noeud->obtenirType() == ArbreRenduINF2990::NOM_VAISSEAU );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testEtat()
///
/// Cas de test: definition/obtention de l'etat (booleens) du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testEtat()
{
	// Regler tous les etats (booleens) a faux
	noeud->assignerAffiche(false);
	noeud->assignerEstEnregistrable(false);

	// Verifier que la valeur attribuee est fausse
	CPPUNIT_ASSERT( noeud->estAffiche() == false );
	CPPUNIT_ASSERT( noeud->estEnregistrable() == false );

	// Regler tous les etats (booleens) a true
	noeud->assignerAffiche(true);
	noeud->assignerEstEnregistrable(true);

	// Verifier que la valeur attribuee est fausse
	CPPUNIT_ASSERT( noeud->estAffiche() == true );
	CPPUNIT_ASSERT( noeud->estEnregistrable() == true );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testSelection()
///
/// Cas de test: definition/obtention des etats de selection du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testSelection()
{
	// Cas 1 : non selectionnable, non selectionne
	noeud->assignerEstSelectionnable(false);
	noeud->assignerSelection(false);
	CPPUNIT_ASSERT( noeud->estSelectionnable() == false );
	CPPUNIT_ASSERT( noeud->estSelectionne() == false );

	// Cas 2 : non selectionnable, selectionne
	noeud->assignerEstSelectionnable(false);
	noeud->assignerSelection(true);
	CPPUNIT_ASSERT( noeud->estSelectionnable() == false );
	CPPUNIT_ASSERT( noeud->estSelectionne() == false );

	// Cas 3 : selectionnable, non selectionne
	noeud->assignerEstSelectionnable(true);
	noeud->assignerSelection(false);
	CPPUNIT_ASSERT( noeud->estSelectionnable() == true );
	CPPUNIT_ASSERT( noeud->estSelectionne() == false );

	// Cas 4 : non selectionnable, selectionne
	noeud->assignerEstSelectionnable(true);
	noeud->assignerSelection(true);
	CPPUNIT_ASSERT( noeud->estSelectionnable() == true );
	CPPUNIT_ASSERT( noeud->estSelectionne() == true );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testEnfants()
///
/// Cas de test: s'assurer que le noeud abstrait n'a pas d'enfant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testEnfants()
{
	CPPUNIT_ASSERT( noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT( noeud->calculerProfondeur() == 1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testAjout()
///
/// Cas de test: s'assurer qu'il est impossible d'ajouter un enfant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testAjout()
{
	// Essaie d'ajouter un noeud
	NoeudAbstrait* nouveauNoeud = new NoeudVaisseau(ArbreRenduINF2990::NOM_VAISSEAU);
	bool ajout = noeud->ajouter(nouveauNoeud);

	// L'ajout devrait avoir echoue puisqu'il s'agit d'un noeud abstrait...
	CPPUNIT_ASSERT( ajout==false );

	// Assurons-nous que le noeud ne possede pas d'enfant...
	CPPUNIT_ASSERT( noeud->obtenirNombreEnfants() == 0 );

	// Nettoyage
	delete nouveauNoeud;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////