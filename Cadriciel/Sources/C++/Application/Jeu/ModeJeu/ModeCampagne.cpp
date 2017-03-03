#include "ModeCampagne.h"
#include "../../GestionnaireXML.h"
#include "../../FacadeModele.h"
#include "../../../../../Commun/Utilitaire/Utilitaire.h"

using namespace std;

ModeCampagne::ModeCampagne(Carte& carte, vue::Vue* vue, vector<string> cartes,
	bool modeCoop, bool joueur2Virtuel) : ModeJeu(carte, vue)
{
	// Enfiler le nom des cartes a charger
	for (unsigned int i = 0; i < cartes.size(); i++)
		file_.push(cartes[i]);

	prochaineCarte(modeCoop, joueur2Virtuel); // Recuperer la premiere carte
}

ModeCampagne::~ModeCampagne()
{}

void ModeCampagne::update(float deltaT)
{
	if (FacadeModele::obtenirInstance()->getStatutJeu() == 1) // Si la partie est gagnée
	{
		bool modeCoop = carte_.getModeCoop();
		bool joueur2Virtuel = carte_.getJoueur2Virtuel();

		FacadeModele::obtenirInstance()->setStatutJeu(0); // Partie en cours
		prochaineCarte(modeCoop, joueur2Virtuel); // Selectionner la prochaine carte
	}
	
	if(carte_.joueurIsProcheCadre()){
		carte_.dessinerCadreZoneDeJeu();
	}

	ModeJeu::update(deltaT);

	if (FacadeModele::obtenirInstance()->getStatutJeu() == 1) // Si la partie est gagnée
	{
		FacadeModele::obtenirInstance()->setTempsJeu((int) FacadeModele::obtenirInstance()->getDureeJeu()); // Resetter la minuterie

		if (file_.size() == 0)
			FacadeModele::obtenirInstance()->setStatutJeu(2);
	}

	JeuAbstrait::update(deltaT);
}

void ModeCampagne::prochaineCarte(bool modeCoop, bool joueur2Virtuel)
{
	if (file_.size() > 0)
	{
		Carte* carte;
		if (utilitaire::fichierExiste(file_.top()))
		{
			carte = GestionnaireXML::obtenirInstance()->chargerCarte(file_.top());
		}
		else
		{
			carte = GestionnaireXML::obtenirInstance()->chargerCarteCampagneDefaut();
		}
		carte->definirModeJoueurs(modeCoop, joueur2Virtuel);

		carte_ = *carte;
		delete carte;
		file_.pop();

		traitementInitial(); // Effectuer le traitement initial sur la carte
	}
}	