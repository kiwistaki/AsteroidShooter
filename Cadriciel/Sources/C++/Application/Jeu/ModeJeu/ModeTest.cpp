#include "ModeTest.h"

using namespace std;

ModeTest::ModeTest(Carte& carte, vue::Vue* vue) : ModeJeu(carte, vue)
{
}

ModeTest::~ModeTest()
{
}

/// Update recoit les informations et laisse le jeu analyser les donnees
void ModeTest::update(float deltaT)
{

	carte_.update(deltaT);
	logiqueVaisseaux(deltaT);
	carte_.detruireObjets();
	
	if(carte_.joueurIsProcheCadre()){
		carte_.dessinerCadreZoneDeJeu();
	}

	JeuAbstrait::update(deltaT);


}