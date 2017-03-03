///////////////////////////////////////////////////////////////////////////////
/// @file Barriere.cpp
/// @author FloopyDisketeers
/// @date 2014-01-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Barriere.h"
#include <math.h>
#include "../../../Commun/Utilitaire/Utilitaire.h"

#include "../Arbre/ArbreRenduINF2990.h"
#include "../Application/FacadeModele.h"
#include "GestionnaireSon.h"

#include "Projectile.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn Barriere::Barriere()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Barriere::Barriere(){
	noeud_ = new NoeudBarriere(ArbreRenduINF2990::NOM_BARRIERE);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Barriere::Barriere( Vecteur3f positionDepart,
///				   Vecteur3f taille, Vecteur3f directionVitesse, unsigned int poids)
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Barriere::Barriere( Vecteur3f position1, Vecteur3f position2,
				   Vecteur3f taille, Vecteur3f directionVitesse, float poids){
	//setPositionDepart(position1);
	//setTaille(taille);
	setDirectionVitesse(directionVitesse);
	setPoids(poids);

	noeud_ = new NoeudBarriere(ArbreRenduINF2990::NOM_BARRIERE);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Barriere::Barriere(const Barriere& barriere)
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Barriere::Barriere(const Barriere& barriere) : ElementJeuAbstrait(barriere) {
	noeud_ = new NoeudBarriere(*(barriere.noeud_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Barriere::~Barriere()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Barriere::~Barriere(){
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(noeud_);
	noeud_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Barriere::positionBarriere(Vecteur3f position1, Vecteur3f position2)
///
/// Methode qui permet de set la bonne position de la barriere
///
/// @return void 
///
////////////////////////////////////////////////////////////////////////
void Barriere::positionBarriere(Vecteur3f position1, Vecteur3f position2){
	/*
		position1[0] = X1, position1[1] = Y1
		position2[0] = X2, position2[1] = Y2
	*/
	setPositionActuelle(position1 - (position1-position2)/2);

	// On definie l'angle de rotation
	setAxe(Vecteur3f(0.0f, 0.0f, 1.0f));

	// On calcule l'angle de la barriere 
	float a = position2[1] - position1[1];
	float b = -position1[0] + position2[0];
	setAngle((float)utilitaire::RAD_TO_DEG(atan2(a,b)));

	// On calcule la taille (l'hypothenuse)
	float hyp = sqrt(pow(a,2) + pow(b,2));
	setTaille(Vecteur3f(hyp/100, 1.0f, 1.0f));

}


////////////////////////////////////////////////////////////////////////
///
/// @fn Barriere::getPositionPt1()
///
/// Methode qui retourne le point #1 de la barrière
///
/// @return Vecteur3 
///
////////////////////////////////////////////////////////////////////////
Vecteur3f Barriere::getPositionPt1(){
	BoiteEnglobanteOrientee boite = getBoiteEnglobanteOrientee();

	float x, y, z;
	
	x = (float)(boite.getCoins()[0][0] + (0.5 * (boite.getCoins()[1][0] - boite.getCoins()[0][0])));
	y = (float)(boite.getCoins()[0][1] + (0.5 * (boite.getCoins()[1][1] - boite.getCoins()[0][1])));
	z = 0.0;

	Vecteur3f pt = Vecteur3f(x,y,z);

	return pt;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Barriere::getPositionPt1()
///
/// Methode qui retourne le point #2 de la barrière
///
/// @return Vecteur3 
///
////////////////////////////////////////////////////////////////////////
Vecteur3f Barriere::getPositionPt2(){
	BoiteEnglobanteOrientee boite = getBoiteEnglobanteOrientee();

	float x, y, z;

	x = (float)(boite.getCoins()[3][0] + (0.5 * (boite.getCoins()[2][0] - boite.getCoins()[3][0])));
	y = (float)(boite.getCoins()[3][1] + (0.5 * (boite.getCoins()[2][1] - boite.getCoins()[3][1])));
	z = 0.0;

	Vecteur3f pt = Vecteur3f(x,y,z); 

	return pt;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Barriere::getType()
///
/// Methode qui retourne le type de noeud
///
/// @param[in] aucun
///
/// @return Type::Barriere.
///
////////////////////////////////////////////////////////////////////////
Type Barriere::getType(){
	return BARRIERE;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Barriere::checkCollisionJoueurVirtuel(Vaisseau* joueurVirtuel)
///
/// Methode qui permet au joueur virtuel d'éviter les stations spatiales
///
/// @param[in] Vaisseau* joueurVirtuel 
///
/// @return bool : vrai si la trajectoire du vaisseau intersect la station
///
////////////////////////////////////////////////////////////////////////
bool Barriere::checkCollision(ElementJeuAbstrait* element) {
	return element->checkCollision(this);
}

bool Barriere::checkCollision(Asteroide* asteroide){
		
	//On va chercher la position de chacune des extrémités de la barrière
	Vecteur3 pt1Barriere = this->getPositionPt1();
	Vecteur3 pt2Barriere = this->getPositionPt2();

	//Position du centre de la sphère (Astéroide)
	Vecteur3 centreSphere = Vecteur3(asteroide->getPositionActuelle().x , asteroide->getPositionActuelle().y , 0.0f);

	//Rayon de la sphere
	double rayonSphere = asteroide->getRayon();

	//Vérification de collision
	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSegment(pt1Barriere , pt2Barriere , centreSphere , rayonSphere , true );  

	if(	collision.type != aidecollision::COLLISION_AUCUNE ){

		aiVector3D newPositionAst = asteroide->getPositionActuelle();
		
		collision.direction.normaliser();
		
		newPositionAst.x += (float)(collision.direction[0]*collision.enfoncement);
		newPositionAst.y += (float)(collision.direction[1]*collision.enfoncement);

		asteroide->setPositionActuelle(newPositionAst);

		return true;
	}

	return false;
}

bool Barriere::checkCollision(Projectile* projectile){
	projectile->setPositionPrecedente( projectile->getPositionActuelle() );

	BoiteEnglobanteOrientee boiteEng =  this->getBoiteEnglobanteOrientee();
	
	Vecteur3 pt1Barriere = this->getPositionPt1();
	Vecteur3 pt2Barriere = this->getPositionPt2();

	//Position du centre de la sphère (Astéroide)
	Vecteur3 centreSphere = Vecteur3(projectile->getPositionActuelle().x , projectile->getPositionActuelle().y , 0.0f);

	//Rayon de la sphere
	double rayonSphere = (projectile->getBoiteEnglobanteOrientee().getMoitieHauteur() + projectile->getBoiteEnglobanteOrientee().getMoitieLongueur() )/2.0;

	//Vérification de la boite englobante
	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSegment(pt1Barriere , pt2Barriere , centreSphere , rayonSphere * 3, true ); 

	if(collision.type != aidecollision::COLLISION_AUCUNE){
		return true;
	}

	return false;
}	

bool Barriere::checkCollision(Vaisseau* vaisseau){

	//On va chercher la position de chacune des extrémités de la barrière
	Vecteur3 pt1Barriere = this->getPositionPt1();
	Vecteur3 pt2Barriere = this->getPositionPt2();

	//Position du centre de la sphère (Astéroide)
	Vecteur3 posVaisseau = Vecteur3(vaisseau->getPositionActuelle().x , vaisseau->getPositionActuelle().y , vaisseau->getPositionActuelle().z);
	
	float rayonVaisseau = (vaisseau->getBoiteEnglobanteOrientee().getMoitieHauteur() + vaisseau->getBoiteEnglobanteOrientee().getMoitieLongueur())/2.0f;

	//Vérification de collision
	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSegment(pt1Barriere , pt2Barriere , posVaisseau , rayonVaisseau , true ); 

	if(	  collision.type != aidecollision::COLLISION_AUCUNE){
		aiVector3D newPositionVai = vaisseau->getPositionActuelle();
		
		collision.direction.normaliser();
		
		newPositionVai.x += (float)(collision.direction[0]*collision.enfoncement);
		newPositionVai.y += (float)(collision.direction[1]*collision.enfoncement);

		vaisseau->setPositionActuelle(newPositionVai);

		return true;
	}

	return false;
}

bool Barriere::checkCollisionJoueurVirtuel(Vaisseau* joueurVirtuel)
{
	Vecteur3 posVaisseau;
	posVaisseau[0] = joueurVirtuel->getPositionActuelle().x;
	posVaisseau[1] = joueurVirtuel->getPositionActuelle().y;
	posVaisseau[2] = joueurVirtuel->getPositionActuelle().z;

	float distanceCarte = FacadeModele::obtenirInstance()->getCarte()->getLargeur()/2.0f;
	Vecteur3 pointDir;
	pointDir[0] = joueurVirtuel->getPositionActuelle().x + joueurVirtuel->getDirectionVitesse().x * distanceCarte;
	pointDir[1] = joueurVirtuel->getPositionActuelle().y + joueurVirtuel->getDirectionVitesse().y * distanceCarte;
	pointDir[2] = joueurVirtuel->getDirectionVitesse().z;

	//On va chercher la position de chacune des extrémités de la barrière
	Vecteur3 pt1Barriere = this->getPositionPt1();
	Vecteur3 pt2Barriere = this->getPositionPt2();

	Vecteur3 A = pt1Barriere - posVaisseau;
	A.normaliser();
	Vecteur3 B = pt2Barriere - posVaisseau;
	B.normaliser();
	pointDir.normaliser();

	if(( produitScalaire(A, pointDir) >= 0  && produitScalaire(pointDir, B) >= 0 ) ) {
		double angleAB = produitScalaire(A, B);
		double angleAN = produitScalaire(A, pointDir);
		double angleBN = produitScalaire(B, pointDir);

		if( acos(angleBN) <= acos(angleAB) && acos(angleAN) <= acos(angleAB) ) {
			return true;
		} 
	}

	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Barriere::traiterCollision(ElementJeuAbstrait* elementJeu)
///
/// Methode qui permet d<effectuer le traitement de la collision avec le type d'objet
/// La plupart du temps rien ne se passe.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return Aucune.
///
//////////////////////////////////////////////////////////////////////// 
void Barriere::traiterCollision(ElementJeuAbstrait* element){
	element->traiterCollision(this);
}
void Barriere::traiterCollision(Projectile* projectile){
	projectile->mustDie();
	//SON
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISIONPROJ);
}

void Barriere::traiterCollision(Asteroide* asteroide) {
	asteroide->traiterCollision(this);
}

void Barriere::traiterCollision(Vaisseau* vaisseau){
	
	// SON
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISIONAUTRE); // Wtf ya une collision barrier/vaisseau qui ce produit quand on commence une partie rapide

	Vecteur3f pt1Barriere = this->getPositionPt1();
	Vecteur3f pt2Barriere = this->getPositionPt2();
	Vecteur3f posVaisseau= Vecteur3(vaisseau->getPositionActuelle().x , vaisseau->getPositionActuelle().y, 0.0f);
	bool casCritique = false;

	//On détecte si la barrière est verticale ou horizontale
	float dx = abs(pt1Barriere[0] - pt2Barriere[0]);
	float dy = abs(pt1Barriere[1] - pt2Barriere[1]);

	if(dx >= dy){ /*Horizontal*/

		//Détection d'un cas critique
		if(( (posVaisseau[0] > pt2Barriere[0] && posVaisseau[0] > pt1Barriere[0]) 
		  || (posVaisseau[0] < pt1Barriere[0] && posVaisseau[0] < pt2Barriere[0])) )
			casCritique = true;

	}else {

		//Détection d'un cas critique
		if(( (posVaisseau[1] > pt2Barriere[1] && posVaisseau[1] > pt1Barriere[1]) 
		  || (posVaisseau[1] < pt1Barriere[1] && posVaisseau[1] < pt2Barriere[1])) )
			casCritique = true;

	}

	if(!casCritique){
		//Vitesse initial du vaisseau
		aiVector3D v = vaisseau->getVitesse();

		//Normale
		aiVector3D ptSegment1 = aiVector3D(pt1Barriere[0] , pt1Barriere[1] , 0.0f);
		aiVector3D ptSegment2 = aiVector3D(pt2Barriere[0] , pt2Barriere[1] , 0.0f);

		aiVector3D ptCollision(vaisseau->getPositionActuelle().x , vaisseau->getPositionActuelle().y , 0.0f); //Estimation assez précise - Erreur d'environ la distance du rayon.

		aiVector3D vecTemp;
		//On sélectionne le pt le plus loin du point d'impact comme étant l'extrémité de la barrière.
		if( (ptSegment1 - ptCollision).Length() >= (ptSegment2 - ptCollision).Length()){
			vecTemp = ptSegment1 - ptCollision;
		}else{
			vecTemp = ptSegment2 - ptCollision;
		}

		vecTemp.Normalize();

		aiVector3D n = vecTemp;
		n.x = -vecTemp.y;
		n.y = vecTemp.x;

		//Calcul de la projection de la vitesse
		float vDOTn = v*n; 
		aiVector3D vitesseFinale = ((-2.0f * vDOTn) * n) + v;

		vaisseau->setVitesse(vitesseFinale);

	}else{
		//Dans le cas critique on ne fait qu'inverser la direction de la vitesse - Pour le moment.
		vaisseau->setVitesse(-1.0f * vaisseau->getVitesse());		
	}

	vaisseau->setPositionActuelle(vaisseau->getPositionPrecedente());
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Barriere::update()
///
/// Methode qui permet d'actualiser le rendu de l'objet
///
/// @param[in] aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Barriere::update(float deltaT) {
	noeud_->setTransformation(positionActuelle_, angle_, axe_, taille_);
}

ElementJeuAbstrait* Barriere::clone() const
{
	return new Barriere(*this);
}

