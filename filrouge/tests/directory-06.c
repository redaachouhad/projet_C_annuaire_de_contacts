/*
  Test du module directory.

  Teste l'agrandissement du directory.
*/

#include <stdlib.h>

#include "../include/directory.h"

int main(void)
{
    struct dir *dir = dir_create(10);
    dir_insert(dir, "Colonel Moutarde", "06789435351");
    dir_insert(dir, "Caporal Ketchup", "0678346533");
    dir_insert(dir, "Sergent Mayo", "06723236533");
    dir_insert(dir, "Adjudant Barbecue", "01723236533");
    dir_insert(dir, "Lieutenant Aioli", "02733236533");
    dir_insert(dir, "Soldat Savora", "02444444444");
    dir_insert(dir, "Commandant Cornichon", "08444444444");
    dir_print(dir);
    dir_insert(dir, "Général Motors", "99444444444");
    dir_print(dir);
    dir_free(dir);

    return EXIT_SUCCESS;
}
