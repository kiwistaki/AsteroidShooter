//////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireXML.cpp
/// @author FloppyDisketeers
/// @date 2014-01-25
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "GestionnaireXML.h"
#include "../../../Commun/Utilitaire/Utilitaire.h"
#include "FacadeModele.h"
#include "../ElementObjet/ElementJeuAbstrait.h"
#include "../ElementObjet/PositionDepart.h"
#include "../ElementObjet/Portail.h"
#include "AffichageDebogage.h"

SINGLETON_DECLARATION_CPP(GestionnaireXML);

/// Messages d'erreurs
const string erreurFichier = "Erreur fichier inexistant.";
const string erreurSauvegardeCarteDefaut = "Erreur, il n'est pas permis de sauvegarder la carte de defaut."; 
const string erreurChargement = "Erreur lors du chargement de la carte.";

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireXML::GestionnaireXML()
///
/// Constructeur par defaut
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
GestionnaireXML::GestionnaireXML():nomCarteDefaut_("zones/carteDefaut.xml"), nomFichierConfig_("donnee/configuration.xml"), nomCampagneDefaut_("zones/campagneDefaut.xml")
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireXML::~GestionnaireXML()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
GestionnaireXML::~GestionnaireXML()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireXML::creerCarte(string nom)
///
/// Methode qui permet de créer une carte
///
/// @param[in] ficierXML : racine du fichier XML
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireXML::creerXML(TiXmlNode& noeud, Carte &carte) const
{
	TiXmlElement * root = new TiXmlElement("Root");

	TiXmlElement * conteneurElement = new TiXmlElement("ConteneurElement");

	// Le niveau de difficulte
	TiXmlElement * niveauDiff = new TiXmlElement("NiveauDiff");
	niveauDiff->SetAttribute("diff", carte.getDifficulte());

	// La frequence d'asteroide
	TiXmlElement * frequenceAsteroide = new TiXmlElement("FrequenceAsteroide");
	frequenceAsteroide->SetDoubleAttribute("frequenceAsteroide", carte.getFrequenceAsteroides());

	// Le nb min de station a sauver
	TiXmlElement * nbMinDeStation = new TiXmlElement("NbMinDeStation");
	nbMinDeStation->SetAttribute("nbMinDeStation", carte.getNbMinStationASauver());

	// L'acceleration bonnus
	TiXmlElement * bonusAcceleration = new TiXmlElement("BonusAcceleration");
	bonusAcceleration->SetAttribute("bonusAcceleration", carte.getAccelerationBonus());

	// On recupere le conteneur
	vector<ElementJeuAbstrait*>& conteneurElementCarte = carte.getVecteurElement();

	// Type de l'element
	Type type;

	// Parcour le conteneur d'élement et les rajouter aux differents noeuds
	for(vector<ElementJeuAbstrait*>::iterator it = conteneurElementCarte.begin(); it != conteneurElementCarte.end(); ++it)
	{
		type = (*it)->getType();
		
		TiXmlElement * element = new TiXmlElement("Element");
		element->SetAttribute("type", type);
		element->SetAttribute("id", (*it)->getId());
		element->SetDoubleAttribute("posX", (*it)->getPositionActuelle().x);
		element->SetDoubleAttribute("posY", (*it)->getPositionActuelle().y);
		element->SetDoubleAttribute("posZ", (*it)->getPositionActuelle().z);
		element->SetDoubleAttribute("angle", (*it)->getAngle());
		element->SetDoubleAttribute("axeX", (*it)->getAxe().x);
		element->SetDoubleAttribute("axeY", (*it)->getAxe().y);
		element->SetDoubleAttribute("axeZ", (*it)->getAxe().z);
		element->SetDoubleAttribute("tailleX", (*it)->getTaille().x);
		element->SetDoubleAttribute("tailleY", (*it)->getTaille().y);
		element->SetDoubleAttribute("tailleZ", (*it)->getTaille().z);

		if (type == PORTAIL) {
			element->SetAttribute("idFrere", DYNAMIC_CAST<Portail*>(*it)->getIdFrere());
		}

		conteneurElement->LinkEndChild(element);
	}

	root->LinkEndChild(niveauDiff);
	root->LinkEndChild(frequenceAsteroide);
	root->LinkEndChild(nbMinDeStation);
	root->LinkEndChild(bonusAcceleration);
	root->LinkEndChild(conteneurElement);

	noeud.LinkEndChild(root);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireXML::sauvegarderCarte(string nom) const
///
/// Methode qui permet de sauvegarder une carte
///
/// @param[in] nom : nom avec lequelle la carte va etre sauvegarder 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireXML::sauvegarderCarte(const string nom, Carte &carte) const
{
	if (nom == nomCarteDefaut_ || nom == "carteDefaut.xml")
	{
		// Il n'est pas permis de sauvegarder la carte de defaut
		utilitaire::afficherErreur(erreurSauvegardeCarteDefaut);
	} else {
		if(carte.sauvegardeOk()) {
			// La carte peu etre sauvegarder

			if(utilitaire::fichierExiste(nom)) {
				// Le fichier existe déja
				// TODO : Incrementer la version (BONBON)
			} 

			TiXmlDocument doc;
			TiXmlDeclaration * decl = new TiXmlDeclaration("1,0","","");
			doc.LinkEndChild(decl);
			
			// On cree tous les elements XML present dans la carte
			creerXML(doc, carte);

			// On modifie le nom de la carte
			carte.setNom(nom);

			// On sauvegarde la carte qui a ete modifier
			doc.SaveFile(nom.c_str());
		}
	}
}

////////////////////////////////////////////////////////////////////////
////// @fn void GestionnaireXML::chargerCarte(string nom) const
///
/// Methode qui permet de charger une zone de jeu
///
/// @param[in] nom : nom de la carte a charger
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Carte* GestionnaireXML::chargerCarte(const string nom) 
{
	// TEMP il faut l'arbre de rendu maintenant pour le populer avec les noeuds
	Carte* carte = new Carte(nom, FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990());

	if(!utilitaire::fichierExiste(nom)){
		// Si la carte n'existe pas, on la cree a partir de la carte par defaut
		carte = chargerCarteDefaut();
		//sauvegarderCarte(nom.c_str(), *carte);
	} else {
		// Le fichier existe
		TiXmlDocument doc;

		if(!doc.LoadFile(nom.c_str())){
			// Erreur lors du chargement de la carte.
			utilitaire::afficherErreur(erreurChargement);

		} else {
			// Charger tout les elements de la carte
			lireXML(doc, *carte); 
			// La carte a bien été charger

		}
	}
	
	return carte;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireXML::lireCarte()
///
/// Methode qui permet de lire des elements d'un fichier XML
///
/// @param[in] carte : le noeud de la carte XML
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void GestionnaireXML::lireXML(TiXmlNode& fichierXML, Carte& carte) const
{
	TiXmlHandle docHandle(&fichierXML);
	TiXmlElement* pRoot;
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	// block: root
	
		// On met le root ds pElem
		pRoot = docHandle.FirstChildElement().Element();
		// Il n'y a pas de root, on quitte.
		if (!pRoot) 
			return;

		//string nom = pElem->Value();

		hRoot = TiXmlHandle(pRoot);

	// On recupere la difficulte
	int diff = 0;
	pElem = hRoot.FirstChild("NiveauDiff").Element();
	if(pElem->QueryIntAttribute("diff", &diff) == TIXML_SUCCESS)
		carte.setDifficulte(diff);

	// La frequence d'asteroide
	float frequence = 0;
	pElem = hRoot.FirstChild("FrequenceAsteroide").Element();
	if(pElem->QueryFloatAttribute("frequenceAsteroide", &frequence) == TIXML_SUCCESS)
		carte.setFrequenceAsteroides(frequence);

	// Le nb min de station a sauver
	int nbStationASauver = 0;
	pElem = hRoot.FirstChild("NbMinDeStation").Element();
	if(pElem->QueryIntAttribute("nbMinDeStation", &nbStationASauver) == TIXML_SUCCESS)
		carte.setNbMinStationASauver(nbStationASauver);

	// L'acceleration bonnus
	int acceleration = 0;
	pElem = hRoot.FirstChild("BonusAcceleration").Element();
	if(pElem->QueryIntAttribute("bonusAcceleration", &acceleration) == TIXML_SUCCESS)
		carte.setAccelerationBonus(acceleration);

	// On récupere tous les éléments
	pElem = hRoot.FirstChild("ConteneurElement").FirstChild().Element();
	for(pElem; pElem; pElem=pElem->NextSiblingElement()) {
		carte.creerElementParXML(*pElem);
	}

	carte.associerFreresPortails();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireXML::creerCarteDefaut()
///
/// Methode qui cree la carte par defaut
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Carte* GestionnaireXML::chargerCarteDefaut()
{
	Carte* carte = new Carte(nomCarteDefaut_, FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990());

	TiXmlDocument carteDefaut;
	TiXmlDeclaration *decl = new TiXmlDeclaration("1,0","","");
	carteDefaut.LinkEndChild(decl);

	// 2 position de départ
	PositionDepart* positionDepartVaisseau1 = new PositionDepart();
	carte->ajouterElement(positionDepartVaisseau1);
	Vecteur3 positionDepart1;
	positionDepart1[0] = -50.0;
	positionDepart1[1] = 0.0;
	positionDepartVaisseau1->setPositionActuelle(positionDepart1);

	PositionDepart* positionDepartVaisseau2 = new PositionDepart();
	Vecteur3 positionDepart2;
	positionDepart2[0] = 50.0;
	positionDepart2[1] = 0.0;
	positionDepartVaisseau2->setPositionActuelle(positionDepart2);
	carte->ajouterElement(positionDepartVaisseau2);

	creerXML(carteDefaut, *carte);

	carteDefaut.SaveFile(nomCarteDefaut_.c_str());

	return carte;
}

Carte* GestionnaireXML::chargerCarteCampagneDefaut()
{
	Carte* carte = new Carte(nomCampagneDefaut_, FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990());

	TiXmlDocument carteCampagneDefaut;
	TiXmlDeclaration *decl = new TiXmlDeclaration("1,0","","");
	carteCampagneDefaut.LinkEndChild(decl);

	// 2 position de départ
	PositionDepart* positionDepartVaisseau1 = new PositionDepart();
	carte->ajouterElement(positionDepartVaisseau1);
	Vecteur3 positionDepart1;
	positionDepart1[0] = -50.0;
	positionDepart1[1] = 0.0;
	positionDepartVaisseau1->setPositionActuelle(positionDepart1);

	PositionDepart* positionDepartVaisseau2 = new PositionDepart();
	Vecteur3 positionDepart2;
	positionDepart2[0] = 50.0;
	positionDepart2[1] = 0.0;
	positionDepartVaisseau2->setPositionActuelle(positionDepart2);
	carte->ajouterElement(positionDepartVaisseau2);

	// 2 station
	Station* station1 = new Station();
	Vecteur3 positionStation1;
	positionStation1[0] = 200.0;
	positionStation1[1] = 200.0;
	station1->setPositionActuelle(positionDepart2);
	carte->ajouterElement(station1);

	Station* station2 = new Station();
	Vecteur3 positionStation2;
	positionStation2[0] = -200.0;
	positionStation2[1] = -200.0;
	station1->setPositionActuelle(positionStation2);
	carte->ajouterElement(station2);

	carte->setDifficulte(1);

	creerXML(carteCampagneDefaut, *carte);

	carteCampagneDefaut.SaveFile(nomCampagneDefaut_.c_str());

	return carte;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireXML::creerCarteDefaut()
///
/// Methode qui retourne le nom de la carte par défaut
///
/// @return string nomCarteDefaut_.
///
////////////////////////////////////////////////////////////////////////
string GestionnaireXML::getNomCarteDefaut() const
{
	return nomCarteDefaut_;
}

void GestionnaireXML::sauvegarderConfiguration(int toucheJoueur1Propulsion, int toucheJoueur1TournerGauche,
											   int toucheJoueur1TournerDroite, int toucheJoueur1Manoeuvre,
											   int toucheJoueur1Tir, int toucheJoueur2Propulsion,
											   int toucheJoueur2TournerGauche, int toucheJoueur2TournerDroite,
											   int toucheJoueur2Manoeuvre, int toucheJoueur2Tir,
											   double dureeJeu, int pointsDeVieStation, bool apparitionAsteroide, 
											   bool changementMode, bool eclairage,
											   bool cibleJoueur, bool cadreDepart, bool zonePassage,
											   bool attractionPort) const
{
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1,0","","");
	doc.LinkEndChild(decl);
			
	// On cree tous les elements XML present dans le fichier de configuration
	TiXmlElement * root = new TiXmlElement("Root");
	// On creer le noeud touches qui contient toutes les touches
	TiXmlElement * touches = new TiXmlElement("Touches");

	touches->SetAttribute("j1Prop",		toucheJoueur1Propulsion);
	touches->SetAttribute("j1Gauche",	toucheJoueur1TournerGauche);
	touches->SetAttribute("j1Droite",	toucheJoueur1TournerDroite);
	touches->SetAttribute("j1Man",		toucheJoueur1Manoeuvre);
	touches->SetAttribute("j1Tir",		toucheJoueur1Tir);
	touches->SetAttribute("j2Prop",		toucheJoueur2Propulsion);
	touches->SetAttribute("j2Gauche",	toucheJoueur2TournerGauche);
	touches->SetAttribute("j2Droite",	toucheJoueur2TournerDroite);
	touches->SetAttribute("j2Man",		toucheJoueur2Manoeuvre);
	touches->SetAttribute("j2Tir",		toucheJoueur2Tir);

	root->LinkEndChild(touches);

	TiXmlElement * dureeDeJeu = new TiXmlElement("DureeDeJeu");
	dureeDeJeu->SetDoubleAttribute("DureeJeu", dureeJeu);

	TiXmlElement * ptsDeVies = new TiXmlElement("PointsDeVie");
	ptsDeVies->SetAttribute("PointsVieStation", pointsDeVieStation);
	
	TiXmlElement * apparitionDeAsteroide = new TiXmlElement("ApparitionDeAsteroide");
	apparitionDeAsteroide->SetAttribute("ApparitionAsteroide", apparitionAsteroide);

	TiXmlElement * changementDeMode = new TiXmlElement("ChangementDeMode");
	changementDeMode->SetAttribute("ChangementMode", changementMode);

	TiXmlElement * eclairageDe = new TiXmlElement("EclairageDe");
	eclairageDe->SetAttribute("Eclairage", eclairage);

	TiXmlElement * cibleDeJoueur = new TiXmlElement("CibleDeJoueur");
	cibleDeJoueur->SetAttribute("CibleJoueur", cibleJoueur);

	TiXmlElement * cadreDeDepart = new TiXmlElement("CadreDeDepart");
	cadreDeDepart->SetAttribute("CadreDepart", cadreDepart);

	TiXmlElement * zoneDePassage = new TiXmlElement("ZoneDePassage");
	zoneDePassage->SetAttribute("ZonePassage", zonePassage);

	TiXmlElement * attractionDePort = new TiXmlElement("AttractionDePort");
	attractionDePort->SetAttribute("AttractionPort", attractionPort);

	root->LinkEndChild(attractionDePort);
	root->LinkEndChild(zoneDePassage);
	root->LinkEndChild(cadreDeDepart);
	root->LinkEndChild(cibleDeJoueur);
	root->LinkEndChild(eclairageDe);
	root->LinkEndChild(changementDeMode);
	root->LinkEndChild(apparitionDeAsteroide);

	root->LinkEndChild(ptsDeVies);
	root->LinkEndChild(dureeDeJeu);
	
	doc.LinkEndChild(root);

	// On sauvegarde le fichier
	doc.SaveFile(nomFichierConfig_.c_str());
}

void GestionnaireXML::chargerConfiguration(int& toucheJoueur1Propulsion, int& toucheJoueur1TournerGauche,
										   int& toucheJoueur1TournerDroite, int& toucheJoueur1Manoeuvre,
										   int& toucheJoueur1Tir, int& toucheJoueur2Propulsion,
										   int& toucheJoueur2TournerGauche, int& toucheJoueur2TournerDroite,
										   int& toucheJoueur2Manoeuvre, int& toucheJoueur2Tir,
										   double& dureeJeu, int& pointsDeVieStation, bool& apparitionAsteroide,
										 bool& changementMode, bool& eclairage, bool& cibleJoueur,
										 bool& cadreDepart, bool& zonePassage, bool& attractionPort, bool& fichierExiste) const
{  
	if(!utilitaire::fichierExiste(nomFichierConfig_)){
		// Si la carte n'existe pas
		fichierExiste = false;
	} else {
		fichierExiste = true; 

		// Le fichier existe
		TiXmlDocument doc;

		if(!doc.LoadFile(nomFichierConfig_.c_str())){
			// Erreur lors du chargement de la carte.
			utilitaire::afficherErreur(erreurChargement);

		} else {
			// Charger tout les elements du fichier
			TiXmlHandle docHandle(&doc);
			TiXmlElement* pRoot;
			TiXmlElement* pElem;
			TiXmlHandle hRoot(0);

			// block: root
	
				// On met le root ds pElem
				pRoot = docHandle.FirstChildElement().Element();
				// Il n'y a pas de root, on quitte.
				if (!pRoot) 
					return;

				hRoot = TiXmlHandle(pRoot);

			// fin block root

			// On recupere la map des touches
			map<int,int>* mapDesTouches_ = FacadeModele::obtenirInstance()->getMapCommandes();
			// On recupere la carte
			Carte *carte_ = FacadeModele::obtenirInstance()->getCarte();

			// On récupere tous les éléments
			pElem = hRoot.FirstChild("Touches").Element();

			if(pElem->QueryIntAttribute("j1Prop", &toucheJoueur1Propulsion) == TIXML_SUCCESS) {					
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur1Propulsion);					
			}																									
			if(pElem->QueryIntAttribute("j1Gauche", &toucheJoueur1TournerGauche) == TIXML_SUCCESS) {					
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur1TournerGauche);						
			}																										
			if(pElem->QueryIntAttribute("j1Droite", &toucheJoueur1TournerDroite) == TIXML_SUCCESS) {					
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur1TournerDroite);					
			}																										
			if(pElem->QueryIntAttribute("j1Man", &toucheJoueur1Manoeuvre) == TIXML_SUCCESS) {						
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur1Manoeuvre);
			}
			if(pElem->QueryIntAttribute("j1Tir", &toucheJoueur1Tir) == TIXML_SUCCESS) {
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur1Tir);
			}
			if(pElem->QueryIntAttribute("j2Prop", &toucheJoueur2Propulsion) == TIXML_SUCCESS) {
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur2Propulsion);
			}
			if(pElem->QueryIntAttribute("j2Gauche",	&toucheJoueur2TournerGauche) == TIXML_SUCCESS) {
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur2TournerGauche);
			}
			if(pElem->QueryIntAttribute("j2Droite", &toucheJoueur2TournerDroite) == TIXML_SUCCESS) {
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur2TournerDroite);
			}
			if(pElem->QueryIntAttribute("j2Man", &toucheJoueur2Manoeuvre) == TIXML_SUCCESS) {
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur2Manoeuvre);
			}
			if(pElem->QueryIntAttribute("j2Tir", &toucheJoueur2Tir) == TIXML_SUCCESS) {
				FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJoueur2Tir);
			}

			// On recupere la duree de jeu
			pElem = hRoot.FirstChild("DureeDeJeu").Element();
			if(pElem->QueryDoubleAttribute("DureeJeu", &dureeJeu) == TIXML_SUCCESS) {
				FacadeModele::obtenirInstance()->setDureeJeu(dureeJeu);
			}

			// On recupere les points de vies
			pElem = hRoot.FirstChild("PointsDeVie").Element();
			if(pElem->QueryIntAttribute("PointsVieStation", &pointsDeVieStation) == TIXML_SUCCESS) {
				FacadeModele::obtenirInstance()->setPtsVieStation(pointsDeVieStation);
			}


			// apparitionAsteroide
			pElem = hRoot.FirstChild("ApparitionDeAsteroide").Element();
			if(pElem->QueryBoolAttribute("ApparitionAsteroide", &apparitionAsteroide) == TIXML_SUCCESS) {
				AffichageDebogage::obtenirInstance()->setAfficherApparitionAsteroide(apparitionAsteroide);
			}
			
			// changementDeMode
			pElem = hRoot.FirstChild("ChangementDeMode").Element();
			if(pElem->QueryBoolAttribute("ChangementMode", &changementMode) == TIXML_SUCCESS) {
				AffichageDebogage::obtenirInstance()->setAfficherChangementModeJoueurVirtuel(changementMode);
			}

			// eclairage
			pElem = hRoot.FirstChild("EclairageDe").Element();
			if(pElem->QueryBoolAttribute("Eclairage", &eclairage) == TIXML_SUCCESS) {
				AffichageDebogage::obtenirInstance()->setAfficherModificationEclairage(eclairage);
			}

			// cibleJoueur
			pElem = hRoot.FirstChild("CibleDeJoueur").Element();
			if(pElem->QueryBoolAttribute("CibleJoueur", &cibleJoueur) == TIXML_SUCCESS) {
				AffichageDebogage::obtenirInstance()->setAfficherAsteroideCible(cibleJoueur);
			}

			// cadreDeDepart
			pElem = hRoot.FirstChild("CadreDeDepart").Element();
			if(pElem->QueryBoolAttribute("CadreDepart", &cadreDepart) == TIXML_SUCCESS) {
				AffichageDebogage::obtenirInstance()->setAfficherCadreDepart(cadreDepart);
			}

			// zonePassage
			pElem = hRoot.FirstChild("ZoneDePassage").Element();
			if(pElem->QueryBoolAttribute("ZonePassage", &zonePassage) == TIXML_SUCCESS) {
				AffichageDebogage::obtenirInstance()->setAfficherZonePassage(zonePassage);
			}

			// attractionPort
			pElem = hRoot.FirstChild("AttractionDePort").Element();
			if(pElem->QueryBoolAttribute("AttractionPort", &attractionPort) == TIXML_SUCCESS) {
				AffichageDebogage::obtenirInstance()->setAfficherRayonAttraction(attractionPort);
			}

		}
	}
}

void GestionnaireXML::sauvegarderConfigCampagne(bool modeCoop, bool joueur2Virtuel, vector<string> listeCarte)
{
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1,0","","");
	doc.LinkEndChild(decl);
			
	// On cree tous les elements XML present dans le fichier de configuration
	TiXmlElement * root = new TiXmlElement("Root");

	TiXmlElement * modeDeCoop = new TiXmlElement("ModeCoop");
	modeDeCoop->SetAttribute("modeCoop", modeCoop);
	TiXmlElement * joueur2deVirtuel = new TiXmlElement("Joueur2Virtuel");
	joueur2deVirtuel->SetAttribute("joueur2Virtuel", joueur2Virtuel);

	TiXmlElement * conteneurCarte = new TiXmlElement("ConteneurCarte");
	for(vector<string>::iterator it = listeCarte.begin(); it != listeCarte.end(); it++){
		TiXmlElement * nomCarte = new TiXmlElement("Carte");
		nomCarte->SetAttribute("Nom", (*it).c_str());

		conteneurCarte->LinkEndChild(nomCarte);
	}

	root->LinkEndChild(conteneurCarte);

	root->LinkEndChild(joueur2deVirtuel);
	root->LinkEndChild(modeDeCoop);
	
	doc.LinkEndChild(root);

	// On sauvegarde le fichier
	doc.SaveFile("donnee/ConfigCampagne.xml");
}

void GestionnaireXML::chargerConfigCampagne(bool& modeCoop, bool& joueur2Virtuel, bool& fichier, vector<string>& listeCarte)
{
	if(!utilitaire::fichierExiste("donnee/ConfigCampagne.xml")){
		fichier = false;
	} else {
		fichier = true;
		// Le fichier existe
		TiXmlDocument doc;

		string nom = "donnee/ConfigCampagne.xml";
		if(!doc.LoadFile(nom.c_str())){
			// Erreur lors du chargement de la carte.
			utilitaire::afficherErreur(erreurChargement);

		} else {
			// Charger tout les elements du fichier
			TiXmlHandle docHandle(&doc);
			TiXmlElement* pRoot;
			TiXmlElement* pElem;
			TiXmlHandle hRoot(0);

			// block: root
	
				// On met le root ds pElem
				pRoot = docHandle.FirstChildElement().Element();
				// Il n'y a pas de root, on quitte.
				if (!pRoot) 
					return;

				hRoot = TiXmlHandle(pRoot);

			// fin block root
		
			// modeCoop
			pElem = hRoot.FirstChild("ModeCoop").Element();
			if(pElem->QueryBoolAttribute("modeCoop", &modeCoop) == TIXML_SUCCESS){}

			// modeCoop
			pElem = hRoot.FirstChild("Joueur2Virtuel").Element();
			if(pElem->QueryBoolAttribute("joueur2Virtuel", &modeCoop) == TIXML_SUCCESS){}

			// On récupere tous les éléments
			/*string nomCarte;
			pElem = hRoot.FirstChild("ConteneurCarte").FirstChild().Element();
			for(pElem; pElem; pElem=pElem->NextSiblingElement()) {	
				nomCarte = pElem->GetText();
				listeCarte.push_back(nomCarte);
			}*/
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////