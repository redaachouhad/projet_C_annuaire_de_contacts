#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>



struct contact{
  char* name;
  char* numero;
  struct contact *next;
};

struct dir{
  struct contact *liste;
  struct dir *suivant;
};


void inserer_debut_liste(struct contact **liste, char *name, char *numero)
{
  /* insertion au debut d'une liste simplement chainnee*/

  struct contact *case_contact= malloc(sizeof(struct contact));
  case_contact->name = name;
  case_contact->numero = numero;
  case_contact->next = *liste;
  *liste = case_contact;
}

void afficher(struct contact *liste)
{
  /*afficher sur la sortie standard le contenu de la liste simplement chainnee */

  if(liste != NULL){
    struct contact *case_contact = liste;
    do
    {
      printf("/ {(%s , %s)} ", case_contact->name, case_contact->numero);
      case_contact = case_contact->next;
    }while(case_contact != NULL);
    printf("\n");
  }
  else{printf("vide\n");}
}

u_int32_t liste_size(struct contact *liste)
{
  /* Calculer la taille d'une liste simplement chainnee */

  if(liste == NULL){ return 0;}
  u_int32_t i = 1;
  struct contact *case_contact = liste->next;
  while(case_contact != NULL){
    case_contact = case_contact->next;
    i++;
  }
  return i;
}


char* inserer_fin_liste(struct contact **liste, char* name, char* numero)
{
  /* l'insertion à la fin d'uhe liste simplement chainnee */

  if(*liste != NULL)
  {
    struct contact *case_contact = *liste;
    if(case_contact->name == name)
    {
        char* number = case_contact->numero;
        case_contact->numero = numero;
        return number;
    }
    while(case_contact->next != NULL)
    {
        case_contact = case_contact->next;
        if(case_contact->name == name)
        {
          char* number = case_contact->numero;
          case_contact->numero = numero;
          return number;
        }
    }
    struct contact *cellule = malloc(sizeof(struct contact));
    case_contact->next = cellule;
    cellule->numero = numero;
    cellule->name = name;
    cellule->next = NULL;
    return NULL;
  }
  else
  {
    inserer_debut_liste(liste, name, numero);
    return NULL;
  }
}


int supprimer_le_contact_de_liste(struct contact **liste, char *name)
{
  /*la supprission d'un contact d'une liste simplement chainnee */

  if(*liste != NULL){
    struct contact *case_contact = *liste;
    if(case_contact->name == name)
    {
      *liste = case_contact->next;
      free(case_contact);
    }
    else
    {
      struct contact *cellule = malloc(sizeof(struct contact));
      while(case_contact->name != name){
        cellule = case_contact ;
        case_contact = case_contact->next;
        if(case_contact == NULL){return 0;}
      }
      cellule->next = case_contact->next;
      free(case_contact);
    }
  }
  return 0;
}

char* chercher_numero(struct contact **liste, char *name)
{
  /*Chercher la numero d'un contact dans une liste simplement chainnee */

  if(*liste != NULL){
    struct contact *case_contact = *liste;
    if(case_contact->name == name){return case_contact->numero; }
    while(case_contact->next != NULL)
    {
        case_contact = case_contact->next;
        if(case_contact->name == name){return case_contact->numero;}
    }
    return NULL;
  }
  else{return NULL;}
}


void liberer_liste(struct contact **liste)
{
  /* Libère la mémoire associée à une liste simplement chainnee */

  struct contact *cellule =*liste;
  *liste = NULL;
  if(cellule != NULL)
  {
    while(cellule->next != NULL)
    {
      struct contact *case_contact = cellule;
      cellule = cellule->next;
      free(case_contact);
    }
    free(cellule);
  }
}

u_int32_t taille_liste_contact(struct contact *liste)
{
  /* Calculer la taille d'une liste simplement chainnee */

  u_int32_t i = 1;
  if(liste == NULL){return 0;}
  struct contact *case_contact = liste->next;
  while(case_contact != NULL)
  {
    case_contact = case_contact->next;
    i++;
  }
  return i;
}

u_int32_t dir_taille(struct dir *dir)
{
  /* Calculer la taille totale d'un annuire de contact*/

  u_int32_t i = 1;
  if(dir == NULL){return 0;}
  struct dir *case_dir = dir->suivant;
  while(case_dir != NULL){
    case_dir = case_dir->suivant;
    i++;
  }
  return i;
}

u_int32_t nombres_totale_contact(struct dir *dir)
{
  /*Calculer le nombre totale de contact*/

  struct dir *copy_dir = dir;
  u_int32_t nombre_contacts = 0;
  while(copy_dir != NULL)
  {
    nombre_contacts += taille_liste_contact(copy_dir->liste);
    copy_dir = copy_dir->suivant;
  }
  return nombre_contacts;
}
