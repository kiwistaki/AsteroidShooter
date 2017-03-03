///////////////////////////////////////////////////////////////////////////////
/// @file Portail.cpp
/// @author FloopyDisketeers
/// @date 2014-01-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Portail.h"

#include "../Arbre/ArbreRenduINF2990.h"
#include "../Application/FacadeModele.h"
#include "GestionnaireSon.h"

#include "Projectile.h"

#define FORCEACCELERATION 20000000.0f
#define TAILLECHAMPSATTRACTION 3.0f
#define RAYONMINPORTAIL 50.0f

////////////////////////////////////////////////////////////////////////
///
/// @fn Portail::Portail()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Portail::Portail() : frere_(NULL), idFrere_(0)
{
	noeud_ = new NoeudPortail(ArbreRenduINF2990::NOM_PORTAIL);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	acceleration_ = FORCEACCELERATION;
	rayon_ = getRayon();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Portail::Portail()
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Portail::Portail( Vecteur3f positionDepart,
				 Vecteur3f taille, Vecteur3f directionVitesse, float poids) : frere_(NULL), idFrere_(0)
{
	setPositionDepart(positionDepart);
	setTaille(taille);
	setDirectionVitesse(directionVitesse);
	setPoids(poids);
	
	noeud_ = new NoeudPortail(ArbreRenduINF2990::NOM_PORTAIL);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	acceleration_ = FORCEACCELERATION;
	rayon_ = getRayon();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Portail::Portail(const Portail& portail)
///
/// Constructeur par copie
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Portail::Portail(const Portail& portail) : ElementJeuAbstrait(portail), frere_(NULL) {
	noeud_ = new NoeudPortail(*(portail.noeud_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	positionActuelle_ = portail.positionActuelle_;
	acceleration_ = portail.acceleration_;
	idFrere_ = portail.idFrere_;
	//rayon_ = portail.getRayon();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Portail::~Portail()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Portail::~Portail(){
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(noeud_);
	noeud_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Portail::getType()
///
/// Methode qui retourne le type de noeud
///
/// @param[in] aucun
///
/// @return Type::Portail.
///
////////////////////////////////////////////////////////////////////////
Type Portail::getType(){
	return PORTAIL;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Portail::update()
///
/// Methode qui permet d'actualiser le rendu de l'objet
///
/// @param[in] aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Portail::update(float deltaT) {
	noeud_->setTransformation(positionActuelle_, angle_, axe_, taille_);
}

ElementJeuAbstrait* Portail::clone() const
{
	return new Portail(*this);
}

void Portail::setFrere(Portail* frere)
{
	frere_ = frere;

	if (frere_ != NULL) {
		idFrere_ = frere_->getId();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Asteroide::checkCollision(Asteroide* elementJeu)
///
/// Methode qui permet de verifier s'il y a une collision de l'objet avec un autre objet.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return bool : Est-ce qu'il y a eu une collision
///
////////////////////////////////////////////////////////////////////////	
bool Portail::checkCollision(ElementJeuAbstrait* element) {
	return element->checkCollision(this);
}

bool Portail::checkCollision(Asteroide* asteroide)
{
	bool hasCollision = false;
	Vecteur3 vecTemp1_ = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2_ = Vecteur3(asteroide->getPositionActuelle().x, asteroide->getPositionActuelle().y, asteroide->getPositionActuelle().z);
	double rayon = this->getBoiteEnglobanteOrientee().getMoitieHauteur();

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1_, rayon, vecTemp2_, asteroide->getRayon());

	// L'objet se trouve dans le champ d'attraction
	if(collision.direction.norme() < TAILLECHAMPSATTRACTION*rayon)
	{
		hasCollision = true;
	}
	else
	{
		// Si on se trouve dans le portail recemment transporte et qu'on quitte sa zone d'attraction, 
		// l'objet peut etre de nouveau attire par ce portail
		if(asteroide->getPreviousPortail() == this)
		{
			asteroide->setCanBeAttracted(true);
			asteroide->setPreviousPortail(NULL);
		}
		asteroide->setForcePortail(0); // Un fix pour pas qu'il continue de curver

	}

	return hasCollision;
}	

bool Portail::checkCollision(Projectile* projectile)
{
	bool hasCollision = false;
	Vecteur3 vecTemp1_ = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2_ = Vecteur3(projectile->getPositionActuelle().x, projectile->getPositionActuelle().y, projectile->getPositionActuelle().z);
	double rayon = this->getBoiteEnglobanteOrientee().getMoitieHauteur();

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1_, rayon, vecTemp2_, projectile->getRayon());

	// L'objet se trouve dans le champ d'attraction
	if(collision.direction.norme() < TAILLECHAMPSATTRACTION*rayon)
	{
		hasCollision = true;
	}
	else
	{
		// Si on se trouve dans le portail recemment transporte et qu'on quitte sa zone d'attraction, 
		// l'objet peut etre de nouveau attire par ce portail
		if(projectile->getPreviousPortail() == this)
		{
			projectile->setCanBeAttracted(true);
			projectile->setPreviousPortail(NULL);
		}
		projectile->setForcePortail(0); // Un fix pour pas qu'il continue de curver

	}

	return hasCollision;
}	 

bool Portail::checkCollision(Vaisseau* vaisseau)
{
	bool hasCollision = false;
	Vecteur3 vecTemp1_ = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2_ = Vecteur3(vaisseau->getPositionActuelle().x, vaisseau->getPositionActuelle().y, vaisseau->getPositionActuelle().z);
	double rayon = this->getBoiteEnglobanteOrientee().getMoitieHauteur();

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1_, rayon, vecTemp2_, vaisseau->getRayon());

	// L'objet se trouve dans le champ d'attraction
	if(collision.direction.norme() < TAILLECHAMPSATTRACTION*rayon)
	{
		hasCollision = true;
	}
	else
	{
		// Si on se trouve dans le portail recemment transporte et qu'on quitte sa zone d'attraction, 
		// l'objet peut etre de nouveau attire par ce portail
		if(vaisseau->getPreviousPortail() == this)
		{
			vaisseau->setCanBeAttracted(true);
			vaisseau->setPreviousPortail(NULL);
		}
		vaisseau->setForcePortail(0); // Un fix pour pas qu'il continue de curver
	}

	return hasCollision;
}

bool Portail::checkCollisionJoueurVirtuel(Vaisseau* joueurVirtuel)
{
	Vecteur3 posVaisseau;
	posVaisseau[0] = joueurVirtuel->getPositionActuelle().x;
	posVaisseau[1] = joueurVirtuel->getPositionActuelle().y;
	posVaisseau[2] = joueurVirtuel->getPositionActuelle().z;

	float distanceCarte = FacadeModele::obtenirInstance()->getCarte()->getLargeur()/2;

	Vecteur3 pointDir;
	pointDir[0] = joueurVirtuel->getPositionActuelle().x + joueurVirtuel->getDirectionVitesse().x * distanceCarte;
	pointDir[1] = joueurVirtuel->getPositionActuelle().y + joueurVirtuel->getDirectionVitesse().y * distanceCarte;
	pointDir[2] = joueurVirtuel->getDirectionVitesse().z;

	if( pointDir[0] != posVaisseau[0] && pointDir[1] != posVaisseau[1] ) {
		Droite3D trajectoireVaisseau(posVaisseau, pointDir);

		Vecteur3 posPortail;
		posPortail[0] =	positionActuelle_.x;
		posPortail[1] =	positionActuelle_.y;
		posPortail[2] =	positionActuelle_.z;

		if ( produitScalaire(pointDir, posPortail) >= 0 ) {
			Vecteur3 pointIntersection = trajectoireVaisseau.perpendiculaireDroite(posPortail);

			if((pointIntersection - posPortail).norme() < 2.0f*getRayon()){
				return true;
			} 
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Asteroide::traiterCollision(ElementJeuAbstrait* elementJeu)
///
/// Methode qui permet d<effectuer le traitement de la collision avec le type d'objet
/// La plupart du temps rien ne se passe.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return Aucune.
///
//////////////////////////////////////////////////////////////////////// 
void Portail::traiterCollision(ElementJeuAbstrait* elementAbstrait){
	elementAbstrait->traiterCollision(this);
}
void Portail::traiterCollision(Asteroide* asteroide)
{
	float distObjets = (this->positionActuelle_ - asteroide->getPositionActuelle()).Length();
	float rayon = this->getRayon();

	if(asteroide->canBeAttracted())
	{
		// Si objet se trouve dans le rayon du portail, on le teleporte
		if(distObjets < RAYONMINPORTAIL)//rayon)
		{
			// SON
			GestionnaireSon::obtenirInstance()->jouerSon(PORTAIL);

			asteroide->setPositionActuelle(this->frere_->positionActuelle_);
			asteroide->setPreviousPortail( this->frere_); // Permet de savoir quel portail il faut pas affecter par la force
			asteroide->setCanBeAttracted(false);
			asteroide->setForcePortail(0);
			asteroide->setAcceleration(0);
		}
		else
		{
			// Si on est dans le champ d'attraction on subit la force de celui-ci
			asteroide->setForcePortail( FORCEACCELERATION*rayon/(distObjets*distObjets) );
			asteroide->setAcceleration( (this->positionActuelle_-asteroide->getPositionActuelle()).Normalize() );
		}
	}
	// Dans le cas ou l'objet vient d'etre transporte
	else
	{
		// Si on est pas dans le nouveau portail, mais un qui se trouve proche
		if(this != asteroide->getPreviousPortail())
		{
			if(distObjets < RAYONMINPORTAIL)//rayon)
			{
				asteroide->setPositionActuelle(this->frere_->positionActuelle_);
				asteroide->setPreviousPortail( this->frere_);
				asteroide->setCanBeAttracted(false);
				asteroide->setForcePortail(0);
				asteroide->setAcceleration(0);
			}
			else
			{
				// L'objet est affecte par la force du portail qu'il ne vient pas de sortir
				asteroide->setForcePortail( FORCEACCELERATION*rayon/(distObjets*distObjets) );
				asteroide->setAcceleration( (this->positionActuelle_-asteroide->getPositionActuelle()).Normalize() );
			}
		}
	}
}	   
void Portail::traiterCollision(Projectile* projectile)
{
	float distObjets = (this->positionActuelle_ - projectile->getPositionActuelle()).Length();
	float rayon = this->getRayon();

	if(projectile->canBeAttracted())
	{
		// Si objet se trouve dans le rayon du portail, on le teleporte
		if(distObjets < RAYONMINPORTAIL)//rayon)
		{
			// SON
			GestionnaireSon::obtenirInstance()->jouerSon(PORTAIL);

			projectile->setPositionActuelle(this->frere_->positionActuelle_);
			projectile->setPreviousPortail( this->frere_); // Permet de savoir quel portail il faut pas affecter par la force
			projectile->setCanBeAttracted(false);
			projectile->setForcePortail(0);
			projectile->setAcceleration(0);
		}
		else
		{
			// Si on est dans le champ d'attraction on subit la force de celui-ci
			projectile->setForcePortail( FORCEACCELERATION*rayon/(distObjets*distObjets) );
			projectile->setAcceleration( (this->positionActuelle_-projectile->getPositionActuelle()).Normalize() );
		}
	}
	// Dans le cas ou l'objet vient d'etre transporte
	else
	{
		// Si on est pas dans le nouveau portail, mais un qui se trouve proche
		if(this != projectile->getPreviousPortail())
		{
			if(distObjets < RAYONMINPORTAIL)//rayon)
			{
				projectile->setPositionActuelle(this->frere_->positionActuelle_);
				projectile->setPreviousPortail( this->frere_);
				projectile->setCanBeAttracted(false);
				projectile->setForcePortail(0);
				projectile->setAcceleration(0);
			}
			else
			{
				// L'objet est affecte par la force du portail qu'il ne vient pas de sortir
				projectile->setForcePortail( FORCEACCELERATION*rayon/(distObjets*distObjets) );
				projectile->setAcceleration( (this->positionActuelle_-projectile->getPositionActuelle()).Normalize() );
			}
		}
	}
}	 	 
void Portail::traiterCollision(Vaisseau* vaisseau)
{
	float distObjets = (this->positionActuelle_ - vaisseau->getPositionActuelle()).Length();
	float rayon = this->getRayon();

	if(vaisseau->canBeAttracted())
	{
		// Si objet se trouve dans le rayon du portail, on le teleporte
		if(distObjets < RAYONMINPORTAIL)//rayon)
		{
			//Son
			GestionnaireSon::obtenirInstance()->jouerSon(SONPORTAIL);

			vaisseau->setPositionActuelle(this->frere_->positionActuelle_);
			vaisseau->setPreviousPortail( this->frere_); // Permet de savoir quel portail il faut pas affecter par la force
			vaisseau->setCanBeAttracted(false);
			vaisseau->setForcePortail(0);
			vaisseau->setAccelerationPortail(0);
		}
		else
		{
			// Si on est dans le champ d'attraction on subit la force de celui-ci
			vaisseau->setForcePortail( FORCEACCELERATION*rayon/(distObjets*distObjets) );
			vaisseau->setAccelerationPortail( (this->positionActuelle_-vaisseau->getPositionActuelle()).Normalize() );
		}
	}
	// Dans le cas ou l'objet vient d'etre transporte
	else
	{
		// Si on est pas dans le nouveau portail, mais un qui se trouve proche
		if(this != vaisseau->getPreviousPortail())
		{
			if(distObjets < RAYONMINPORTAIL)//rayon)
			{
				vaisseau->setPositionActuelle(this->frere_->positionActuelle_);
				vaisseau->setPreviousPortail( this->frere_);
				vaisseau->setCanBeAttracted(false);
				vaisseau->setForcePortail(0);
				vaisseau->setAccelerationPortail(0);
			}
			else
			{
				// L'objet est affecte par la force du portail qu'il ne vient pas de sortir
				vaisseau->setForcePortail( FORCEACCELERATION*rayon/(distObjets*distObjets) );
				vaisseau->setAccelerationPortail( (this->positionActuelle_-vaisseau->getPositionActuelle()).Normalize() ); // ATTENTION ICI UNE METHODE DIFFERENTE POUR SETTER UN AUTRE ACCELERATION
			}
		}
	}
}

float Portail::getRayon(){
	return this->getBoiteEnglobanteOrientee().getMoitieHauteur();
}