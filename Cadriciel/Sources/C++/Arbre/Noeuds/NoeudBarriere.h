/**
 * @file NoeudBarriere.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef NOEUD_BARRIERE_H
#define NOEUD_BARRIERE_H

#include "NoeudAbstrait.h"

/**
 * @class NoeudBarriere
 * @brief Cette classe permet d'afficher une barriere protectrice grace a l'arbre de rendu
 */
class NoeudBarriere : public NoeudAbstrait {
	public:
		/**
		 * Constructeur. Creer la liste d'affichage pour la barriere protectrice
		 * @param type Le type du noeud
		 */
						NoeudBarriere(const std::string& type);

		/**
		* Constructeur par copie
		* @param src L'objet que l'on veut copier
		*/
						NoeudBarriere(const NoeudBarriere& src);

		/**
		 * Destructeur
		 */
					   ~NoeudBarriere();

		/**
		 * Animation du noeud
		 */
		virtual void	animer(float dt);

		/// Le dessin concret du noeud (pour le moment c'est temporaire
		virtual void	afficherConcret() const;
};

#endif

/**
 * @}
 */