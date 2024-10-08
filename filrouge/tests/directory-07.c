/*
  Test du module directory.

  Teste le rétrécissement du directory.
*/

#include <stdlib.h>

#include "../include/directory.h"

int main(void)
{
    struct dir *dir = dir_create(20);
    dir_insert(dir, "Colonel Moutarde", "06789435351");
    dir_insert(dir, "Caporal Ketchup", "0678346533");
    dir_insert(dir, "Sergent Mayo", "06723236533");
    dir_insert(dir, "Adjudant Barbecue", "01723236533");
    dir_print(dir);
    dir_delete(dir, "Adjudant Barbecue");
    dir_delete(dir, "Sergent Mayo");
    dir_print(dir);
    dir_free(dir);

    return EXIT_SUCCESS;
}
