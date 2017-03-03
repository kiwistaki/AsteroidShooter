///////////////////////////////////////////////////////////////////////////////
/// @file VaisseauVirtuel.cpp
/// @author FloopyDisketeers
/// @date 2014-01-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "VaisseauVirtuel.h"

#include "../Arbre/ArbreRenduINF2990.h"
#include "../Application/FacadeModele.h"
#include "ModeRecherche.h"
#include "ModeAttaque.h"
#include "ModeApproche.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VaisseauVirtuel::VaisseauVirtuel()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VaisseauVirtuel::VaisseauVirtuel(bool joueur1) : Vaisseau(joueur1){
	etatCourrant_ = new ModeRecherche();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VaisseauVirtuel::VaisseauVirtuel(Vecteur3f positionDepart, Vecteur3f taille, Vecteur3f vitesse, unsigned int poids)
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VaisseauVirtuel::VaisseauVirtuel( Vecteur3f positionDepart,
								  Vecteur3f taille, Vecteur3f directionVitesse, float poids,
								  bool joueur1) : Vaisseau( positionDepart, taille, directionVitesse, poids, joueur1){
	etatCourrant_ = new ModeRecherche();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VaisseauVirtuel::VaisseauVirtuel(const Vaisseau& vaisseau)
///
/// Constructeur par copie
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VaisseauVirtuel::VaisseauVirtuel(const VaisseauVirtuel& vaisseau) : Vaisseau(vaisseau) {
	etatCourrant_ = new ModeRecherche();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VaisseauVirtuel::~VaisseauVirtuel()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VaisseauVirtuel::~VaisseauVirtuel(){
	delete etatCourrant_;
	etatCourrant_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VaisseauVirtuel::getType()
///
/// Methode qui retourne le type de noeud
///
/// @param[in] aucun
///
/// @return Type::VAISSEAU.
///
////////////////////////////////////////////////////////////////////////
Type VaisseauVirtuel::getType(){
	return VAISSEAUVIRTUEL;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VaisseauVirtuel::update(float deltaT)
///
/// Methode pour updater le vaisseau
///
/// @param[in] poids : poids du vaisseau
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VaisseauVirtuel::update(float deltaT) {
	Vaisseau::update(deltaT);
	if(isControlable_){
		etatCourrant_->update(*this, deltaT);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void setEtat(EtatJoueurVirtuel *etat)
///
/// Methode qui permet de set le state du vaisseau
///
/// @param[in] etat : l'etat a setter
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VaisseauVirtuel::setEtat(EtatJoueurVirtuel *etat)
{
	delete etatCourrant_;
	etatCourrant_ = etat;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Etat const VaisseauVirtuel::getEtat() const
///
/// Methode qui permet de récuperer l'état du vaisseau virtuel
///
/// @return Etat : enum de l'etat du vaisseau
///
////////////////////////////////////////////////////////////////////////
Mode const VaisseauVirtuel::getEtat() const
{
	return etatCourrant_->getEtat();
}

ElementJeuAbstrait* VaisseauVirtuel::clone() const
{
	return new VaisseauVirtuel(*this);
}

Asteroide* VaisseauVirtuel::getAstCible()
{
	return etatCourrant_->getAsteroideCible();
}

void VaisseauVirtuel::setAstCibleNull()
{
	etatCourrant_->setAstNull();
}