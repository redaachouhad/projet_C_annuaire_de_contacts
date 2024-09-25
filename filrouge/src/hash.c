#include <stdlib.h>
#include <stdint.h>
#include <string.h>


uint32_t hash(const char *name)
{
  uint32_t valeur_hachage = 5381;
  char caractere = name[0];
  uint32_t i = 0;
  while(caractere != '\0'){
    valeur_hachage = valeur_hachage*33+caractere;
    i++;
    caractere = name[i];
  }
  return valeur_hachage;
}
