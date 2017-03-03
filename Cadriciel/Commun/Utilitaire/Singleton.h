//////////////////////////////////////////////////////////////////////////////
/// @file Singleton.h
/// @author Martin Bisson
/// @date 2007-03-11
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_SINGLETON_H__
#define __UTILITAIRE_SINGLETON_H__


///////////////////////////////////////////////////////////////////////////
/// @class Singleton
/// @brief Cette classe represente une base generique pour la declaration
///        de singleton.
///
///        Les singletons qui deriveront de cette classe generique et qui
///        utiliseront les macros appropriees auront deja les parties communes
///        a pratiquement tous les singletons, soit la gestion de l'instance
///        unique.
///
/// @author Martin Bisson
/// @date 2007-03-11
///////////////////////////////////////////////////////////////////////////
template <class T>
class Singleton
{
public:
   /// Obtient l'instance unique de la classe.
   static T* obtenirInstance();
   /// Libere l'instance unique de la classe.
   static void libererInstance();

protected:
   /// Constructeur vide declare protected.
   Singleton() {}
   /// Destructeur vide declare protected.
   ~Singleton() {}

private:
   /// Instance unique de la classe.
   static T* instance_;

   /// Constructeur par copie declare mais non defini.
   Singleton(const Singleton&);
   /// Operateur d'assignation declare mais non defini.
   Singleton& operator=(const Singleton&);

};


/// Cette macro doit etre incluse dans les classes derivees de Singleton.  Elle
/// declare les constructeurs et destructeurs prives.
#define SINGLETON_DECLARATION_CLASSE(Classe) \
private:                                     \
   Classe () {}                              \
   ~ Classe () {}                            \
   Classe ( const Classe& );                 \
   Classe & operator = ( const Classe& );    \
   friend class Singleton< Classe >;         \

/// Cette macro doit etre incluse dans les classes derivees de Singleton.  Elle
/// declare le constructeur copie et l'operateur d'assignation prive, en
/// laissant a la classe derivee le soin de definir le constructeur par defaut
/// et le destructeur afin de faire le traitement souhaite.
#define SINGLETON_DECLARATION_CLASSE_SANS_CONSTRUCTEUR(Classe) \
private:                                                       \
   Classe( const Classe& );                                  \
   Classe& operator=( const Classe& );                     \
   friend class Singleton< Classe >;                           \

// Cette macro doit etre incluse dans un fichier source (.cpp).  Elle declare
// l'instance unique de la classe.
#define SINGLETON_DECLARATION_CPP(Classe)       \
   Classe * Singleton< Classe >::instance_ = 0; \


////////////////////////////////////////////////////////////////////////
///
/// @fn inline T* Singleton<T>::obtenirInstance()
///
/// Cette fonction retourne l'instance unique de la classe. Si l'instance
/// n'existe pas, elle est creee. Ainsi, une seule instance sera creee.
/// Cette fonction n'est pas "thread-safe".
///
/// @return L'instance unique de la classe.
///
////////////////////////////////////////////////////////////////////////
template <class T>
inline T* Singleton<T>::obtenirInstance()
{
   if (instance_ == 0)
      instance_ = new T();

   return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void Singleton<T>::libererInstance()
///
/// Detruit l'instance unique de la classe.  Cette fonction n'est pas
/// "thread-safe".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
template <class T>
inline void Singleton<T>::libererInstance()
{
   delete instance_;
   instance_ = 0;
}


#endif // __UTILITAIRE_SINGLETON_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
