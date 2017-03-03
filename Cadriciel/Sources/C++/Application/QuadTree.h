///////////////////////////////////////////////////////////////////
/// @file QuadTree.h
/// @author FloppyDisketeers
/// @date 2014-03-19
/// @version 1.0
///////////////////////////////////////////////////////////////////
#ifndef QUAD_TREE_H
#define	QUAD_TREE_H

#include "../../Commun/Utilitaire/Vecteur.h"

#include <set>
#include <vector>
using namespace std;

// Forward class declaration
class ElementJeuAbstrait;

/**
 * @class QuadTree
 * @brief Cette class impl�mente la fonctionnalit� d'un QuadTree.
 *
 * C'est un arbre dans lequel chaque noeud contient exactement 4 enfants. On 
 * ajoute des noeuds suppl�mentaires en ajoutant des �l�ments dans l'arbre: 
 * lorsque le nombre d'objets se trouvant dans un noeud est sup�rieure � une 
 *constante d�finie par l'utilisateur, on subdivise le noeud courant en 4 sous-noeuds.
 *
 * Cet arbre permet de traiter les collisions seulement avec les autres objets
 * qui se trouvent dans le m�me noeud, r�duisant dramatiquement le nombre de
 * cas � traiter.
 *
 * L'insertion utilise des boites englobantes non-orient�es pour d�terminer si
 * un objet est dans un noeud. Cette m�thode n'est pas la plus pr�cise, mais
 * avec un QuadTree on cherche a donner une approximation rapidement pour
 * �viter de plus gros calculs, donc une boite englobante non-orient�e suffit
 * largement.
 *
 * L'indexation des sous-noeuds est comme suit:
 *		|
 *	II	|	I
 * -----------
 *	III	|  IV
 *		|
 *
 * Impl�mentation tir� de http://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
 */
class QuadTree {
	public:
		/**
		 * Constructeur par param�tres
		 * @param coinHautGauche La position du coin en haut � gauche du noeud courant
		 * @param coinBasDroite La position du coin en bas � droite du noeud courant
		 * @param niveau Le niveau du QuadTree, 0 �tant le premier niveau. 0 par d�faut.
		 */
										QuadTree(const Vecteur2f& coinHautGauche,
												 const Vecteur2f& coinBasDroite,
												 int niveau=0);

		/**
		 * Vide le QuadTree. Les destructeurs des enfants se chargeront du reste
		 */
		void							clear();

		/**
		 * Ins�re un �l�ment dans le QuadTree. Si l'ajout du nouvel objet fait
		 * exploser la capacit� du noeud courant, on le subdivise et on assigne
		 * les objets dans les nouveaux noeuds.
		 * @param objet L'objet � ajouter dans le QuadTree
		 */
		void							inserer(ElementJeuAbstrait* objet);

		/**
		 * Va chercher tous les objets qui pourraient entrer en collision avec
		 * l'objet courant.
		 * @param objet L'objet pour lequel on veut une liste des autres objets
		 * qui pourraient entrer en collision
		 * @return Un set de pointeurs d'�l�ments abstraits. Ce sont des objets
		 * avec lesquels l'objet courant pourrait entrer en collision.
		 */
		set<ElementJeuAbstrait*>		retrieve(ElementJeuAbstrait* objet) const;

		const set<ElementJeuAbstrait*>	getObjets() const { return objets_; }

		// TEMP
		void							afficher() const;

	private:
		/** Nombre d'objets maximum dans un noeud */
		static const int				NB_OBJETS_MAX = 5;

		/** Nombre de niveau maximum dans l'arbre */
		static const int				NIVEAU_MAX = 5;

		/** Les noeuds enfants du noeud courant. Tableau de taille 4 */
		vector<QuadTree>				noeuds_;

		/** Liste des objets se trouvant dans le noeud courant */
		set<ElementJeuAbstrait*>		objets_;

		/** Le coin en haut � gauche du noeud courant. Sert � d�limiter la zone */
		Vecteur2f						coinHautGauche_;

		/** Le coin en bas � droite du noeud courant. Sert � d�limiter la zone */
		Vecteur2f						coinBasDroite_;

		/** Le niveau du noeud courant, 0 �tant le plus �lev� (donc le premier noeud) */
		int								niveau_;

		/**
		 * Subdivise le noeud courant en 4 noeuds plus petits.
		 */
		void							subdivision();

		/**
		 * D�termine dans quel sous-noeud le rectangle pass� en param�tre (2 coins)
		 * se trouve-t'il.
		 * @param coinHautGauche Le coin en haut � gauche du rectangle
		 * @param coinBasDroite Le coin en bas � droite du rectangle
		 * @return Retourne l'indice compris dans [0, 3] ou -1 si le rectangle
		 * n'est pas compl�tement dans un des sous-noeuds.
		 */
		int								getIndex(const Vecteur2f& coinHautGauche,
												 const Vecteur2f& coinBasDroite) const;
};

#endif