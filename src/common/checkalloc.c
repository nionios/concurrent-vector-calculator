/* Author: Dionisis Nikolopoulos (dennis.nik@protonmail.com)
 * Description: Helper function to check if a mem allocation is successful
 * Student Email: ice18390126@uniwa.gr
 * Author: Dionisis Nikolopoulos
 * License: GPLv3
 * Date Written: May 2022
 */
#include <stdio.h>
#include <stdlib.h>

void
checkalloc(void * ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "\nError: Failed to allocate memory!\n");
        abort();
    }
}
