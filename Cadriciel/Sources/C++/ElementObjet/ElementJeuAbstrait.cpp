///////////////////////////////////////////////////////////////////////////////
/// @file ElementJeuAbstrait.cpp
/// @author FloopyDisketeers
/// @date 2014-01-27
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "ElementJeuAbstrait.h"

#include "../Arbre/Noeuds/NoeudAbstrait.h"

class Asteroide; // Foward declaration pour traiter les collision elements / asteroides

// le numero de la position de depart
unsigned long ElementJeuAbstrait::numero_ = 0;

////////////////////////////////////////////////////////////////////////
///
/// @fn ElementJeuAbstrait::ElementJeuAbstrait()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ElementJeuAbstrait::ElementJeuAbstrait() : angle_(0.0f), taille_(1.0f),
										   noeudAbstrait_(NULL), forcePortail_(0.0f),
										   previousPortail_(0), axe_(0.0f, 0.0f, 1.0f),
										   acceleration_(0.0f, 0.0f, 0.0f), moduleVitesse_(0.0f)
{
	numero_++;
	this->setId(numero_);
	previousPortail_ = NULL;
	positionPrecedente_ = aiVector3D(0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ElementJeuAbstrait::ElementJeuAbstrait(const ElementJeuAbstrait& element)
///
/// Constructeur par copie
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ElementJeuAbstrait::ElementJeuAbstrait(const ElementJeuAbstrait& element){
	setTaille(element.taille_);
	setDirectionVitesse(element.directionVitesse_);
	setPositionDepart( element.positionDepart_);
	setPoids(element.poids_);
	positionActuelle_ = element.positionActuelle_;
	angle_ = element.angle_;
	axe_ = element.axe_;
	noeudAbstrait_ = element.noeudAbstrait_;
	forcePortail_ = element.forcePortail_;
	acceleration_ = element.acceleration_;

	id_ = element.id_;
	previousPortail_ = NULL;
	positionPrecedente_ = aiVector3D(0);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ElementJeuAbstrait::~ElementJeuAbstrait()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ElementJeuAbstrait::~ElementJeuAbstrait(){
	noeudAbstrait_ = NULL;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setPositionDepart(Vecteur3f positionDepart)
///
/// Methode qui permet de choisir la position initial d'un objet
///
/// @param[in] positionDepart : vecteur de la position de depart
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setPositionDepart(Vecteur3f positionDepart){
	for(unsigned int i=0; i < 3; i++){
		positionDepart_[i]=positionDepart[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setPositionDepart(aiVector3D positionDepart)
///
/// Methode qui permet de choisir la position initial d'un objet
///
/// @param[in] positionDepart : vecteur de la position de depart
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setPositionDepart(aiVector3D positionDepart){
	for(unsigned int i=0; i < 3; i++){
		positionDepart_[i]=positionDepart[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setPositionActuelle(Vecteur3f positionActuelle)
///
/// Methode qui permet de choisir la position actuelle d'un objet
///
/// @param[in] positionActuelle : vecteur de la position de actuelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setPositionActuelle(Vecteur3f positionActuelle){
	for(unsigned int i=0; i < 3; i++){
		positionActuelle_[i]=positionActuelle[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setPositionActuelle(aiVector3D positionActuelle)
///
/// Methode qui permet de choisir la position actuelle d'un objet
///
/// @param[in] positionActuelle : vecteur de la position de actuelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setPositionActuelle(aiVector3D positionActuelle){
	for(unsigned int i=0; i < 3; i++){
		positionActuelle_[i]=positionActuelle[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setDirectionVitesse(Vecteur3f directionVitesse)
///
/// Methode qui permet de choisir la vitesse de l'objet
///
/// @param[in] directionVitesse : vecteur de la vitesse de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setDirectionVitesse(Vecteur3f directionVitesse){
	for(unsigned int i=0; i < 3; i++){
		directionVitesse_[i]=directionVitesse[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setDirectionVitesse(aiVector3D directionVitesse)
///
/// Methode qui permet de choisir la vitesse de l'objet
///
/// @param[in] directionVitesse : vecteur de la vitesse de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setDirectionVitesse(aiVector3D directionVitesse){
	for(unsigned int i=0; i < 3; i++){
		directionVitesse_[i]=directionVitesse[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setModuleVitesse(float moduleVitesse)
///
/// Methode qui permet de modifier le module de vitesse de l'objet
///
/// @param[in] directionVitesse : vecteur de la vitesse de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setModuleVitesse(float moduleVitesse){
	moduleVitesse_ = moduleVitesse;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setAxe(Vecteur3f axe)
///
/// Methode qui permet de choisir l'axe de rotation de l'objet
///
/// @param[in] axe : vecteur de l'axe de rotation de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setAxe(Vecteur3f axe){
	for(unsigned int i=0; i < 3; i++){
		axe_[i]=axe[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setTaille(Vecteur3f taille)
///
/// Methode qui permet de modifier la taille de l'objet
///
/// @param[in] taille : vecteur de taille de l'objet par rapport a chaque axe
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setTaille( Vecteur3f taille){
	for(unsigned int i=0; i < 3; i++){
		taille_[i]=taille[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setTaille(aiVector3D taille)
///
/// Methode qui permet de modifier la taille de l'objet
///
/// @param[in] taille : vecteur de taille de l'objet par rapport a chaque axe
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setTaille( aiVector3D taille){
	for(unsigned int i=0; i < 3; i++){
		taille_[i]=taille[i];
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::setAngle(float angle)
///
/// Methode qui permet de choisir l'angle de rotation de l'objet
///
/// @param[in] angle :  l'angle rotation de l'objet 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setAngle(float angle){
	angle_ = angle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ElementJeuAbstrait::setPoids( float poids)
///
/// Methode qui permet de determiner le poids d'un objet
///
/// @param[in] poids : poids du vaisseau
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setPoids( float poids){
	poids_ = poids;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ElementJeuAbstrait::setId(unsigned int id)
///
/// Methode qui permet de determiner l'identificateur du l'objet
///
/// @param[in] id : identificateur du l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setId(unsigned int id){
	id_= id;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::deplacer(Vecteur3f deplacement)
///
/// Methode qui permet de modifier la position de l'objet
///
/// @param[in] deplacement : vecteur de la position de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::deplacer(Vecteur3f deplacement){
	positionActuelle_.x += deplacement[0];
	positionActuelle_.y += deplacement[1];
	positionActuelle_.z += deplacement[2];
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::deplacer(aiVector3D deplacement)
///
/// Methode qui permet de modifier la position de l'objet
///
/// @param[in] deplacement : vecteur de la position de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::deplacerAiVector(aiVector3D deplacement){
	positionActuelle_ += deplacement;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::pivoter(Vecteur3f pivot)
///
/// Methode qui permet de modifier la rotation de l'objet
///
/// @param[in] pivot : vecteur du pivot de rotation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::pivoter(Vecteur3f axe, float angle){
	setAngle(angle);
	setAxe(axe);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::pivoter(Vecteur3f pivot)
///
/// Methode qui permet de modifier la rotation de l'objet
///
/// @param[in] pivot : vecteur du pivot de rotation
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::pivoterAiVector(aiVector3D axe, float angle){
	setAngle(angle);
	axe_ = axe;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vElementJeuAbstrait::redimensionner(Vecteur3f redimensionnement)
///
/// Methode qui permet de redimensionner l'objet
///
/// @param[in] redimensionnement : vecteur de redimensionnement de l'objet
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::redimensionner(Vecteur3f redimensionnement){
	for(unsigned int i=0; i < 3; i++){
		taille_[i]=redimensionnement[i];
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ElementJeuAbstrait::checkCollision(ElementJeuAbstrait* elementJeu)
///
/// Methode qui permet de verifier s'il y a une collision de l'objet avec un autre objet.
/// Le traitement par defaut sera que le "this" est un cercle.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return bool : Est-ce qu'il y a eu une collision
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///
/// @fn void ElementJeuAbstrait::afficherTexte()
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
void ElementJeuAbstrait::afficherTexte()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool ElementJeuAbstrait::traiterCollision(ElementJeuAbstrait* elementJeu)
///
/// Methode qui permet d<effectuer le traitement de la collision avec le type d'objet
/// La plupart du temps rien ne se passe.
///
/// @param[in] elementJeu : l'autre objet avec lequel il faut verifier la collision
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

float ElementJeuAbstrait::getRayon(){
	return noeudAbstrait_->getModele3D()->getRayonSphereEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ElementJeuAbstrait::setForcePortail(float forcePortail)
///
/// Methode qui permet de setter la force d'attraction cause par un portail a proximite
///
/// @param[in] forcePortail : l'autre objet avec lequel il faut verifier la collision
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setForcePortail(float forcePortail){
	forcePortail_ = forcePortail;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ElementJeuAbstrait::setPreviousPortail(Portail* previousPortail)
///
/// Methode qui permet de setter le portail precedent (portail nouvellement transporte)
///
/// @param[in] previousPortail : le portail que l'objet vient d'etre transporte.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ElementJeuAbstrait::setPreviousPortail(Portail* previousPortail){
	previousPortail_ = previousPortail;
}

void ElementJeuAbstrait::setAcceleration(aiVector3D acceleration){
	acceleration_ = acceleration;
}

void ElementJeuAbstrait::setSelectionne(bool selectionner) {
	if (noeudAbstrait_->estSelectionne() && !selectionner ||
		!noeudAbstrait_->estSelectionne() && selectionner)
	{
		noeudAbstrait_->inverserSelection();
	}
}

bool ElementJeuAbstrait::getSelectionne() const {
	return noeudAbstrait_->estSelectionne();
}

void ElementJeuAbstrait::inverserSelection() {
	noeudAbstrait_->inverserSelection();
}

double ElementJeuAbstrait::calculerSphereEnglobante() const {
	return noeudAbstrait_->getModele3D()->calculerSphereEnglobante();
}

void ElementJeuAbstrait::calculerCylindreEnglobant(double& rayon,
												   double& bas,
												   double& haut) const {
	noeudAbstrait_->getModele3D()->calculerCylindreEnglobant(rayon, bas, haut);
}

void ElementJeuAbstrait::calculerBoiteEnglobante(Vecteur3& coinMin,
												 Vecteur3& coinMax) const {
	noeudAbstrait_->getModele3D()->calculerBoiteEnglobante(coinMin, coinMax);

	// Appliquer la transformation sur la boite
	coinMin[0] += positionActuelle_.x;
	coinMin[1] += positionActuelle_.y;
	coinMin[2] += positionActuelle_.z;

	coinMax[0] += positionActuelle_.x;
	coinMax[1] += positionActuelle_.y;
	coinMax[2] += positionActuelle_.z;
}

BoiteEnglobanteOrientee& ElementJeuAbstrait::getBoiteEnglobanteOrientee() {
	return noeudAbstrait_->getBoiteEnglobanteOrientee();
}