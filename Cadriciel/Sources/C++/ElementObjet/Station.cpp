///////////////////////////////////////////////////////////////////////////////
/// @file Asteroid.cpp
/// @author FloopyDisketeers
/// @date 2014-01-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Station.h"

#include "../Arbre/ArbreRenduINF2990.h"
#include "../Application/FacadeModele.h"
#include "../../../Commun/Utilitaire/Droite3D.h"
#include "GestionnaireSon.h"

#include "Projectile.h"

/// Attribut du nb de station
unsigned int Station::nbStation_ = 0;
const float Station::VITESSE_ROTATION = 10.0f;

////////////////////////////////////////////////////////////////////////
///
/// @fn Station::Station()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Station::Station(){
	noeud_ = new NoeudStation("Station");
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
	nbStation_++;
	taille_.x = taille_.y = taille_.z = 1.0f;
	axe_.x = axe_.y = 0.0f;
	axe_.z = 1.0f;
	angle_ = 0.0f;
	poids_ = 1000000;

	pointDeVie_ = FacadeModele::obtenirInstance()->getPtsDeVieStation();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Station::Station()
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Station::Station( Vecteur3f positionDepart,
				 Vecteur3f taille, Vecteur3f directionVitesse, float poids,
				 unsigned int pointDeVie){
	setPositionDepart(positionDepart);
	setTaille(taille);
	setDirectionVitesse(directionVitesse);
	setPoids(poids);
	setPointDeVie( pointDeVie);
	axe_.x = axe_.y = 0.0f;
	axe_.z = 1.0f;
	angle_ = 0.0f;

	noeud_ = new NoeudStation(ArbreRenduINF2990::NOM_STATION);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
	nbStation_++;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Station::Station(const Station& station)
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Station::Station(const Station& station) : ElementJeuAbstrait(station) {
	setPointDeVie(station.pointDeVie_);

	noeud_ = new NoeudStation(*(station.noeud_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
	nbStation_++;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Station::~Station()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Station::~Station(){
	nbStation_--;
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(noeud_);
	noeud_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int	Station::getNbStation()
///
/// Methode qui permet de retourner le nb de station
///
/// @return int : nbStation_
///
////////////////////////////////////////////////////////////////////////
unsigned int Station::getNbStation()
{
	return nbStation_;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn bool Station::checkCollisionJoueurVirtuel(Vaisseau* joueurVirtuel)
///
/// Methode qui permet au joueur virtuel d'éviter les stations spatiales
///
/// @param[in] Vaisseau* joueurVirtuel 
///
/// @return bool : vrai si la trajectoire du vaisseau intersect la station
///
////////////////////////////////////////////////////////////////////////
bool Station::checkCollision(ElementJeuAbstrait* element) {
	return element->checkCollision(this);
}

bool Station::checkCollision(Asteroide* asteroide){

	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2 = Vecteur3(asteroide->getPositionActuelle().x, asteroide->getPositionActuelle().y, asteroide->getPositionActuelle().z);

	float rayon = (this->getBoiteEnglobanteOrientee().getMoitieHauteur() + this->getBoiteEnglobanteOrientee().getMoitieLongueur())/2.0f;

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1, rayon, vecTemp2, asteroide->getRayon());

	if(collision.type != aidecollision::COLLISION_AUCUNE){
		aiVector3D newPositionAst = asteroide->getPositionActuelle();
		collision.direction.normaliser();
		
		newPositionAst.x += (float)(collision.direction[0]*collision.enfoncement);
		newPositionAst.y += (float)(collision.direction[1]*collision.enfoncement);

		asteroide->setPositionActuelle( newPositionAst );
		return true;
	}

	return false;

}

bool Station::checkCollision(Projectile* projectile){

	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2 = Vecteur3(projectile->getPositionActuelle().x, projectile->getPositionActuelle().y, projectile->getPositionActuelle().z);
	
	float rayon = (this->getBoiteEnglobanteOrientee().getMoitieHauteur() + this->getBoiteEnglobanteOrientee().getMoitieLongueur())/2.0f;

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1, rayon, vecTemp2, projectile->getRayon());

	if(collision.type != aidecollision::COLLISION_AUCUNE){
		return true;
	}

	return false;
}	

bool Station::checkCollision(Vaisseau* vaisseau)
{

	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, positionActuelle_.z);
	Vecteur3 vecTemp2 = Vecteur3(vaisseau->getPositionActuelle().x, vaisseau->getPositionActuelle().y, vaisseau->getPositionActuelle().z);

	float rayon = (this->getBoiteEnglobanteOrientee().getMoitieHauteur()+this->getBoiteEnglobanteOrientee().getMoitieLongueur())/2.0f;
	float rayonVaisseau = (vaisseau->getBoiteEnglobanteOrientee().getMoitieHauteur()+vaisseau->getBoiteEnglobanteOrientee().getMoitieLongueur())/2.0f;

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1, rayon, vecTemp2, rayonVaisseau);

	if(collision.type != aidecollision::COLLISION_AUCUNE){
		aiVector3D newPositionVais = vaisseau->getPositionActuelle();
		collision.direction.normaliser();
		
		newPositionVais.x += (float)(collision.direction[0]*collision.enfoncement);
		newPositionVais.y += (float)(collision.direction[1]*collision.enfoncement);

		vaisseau->setPositionActuelle( newPositionVais );
		return true;
	}

	return false;

}

bool Station::checkCollisionJoueurVirtuel(Vaisseau* joueurVirtuel)
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

		Vecteur3 posStation;
		posStation[0] =	positionActuelle_.x;
		posStation[1] =	positionActuelle_.y;
		posStation[2] =	positionActuelle_.z;

		if ( produitScalaire(pointDir, posStation) >= 0 ) {
			Vecteur3 pointIntersection = trajectoireVaisseau.perpendiculaireDroite(posStation);

			if((pointIntersection - posStation).norme() < getRayon()){
				return true;
			} 
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Station::traiterCollision(ElementJeuAbstrait* elementJeu)
///
/// Methode qui permet d<effectuer le traitement de la collision avec le type d'objet
/// La plupart du temps rien ne se passe.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return Aucune.
///
//////////////////////////////////////////////////////////////////////// 
void Station::traiterCollision(Projectile* projectile){
	this->pointDeVie_ -= 1;
	projectile->mustDie();
}	

////////////////////////////////////////////////////////////////////////
///
/// @fn Station::setPointDeVie(int pointDeVie)
///
/// Methode qui permet de determiner le nombre de point de vie de la station
///
/// @param[in] pointDeVie : nombre de point de vie de la station
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Station::setPointDeVie( int pointDeVie){
	pointDeVie_ = pointDeVie;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Station::getType()
///
/// Methode qui retourne le type de noeud
///
/// @param[in] aucun
///
/// @return Type::STATION.
///
////////////////////////////////////////////////////////////////////////
Type Station::getType(){
	return STATION;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void Station::update(float deltaT)
///
/// Methode qui permet de updater la station
///
/// @param[in] poids : poids de la station
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Station::update(float deltaT) {
	angle_ += VITESSE_ROTATION * deltaT;
	noeud_->setTransformation(positionActuelle_, angle_, axe_, taille_);
	if(!FacadeModele::obtenirInstance()->isModeEdition()){
		noeud_->afficherVie(this->pointDeVie_);
	}
}

ElementJeuAbstrait* Station::clone() const
{
	return new Station(*this);
}

void Station::traiterCollision(ElementJeuAbstrait* element){
	element->traiterCollision(this);
}

void Station::traiterCollision(Asteroide* asteroide) {
	asteroide->traiterCollision(this);
}

void Station::traiterCollision(Vaisseau* vaisseau){

	// SON
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISIONAUTRE);

	// Normale unitaire (vecteur centre-centre des Vaisseau)
	aiVector3D unitNormale = vaisseau->getPositionActuelle() - this->getPositionActuelle();
	unitNormale.Normalize();

	// Tangeante unitaire
	aiVector3D unitTangent = unitNormale;
	unitTangent.x = -unitNormale.y;
	unitTangent.y = unitNormale.x;

	// Vitesse initiale de chaque Vaisseaus
	aiVector3D vitVaisseau1 = vaisseau->getVitesse();
	aiVector3D vitStation = aiVector3D(0.0f , 0.0f , 0.0f);

	// Projection des vitesses sur la tangeante et la normale unitaire (avant la collision)
	double vitVaisseau1Normale   = unitNormale*vitVaisseau1;
	double vitVaisseau1Tangeante = unitTangent*vitVaisseau1;
	double vitStationNormale   = unitNormale*vitStation; // 0.0f
	double vitStationTangeante = unitTangent*vitStation; // 0.0f

	// La vitesse tangentielle reste pareille apres la collision
	double newVitVaisseau1Tangeante = vitVaisseau1Tangeante;

	// Cependant, la vitesse normale va changer
	double poidsStation = 100000000.0;
	double newVitVaisseau1Normale   = (vitVaisseau1Normale*(vaisseau->getPoids()-poidsStation)+2.0*poidsStation*vitStationNormale)
		/(vaisseau ->getPoids()+poidsStation); 

	// Reconvertir en vecteur les nouvelles vitesses (combinaison entre la vitesse normale et la vitesse tangeantielle
	vitVaisseau1 = (float)(newVitVaisseau1Normale)*unitNormale+(float)(newVitVaisseau1Tangeante)*unitTangent;

	//Reattribuer les vitesse
	vaisseau->setVitesse(vitVaisseau1);

	/*
	//Verifier s'il y encore un enfoncement entre station et Vaisseau
	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, 0.0f);
	Vecteur3 vecTemp2 = Vecteur3(vaisseau->getPositionActuelle().x, vaisseau->getPositionActuelle().y, 0.0f);
	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1, this->getRayon(), vecTemp2, vaisseau->getRayon());

	// S'il y a encore collision, separer les objets de l'enfoncement, on peut remplacer ca directement dans la section pour mettre les positions precedentes
	if(collision.type != aidecollision::Collision::COLLISION_AUCUNE){
		collision.direction.normaliser();

		aiVector3D newPosition = vaisseau->getPositionActuelle();
		
		// Si Vaisseau et a droite de this
		if(collision.direction[0]>0){
			newPosition.x += (float)(collision.direction[0]*collision.enfoncement);
		} else {
			newPosition.x -= (float)(collision.direction[0]*collision.enfoncement);
		}
		// Si Vaisseau est au dessus de l'autre
		if(collision.direction[1]>0){
			newPosition.y += (float)(collision.direction[1]*collision.enfoncement);
		} else {												
			newPosition.y -= (float)(collision.direction[1]*collision.enfoncement);
		}

		vaisseau->setPositionActuelle ( newPosition );
	}
	*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Station::afficherTexte()
///
/// Cette fonction effectue l'affichage de texte que les objets doivent
/// ecrire.
///
/// Elle ne fait rien de base car c'est seulement les stations pour le
/// moment qui affichent leurs point de vie.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Station::afficherTexte()
{	
	GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLdouble winX, winY, winZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

	Phont& monPhont = FacadeModele::obtenirInstance()->phontTexte_;
 
	gluProject(this->positionActuelle_.x-36, this->positionActuelle_.y-this->getRayon(), 0, modelview, projection, viewport, &winX, &winY, &winZ);

	int coinMaxX, coinMaxY;
	FacadeModele::obtenirInstance()->obtenirVue()->obtenirCoinsMax(coinMaxX, coinMaxY);
	monPhont.print(coinMaxX, coinMaxY, (GLuint) winX, (GLuint)winY, true, "%2.2i", this->pointDeVie_ );
}