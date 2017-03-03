///////////////////////////////////////////////////////////////////////////////
/// @file Projectile.cpp
/// @author FloopyDisketeers
/// @date 2014-01-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Projectile.h"

#include "../Arbre/ArbreRenduINF2990.h"
#include "../Application/FacadeModele.h"

#include "Portail.h"
#include "Barriere.h"
#include "GestionnaireSon.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn Projectile::Projectile()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Projectile::Projectile(){
	noeud_ = new NoeudProjectile(ArbreRenduINF2990::NOM_PROJECTILE);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
	canBeAttracted_ = true;
	// la vitesse du projectile doit être la suivante
	moduleVitesse_ = 300.0f;
	
	aiVector3D axe;
	axe[0] = 0.0f;
	axe[1] = 0.0f;
	axe[2] = 1.0f;
	axe_ = axe;

	angle_ = 0;

	taille_.x = taille_.y = taille_.z = 1.0f;

	mustLeaveThisWorld_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Projectile::Projectile()
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Projectile::Projectile( aiVector3D positionDepart,
					   aiVector3D taille, aiVector3D directionVitesse, float poids){
	positionActuelle_ = positionDepart;
	taille_ = taille;
	directionVitesse_ = directionVitesse;
	poids_ = poids;
	axe_[0] = 0.0f;
	axe_[0] = 1.0f;
	axe_[1] = 1.0f;
	angle_ = 0;
	moduleVitesse_ = 300.0f;

	noeud_ = new NoeudProjectile(ArbreRenduINF2990::NOM_PROJECTILE);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
	noeud_->setTransformation(positionActuelle_, angle_, axe_, taille_);

	canBeAttracted_ = true;
	mustLeaveThisWorld_ = false;
}

Projectile::Projectile(const Projectile& projectile) : ElementJeuAbstrait(projectile) {
	noeud_ = new NoeudProjectile(*(projectile.noeud_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	canBeAttracted_ = true;
	mustLeaveThisWorld_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Projectile::~Projectile()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Projectile::~Projectile(){
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
Type Projectile::getType(){
	return PROJECTILE;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Projectile::update()
///
/// Methode qui permet d'actualiser le rendu de l'objet
///
/// @param[in] aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Projectile::update(float deltaT) {
	positionPrecedente_ = positionActuelle_;

	// Calcul de la nouvelle direction de la vitesse si y'a une force d'attraction du portail
	if(forcePortail_ > 0){
		directionVitesse_ = (directionVitesse_*moduleVitesse_ + acceleration_*forcePortail_*deltaT*deltaT);
		float newModuleVitesse_ = directionVitesse_.Length();
		directionVitesse_.Normalize();
		// Eviter de perdre la vitesse initiale.
		positionActuelle_ = positionActuelle_+directionVitesse_*newModuleVitesse_*deltaT;
	} else {
		positionActuelle_ = positionActuelle_+directionVitesse_*moduleVitesse_*deltaT;
	}

	noeud_->setTransformation(positionActuelle_, angle_, axe_, taille_);
}

bool Projectile::checkCollision(ElementJeuAbstrait* element) {
	return element->checkCollision(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Projectile::checkCollision(Asteroide* elementJeu)
///
/// Methode qui permet de verifier s'il y a une collision de l'objet avec un autre objet.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return bool : Est-ce qu'il y a eu une collision
///
////////////////////////////////////////////////////////////////////////	  
bool Projectile::checkCollision(Asteroide* asteroide){

	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2 = Vecteur3(asteroide->getPositionActuelle().x, asteroide->getPositionActuelle().y, asteroide->getPositionActuelle().z);

	// SINON LE SETTER AU DEPART?
	double rayon = this->getBoiteEnglobanteOrientee().getMoitieHauteur();

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1, rayon, vecTemp2, asteroide->getRayon());

	if(collision.type != aidecollision::COLLISION_AUCUNE){
		return true;
	}

	return false;
}	 

bool Projectile::checkCollision(Barriere* barriere) {
	return barriere->checkCollision(this);
}

bool Projectile::checkCollision(Portail* portail) {
	return portail->checkCollision(this);
}

bool Projectile::checkCollision(Station* station) {
	return station->checkCollision(this);
}

bool Projectile::checkCollision(Vaisseau* vaisseau){
	return vaisseau->checkCollision(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Projectile::traiterCollision(ElementJeuAbstrait* elementJeu)
///
/// Methode qui permet d<effectuer le traitement de la collision avec le type d'objet
/// La plupart du temps rien ne se passe.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return Aucune.
///
//////////////////////////////////////////////////////////////////////// 
void Projectile::traiterCollision(ElementJeuAbstrait* elementAbstrait){
	elementAbstrait->traiterCollision(this);
}

void Projectile::traiterCollision(Barriere* barriere){
	this->mustDie();
}

void Projectile::traiterCollision(Portail* portail){
	portail->traiterCollision(this);
}

void Projectile::traiterCollision(Station* station){
	this->mustDie();
	station->setPointDeVie(station->getPointDeVie()-1);

	//SON
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISIONPROJ);
}

void Projectile::traiterCollision(Asteroide* asteroide) {
	asteroide->traiterCollision(this);
}

void Projectile::traiterCollision(Vaisseau* vaisseau){
	vaisseau->traiterCollision(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Projectile::mustDie()
///
/// Methode qui permet de marquer un projectile comme etant mort.
///
/// @param[in] Aucune
///
/// @return Aucune.
///
//////////////////////////////////////////////////////////////////////// 
void Projectile::mustDie(){
	mustLeaveThisWorld_ = true;
}

ElementJeuAbstrait* Projectile::clone() const
{
	return new Projectile(*this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Projectile::setCanBeAttracted(bool canBeAttracted)
///
/// Methode qui permet de setter si l'objet peut-etre attire
///
/// @param[in] canBeAttracted : si l'objet peut se faire attirer
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Projectile::setCanBeAttracted(bool canBeAttracted){
	canBeAttracted_ = canBeAttracted;
}