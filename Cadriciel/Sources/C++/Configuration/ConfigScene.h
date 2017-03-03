//////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.h
/// @author Jean-Francois Perusse
/// @date 2007-01-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGSCENE_H__
#define __CONFIGURATION_CONFIGSCENE_H__


#include "Singleton.h"
#include "Vecteur.h"
#include "tinyxml.h"


///////////////////////////////////////////////////////////////////////////
/// @class ConfigScene
/// @brief Les variables de configuration de la classe CScene.
///        C'est une classe singleton.
///
/// @author Jean-Francois Perusse
/// @date 2007-01-10
///////////////////////////////////////////////////////////////////////////
class ConfigScene : public Singleton<ConfigScene>
{
   SINGLETON_DECLARATION_CLASSE(ConfigScene);

public:
   /// Creer le DOM avec les valeurs.
	/// @param node Le node
   void creerDOM( TiXmlNode& node ) const;

   /// Lire les valeurs du DOM.
   /// @param node Le node
   void lireDOM( const TiXmlNode& node );

   /// Nombre de calculs par image.
   static int CALCULS_PAR_IMAGE;

};


#endif // __CONFIGURATION_CONFIGSCENE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
