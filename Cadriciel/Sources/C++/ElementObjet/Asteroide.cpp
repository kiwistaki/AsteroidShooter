///////////////////////////////////////////////////////////////////////////////
/// @file Asteroid.cpp
/// @author FloopyDisketeers
/// @date 2014-01-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Asteroide.h"
#include "math.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Application/FacadeModele.h"
#include "Vaisseau.h"
#include "Barriere.h"
#include "Portail.h"
#include "Projectile.h"
#include "../Application/AffichageDebogage.h"
#include "GestionnaireSon.h"

// Constante
const float  Asteroide::tabValeursNormale[] = {0.047790352f , 0.09121122f , 0.158655254f , 0.252492538f , 0.36944134f , 0.5f , 0.63055866f , 0.747507462f , 0.841344746f , 0.90878878f , 0.952209648f , 0.977249868f };
const int	 Asteroide::sizeOfTableauNormal = sizeof(Asteroide::tabValeursNormale)/sizeof(float);
const int	 Asteroide::pointDeVieMax		= 10;

////////////////////////////////////////////////////////////////////////
///
/// @fn Asteroide::Asteroide()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Asteroide::Asteroide() {
	noeud_ = new NoeudAsteroide(ArbreRenduINF2990::NOM_ASTEROIDE);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
	
	rotationX_=1.0f;
	rotationY_=1.0f;
	rotationZ_=1.0f;

	incX = randomFloat(0.1f , 0.8f);
	incY = randomFloat(0.1f , 0.8f);
	incZ = randomFloat(0.1f , 0.8f);

	toBeDeleted_ = false;
	canBeAttracted_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Asteroide::Asteroide( Vecteur4f cadreDepart, Vecteur4f zonePassage)
///
/// Constructeur par parametres
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Asteroide::Asteroide( Vecteur4f cadreDepart, Vecteur4f zonePassage){
	canBeAttracted_ = true;

	//On génère la taille.
	float t = (float)genererTailleAsteroide();

	// Une bonne formule pour la taille des astéroïdes semble être: 75 + 25 * taille ou taille est compris dans [0, 11]
	taille_.x = taille_.y = taille_.z = 75.0f + 25.0f * t;
	
	// Une bonne formule pour le rayon des astéroïdes (pour la collision) semble être 0.62 * (75 + 25 * taille)
	rayon_ = 0.60f * (75.0f + 23.0f * t);

	//Generer poids proportionnelle a la taille
	poids_ = t;

	//Generer vitesse rotation ou axe de rotation???
		// vitesseRotation_ = ??? // Il faut ajouter l'attribut
	
	//Generer points de vie proportionnel a la taille
	pointDeVie_ = (int) ceil( t / sizeOfTableauNormal*pointDeVieMax);

	//On génère la vitesse ATTENTION VITESSE PEUT ALLER DE 0.25 À 1.5 FOIS VITESSE MAX, FAUT PAS LIMITER
	moduleVitesse_ =(float)((double)(rand()%(RAND_MAX-(int)(RAND_MAX*0.25f) + 1) + RAND_MAX*0.25f)/ /*Partie pour avoir plage de valeur entre 0,25 fois randmax et randmax*/
					 (double)(RAND_MAX+1)*(Vaisseau::VITESSE_MAX*1.5f)); 

	// 0 == xMin, 1 == xMax, 2 == yMin, 3 == yMax
	//On génère la position de départ sur le cadre de départ.
	int	coteCadre= rand()%4;
	
	if(coteCadre == 0 || coteCadre == 1){

			positionDepart_[0] = cadreDepart[coteCadre];
			positionDepart_[1] = (float)(rand() % (int)(cadreDepart[3]-cadreDepart[2])+1 ) + cadreDepart[2]; //On génère une valeur entre yMin et yMax pour l'astéroide

	}else if(coteCadre == 2 || coteCadre == 3){

			positionDepart_[1] = cadreDepart[coteCadre];
			positionDepart_[0] = (float)(rand() % (int)(cadreDepart[1]-cadreDepart[0])+1 ) + cadreDepart[0]; //""
	}
	positionDepart_[2] = 0.0f;
	
	positionPrecedente_ = positionDepart_;
	positionActuelle_ = positionDepart_;

	// Calcul pour avoir le vecteur de la direction de l'asteroide.
	// Prendre n'importe quel point dans la zone de passage pour faire le vecteur de directionh
	Vecteur3f pointPourPassage;
	pointPourPassage[0] = (float)(rand() % ((int)zonePassage[1]+1) ) + zonePassage[0]; //""
	pointPourPassage[1] = (float)(rand() % ((int)zonePassage[3]+1) ) + zonePassage[2]; //On génère une valeur entre yMin et yMax pour l'astéroide
	pointPourPassage[2] = 0.0f;

	// Calcul des pentes
	for(unsigned int i=0; i<3; ++i){
		directionVitesse_[i]=pointPourPassage[i]-positionDepart_[i];
	}
	directionVitesse_.Normalize();
	
	noeud_ = new NoeudAsteroide(ArbreRenduINF2990::NOM_ASTEROIDE);

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;
	noeud_->setRayon(rayon_);

	rotationX_=1.0f;
	rotationY_=1.0f;
	rotationZ_=1.0f;

	incX = randomFloat(0.1f , 0.8f);
	incY = randomFloat(0.1f , 0.8f);
	incZ = randomFloat(0.1f , 0.8f);

	toBeDeleted_ = false;

	AffichageDebogage::obtenirInstance()->afficherApparitionAsteroide(positionActuelle_, moduleVitesse_, (unsigned int) t);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Asteroide::Asteroide()
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Asteroide::Asteroide( Vecteur3f positionDepart,
					 Vecteur3f taille, Vecteur3f directionVitesse, float poids, unsigned int pointDeVie){
	setPositionDepart(positionDepart);
	setTaille(taille);
	setDirectionVitesse(directionVitesse);
	setPoids(poids);
	setPointDeVie( pointDeVie);

	noeud_ = new NoeudAsteroide(ArbreRenduINF2990::NOM_ASTEROIDE);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	rotationX_=1.0f;
	rotationY_=1.0f;
	rotationZ_=1.0f;

	incX = randomFloat(0.1f , 0.8f);
	incY = randomFloat(0.1f , 0.8f);
	incZ = randomFloat(0.1f , 0.8f);

	canBeAttracted_ = true;
	toBeDeleted_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Asteroide::Asteroide(const Asteroide& asteroide)
///
/// Constructeur par parametre
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Asteroide::Asteroide(const Asteroide& asteroide) : ElementJeuAbstrait(asteroide) {
	setPointDeVie(asteroide.pointDeVie_);

	noeud_ = new NoeudAsteroide(*(asteroide.noeud_));
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->ajouter(noeud_);
	noeudAbstrait_ = noeud_;

	rotationX_=1.0;
	rotationY_=1.0;
	rotationZ_=1.0;

	incX = randomFloat(0.1f , 0.8f);
	incY = randomFloat(0.1f , 0.8f);
	incZ = randomFloat(0.1f , 0.8f);

	toBeDeleted_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Asteroide::~Asteroide()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Asteroide::~Asteroide(){
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(noeud_);
	noeud_ = 0;	

}

////////////////////////////////////////////////////////////////////////
///
/// @fn Asteroid::setPointDeVie(int pointDeVie)
///
/// Methode qui permet de determiner le nombre de point de vie du vaisseau
///
/// @param[in] pointDeVie : nombre de point de vie d'un asteroid
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Asteroide::setPointDeVie(int pointDeVie){
	pointDeVie_ = pointDeVie;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Asteroide::getType()
///
/// Methode qui retourne le type de noeud
///
/// @param[in] aucun
///
/// @return Type::ASTEROIDE.
///
////////////////////////////////////////////////////////////////////////
Type Asteroide::getType(){
	return ASTEROIDE;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Asteroide::update()
///
/// Methode qui permet d'actualiser le rendu de l'objet
///
/// @param[in] aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Asteroide::update(float deltaT) {
	positionPrecedente_ = positionActuelle_;

	rotationX_+=incX;
	this->noeud_->setAngleX(rotationX_);
			   		
	rotationY_+=incY;
	this->noeud_->setAngleY(rotationY_);
			   	
	rotationZ_+=incZ;
    this->noeud_->setAngleZ(rotationZ_);
			   	
		
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

ElementJeuAbstrait* Asteroide::clone() const
{
	return new Asteroide(*this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool Asteroide::checkCollision(ElementJeuAbstrait* elementJeu)
///
/// Methode qui permet de verifier s'il y a une collision de l'objet avec un autre objet.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return bool : Est-ce qu'il y a eu une collision
///
////////////////////////////////////////////////////////////////////////	 
bool Asteroide::checkCollision(ElementJeuAbstrait* elementJeuAbstrait){
	return elementJeuAbstrait->checkCollision(this);
}

bool Asteroide::checkCollision(Asteroide* asteroide)
{
	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, 0.0f);
	Vecteur3 vecTemp2 = Vecteur3(asteroide->positionActuelle_.x, asteroide->positionActuelle_.y, 0.0f);

	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1, rayon_, vecTemp2, asteroide->rayon_);

	if(collision.type != aidecollision::COLLISION_AUCUNE)
	{
		aiVector3D newPositionAst1 = this->getPositionActuelle();
		aiVector3D newPositionAst2 = asteroide->getPositionActuelle();
		
		collision.direction.normaliser();
		
		newPositionAst1.x -= (float)(collision.direction[0]*collision.enfoncement)/2.0f;
		newPositionAst2.x += (float)(collision.direction[0]*collision.enfoncement)/2.0f;

		newPositionAst1.y -= (float)(collision.direction[1]*collision.enfoncement)/2.0f;
		newPositionAst2.y += (float)(collision.direction[1]*collision.enfoncement)/2.0f;

		this->positionActuelle_ = newPositionAst1;
		asteroide->positionActuelle_ = newPositionAst2;

		return true;
	}

	return false;
}

bool Asteroide::checkCollision(Barriere* barriere) {
	return barriere->checkCollision(this);
}

bool Asteroide::checkCollision(Portail* portail) {
	return portail->checkCollision(this);
}

bool Asteroide::checkCollision(Projectile* projectile) {
	return projectile->checkCollision(this);
}

bool Asteroide::checkCollision(Station* station) {
	return station->checkCollision(this);
}

bool Asteroide::checkCollision(Vaisseau* vaisseau){
	return vaisseau->checkCollision(this);
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
void Asteroide::traiterCollision(ElementJeuAbstrait* elementAbstrait){
	elementAbstrait->traiterCollision(this);
}

void Asteroide::traiterCollision(Asteroide* asteroide){
	// Source: http://www.vobarian.com/collisions/2dcollisions2.pdf
	// Normale unitaire (vecteur centre-centre des asteroide)
	aiVector3D unitNormale = this->positionActuelle_ - asteroide->positionActuelle_;
	unitNormale.Normalize();
	
	// Tangeante unitaire
	aiVector3D unitTangent = unitNormale;
	unitTangent.x = -unitNormale.y;
	unitTangent.y = unitNormale.x;

	// Vitesse initiale de chaque asteroides
	aiVector3D vitAsteroide1 = this->moduleVitesse_*this->directionVitesse_;
	aiVector3D vitAsteroide2 = asteroide->moduleVitesse_*asteroide->directionVitesse_;

	// Projection des vitesses sur la tangeante et la normale unitaire (avant la collision)
	float vitAsteroide1Normale   = unitNormale*vitAsteroide1;
	float vitAsteroide1Tangeante = unitTangent*vitAsteroide1;
	float vitAsteroide2Normale   = unitNormale*vitAsteroide2;
	float vitAsteroide2Tangeante = unitTangent*vitAsteroide2;
	
	// La vitesse tangentielle reste pareille apres la collision
	float newVitAsteroide1Tangeante = vitAsteroide1Tangeante;
	float newVitAsteroide2Tangeante = vitAsteroide2Tangeante;
	// Cependant, la vitesse normale va changer
	float newVitAsteroide1Normale   = (vitAsteroide1Normale*(this->poids_-asteroide->poids_)+2.0f*asteroide->poids_*vitAsteroide2Normale)
									  /(this->poids_+asteroide->poids_); 
	float newVitAsteroide2Normale   = (vitAsteroide2Normale*(asteroide->poids_-this->poids_)+2.0f*this->poids_*vitAsteroide1Normale)
									  /(this->poids_+asteroide->poids_);
	
	// Reconvertir en vecteur les nouvelles vitesses (combinaison entre la vitesse normale et la vitesse tangeantielle
	vitAsteroide1 = newVitAsteroide1Normale*unitNormale+newVitAsteroide1Tangeante*unitTangent;
	vitAsteroide2 = newVitAsteroide2Normale*unitNormale+newVitAsteroide2Tangeante*unitTangent;
	
	//Reattribuer les vitesse
	this->moduleVitesse_		 = vitAsteroide1.Length();
	this->directionVitesse_		 = vitAsteroide1.Normalize();
	asteroide->moduleVitesse_	 = vitAsteroide2.Length();
	asteroide->directionVitesse_ = vitAsteroide2.Normalize();
	
	// SON
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISION);

	/*
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Verifier si l'enfoncement est trop profond(a cause des portails).
	Vecteur3 vecTemp1 = Vecteur3(positionActuelle_.x, positionActuelle_.y, 0.0f);
	Vecteur3 vecTemp2 = Vecteur3(asteroide->positionActuelle_.x, asteroide->positionActuelle_.y, 0.0f);
	aidecollision::DetailsCollision collision = aidecollision::calculerCollisionSphere(vecTemp1, rayon_, vecTemp2, asteroide->rayon_);

	// S'il y a encore collision, separer les objets de l'enfoncement, on peut remplacer ca directement dans la section pour mettre les positions precedentes
	if(collision.type != aidecollision::COLLISION_AUCUNE){
		collision.direction.normaliser();
		// Si asteroide et a droite de this
		if(collision.direction[0]>0){
			asteroide->positionActuelle_.x	+= (float)(collision.direction[0]*collision.enfoncement);
			this->positionActuelle_.x		-= (float)(collision.direction[0]*collision.enfoncement);
		} else {
			asteroide->positionActuelle_.x	-= (float)(collision.direction[0]*collision.enfoncement);
			this->positionActuelle_.x		+= (float)(collision.direction[0]*collision.enfoncement);
		}
		// Si asteroide est au dessus de l'autre
		if(collision.direction[1]>0){
			asteroide->positionActuelle_.y	+= (float)(collision.direction[1]*collision.enfoncement);
			this->positionActuelle_.y		-= (float)(collision.direction[1]*collision.enfoncement);
		} else {												
			asteroide->positionActuelle_.y	-= (float)(collision.direction[1]*collision.enfoncement);
			this->positionActuelle_.y		+= (float)(collision.direction[1]*collision.enfoncement);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	*/
	
}	 


void Asteroide::traiterCollision(Barriere* barriere){

	//Source : http://www.3dkingdoms.com/weekly/weekly.php?a=2

	Vecteur3f pt1Barriere = barriere->getPositionPt1();
	Vecteur3f pt2Barriere = barriere->getPositionPt2();
	Vecteur3f posAsteroide = Vecteur3(positionActuelle_.x , positionActuelle_.y, 0.0f);
	bool casCritique = false;

	//On détecte si la barrière est verticale ou horizontale
	float dx = abs(pt1Barriere[0] - pt2Barriere[0]);
	float dy = abs(pt1Barriere[1] - pt2Barriere[1]);

	if(dx >= dy){ /*Horizontal*/

		//Détection d'un cas critique
		if(( (posAsteroide[0] > pt2Barriere[0] && posAsteroide[0] > pt1Barriere[0]) 
		  || (posAsteroide[0] < pt1Barriere[0] && posAsteroide[0] < pt2Barriere[0])) )
			casCritique = true;

	}else {

		//Détection d'un cas critique
		if(( (posAsteroide[1] > pt2Barriere[1] && posAsteroide[1] > pt1Barriere[1]) 
		  || (posAsteroide[1] < pt1Barriere[1] && posAsteroide[1] < pt2Barriere[1])) )
			casCritique = true;

	}

	if(!casCritique){
		//Vitesse initial de l'astéroide
		aiVector3D v = this->moduleVitesse_*this->directionVitesse_;
		
		//Normale
		aiVector3D ptSegment1 = aiVector3D(pt1Barriere[0] , pt1Barriere[1] , 0.0f);
		aiVector3D ptSegment2 = aiVector3D(pt2Barriere[0] , pt2Barriere[1] , 0.0f);

		aiVector3D ptCollision(this->getPositionActuelle().x , this->getPositionActuelle().y , 0.0f); //Estimation assez précise - Erreur d'environ la distance du rayon.

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
		
		this->directionVitesse_	 = vitesseFinale.Normalize();

	}else{
		//Dans le cas critique on ne fait qu'inverser la direction de la vitesse.
		this->directionVitesse_	 = -1.0f * this->directionVitesse_	;		
	}

	this->positionActuelle_  = this->positionPrecedente_;

	// SON
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISION);

}	 
void Asteroide::traiterCollision(Portail* portail){
	portail->traiterCollision(this);
}	  
void Asteroide::traiterCollision(Projectile* projectile){
	this->pointDeVie_--;
	projectile->mustDie();

	// SON
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISIONPROJ);
}	 


void Asteroide::traiterCollision(Station* station){
	// Normale unitaire (vecteur centre-centre des asteroide)
	aiVector3D unitNormale = this->positionActuelle_ - station->getPositionActuelle();
	unitNormale.Normalize();

	// Tangeante unitaire
	aiVector3D unitTangent = unitNormale;
	unitTangent.x = -unitNormale.y;
	unitTangent.y = unitNormale.x;

	// Vitesse initiale de chaque asteroides
	aiVector3D vitAsteroide1 = this->moduleVitesse_*this->directionVitesse_;
	aiVector3D vitStation = aiVector3D(0.0f , 0.0f , 0.0f);

	// Projection des vitesses sur la tangeante et la normale unitaire (avant la collision)
	double vitAsteroide1Normale   = unitNormale*vitAsteroide1;
	double vitAsteroide1Tangeante = unitTangent*vitAsteroide1;
	double vitStationNormale   = unitNormale*vitStation; // 0.0f
	double vitStationTangeante = unitTangent*vitStation; // 0.0f

	// La vitesse tangentielle reste pareille apres la collision
	double newVitAsteroide1Tangeante = vitAsteroide1Tangeante;

	// Cependant, la vitesse normale va changer
	double poidsStation = 100000000.0;
	double newVitAsteroide1Normale   = (vitAsteroide1Normale*(this->poids_ - poidsStation)+2.0 * poidsStation *vitStationNormale)
		/(this->poids_+poidsStation); 

	// Reconvertir en vecteur les nouvelles vitesses (combinaison entre la vitesse normale et la vitesse tangeantielle
	vitAsteroide1 = (float)(newVitAsteroide1Normale)*unitNormale+(float)(newVitAsteroide1Tangeante)*unitTangent;

	//Reattribuer les vitesse
	this->moduleVitesse_		 = vitAsteroide1.Length();
	this->directionVitesse_		 = vitAsteroide1.Normalize();

	// Faire perdre points de vie a la station
	station->setPointDeVie(station->getPointDeVie()-1);

	// SON
	GestionnaireSon::obtenirInstance()->jouerSon(COLLISION);
}


void Asteroide::traiterCollision(Vaisseau* vaisseau){
	vaisseau->traiterCollision(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Asteroide::setCanBeAttracted(bool canBeAttracted)
///
/// Methode qui permet de setter si l'objet peut-etre attire
///
/// @param[in] canBeAttracted : si l'objet peut se faire attirer
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Asteroide::setCanBeAttracted(bool canBeAttracted){
	canBeAttracted_ = canBeAttracted;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int Asteroide::genererTailleAsteroide()
///
/// Génère un facteur multiplicatif de taille compris entre 1 et 12
///
/// @return taille générée
///
////////////////////////////////////////////////////////////////////////
int Asteroide::genererTailleAsteroide(){

	float valRandom = ((float) rand()) / ((float) RAND_MAX); // Valeur entre 0 et 1
	int taille;

	for(taille=0; taille<sizeOfTableauNormal; ++taille){
		// Prendre la bonne taille selon la distribution normale
		if(valRandom < tabValeursNormale[taille]){
			break;
		}
	}

	return taille+1;
}

void Asteroide::setCible(bool estCible)
{
	noeud_->setCible(estCible);
}

float Asteroide::getRayon(){
	return rayon_;
}

float Asteroide::randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
