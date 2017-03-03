//////////////////////////////////////////////////////////////////////////////
/// @file FoncteurType.h
/// @author FloppyDisketeers
/// @date 2014-03-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef FONCTEUR_TYPE_H
#define FONCTEUR_TYPE_H

#include <iostream>
#include "../ElementObjet/ElementJeuAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class FoncteurType
/// @brief Classe foncteur qui permet de determiner si le type d'un element
///        est celui desire.
/// @author FloppyDisketeers
/// @date 2014-03-15
///////////////////////////////////////////////////////////////////////////
class FoncteurType
{
public:
	FoncteurType(int type) : type_(type) {}

	/**
	 *  Surcharge de l'opérateur ()
	 * @param: element du jeu  a verifier
	 * @return: bool 
	 */
	bool operator() (ElementJeuAbstrait *element)
	{
		return (element->getType() == type_);
	}

private:

	/**
	 * Int qui determine le type
	 */
	int type_;
};

#endif