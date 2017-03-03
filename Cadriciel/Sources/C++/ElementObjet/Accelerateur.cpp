///////////////////////////////////////////////////////////////////////////////
/// @file Accelerateur.cpp
/// @author FloopyDisketeers
/// @date 2014-01-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Accelerateur.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Application/FacadeModele.h"
#include "GestionnaireSon.h"

const double Accelerateur::TEMPS_DINACTIVITE= 5.0f; 

////////////////////////////////////////////////////////////////////////
///
/// @fn Accelerateur::Accelerateur()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Accelerateur::Accelerateur(){
	noeud_ = new NoeudAccelerateur(ArbreRenduINF2990::NOM_ACCELERATEUR);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	isActif_ = true;
	tempsAvantActif_ = 0.0f;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Accelerateur::Accelerateur()
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Accelerateur::Accelerateur(Vecteur3f positionDepart,
						   Vecteur3f taille, Vecteur3f directionVitesse, float poids){
	setPositionDepart(positionDepart);
	setTaille(taille);
	setDirectionVitesse(directionVitesse);
	setPoids(poids);

	noeud_ = new NoeudAccelerateur(ArbreRenduINF2990::NOM_ACCELERATEUR);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	isActif_ = true;
	tempsAvantActif_ = 0.0f;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Accelerateur::Accelerateur(const Accelerateur& Accelerateur)
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Accelerateur::Accelerateur(const Accelerateur& accelerateur) : ElementJeuAbstrait(accelerateur) {
	noeud_ = new NoeudAccelerateur(*(accelerateur.noeud_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	// ATTENTION JUSTE METTRE CA COMME CA C'EST CORRECT???
	isActif_ = true;
	tempsAvantActif_ = 0.0f;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Accelerateur::~Accelerateur()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Accelerateur::~Accelerateur(){
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(noeud_);
	noeud_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Accelerateur::getType()
///
/// Methode qui retourne le type de noeud
///
/// @param[in] aucun
///
/// @return Type::Accelerateur.
///
////////////////////////////////////////////////////////////////////////
Type Accelerateur::getType(){
	return ACCELERATEUR;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Accelerateur::update(float deltaT)
///
/// Methode qui permet d'actualiser le rendu de l'objet
///
/// @param[in] aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Accelerateur::update(float deltaT) {
	noeud_->setTransformation(positionActuelle_, angle_, axe_, taille_);
	
	// 5 secondes d'inactivitee
	if(!isActif_)
	{
		tempsAvantActif_ -= deltaT;

		if(tempsAvantActif_ < 0){
			isActif_ = true;
		}
	}

	noeud_->setEstActif(isActif_);
}

ElementJeuAbstrait* Accelerateur::clone() const
{
	return new Accelerateur(*this);
}

bool Accelerateur::checkCollision(ElementJeuAbstrait* element) {
	return element->checkCollision(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Accelerateur::checkCollision(ElementJeuAbstrait* elementJeu)
///
/// Methode qui permet de verifier s'il y a une collision de l'objet avec un autre objet.
/// Collision de type Boite avec Boite
///
/// @param[in] vaisseau : l'autre objet avec lequel il faut verifier la collision
///
/// @return bool : Est-ce qu'il y a eu une collision
///
////////////////////////////////////////////////////////////////////////
bool Accelerateur::checkCollision(Vaisseau* vaisseau){
		
	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2 = Vecteur3(vaisseau->getPositionActuelle().x, vaisseau->getPositionActuelle().y, vaisseau->getPositionActuelle().z);

	float approxRayonBonus = (this->getBoiteEnglobanteOrientee().getMoitieHauteur() + this->getBoiteEnglobanteOrientee().getMoitieLongueur())/2.0f;

	float approxRayonVaisseau = (vaisseau->getBoiteEnglobanteOrientee().getMoitieHauteur() + vaisseau->getBoiteEnglobanteOrientee().getMoitieLongueur())/2.0f;

	aidecollision::DetailsCollision collision1 = aidecollision::calculerCollisionSphere(vecTemp1, approxRayonBonus, vecTemp2, approxRayonVaisseau);

	if(collision1.type != aidecollision::COLLISION_AUCUNE){
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Accelerateur::traiterCollision(Vaisseau* vaisseau)
///
/// Methode qui permet de traiter la collision avec un vaisseau
///
/// @param[in] vaisseau: l'objet de type vaisseau avec lequel il y aurait
///						 possibilite de collision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Accelerateur::traiterCollision(Vaisseau* vaisseau)
{
	if(isActif_)
	{
		tempsAvantActif_ = TEMPS_DINACTIVITE;
		isActif_ = false;

		vaisseau->setTempsAcceleration(5.0);
		vaisseau->setEstAccelere(true);

		// Son
		GestionnaireSon::obtenirInstance()->jouerSon(SONBONUSACC);
	}
}