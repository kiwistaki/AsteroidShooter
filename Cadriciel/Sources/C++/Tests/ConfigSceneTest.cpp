////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigSceneTest.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigSceneTest.h"
#include "FacadeModele.h"
#include "../ElementObjet/Station.h"
#include "Jeu\JeuAbstrait.h"

#include "../../../Commun/Utilitaire/Utilitaire.h"


// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( ConfigSceneTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigSceneTest::setUp()
{
	// On donne le nom a la carte
	nom_ = "TestUnitaire.xml";
	// Initialiser
	FacadeModele::obtenirInstance()->initialiser();
	FacadeModele::obtenirInstance()->initialiserModeEdition();

	// On cree une carte
	//carte_ = FacadeModele::obtenirInstance()->getCarte();
	carte_ = new Carte(nom_,FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigSceneTest::tearDown()
{
	// On detruit la carte
	delete carte_;
	// Detruire l'instance
	FacadeModele::obtenirInstance()->libererInstance();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::testSauvegardeChargement()
///
/// Cas de test: sauvegarde et chargement XML de la configuration
/// Modifier la valeur de la difficulte, enregistrer la configuration,
/// restaurer la valeur de la difficulte, charger la configuration,
/// s'assurer que la valeur sauvegardée a bien été restaurée du fichier
/// XML, restaurer la valeur par défaut.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigSceneTest::testSauvegardeChargement()
{
   	// On ajoute une station pour pouvoir sauvegarder le fichier XML
	Station *stationTest = new Station();
	FacadeModele::obtenirInstance()->getCarte()->ajouterElement(stationTest);

	// On modifie la difficulte
	FacadeModele::obtenirInstance()->getCarte()->setDifficulte(2);

	// On sauvegarde le XML...
	FacadeModele::obtenirInstance()->enregistrerConfiguration(nom_);

	// On remet les valeurs par défaut
	FacadeModele::obtenirInstance()->getCarte()->setDifficulte(1);

	// On charge le XML...
	FacadeModele::obtenirInstance()->chargerConfiguration(nom_);
	
	// On vérifie si les valeurs de test sont celles qui ont bien été chargées
	CPPUNIT_ASSERT( FacadeModele::obtenirInstance()->getCarte()->getDifficulte() == 2 );

	// On réaffecte les valeurs par défaut
	FacadeModele::obtenirInstance()->getCarte()->setDifficulte(1);

	// On resauvegarde le XML
	FacadeModele::obtenirInstance()->enregistrerConfiguration(nom_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::testAjoutStation()
///
/// Cas de test: Ajoute un element avec une taille augmenter a la carte, 
/// sauvegarde la carte, modifie la taille et charge la carte de nouveau.
/// S'assurer que la taille est la bonne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigSceneTest::testTaille()
{/*
	// On cree un element et on augmente sa taille
	Station *stationTest = new Station(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990());
	aiVector3D taille = ( 2.0f, 3.0f, 4.0f);
	stationTest->setTaille(taille);

	// On set la difficulte pour pouvoir enregistrer le fichier 
	FacadeModele::obtenirInstance()->getCarte()->setDifficulte(2);

	// On ajoute l'élément
	FacadeModele::obtenirInstance()->getCarte()->ajouterElement(stationTest);

	// On sauvegarde le XML
	FacadeModele::obtenirInstance()->enregistrerConfiguration(nom_);

	// On modifie la taille
	aiVector3D taille2 = ( 1.0f, 1.0f, 1.0f);
	stationTest->setTaille(taille2);

	// On charge le XML
	FacadeModele::obtenirInstance()->chargerConfiguration(nom_);

	// On vérifie si les valeurs de test sont celles qui ont bien été chargées
	CPPUNIT_ASSERT( FacadeModele::obtenirInstance()->getCarte()->getVecteurElement().back()->getTaille()[0] == 2.0f ); // tailleX
	CPPUNIT_ASSERT( FacadeModele::obtenirInstance()->getCarte()->getVecteurElement().back()->getTaille()[1] == 3.0f ); // tailleY
	CPPUNIT_ASSERT( FacadeModele::obtenirInstance()->getCarte()->getVecteurElement().back()->getTaille()[2] == 4.0f ); // tailleZ

	// On retire l'élément
	FacadeModele::obtenirInstance()->getCarte()->effacerElement(stationTest);

	// On resauvegarde le XML
	FacadeModele::obtenirInstance()->enregistrerConfiguration(nom_);*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigSceneTest::testAjoutStation()
///
/// Cas de test: Ajoute un element avec une rotation modifiée a la carte, 
/// sauvegarde la carte, modifie la rotation et charge la carte de nouveau.
/// S'assurer que la rotation est la bonne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigSceneTest::testRotation()
{/*
	// On cree un element et on effectue une rotation
	Station *stationTest = new Station(FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990());
	stationTest->setAxe(Vecteur3f(0.0, 0.0, 1.0));
	stationTest->setAngle(180.0);

	// On set la difficulte pour pouvoir enregistrer le fichier 
	FacadeModele::obtenirInstance()->getCarte()->setDifficulte(2);

	// On ajoute l'élément
	FacadeModele::obtenirInstance()->getCarte()->ajouterElement(stationTest);

	// On sauvegarde le XML
	FacadeModele::obtenirInstance()->enregistrerConfiguration(nom_);

	// On modifie la taille
	stationTest->setAngle(90);

	// On charge le XML
	FacadeModele::obtenirInstance()->chargerConfiguration(nom_);

	// On vérifie si les valeurs de test sont celles qui ont bien été chargées
	//CPPUNIT_ASSERT( FacadeModele::obtenirInstance()->getCarte()->getVecteurElement().back()->getAngle() == 180.0 ); 
	CPPUNIT_ASSERT( FacadeModele::obtenirInstance()->getCarte()->getVecteurElement().back()->getAxe()[0] ==  0.0 ); // AxeX
	CPPUNIT_ASSERT( FacadeModele::obtenirInstance()->getCarte()->getVecteurElement().back()->getAxe()[1] ==  0.0 ); // AxeY
	CPPUNIT_ASSERT( FacadeModele::obtenirInstance()->getCarte()->getVecteurElement().back()->getAxe()[2] ==  1.0 ); // AxeZ

	// On retire l'élément
	FacadeModele::obtenirInstance()->getCarte()->effacerElement(stationTest);

	// On resauvegarde le XML
	FacadeModele::obtenirInstance()->enregistrerConfiguration(nom_);*/
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
