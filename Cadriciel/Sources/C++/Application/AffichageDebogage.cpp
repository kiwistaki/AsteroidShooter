//////////////////////////////////////////////////////////////////////////////
/// @file AffichageDebogage.cpp
/// @author Vincent Longpre
/// @date 2014-02-25
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#define DEUX_PI 6.28319

#include "AffichageDebogage.h"

#include <iostream>
#include <Windows.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <GL/gl.h>
#include <gl/GLU.h>

AffichageDebogage* AffichageDebogage::instance_ = NULL;

AffichageDebogage* AffichageDebogage::obtenirInstance()
{
	if (instance_ == NULL)
		instance_ = new AffichageDebogage();

	return instance_;
}

void AffichageDebogage::afficherApparitionAsteroide(aiVector3D position, aiVector3D vitesse, unsigned int taille) const
{
	if (afficherApparitionAsteroide_)
	{
		cout << obtenirTempsCourant();
		cout << " - Creation d'asteroide : ";
		cout << "x: " << position.x;
		cout << "  y: " << position.y;
		cout << "  vitesse: " << sqrt(vitesse.x * vitesse.x + vitesse.y * vitesse.y + vitesse.z * vitesse.z);
		cout << "  taille: " << taille << endl;
	}
}

void AffichageDebogage::afficherChangementModeJoueurVirtuel(Mode mode) const
{
	if (afficherChangementModeJoueurVirtuel_)
	{
		cout << obtenirTempsCourant();
		cout << " - JV passage au mode : ";

		switch (mode)
		{
		case RECHERCHE:
			cout << "RECHERCHE";
			break;
		case APPROCHE:
			cout << "APPROCHE";
			break;
		case ATTAQUE:
			cout << "ATTAQUE";
			break;
		default:
			break;
		}

		cout << endl;
	}
}

void AffichageDebogage::afficherModificationEclairage(unsigned int typeLumiere, bool etatActuel) const
{
	if (afficherModificationEclairage_)
	{
		cout << obtenirTempsCourant();
		cout << " - Lumiere(s) ";

		switch (typeLumiere)
		{
		case 0:
			cout << "ambiante ";
			break;
		case 1:
			cout << "directionnelle ";
			break;
		case 2:
			cout << "d'appoints ";
			break;
		default:
			break;
		}

		if (etatActuel)
			cout << "ouverte(s)";
		else
			cout << "fermee(s)";

		cout << endl;
	}
}

void AffichageDebogage::afficherRayonAttraction(const NoeudPortail* nPortail) const
{
	if (afficherRayonAttraction_)
	{
		glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		// Le rayon d'attraction doit etre de 3 fois le rayon de l'objet
		float rayonAttraction = 3.0f * nPortail->getBoiteEnglobanteOrientee().getMoitieLongueur();

		// Nb de sommets pour dessiner le cercle
		unsigned int nbSommets = 32; // 32 sommets suffisant pour un affichage debogage

		glColor3f(0.09f, 0.65f, 0.71f); // Teal-ish color

		glMatrixMode(GL_MODELVIEW); // Choisir la matrice de modelisation
		glBegin(GL_LINE_LOOP); // Primitive line_loop
		for (unsigned int i = 0; i < nbSommets; i++)
		{
			// Dessiner le cercle
			glVertex2f((GLfloat) (nPortail->getPosition().x + (rayonAttraction * cos(i * DEUX_PI / nbSommets))),
				(GLfloat) (nPortail->getPosition().y + (rayonAttraction * sin(i * DEUX_PI / nbSommets))));
		}
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

		glPopAttrib();
	}
}

void AffichageDebogage::afficherAsteroideCibleJoueurVirtuel(const NoeudAsteroide* nAsteroide) const
{
	if (afficherAsteroideCible_)
	{
		glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		
		float rayon = 1.5f * nAsteroide->getRayon(); // Rayon du cercle

		// Nb de sommets pour dessiner le cercle
		unsigned int nbSommets = 32;

		glColor3f(1.0f, 0.0f, 0.0f); // Rouge

		glMatrixMode(GL_MODELVIEW);
		glBegin(GL_LINE_LOOP);
		for (unsigned int i = 0; i < nbSommets; i++)
		{
			// Dessiner le cercle
			glVertex2f((GLfloat) (nAsteroide->getPosition().x + (rayon * cos(i * DEUX_PI / nbSommets))),
			(GLfloat) (nAsteroide->getPosition().y + (rayon * sin(i * DEUX_PI / nbSommets))));
		}
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

		glPopAttrib();
	}
}

void AffichageDebogage::afficherZonePassage(const Carte* carte) const
{
	if (afficherZonePassage_)
	{
		Vecteur4f coins = carte->getCoinsZonePassage(); // Les XY min/max de la zone de passage

		glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glColor3f(0.35f, 0.55f, 1.0f); // Blue tron-ish color

		glMatrixMode(GL_MODELVIEW);
		glBegin(GL_LINE_LOOP);
			glVertex2f(coins[0], coins[2]); // xMin yMin
			glVertex2f(coins[0], coins[3]); // xMin yMax
			glVertex2f(coins[1], coins[3]); // xMax yMax
			glVertex2f(coins[1], coins[2]); // xMax yMin
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

		glPopAttrib();
	}
}

void AffichageDebogage::afficherCadreDepart(const Carte* carte) const
{
	if (afficherCadreDepart_)
	{
		Vecteur4f coins = carte->getCoinsCadreDepart(); // Les XY min/max du cadre de depart

		glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glColor3f(1.0f, 0.55f, 0.0f); // Orange color

		glMatrixMode(GL_MODELVIEW);
		glBegin(GL_LINE_LOOP);
			glVertex2f(coins[0], coins[2]); // xMin yMin
			glVertex2f(coins[0], coins[3]); // xMin yMax
			glVertex2f(coins[1], coins[3]); // xMax yMax
			glVertex2f(coins[1], coins[2]); // xMax yMin
		glEnd();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

		glPopAttrib();
	}
}

void AffichageDebogage::setAfficherApparitionAsteroide(bool affichage)
{
	afficherApparitionAsteroide_ = affichage;
}

void AffichageDebogage::setAfficherChangementModeJoueurVirtuel(bool affichage)
{
	afficherChangementModeJoueurVirtuel_ = affichage;
}

void AffichageDebogage::setAfficherModificationEclairage(bool affichage)
{
	afficherModificationEclairage_ = affichage;
}

void AffichageDebogage::setAfficherRayonAttraction(bool affichage)
{
	afficherRayonAttraction_ = affichage;
}

void AffichageDebogage::setAfficherAsteroideCible(bool affichage)
{
	afficherAsteroideCible_ = affichage;
}

void AffichageDebogage::setAfficherZonePassage(bool affichage)
{
	afficherZonePassage_ = affichage;
}

void AffichageDebogage::setAfficherCadreDepart(bool affichage)
{
	afficherCadreDepart_ = affichage;
}

AffichageDebogage::AffichageDebogage() : afficherApparitionAsteroide_(false),
										 afficherChangementModeJoueurVirtuel_(false),
										 afficherModificationEclairage_(false),
										 afficherRayonAttraction_(false),
										 afficherAsteroideCible_(false),
										 afficherZonePassage_(false)
{}

AffichageDebogage::~AffichageDebogage()
{}

string AffichageDebogage::obtenirTempsCourant() const
{
	// Cette facon de faire permet d'obtenir un temps avec une precision en millisecondes
	SYSTEMTIME temps;
	GetLocalTime(&temps); // Obtenir le temps local du systeme

	stringstream ss; // Stream pour permettre la conversion de nombres en string

	// Largeur de 2, padding de 0
	ss << setw(2) << setfill('0') << temps.wHour << ":";
	ss << setw(2) << setfill('0') << temps.wMinute << ":";
	ss << setw(2) << setfill('0') << temps.wSecond << ":";
	ss << setw(2) << setfill('0') << temps.wMilliseconds;

	return ss.str().substr(0, 11); // La chaine de caracteres finale
}