#include "ModePartieRapide.h"

using namespace std;

ModePartieRapide::ModePartieRapide(Carte& carte, vue::Vue* vue) : ModeJeu(carte, vue)
{
}

ModePartieRapide::~ModePartieRapide()
{
}

void ModePartieRapide::update(float deltaT)
{
	if(carte_.joueurIsProcheCadre()){
		carte_.dessinerCadreZoneDeJeu();
	}

	ModeJeu::update(deltaT);

}