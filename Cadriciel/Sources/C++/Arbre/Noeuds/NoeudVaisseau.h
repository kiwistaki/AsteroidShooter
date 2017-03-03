/**
 * @file NoeudVaisseau.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef NOEUD_VAISSEAU_H
#define NOEUD_VAISSEAU_H

#include "NoeudAbstrait.h"

/**
 * @class NoeudVaisseau
 * @brief Cette classe permet d'afficher un vaisseau grace a l'arbre de rendu
 */
class NoeudVaisseau : public NoeudAbstrait {
	public:
		/**
		 * Constructeur. Creer la liste d'affichage pour le vaisseau
		 * @param type Le type du noeud
		 */
						NoeudVaisseau(const std::string& type);

		/**
		* Constructeur par copie
		* @param src L'objet que l'on veut copier
		*/
						NoeudVaisseau(const NoeudVaisseau& src);

		/**
		 * Destructeur
		 */
					   ~NoeudVaisseau();

		/**
		 * Animation du noeud
		 */
		virtual void	animer(float dt);

		/// Le dessin concret du noeud (pour le moment c'est temporaire
		virtual void	afficherConcret() const;

		inline void		setJoueur1(bool val) { joueur1_ = val; }
		inline bool		getJoueur1() const { return joueur1_; }

	private:
		/** Est-ce que c'est le joueur 1? */
		bool			joueur1_;
};

#endif

/**
 * @}
 */