/* Description: Input Functions that ensure correct input types
 *              Take input by user, scan it afterwards, if it is not of the
 *              appropriate type assign the variable to NULL (to error check)
 * Author: Dionisis Nikolopoulos
 * License: GPLv3
 * Date Written: May 2022
 */
#include <stdio.h>

// Pointer to pointer (double pointers) Needed to pass pointers by reference
void
sanitary_int(int ** intp) {
    char line[256];
    int scanned;
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%d", &scanned))
            **intp = scanned;
        else *intp = NULL;
    }
}

void
sanitary_double(double ** dblp) {
    char line[256];
    double scanned;
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%lf", &scanned))
            **dblp = scanned;
        else *dblp = NULL;
    }
}
