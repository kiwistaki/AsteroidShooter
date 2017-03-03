//////////////////////////////////////////////////////////////////////////////
/// @file ComparateurCartes.h
/// @author FloppyDisketeers
/// @date 2014-03-18
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _COMPARATEUR_CARTES_H_
#define _COMPARATEUR_CARTES_H_

#include "../../Carte.h"
#include "../../GestionnaireXML.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
/// @class ComparateurCartes
/// @brief Foncteur permettant de comparer deux cartes entre elles selon
///			leur niveau de difficulte, puis selon leur nom.
///
/// @author Vincent Longpre
/// @date 2014-03-18
///////////////////////////////////////////////////////////////////////////
class ComparateurCartes
{
public:
	/// Redefinition de l'operateur ()
	/// @param s1 Le nom de la premiere carte a comparer
	/// @param s2 Le nom de la deuxieme carte a comparer
	bool operator() (string s1, string s2)
	{
		Carte* c1 = GestionnaireXML::obtenirInstance()->chargerCarte(s1);
		Carte* c2 = GestionnaireXML::obtenirInstance()->chargerCarte(s2);

		int diff1 = c1->getDifficulte(); // Difficulte de la premiere carte
		int diff2 = c2->getDifficulte(); // Difficulte de la deuxieme carte

		delete c1;
		delete c2;

		if (diff1 == diff2) // Si les deux cartes sont de meme difficulte
			return s1 < s2; // Trier par nom
		else
			return diff1 > diff2; // Trier par difficulte
	}
};

#endif // _COMPARATEUR_CARTES_H_