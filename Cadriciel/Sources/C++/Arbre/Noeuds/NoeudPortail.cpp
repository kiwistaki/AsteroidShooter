#include "NoeudPortail.h"
#include "../../Application/AffichageDebogage.h"

NoeudPortail::NoeudPortail(const std::string& type) : NoeudAbstrait(type)
{
	// MODeLE TEMPORAIRE
	modele_.charger("media/torus.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudPortail::NoeudPortail(const NoeudPortail& src) : NoeudAbstrait(src)
{
	modele_.charger("media/torus.obj");

	Vecteur3 coinMin, coinMax;
	modele_.calculerBoiteEnglobante(coinMin, coinMax);
	boiteEnglobanteOrientee_ = math::BoiteEnglobanteOrientee(coinMin, coinMax);
}

NoeudPortail::~NoeudPortail()
{
}

void NoeudPortail::animer(float dt)
{
	NoeudAbstrait::animer(dt);
}

void NoeudPortail::afficherConcret() const
{
	NoeudAbstrait::afficherConcret();
	AffichageDebogage::obtenirInstance()->afficherRayonAttraction(this);
}