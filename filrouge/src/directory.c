#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "../include/contact.h"
#include "../include/hash.h"



/*la structure d'une case de tableau T(ou le tableau de hachage).
dans ce programme le tableau de hachage prends la forme d'une liste simplement
chainee, et chaque cellule de cette liste (qui est de type struct dir*) est lié
une autre liste simplement chainee dans les cellules sont de type struct contact
*/
struct dir{
  struct contact *liste;
  struct dir *suivant;
};



struct dir*dir_create(uint32_t len)
{
/* la fonction dir create permet de cree le tableau de hachage T (qui prend la
forme d'une liste simplement chainee dont les cellules sont de type struct dir
et sont vide) de taille _len_ */

  struct dir*case_dir = malloc(sizeof(struct dir));
  case_dir->liste = NULL;
  case_dir->suivant = NULL;
  struct dir *case_dir_copy = case_dir;
  /* creation de tableau de hachage par boucle for*/
  for(uint32_t i=1; i<len; i++)
  {
    struct dir *liste_dir = malloc(sizeof(struct dir));
    liste_dir->liste = NULL;
    liste_dir->suivant = case_dir_copy;
    case_dir_copy = liste_dir;
  }
  return case_dir_copy;
}


void dir_redimensionner(struct dir* dir, const char * name, uint32_t type )
{
/* Pour éviter  le risque de collisions ,la fonction dir_redimmensionner permet
de  le redimensionnement de la table afin de minimiser les coûts liés à
une table très remplie, ou de réduire l’empreinte mémoire
 d’une table majoritairement vide. */
  float nombre_entree = dir_taille(dir);
  float nombre_contacts = nombres_totale_contact(dir);
  struct contact * case_contact = NULL;
  struct dir *h = dir;
  /*Dans cette etape, on prend touts les contacts de directory ancien et on le met
  dans une liste simplement chainee dont les cellules sont de structure
  struct contact*/
  while(h != NULL)
  {
    struct contact* aa = h->liste;
    while(aa != NULL)
    {
      char* nom = aa->name;
      char* numar = aa->numero;
      inserer_fin_liste(&case_contact, nom, numar);
      aa = aa->next;
    }
    h = h->suivant;
  }
  /* ici on pointe sur la premiere cellule de tableau dir*/
  h = dir;
  while(h->suivant != NULL)
  {
    /* on supprime et on libère les espaces memoires des celulles de tableau dir
    sauf sa premiere cellule car si on efface cette derniere alors on va perdre
    le tableau dir*/
      struct contact *m = h->suivant->liste;
      struct dir* lm = malloc(sizeof(struct dir*));
      liberer_liste(&m);
      h->suivant->liste = NULL;
      lm = h->suivant;
      h->suivant = lm->suivant;
      free(lm);
  }
  if(h->liste != NULL)
  {
    /*ici , on librere l'espace memoire occupee par la liste de la premiere
  cellule restante du tableau dir (C'est la meme cellule qu'on a expliquee
  precedemment)*/

    struct contact *yu = h->liste;
    liberer_liste(&yu);
    h->liste = NULL;
  }


  if( nombre_entree*0.75 < nombre_contacts)
  {
    /*un agrandissement de la table lorsque le nombre de contacts se trouvant
    dans l'annuaire dépasse 75% du nombre d'entrées dans la table (en pratique,
     on doublera la taille de la table)
    */
    struct dir *p = dir;
    uint32_t j = nombre_entree;
    for(uint32_t i=1; i<j*2; i++)
    {
      /*ici, on fait la creation de tableau  de taille len = nombre_entree*2
      et puisque on adéja une cellule  alors il suffit d'ajouter (len-1) cellule
      vide */
      struct dir *liste_dir = malloc(sizeof(struct dir*));
      liste_dir->liste = NULL;
      liste_dir->suivant = NULL;
      p->suivant = liste_dir;
      p = p->suivant;
    }
  }
  else if( nombre_entree*0.15 > nombre_contacts)
  {
    /*un rétrécissement de la table lorsque le nombre de contacts se trouvant
   dans l'annuaire représente moins de 15% du nombre d'entrées dans
   la table (en pratique, on divisera par deux la taille de la table,
    sans toutefois descendre en-dessous de 10 entrées).*/
    struct dir*p = dir;
    uint32_t j = nombre_entree;
    for(uint32_t i=1; i < j/2 ; i++)
    {
      /*ici, on fait la creation de tableau  de taille len = nombre_entree/2
      et puisque on adéja une cellule  alors il suffit d'ajouter (len-1) cellule
      vide */
      struct dir *liste_dir = malloc(sizeof(struct dir*));
      liste_dir->liste = NULL;
      liste_dir->suivant = NULL;
      p->suivant = liste_dir;
      p = p->suivant;
    }

  }
  else
  {
    /*si les condion d'agrandissement ou de rétrécissement ne sont pas vérifier,
     alors la fonction prend ce chemin et la taille de dir ne change pas*/
    struct dir *p = dir;
    uint32_t j = nombre_entree;
    for(uint32_t i=1; i<j; i++)
    {/*ici; on fait la creation du tableau sans changer la taille*/
      struct dir *liste_dir = malloc(sizeof(struct dir));
      liste_dir->liste = NULL;
      liste_dir->suivant = NULL;
      p->suivant = liste_dir;
      p = p->suivant;
    }
  }
  /*l'insertion des contacts qu'on a déja recuperer precedemment et qu'on
  a met dans la liste simplement  chainee case_contact*/
  struct contact *s = case_contact;
  while( s!= NULL)
  {
    struct dir *f = dir;
    uint32_t rang_dir = hash(s->name)%dir_taille(f);
    for(uint32_t i=0; i<rang_dir; i++)
    {
      f = f->suivant;
    }
    inserer_fin_liste(&(f->liste), s->name, s->numero);
    s = s->next;
  }
  /*la liberation de l'espace memoire occuper par la liste simplement chainee
  precedente */
  liberer_liste(&case_contact);
  free(case_contact);
  /* ici on fait des printf sur le terminale pour bien suivre les changements
  de la taille du tableau lors de l'insertion et la suppression */
  if(type == 1)
  {
    printf("\nApres L'insertion de contact {%s} : La taille se passe de %u à %u (Redimensionnement du tableau)\n ", name, (uint32_t) nombre_entree, dir_taille(dir));
  }
  else if(type == 0)
  {
    printf("\n Apres La suppression de contact {%s} : La taille se passe de %u à %u (Redimensionnement du tableau)\n ", name, (uint32_t) nombre_entree, dir_taille(dir));
  }

}



char *dir_insert(struct dir *dir, const char *name, const char *numero)
{
  /*
    Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
    numéro passés en paramètre. Si il existait déjà un contact du même nom, son
    numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
    Sinon, la fonction retourne NULL.
  */
  uint32_t i = 1;
  if(dir == NULL){i = 0;}
  struct dir *case_dir = dir->suivant;
  while(case_dir != NULL){
    case_dir = case_dir->suivant;
    i++;
  }
  char  *nom = (char*)name;
  char *nombre = (char *)numero;
  uint32_t rang_dir = hash(nom)%i;
  struct dir *case_diro = dir;
  for(uint32_t i=0; i<rang_dir; i++)
  {
    case_diro = case_diro->suivant;
  }

 char *e = inserer_fin_liste(&(case_diro->liste), nom, nombre);
 dir_redimensionner(dir, nom, 1);
 return e;
}

const char *dir_lookup_num(struct dir *dir, const char *name)
{
  /*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
  uint32_t i = 1;
  if(dir == NULL){i = 0;}
  struct dir *case_dir = dir->suivant;
  while(case_dir != NULL){
    case_dir = case_dir->suivant;
    i++;
  }
  char  *nom = (char*)name;
  uint32_t rang_dir = hash(nom)%i;
  struct dir *case_diro = dir;
  for(uint32_t i=0; i<rang_dir; i++)
  {
    case_diro = case_diro->suivant;
  }
  return chercher_numero(&(case_diro->liste), nom);
}



void dir_delete(struct dir *dir, const char *name)
{
  /*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
  const char * exist = dir_lookup_num(dir, name);
  uint32_t i = 1;
  if(dir == NULL){i = 0;}
  struct dir *case_dir = dir->suivant;
  while(case_dir != NULL){
    case_dir = case_dir->suivant;
    i++;
  }
  char  *nom = (char*)name;
  uint32_t rang_dir = hash(nom)%i;
  struct dir *case_diro = dir;
  for(uint32_t i=0; i<rang_dir; i++)
  {
    case_diro = case_diro->suivant;
  }
  if(exist == NULL){
    /*le nom n'existe pas alors on ne fait rien*/
    printf(" \non ne peut pas supprimer le nom {%s} car il n'existe pas dans le directory\n\n", name);
  }
  else
  {/* si le nom exist alors on fait la suppression*/
  supprimer_le_contact_de_liste(&(case_diro->liste), nom);
  dir_redimensionner(dir, nom, 0);
  }
}

void dir_free(struct dir *dir)
{
  /*
Libère la mémoire associée à l'annuaire _dir_.
*/
    while(dir->suivant != NULL)
    { struct dir* dir_copy = dir;
      dir = dir->suivant;
      liberer_liste(&(dir_copy->liste));
      free(dir_copy);
    }
    liberer_liste(&(dir->liste));
    free(dir);
}

void dir_print(struct dir* dir)
{
  /*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
  struct dir *case_dir = dir;
  uint32_t a =1 ;
  printf("\n================[ LES CONTACTS: {NOM || NUMERO}]==============================\n");
  while(case_dir != NULL)
  {
    printf("|| %d) : ", a);
    afficher(case_dir->liste);
    a++;
    case_dir = case_dir->suivant;
  }
  printf("==============================================================================\n");
  printf("\n_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*");
  printf("\n\n");

}
