#ifndef _CONTACT_H_
#define _CONTACT_H_


/*
  Un contact représente une association {nom, numéro}.
*/

#include <stdint.h>

struct dir;



struct contact{
  char* name;
  char* numero;
  struct contact *next;
};
/* insertion au debut d'une liste simplement chainnee*/
extern void inserer_debut_liste(struct contact **liste, char *name, char *num);

/*afficher sur la sortie standard le contenu de la liste simplement chainnee */
extern void afficher(struct contact *liste);

/* Calculer la taille d'une liste simplement chainnee */
extern uint64_t liste_size(struct contact *liste);

/* l'insertion à la fin d'uhe liste simplement chainnee */
extern char* inserer_fin_liste(struct contact **liste, char* name, char* num);

/*la supprission d'un contact d'une liste simplement chainnee */
extern int supprimer_le_contact_de_liste(struct contact **liste, char *name);

/*Chercher la numero d'un contact dans une liste simplement chainnee */
extern char* chercher_numero(struct contact **liste, char *name);

/* Libère la mémoire associée à une liste simplement chainnee */
extern void liberer_liste(struct contact **liste);

/* Calculer la taille d'une liste simplement chainnee */
extern uint64_t taille_liste_contact(struct contact *liste);

/* Calculer la taille totale d'un annuire de contact*/
extern uint32_t dir_taille(struct dir *dir);

/*Calculer le nombre totale de contact*/
extern uint32_t nombres_totale_contact(struct dir *dir);

#endif /* _CONTACT_H_ */
