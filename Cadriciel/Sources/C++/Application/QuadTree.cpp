#include "QuadTree.h"

#include "../ElementObjet/ElementJeuAbstrait.h"
#include "../../../Commun/Utilitaire/BoiteEnglobanteOrientee.h"

#include <Windows.h>
#include <gl/GL.h>

QuadTree::QuadTree(const Vecteur2f& coinHautGauche, const Vecteur2f& coinBasDroite, int niveau) :
		coinHautGauche_(coinHautGauche), coinBasDroite_(coinBasDroite), niveau_(niveau)
{
	noeuds_.reserve(4);
}

void QuadTree::clear() {
	objets_.clear();
	noeuds_.clear();
}

void QuadTree::inserer(ElementJeuAbstrait* objet) {
	if (noeuds_.size() != 0) {
		Vecteur2f coinHautGauche;
		Vecteur2f coinBasDroite;
		objet->getBoiteEnglobanteOrientee().getBoiteEnglobanteNonOrientee(coinHautGauche, coinBasDroite);

		int index = getIndex(coinHautGauche, coinBasDroite);
		
		if (index != -1) {
			noeuds_[index].inserer(objet);
			return;
		}
	}

	objets_.insert(objet);

	if (objets_.size() > NB_OBJETS_MAX && niveau_ < NIVEAU_MAX) {
		if (noeuds_.size() == 0) {
			subdivision();
		}

		set<ElementJeuAbstrait*>::iterator it = objets_.begin();
		while (it != objets_.end()) {
			Vecteur2f coinHautGauche;
			Vecteur2f coinBasDroite;

			ElementJeuAbstrait* elem = *it;
			elem->getBoiteEnglobanteOrientee().getBoiteEnglobanteNonOrientee(coinHautGauche, coinBasDroite);

			int index = getIndex(coinHautGauche, coinBasDroite);

			if (index != -1) {
				objets_.erase(it++);
				noeuds_[index].inserer(elem);
			} else {
				++it;
			}
		}
	}
}

set<ElementJeuAbstrait*> QuadTree::retrieve(ElementJeuAbstrait* objet) const {
	set<ElementJeuAbstrait*> objets;

	Vecteur2f coinHautGauche;
	Vecteur2f coinBasDroite;
	objet->getBoiteEnglobanteOrientee().getBoiteEnglobanteNonOrientee(coinHautGauche, coinBasDroite);

	int index = getIndex(coinHautGauche, coinBasDroite);
	if (index != -1 && noeuds_.size() != 0) {
		set<ElementJeuAbstrait*> elements = noeuds_[index].retrieve(objet);
		objets.insert(elements.begin(), elements.end());
	}

	objets.insert(objets_.begin(), objets_.end());
	return objets;
}

void QuadTree::afficher() const {
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);

		glBegin(GL_LINES);
			glVertex2f(coinHautGauche_[0], coinHautGauche_[1]);
			glVertex2f(coinBasDroite_[0], coinHautGauche_[1]);

			glVertex2f(coinBasDroite_[0], coinHautGauche_[1]);
			glVertex2f(coinBasDroite_[0], coinBasDroite_[1]);

			glVertex2f(coinBasDroite_[0], coinBasDroite_[1]);
			glVertex2f(coinHautGauche_[0], coinBasDroite_[1]);

			glVertex2f(coinHautGauche_[0], coinBasDroite_[1]);
			glVertex2f(coinHautGauche_[0], coinHautGauche_[1]);
		glEnd();
	glPopMatrix();

	glPopAttrib();

	for (size_t i = 0; i < noeuds_.size(); i++) {
		noeuds_[i].afficher();
	}
}

void QuadTree::subdivision() {
	float subWidth = (coinBasDroite_[0] - coinHautGauche_[0]) * 0.5f;
	float subHeight = (coinHautGauche_[1] - coinBasDroite_[1]) * 0.5f;

	noeuds_.push_back(QuadTree(coinHautGauche_ + Vecteur2f(subWidth, 0.0f), coinBasDroite_ + Vecteur2f(0.0f, subHeight), niveau_ + 1));
	noeuds_.push_back(QuadTree(coinHautGauche_,	coinBasDroite_ + Vecteur2f(-subWidth, subHeight), niveau_ + 1));
	noeuds_.push_back(QuadTree(coinHautGauche_ + Vecteur2f(0.0f, -subHeight), coinBasDroite_ + Vecteur2f(-subWidth, 0.0f), niveau_ + 1));
	noeuds_.push_back(QuadTree(coinHautGauche_ + Vecteur2f(subWidth, -subHeight), coinBasDroite_, niveau_ + 1));
}

int QuadTree::getIndex(const Vecteur2f& coinHautGauche, const Vecteur2f& coinBasDroite) const {
	int index = -1;
	float midPointX = coinHautGauche_[0] + (coinBasDroite_[0] - coinHautGauche_[0]) * 0.5f;
	float midPointY = coinBasDroite_[1]  + (coinHautGauche_[1] - coinBasDroite_[1]) * 0.5f;

	// Est-ce que l'objet est complètement contenu dans les quadrants supériereurs?
	bool topQuadrant = (coinBasDroite[1] > midPointY && coinHautGauche[1] < coinHautGauche_[1]);

	// Est-ce que l'objet est complètement contenu dans les quadrants inférieurs?
	bool bottomQuadrant = (coinHautGauche[1] < midPointY && coinBasDroite[1] > coinBasDroite_[1]);

	// Est-ce que l'objet est complètement contenu dans les quadrants gauches?
	if (coinBasDroite[0] < midPointX && coinHautGauche[0] > coinHautGauche_[0]) {
		if (topQuadrant) {
			index = 1;
		} else if (bottomQuadrant) {
			index = 2;
		}
	// Est-ce que l'objet est complètement contenu dans les quadrants droites?
	} else if (coinHautGauche[0] > midPointX && coinBasDroite[0] < coinBasDroite_[0]) {
		if (topQuadrant) {
			index = 0;
		} else if (bottomQuadrant) {
			index = 3;
		}
	}

	return index;
}