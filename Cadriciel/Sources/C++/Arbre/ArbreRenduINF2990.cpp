///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"

#include "Usines/UsineNoeudAccelerateur.h"
#include "Usines/UsineNoeudAsteroide.h"
#include "Usines/UsineNoeudBarriere.h"
#include "Usines/UsineNoeudPortail.h"
#include "Usines/UsineNoeudProjectile.h"
#include "Usines/UsineNoeudStation.h"
#include "Usines/UsineNoeudVaisseau.h"
#include "Usines/UsineNoeudPositionDepart.h"

#include "EtatOpenGL.h"

// TEMP changer ca pour un enum?
// Chaîne pour les types 
const std::string ArbreRenduINF2990::NOM_ACCELERATEUR		= "Accelerateur";
const std::string ArbreRenduINF2990::NOM_ASTEROIDE			= "Asteroide";
const std::string ArbreRenduINF2990::NOM_BARRIERE			= "Bbarriere";
const std::string ArbreRenduINF2990::NOM_PORTAIL			= "Portail";
const std::string ArbreRenduINF2990::NOM_PROJECTILE			= "Projectile";
const std::string ArbreRenduINF2990::NOM_STATION			= "Station";
const std::string ArbreRenduINF2990::NOM_VAISSEAU			= "Vaisseau";
const std::string ArbreRenduINF2990::NOM_POSITION_DEPART	= "PositionDepart";

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur cree toutes les usines qui seront utilisees par le
/// projet de INF2990et les enregistre aupres de la classe de base.
/// Il cree egalement la structure de base de l'arbre de rendu, c'est-a-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	ajouterUsine(NOM_ACCELERATEUR, new UsineNoeudAccelerateur(NOM_ACCELERATEUR));
	ajouterUsine(NOM_ASTEROIDE, new UsineNoeudAsteroide(NOM_ASTEROIDE));
	ajouterUsine(NOM_BARRIERE, new UsineNoeudBarriere(NOM_BARRIERE));
	ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail(NOM_PORTAIL));
	ajouterUsine(NOM_PROJECTILE, new UsineNoeudProjectile(NOM_PROJECTILE));
	ajouterUsine(NOM_STATION, new UsineNoeudStation(NOM_STATION));
	ajouterUsine(NOM_VAISSEAU, new UsineNoeudVaisseau(NOM_VAISSEAU));
	ajouterUsine(NOM_POSITION_DEPART, new UsineNoeudVaisseau(NOM_POSITION_DEPART));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction cree la structure de base de l'arbre de rendu, c'est-a-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
   // On vide l'arbre
   vider();

   // On ajoute un noeud bidon seulement pour que quelque chose s'affiche.
   /*
   NoeudAbstrait* noeudStation = creerNoeud(NOM_STATION);
   NoeudAbstrait* noeudVaisseau = creerNoeud(NOM_VAISSEAU);
   NoeudAbstrait* noeudAsteroide = creerNoeud(NOM_ASTEROIDE);
   NoeudAbstrait* noeudBarriere = creerNoeud(NOM_BARRIERE);
   NoeudAbstrait* noeudPortail = creerNoeud(NOM_PORTAIL);

   ajouter(noeudStation);
   ajouter(noeudVaisseau);
   ajouter(noeudAsteroide);
   ajouter(noeudBarriere);
   ajouter(noeudPortail);
   */
   /*
	NoeudAbstrait* noeud = creerNoeud(NOM_ARAIGNEE);
   noeud->ajouter(creerNoeud(NOM_CONECUBE));
   ajouter(noeud);
   */
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
