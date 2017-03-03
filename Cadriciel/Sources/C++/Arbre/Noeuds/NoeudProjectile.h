/**
 * @file NoeudProjectile.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef NOEUD_PROJECTILE_H
#define NOEUD_PROJECTILE_H

#include "NoeudAbstrait.h"

/**
 * @class NoeudProjectile
 * @brief Cette classe permet d'afficher un projectile grace a l'arbre de rendu
 */
class NoeudProjectile : public NoeudAbstrait {
	public:
		/**
		 * Constructeur. Creer la liste d'affichage pour le projectile
		 * @param type Le type du noeud
		 */
						NoeudProjectile(const std::string& type);

		/**
		* Constructeur par copie
		* @param src L'objet que l'on veut copier
		*/
						NoeudProjectile(const NoeudProjectile& src);

		/**
		 * Destructeur
		 */
					   ~NoeudProjectile();

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