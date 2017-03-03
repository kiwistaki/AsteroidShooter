///////////////////////////////////////////////////////////////////////////////
/// @file Vaisseau.cpp
/// @author FloopyDisketeers
/// @date 2014-01-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Vaisseau.h"

#include "../Arbre/ArbreRenduINF2990.h"
#include "../Application/FacadeModele.h"
#include "Projectile.h"
#include <time.h>
#include "../../../Commun/Utilitaire/Utilitaire.h"
#include "../../../Commun/Utilitaire/Droite3D.h"
#include <math.h>

#include "Portail.h"
#include "Projectile.h"
#include "Asteroide.h"
#include "Accelerateur.h"

#include "GestionnaireSon.h"

#define FREQUENCETIR	5.0f
#define POIDSVAISSEAU	6.0f
#define TEMPSPIVOT		2.0f // Temps que le vaisseau reste incontrolable.

const float Vaisseau::VITESSE_MAX = 400.0f; // Vitesse maximale du vaisseauconst double 
const float Vaisseau::TEMPS_ENTRE_CHAQUE_TIR =  1.0f/FREQUENCETIR; // nombre de secondes entre chaque tir
const float Vaisseau::VITESSE_ROTATION = 350.0f; // Vitesse de rotation du vaisseau



////////////////////////////////////////////////////////////////////////
///
/// @fn Vaisseau::Vaisseau()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Vaisseau::Vaisseau(bool joueur1) {
	noeud_ = new NoeudVaisseau("Vaisseau");
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
	
	tempsAccelerationExtra_ = 0.0f;
	tempsPourUnTir_ = 0.0f;
	taille_.x = taille_.y = taille_.z = 10.0f;

	// valeurs par defaut
	angle_ = 0; 

	aiVector3D dirV;
	dirV[0] = 0.0f;
	dirV[1] = 1.0f;
	dirV[2] = 0.0f;
	directionVitesse_ = dirV;
	moduleVitesse_ = 0.0f;

	aiVector3D axe;
	axe[0] = 0.0f;
	axe[1] = 0.0f;
	axe[2] = 1.0f;
	axe_ = axe;

	//acceleration_ = aiVector3D(5000.0f,5000.0f,1.0);
	poids_ = POIDSVAISSEAU;
	canBeAttracted_ = true;
	isControlable_ = true;
	tempsAvantControlable_ = TEMPSPIVOT;
	accelerationPortail_ = 0;
	estAccelere_ = false;
	tempsAccelerationExtra_ = 0.0;
	facteurAcceleration_ = 1;
	isBlocked_ = false;

	noeud_->setJoueur1(joueur1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vaisseau::Vaisseau(Vecteur3f positionDepart, Vecteur3f taille, Vecteur3f directionVitesse, unsigned int poids)
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Vaisseau::Vaisseau( Vecteur3f positionDepart,
				   Vecteur3f taille, Vecteur3f directionVitesse, float poids, bool joueur1) {
	setPositionDepart(positionDepart);
	setTaille(taille);
	setDirectionVitesse(directionVitesse);
	setPoids(poids);

	noeud_ = new NoeudVaisseau(ArbreRenduINF2990::NOM_VAISSEAU);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	tempsAccelerationExtra_ = 0.0f;
	tempsPourUnTir_ = 0.0f;

	poids_ = POIDSVAISSEAU;
	canBeAttracted_ = true;
	isControlable_ = true;
	tempsAvantControlable_ = TEMPSPIVOT;
	accelerationPortail_ = 0;
	estAccelere_ = false;
	tempsAccelerationExtra_ = 0.0;
	facteurAcceleration_ = 1;
	isBlocked_ = false;

	noeud_->setJoueur1(joueur1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vaisseau::Vaisseau(const Vaisseau& vaisseau)
///
/// Constructeur par copie
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Vaisseau::Vaisseau(const Vaisseau& vaisseau) : ElementJeuAbstrait(vaisseau) {
	noeud_ = new NoeudVaisseau(*(vaisseau.noeud_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	tempsAccelerationExtra_ = 0.0f;
	tempsPourUnTir_ = 0.0f;
	taille_.x = taille_.y = taille_.z = 10.0f;
	poids_ = POIDSVAISSEAU;
	canBeAttracted_ = true;
	isControlable_ = true;
	tempsAvantControlable_ = TEMPSPIVOT;
	accelerationPortail_ = 0;
	acceleration_ = vaisseau.acceleration_;
	estAccelere_ = false;
	tempsAccelerationExtra_ = 0.0;
	facteurAcceleration_ = 1;
	isBlocked_ = false;

	noeud_->setJoueur1(noeud_->getJoueur1());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vaisseau::~Vaisseau()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Vaisseau::~Vaisseau(){
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(noeud_);
	noeud_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VaisseauVirtuel::attaquer(aiVector3D direction)
///
/// Methode qui permet de creer des projectiles
///
/// @param[in] aiVector3D direction : la direction vers laquel on tire, aiVector3D position : la position actuelle du vaisseau, float deltaT
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::attaquer(aiVector3D direction, aiVector3D position, float deltaT)
{
	if(tempsPourUnTir_ >= TEMPS_ENTRE_CHAQUE_TIR) {
		tempsPourUnTir_ = 0;
		position += 10.0f*this->getRayon()*direction;

		aiVector3D vecVitProj = VITESSE_MAX*3.0f*directionVitesse_ + vitesse_;
		float moduleVitesse = vecVitProj.Length();
		vecVitProj.Normalize();
		vecVitProj.z = 0.0f;
		
		Projectile *proj = new Projectile( position, aiVector3D(1.0f, 1.0f, 1.0f), vecVitProj, 1);
		proj->setModuleVitesse(moduleVitesse);
		FacadeModele::obtenirInstance()->getCarte()->getVecteurProjectile().push_back(proj);
	
		// Son
		GestionnaireSon::obtenirInstance()->jouerSon(TIRVAISSEAU);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vaisseau::update(float deltaT)
///
/// Methode qui permet de updater les objets selon 
///
/// @param[in] poids : poids du vaisseau
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::update(float deltaT) {
	noeud_->setTransformation(positionActuelle_, angle_, axe_, taille_);
	
	tempsAvantControlable_ -= deltaT;
	if(tempsAvantControlable_ <= 0.0){
		tempsAvantControlable_ = TEMPSPIVOT;
		isControlable_ = true;
	}

	if(!isControlable_){
		this->virage(deltaT, 1, 1440.0f); //360 degres * 4  (4 tours par sec)
	} else {
		axe_ = aiVector3D(0.0,0.0,1.0);
	}

	if(estAccelere_){
		if(tempsAccelerationExtra_ > 0){
			tempsAccelerationExtra_ -= deltaT;
		}else{
			estAccelere_ = false;
		}
	}
		
	tempsPourUnTir_ += deltaT;

	positionPrecedente_ = positionActuelle_;

	// Calcul de la nouvelle direction de la vitesse si y'a une force d'attraction du portail
	if(forcePortail_ > 0.0f){
		float ancienneVitesse = vitesse_.Length();
		aiVector3D ancienDirectionVitesse(0);
		if(ancienneVitesse != 0.0f){
			ancienDirectionVitesse = vitesse_.Normalize();
		}
		
		aiVector3D nouvelleVitesse = (ancienDirectionVitesse*ancienneVitesse + accelerationPortail_*forcePortail_*deltaT*deltaT);
		float newModuleVitesse_ = nouvelleVitesse.Length();
		// On obtient ici la nouvelle direction de la vitesse
		nouvelleVitesse.Normalize();
		positionActuelle_ = positionActuelle_ + nouvelleVitesse*newModuleVitesse_*deltaT;
		// Eviter de perdre la vitesse initiale.
		vitesse_ = nouvelleVitesse*ancienneVitesse;
		
	} else {
		if(!isBlocked_)
			positionActuelle_ = positionActuelle_ + vitesse_*deltaT;
	}
	positionActuelle_.z = 0.0f;
	directionVitesse_.z = 0.0f;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Vaisseau::setBonusAccelerateur(Accelerateur* bonusAccelerateur)
///
	/// Methode pour setter la frequence de tir d'un vaisseau
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::setTempsPourUnTir(float freq)
{
	tempsPourUnTir_ = freq;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vaisseau::seDeplacer(float deltaT)
///
/// Permet au vaisseau de ce deplacer
///
/// @param float deltaT
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::seDeplacer(float deltaT)
{
	// L'accélération doit être telle que le vaisseau atteint sa vitesse
	// maximale en 3 secondes
	const float INCREMENT_VITESSE = VITESSE_MAX / 2.0f;
	
	vitesse_ += directionVitesse_ * INCREMENT_VITESSE * deltaT;
			
	vitesse_.x = min(vitesse_.x, VITESSE_MAX);
	vitesse_.y = min(vitesse_.y, VITESSE_MAX);
	vitesse_.x = max(vitesse_.x, -VITESSE_MAX);
	vitesse_.y = max(vitesse_.y, -VITESSE_MAX);


	//BONUS ACCELERATION
	if(estAccelere_){
		vitesse_+= vitesse_*((facteurAcceleration_/100.0f));
	}

	direction_ = directionVitesse_;
	moduleVitesse_ = vitesse_.Length();
}

void Vaisseau::decelerer(float deltaT) {
	const float INCREMENT_VITESSE = VITESSE_MAX / 2.0f;
	aiVector3D directionAbs(abs(directionVitesse_.x), abs(directionVitesse_.y), 0.0f);
	vitesse_ -= directionAbs * INCREMENT_VITESSE * deltaT;
	vitesse_.x = max(vitesse_.x, 0.0f);
	vitesse_.y = max(vitesse_.y, 0.0f);
	vitesse_.z = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vaisseau::seDeplacer(float deltaT)
///
/// Permet au vaisseau deffectuer une rotation
///
/// @param float deltaT, int sens (1 pour horaire, -1 pour anti-horaire)
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::virage(float deltaT, int sens)
{
	angle_ = angle_ + VITESSE_ROTATION*sens*deltaT;
	directionVitesse_[0] = (float)cos(utilitaire::DEG_TO_RAD(angle_ + 90));
	directionVitesse_[1] = (float)sin(utilitaire::DEG_TO_RAD(angle_ + 90));
}

void Vaisseau::virage(float deltaT, int sens, float vitesseRotation)
{
	angle_ = angle_ + vitesseRotation*sens*deltaT;
	directionVitesse_[0] = (float)cos(utilitaire::DEG_TO_RAD(angle_ + 90));
	directionVitesse_[2] = (float)sin(utilitaire::DEG_TO_RAD(angle_ + 90));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vaisseau::manoeuvre()
///
/// Permet au vaisseau deffectuer sa manoeuvre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::manoeuvre()
{
	angle_ -= 180;
	directionVitesse_[0] = (float)cos(utilitaire::DEG_TO_RAD(angle_ + 90));
	directionVitesse_[1] = (float)sin(utilitaire::DEG_TO_RAD(angle_ + 90));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool intersectionTirVaisseau(aiVector3D trajectoireTir)
///
/// Permet au vaisseau virtuel d'éviter de tirer sur le joueur1
///
/// @param[in] aiVector3D trajectoireTir : la trajectoire de tir du vaisseau virtuel
///			   aiVector3D posJoueurVirtuel : la position du joueur virtuel
///
/// @return bool : Est-ce que le joueur virtuel tir sur le joueur1
///
////////////////////////////////////////////////////////////////////////
bool Vaisseau::intersectionTirVaisseau(aiVector3D posJoueurVirtuel ,aiVector3D trajectoireTir)
{
	Vecteur3 posVaisseauVirtuel;
	posVaisseauVirtuel[0] = posJoueurVirtuel.x;
	posVaisseauVirtuel[1] = posJoueurVirtuel.y;
	posVaisseauVirtuel[2] = 0;

	largeurCarte_ = FacadeModele::obtenirInstance()->getCarte()->getLargeur()/2.0;

	Vecteur3 pointTrajectoireTir;
	pointTrajectoireTir[0] = posJoueurVirtuel.x + trajectoireTir.x * largeurCarte_;
	pointTrajectoireTir[1] = posJoueurVirtuel.y + trajectoireTir.y * largeurCarte_;
	pointTrajectoireTir[2] = 0;

	if( posVaisseauVirtuel[0] != pointTrajectoireTir[0] && posVaisseauVirtuel[1] != pointTrajectoireTir[1] ) {
		Droite3D droiteTrajectoireTir(posVaisseauVirtuel, pointTrajectoireTir);

		Vecteur3 posVaisseauJoueur;
		posVaisseauJoueur[0] = positionActuelle_.x;
		posVaisseauJoueur[1] = positionActuelle_.y;
		posVaisseauJoueur[2] = 0;

		Vecteur3 pointDirectionJoueur;
		pointDirectionJoueur[0] = positionActuelle_.x + vitesse_.x * largeurCarte_ ;
		pointDirectionJoueur[1] = positionActuelle_.y + vitesse_.y * largeurCarte_ ;
		pointDirectionJoueur[2] = 0;

		Vecteur3 pointIntersection = droiteTrajectoireTir.perpendiculaireDroite(posVaisseauJoueur);
		Vecteur3 virtuelAJoueur = posVaisseauVirtuel - posVaisseauJoueur;

		if(droiteTrajectoireTir.intersectionSegment(posVaisseauJoueur, pointDirectionJoueur)
			|| (pointIntersection - posVaisseauJoueur).norme() < getRayon() * 30) {
		
			return true;
		}
	}
	return false;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn bool Vaisseau::checkCollision(ElementJeuAbstrait* elementJeu)
///
/// Methode qui permet de verifier s'il y a une collision de l'objet avec un autre objet.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return bool : Est-ce qu'il y a eu une collision
///
////////////////////////////////////////////////////////////////////////
bool Vaisseau::checkCollision(ElementJeuAbstrait* element) {
	return element->checkCollision(this);
}
bool Vaisseau::checkCollision(Accelerateur* accelerateur){
	return accelerateur->checkCollision(this);
}	 
bool Vaisseau::checkCollision(Asteroide* asteroide){
	
	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2 = Vecteur3(asteroide->getPositionActuelle().x, asteroide->getPositionActuelle().y, asteroide->getPositionActuelle().z);

	BoiteEnglobanteOrientee boite = this->getBoiteEnglobanteOrientee();

	double rayon = (boite.getMoitieHauteur() + boite.getMoitieLongueur())/2.0;

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1, rayon, vecTemp2, asteroide->getRayon());

	if(collision.type != aidecollision::COLLISION_AUCUNE){
		aiVector3D newPositionVais = this->positionActuelle_;
		aiVector3D newPositionAst2 = asteroide->getPositionActuelle();
		
		collision.direction.normaliser();
		
		newPositionVais.x -= (float)(collision.direction[0]*collision.enfoncement)/2.0f;
		newPositionAst2.x += (float)(collision.direction[0]*collision.enfoncement)/2.0f;

		newPositionVais.y -= (float)(collision.direction[1]*collision.enfoncement)/2.0f;
		newPositionAst2.y += (float)(collision.direction[1]*collision.enfoncement)/2.0f;

		this->positionActuelle_ = newPositionVais;
		asteroide->setPositionActuelle (newPositionAst2);
		return true;
	}

	return false;
}	 

bool Vaisseau::checkCollision(Barriere* barriere){
	return barriere->checkCollision(this);
}	 
bool Vaisseau::checkCollision(Portail* portail){
	return portail->checkCollision(this);
}	 
bool Vaisseau::checkCollision(Projectile* projectile){
	// Le vaisseau qui tire provoque des collisions avec ses propres projectiles.
	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2 = Vecteur3(projectile->getPositionActuelle().x, projectile->getPositionActuelle().y, projectile->getPositionActuelle().z);

	// SINON LE SETTER AU DEPART?
	double rayon = this->getBoiteEnglobanteOrientee().getMoitieHauteur();

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1, rayon, vecTemp2, projectile->getRayon());

	if(collision.type != aidecollision::COLLISION_AUCUNE){
		return true;
	}
	
	return false;
}	 
bool Vaisseau::checkCollision(Vaisseau* vaisseau){
	
	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2 = Vecteur3(vaisseau->getPositionActuelle().x, vaisseau->getPositionActuelle().y, vaisseau->getPositionActuelle().z);

	BoiteEnglobanteOrientee b1 = this->getBoiteEnglobanteOrientee();
	BoiteEnglobanteOrientee b2 = vaisseau->getBoiteEnglobanteOrientee();

	double approxRayon1 = (b1.getMoitieHauteur() + b1.getMoitieLongueur())/2.0;
	double approxRayon2 = (b2.getMoitieHauteur() + b2.getMoitieLongueur())/2.0;

	aidecollision::DetailsCollision collision1 = aidecollision::calculerCollisionSphere(vecTemp1, approxRayon1, vecTemp2, approxRayon2);


	if(   collision1.type != aidecollision::COLLISION_AUCUNE ){
		aiVector3D newPositionVais1 = this->positionActuelle_;
		aiVector3D newPositionVais2 = vaisseau->positionActuelle_;
		
		collision1.direction.normaliser();
		
		if(collision1.direction == Vecteur3(0)){
			newPositionVais1.x -= (float)(collision1.enfoncement)/2.0f;
			newPositionVais2.x += (float)(collision1.enfoncement)/2.0f;
			
			newPositionVais1.y -= (float)(collision1.enfoncement)/2.0f;
			newPositionVais2.y += (float)(collision1.enfoncement)/2.0f;
		} else {
			newPositionVais1.x -= (float)(collision1.direction[0]*collision1.enfoncement)/2.0f;
			newPositionVais2.x += (float)(collision1.direction[0]*collision1.enfoncement)/2.0f;

			newPositionVais1.y -= (float)(collision1.direction[1]*collision1.enfoncement)/2.0f;
			newPositionVais2.y += (float)(collision1.direction[1]*collision1.enfoncement)/2.0f;
		}

		this->positionActuelle_		= newPositionVais1;
		vaisseau->positionActuelle_ = newPositionVais2;
		
		return true;
	}

	return false;

}
bool Vaisseau::checkCollision(Station* station){
	return station->checkCollision(this);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool Vaisseau::traiterCollision(Vaisseau* elementJeu)
///
/// Methode qui permet d<effectuer le traitement de la collision avec le type d'objet
/// La plupart du temps rien ne se passe.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::traiterCollision(ElementJeuAbstrait* elementJeuAbstrait){
	elementJeuAbstrait->traiterCollision(this);
}	
void Vaisseau::traiterCollision(Accelerateur* accelerateur){
	accelerateur->traiterCollision(this);
}	 

void Vaisseau::traiterCollision(Asteroide* asteroide){
	// Source: http://www.vobarian.com/collisions/2dcollisions2.pdf

	// Normale unitaire (vecteur centre-centre des asteroide)
	aiVector3D unitNormale = this->positionActuelle_ - asteroide->getPositionActuelle();
	unitNormale.Normalize();
	
	// Tangeante unitaire
	aiVector3D unitTangent = unitNormale;
	unitTangent.x = -unitNormale.y;
	unitTangent.y = unitNormale.x;

	// Vitesse initiale du vaisseau et asteroide
	// ATTENTION UTILISER vitesse_ PLUTOT QUE LE MODULE ET LA DIRECTION
	aiVector3D vitVaisseau = this->vitesse_;
	aiVector3D vitAsteroide2 = asteroide->getModuleVitesse()*asteroide->getDirectionVitesse();

	// Projection des vitesses sur la tangeante et la normale unitaire (avant la collision)
	float vitVaisseauNormale   = unitNormale*vitVaisseau;
	float vitVaisseauTangeante = unitTangent*vitVaisseau;
	float vitAsteroide2Normale   = unitNormale*vitAsteroide2;
	float vitAsteroide2Tangeante = unitTangent*vitAsteroide2;
	
	// La vitesse tangentielle reste pareille apres la collision
	float newVitVaisseauTangeante = vitVaisseauTangeante;
	float newVitAsteroide2Tangeante = vitAsteroide2Tangeante;
	// Cependant, la vitesse normale va changer
	float newVitVaisseauNormale   = (vitVaisseauNormale*(this->poids_-asteroide->getPoids())+2.0f*asteroide->getPoids()*vitAsteroide2Normale)
									  /(this->poids_+asteroide->getPoids()); 
	float newVitAsteroide2Normale   = (vitAsteroide2Normale*(asteroide->getPoids()-this->poids_)+2.0f*this->poids_*vitVaisseauNormale)
									  /(this->poids_+asteroide->getPoids());
	
	// Reconvertir en vecteur les nouvelles vitesses (combinaison entre la vitesse normale et la vitesse tangeantielle
	vitVaisseau = newVitVaisseauNormale*unitNormale+newVitVaisseauTangeante*unitTangent;
	vitAsteroide2 = newVitAsteroide2Normale*unitNormale+newVitAsteroide2Tangeante*unitTangent;
	
	//Reattribuer les vitesse
	this->vitesse_ = vitVaisseau;
	asteroide->setModuleVitesse(vitAsteroide2.Length()); 
	asteroide->setDirectionVitesse(vitAsteroide2.Normalize());
		
	this->tempsAvantControlable_ = TEMPSPIVOT;
	this->isControlable_ = false;

	// SON 
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISIONAUTRE);
}	 
void Vaisseau::traiterCollision(Barriere* barriere){
	barriere->traiterCollision(this);
}	 
void Vaisseau::traiterCollision(Portail* portail){
	portail->traiterCollision(this);
}	 
void Vaisseau::traiterCollision(Projectile* projectile){
	this->isControlable_ = false;
	projectile->mustDie();
}
void Vaisseau::traiterCollision(Station* station){
	station->traiterCollision(this);
}	
void Vaisseau::traiterCollision(Vaisseau* vaisseau){

	// Source: http://www.vobarian.com/collisions/2dcollisions2.pdf
	// Normale unitaire (vecteur centre-centre des asteroide)
	aiVector3D unitNormale = this->positionActuelle_ - vaisseau->positionActuelle_;
	unitNormale.Normalize();
	
	// Tangeante unitaire
	aiVector3D unitTangent = unitNormale;
	unitTangent.x = -unitNormale.y;
	unitTangent.y = unitNormale.x;

	// Vitesse initiale du vaisseau et asteroide
	// ATTENTION UTILISER vitesse_ PLUTOT QUE LE MODULE ET LA DIRECTION
	aiVector3D vitVaisseau1 = this->vitesse_;
	aiVector3D vitVaisseau2 = vaisseau->vitesse_;

	// Projection des vitesses sur la tangeante et la normale unitaire (avant la collision)
	float vitVaisseau1Normale   = unitNormale*vitVaisseau1;
	float vitVaisseau1Tangeante = unitTangent*vitVaisseau1;
	float vitVaisseau2Normale   = unitNormale*vitVaisseau2;
	float vitVaisseau2Tangeante = unitTangent*vitVaisseau2;
	
	// La vitesse tangentielle reste pareille apres la collision
	float newvitVaisseau1Tangeante = vitVaisseau1Tangeante;
	float newvitVaisseau2Tangeante = vitVaisseau2Tangeante;
	// Cependant, la vitesse normale va changer
	float newvitVaisseau1Normale   = (vitVaisseau1Normale*(this->poids_-vaisseau->poids_)+2.0f*vaisseau->poids_*vitVaisseau2Normale)
									  /(this->poids_+vaisseau->poids_); 
	float newvitVaisseau2Normale   = (vitVaisseau2Normale*(vaisseau->poids_-this->poids_)+2.0f*this->poids_*vitVaisseau1Normale)
									  /(this->poids_+vaisseau->poids_);
	
	// Reconvertir en vecteur les nouvelles vitesses (combinaison entre la vitesse normale et la vitesse tangeantielle
	vitVaisseau1 = newvitVaisseau1Normale*unitNormale+newvitVaisseau1Tangeante*unitTangent;
	vitVaisseau2 = newvitVaisseau2Normale*unitNormale+newvitVaisseau2Tangeante*unitTangent;
	
	//Reattribuer les vitesse
	if(unitNormale != 0) {
		this->vitesse_ = vitVaisseau1;
		vaisseau->vitesse_ = vitVaisseau2; 
	} else {
		this->vitesse_ = 0.0f;
		vaisseau->vitesse_ = 0.0f;
	}

	// SON 
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISIONAUTRE);
}	

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vaisseau::setCanBeAttracted(bool canBeAttracted)
///
/// Methode qui permet de setter si l'objet peut-etre attire
///
/// @param[in] canBeAttracted : si l'objet peut se faire attirer
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::setCanBeAttracted(bool canBeAttracted){
	canBeAttracted_ = canBeAttracted;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vaisseau::collisionZoneJeu()
///
/// Permet de modifier la trajectoire du vaisseau lorsque celui-ci entre en collision avec la limite de la zone de jeu
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::collisionZoneJeu(char axe){

	if(axe=='x'){
		vitesse_.x = 0.0f;
		//directionVitesse_[0] = 0.0f;
	}else if(axe=='y'){
		vitesse_.y = 0.0f;
		//directionVitesse_[1] = 0.0f;
	}

	//!! On annule pas la direction de la vitesse lors de la collision, puisque si on fait ceci, on auran de la difficulté à repartir du côté approprié /Voir Sacha/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Vaisseau::setControlable(bool isControlable)
///
/// Permet de modifier si le vaisseau est controlable
///
/// @param[in] isControlable : si l'objet est controlable
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void Vaisseau::setControlable(bool isControlable){
	isControlable_ = isControlable;
}

void Vaisseau::setAccelerationPortail(aiVector3D accelerationPortail){
	accelerationPortail_ = accelerationPortail;
}