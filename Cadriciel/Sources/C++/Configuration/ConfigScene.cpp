////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.cpp
/// @author Jean-Francois Perusse
/// @date 2007-01-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigScene.h"
#include <iostream>


SINGLETON_DECLARATION_CPP(ConfigScene);

/// Nombre de calculs par image.
int ConfigScene::CALCULS_PAR_IMAGE   = 50;


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::creerDOM ( TiXmlNode& node ) const
///
/// Cette fonction ecrit les valeurs de la configuration dans un element XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::creerDOM ( TiXmlNode& node ) const
{
	// Creer le noeud 'configuration'
	TiXmlElement* elementConfiguration = new TiXmlElement("configuration");

	// Creer le noeud scene et definir ses attributs
	TiXmlElement* elementScene = new TiXmlElement("CScene");
	elementScene->SetAttribute("CALCULS_PAR_IMAGE", ConfigScene::CALCULS_PAR_IMAGE);
	
	// Adjoindre le noeud 'elementScene'
	elementConfiguration->LinkEndChild(elementScene);

	// Adjoindre le noeud 'configuration' au noeud principal
	// (Rappel : pas besoin de liberer la memoire de elementConfiguration
	// puisque toutes les fonctions Link... le font pour nous)
	node.LinkEndChild(elementConfiguration);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::lireDOM( const TiXmlNode& node )
///
/// Cette fonction lit les valeurs de la configuration a partir d'un element
/// XML.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::lireDOM( const TiXmlNode& node )
{
	// Tenter d'obtenir le noeud 'Configuration'
	const TiXmlElement* elementConfiguration = (TiXmlElement*)(node.FirstChild("configuration"));
	if (elementConfiguration != NULL) {
		// Tenter d'obtenir l'element CScene, puis l'attribut CALCULS_PAR_IMAGE
		const TiXmlElement* elementScene = (TiXmlElement*)(elementConfiguration->FirstChild("CScene"));
		if (elementScene != NULL) {
			if (elementScene->QueryIntAttribute("CALCULS_PAR_IMAGE", &ConfigScene::CALCULS_PAR_IMAGE) != TIXML_SUCCESS){
				std::cerr << "Erreur : CALCULS_PAR_IMAGE : chargement XML : attribut inexistant ou de type incorrect" << std::endl;
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
