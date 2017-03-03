///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"

#include <map>
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui represente l'arbre de rendu specifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilises par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par defaut.
			ArbreRenduINF2990();

   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu a son etat initial.
   void		initialiser();

   // TEMP changer ca pour un enum?
   // Chaînes pour les types
   static const std::string NOM_ACCELERATEUR;
   static const std::string NOM_ASTEROIDE;
   static const std::string NOM_BARRIERE;
   static const std::string NOM_PORTAIL;
   static const std::string NOM_PROJECTILE;
   static const std::string NOM_STATION;
   static const std::string NOM_VAISSEAU;
   static const std::string NOM_POSITION_DEPART;

};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////