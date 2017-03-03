/**
 * @file NoeudAccelerateur.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef NOEUD_ACCELERATEUR_H
#define NOEUD_ACCELERATEUR_H

#include "NoeudAbstrait.h"

/**
 * @class NoeudAccelerateur
 * @brief Cette classe permet d'afficher un bonus accelerateur grace a l'arbre de rendu
 */
class NoeudAccelerateur : public NoeudAbstrait {
	public:
		/**
		 * Constructeur. Creer la liste d'affichage pour le bonus accelerateur
		 * @param type Le type du noeud
		 */
						NoeudAccelerateur(const std::string& type);

		/**
		* Constructeur par copie
		* @param src L'objet que l'on veut copier
		*/
						NoeudAccelerateur(const NoeudAccelerateur& src);

		/**
		 * Destructeur
		 */
					   ~NoeudAccelerateur();

		/**
		 * Animation du noeud
		 */
		virtual void	animer(float dt);

		/// Le dessin concret du noeud (pour le moment c'est temporaire)
		virtual void	afficherConcret() const;

		inline bool		getEstActif() const { return estActif_; }
		void			setEstActif(bool val) { estActif_ = val; }

	private:
		/** Détermine si le noeud est actif ou non (false veut dire qu'il était transparent) */
		bool			estActif_;
};

#endif

/**
 * @}
 */