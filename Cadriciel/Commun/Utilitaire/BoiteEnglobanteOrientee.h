/**
 * @file BoiteEnglobanteOrientee.h
 * @author The Floppydisketeers
 * @date 2014-02-11
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef	BOITE_ENGLOBANTE_ORIENTEE_H
#define BOITE_ENGLOBANTE_ORIENTEE_H

#include "Vecteur.h"

#include "../Externe/assimp/include/assimp.hpp"
#include "../Externe/assimp/include/aiVector3D.h"

#include "Droite3D.h"

#include <vector>
using namespace std;

namespace math {

/**
 * @class BoiteEnglobanteOrientee
 * Cette classe definie une boite englobante orientee selon l'objet qu'elle
 * englobe. Elle permet de tester les intersections avec d'autres boites
 * englobantes orientees.
 */
class BoiteEnglobanteOrientee {
	public:
		/**
		 * Constructeur par defaut
		 */
								BoiteEnglobanteOrientee();

		/**
		 * Constructeur.
		 * @param coinMin Le coin minimum de la boite englobante
		 * @param coinMax Le coin maximum de la boite englobante
		 * @param angle L'angle de rotation de la boite englobante (0 par defaut)
		 */
								BoiteEnglobanteOrientee(const Vecteur3f& coinMin,
														const Vecteur3f& coinMax);

		/**
		 * Verifie si une autre boite englobante orientee intersecte celle-ci
		 * @param obb La seconde boite englobante orientee (Oriented Bounding Box)
		 * avec laquelle on veut verifier la collision.
		 * @return true si l'objet est rentre en collision avec la boite englobante
		 */
		bool					calculerCollision(const BoiteEnglobanteOrientee& obb) const;

		/**
		 * Met a jour la boite englobante pour avoir sa nouvelle orientation et
		 * position
		 * @param position La nouvelle position de la boite englobante
		 * @param angle Le nouvel angle de rotation de la boite englobante
		 * @param taille La nouvelle taille de la boite englobante
		 */
		void					update(const aiVector3D& position, float angle,
									   const aiVector3D& taille);

		/**
		 * Affiche la boite englobante
		 */
		void					afficher() const;

		/**
		 * Retourne les 4 coins de la boite. Les coins sont dans cet ordre:
		 * - Bas gauche;
		 * - Haut gauche;
		 * - Haut droit;
		 * - Bas droit.
		 * Cet ordre est correct lorsque l'objet n'est pas tourne. Si l'objet
		 * est a l'envers, alors les coins apparaîtront a l'envers, mais ils
		 * gardent quand meme cet ordre.
		 */
		const vector<Vecteur3f>	getCoins() const;

		/**
		 * Retourne les 4 droites qui composent la boite. Les droites sont dans cet ordre:
		 * - Bas dans l'axe des x;
		 * - Gauche dans l'axe des y;
		 * - Haut dans l'axe des x;
		 * - Droite dans l'axe des y;
		 * Cet ordre est correct lorsque l'objets n'est pas tourné. Si l'objet
		 * est à l'envers, alors les droites seronts à l'evers, mais ils
		 * gardent quand même cet ordre.
		 */
		const vector<Droite3D>	getDroites() const;

		/**
		 * Retourne 2 vecteurs en 2 dimensions qui définissent la boite englobante
		 * non-orientée dans le plan xy.
		 * @param coinHautGauche Le coin en haut à gauche de la boite non-orientée
		 * @param coinBasDroite Le coin en bas à droite de la boite non-orientée
		 */
		void					getBoiteEnglobanteNonOrientee(Vecteur2f& coinHautGauche,
															  Vecteur2f& coinBasDroite) const;

		float					getMoitieLongueur() const { return moitieLongueurTransforme_; }
		float					getMoitieHauteur() const { return moitieHauteurTransforme_; }

	private:
		/** Centre de la boite englobante */
		aiVector3D				centre_;

		/** Centre apres la transformation */
		aiVector3D				centreTransforme_;

		/** Le vecteur "right" de la boite englobante (x) */
		aiVector3D				right_;

		/** Le vecteur "up" de la boite englobante (y) */
		aiVector3D				up_;

		/** Le vecteur "right" apres la transformation */
		aiVector3D				rightTransforme_;

		/** Le vecteur "up" apres la transformation */
		aiVector3D				upTransforme_;

		/** Moitie de la longueur de la boite */
		float					moitieLongueur_;

		/** Moitie de la hauteur de la boite */
		float					moitieHauteur_;

		/** Moitie de la longueur apres la transformation */
		float					moitieLongueurTransforme_;

		/** Moitie de la hauteur apres la transformation */
		float					moitieHauteurTransforme_;
};

}

#endif

/**
 * @}
 */