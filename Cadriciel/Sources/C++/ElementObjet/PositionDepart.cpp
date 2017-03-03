///////////////////////////////////////////////////////////////////////////
/// @file PositionDepart.h
/// @author FloppyDisketeers
/// @date 2014-01-29
/// @version 1.0
///
/// @addtogroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////////////
#include "PositionDepart.h"

#include "../Arbre/ArbreRenduINF2990.h"
#include "../Application//FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn PositionDepart::PositionDepart()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
PositionDepart::PositionDepart(){
	noeud_ = new NoeudPositionDepart(ArbreRenduINF2990::NOM_POSITION_DEPART);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PositionDepart::PositionDepart( Vecteur3f positionDepart,
///				   Vecteur3f taille, Vecteur3f directionVitesse, unsigned int poids)
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
PositionDepart::PositionDepart(Vecteur3f positionDepart,
				   Vecteur3f taille, Vecteur3f directionVitesse, unsigned int poids){
	setPositionDepart(positionDepart);
	setTaille(taille);
	setDirectionVitesse(directionVitesse);
	setPoids((float)poids);

	noeud_ = new NoeudPositionDepart(ArbreRenduINF2990::NOM_POSITION_DEPART);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PositionDepart::PositionDepart(const PositionDepart& PositionDepart)
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
PositionDepart::PositionDepart(const PositionDepart& positionDepart) : ElementJeuAbstrait(positionDepart) {
	noeud_ = new NoeudPositionDepart(*(positionDepart.noeud_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn PositionDepart::~PositionDepart()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
PositionDepart::~PositionDepart(){
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(noeud_);
	noeud_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PositionDepart::getType()
///
/// Methode qui retourne le type de noeud
///
/// @param[in] aucun
///
/// @return Type::PositionDepart.
///
////////////////////////////////////////////////////////////////////////
Type PositionDepart::getType(){
	return POSITIONDEPART;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn PositionDepart::update(float deltaT)
///
/// Methode qui permet d'actualiser le rendu de l'objet
///
/// @param[in] aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void PositionDepart::update(float deltaT) {
	noeud_->setTransformation(positionActuelle_, angle_, axe_, taille_);
}

ElementJeuAbstrait* PositionDepart::clone() const
{
	return new PositionDepart(*this);
}
///////////////////////////////////////////////////////////////////////////
///@}
//////////////////////////////////////////////////////////////////////////