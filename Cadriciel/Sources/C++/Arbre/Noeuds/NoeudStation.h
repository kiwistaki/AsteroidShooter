/**
 * @file NoeudStation.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef NOEUD_STATION_H
#define NOEUD_STATION_H

#include "NoeudAbstrait.h"

/**
 * @class NoeudStation
 * @brief Cette classe permet d'afficher une Station grace a l'arbre de rendu
 */
class NoeudStation : public NoeudAbstrait {
	public:
		/**
		 * Constructeur. Creer la liste d'affichage pour la station
		 * @param type Le type du noeud
		 */
						NoeudStation(const std::string& type);

		/**
		* Constructeur par copie
		* @param src L'objet que l'on veut copier
		*/
						NoeudStation(const NoeudStation& src);

		/**
		 * Destructeur
		 */
					   ~NoeudStation();

		/**
		 * Animation du noeud
		 */
		virtual void	animer(float dt);

		/// Le dessin concret du noeud (pour le moment c'est temporaire
		virtual void	afficherConcret() const;

		/// Methode pour afficher le nombre de vies de la station
		void			afficherVie(const int& nbVie) const;
};

#endif

/**
 * @}
 */