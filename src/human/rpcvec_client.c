/* Author: Dionisis Nikolopoulos
*  Description: A program that calls the rusers() service
*  License: GPLv3
*  Date Written: April 2022
*/
#include <stdio.h>
#include "../rpc/rpcvec.h"

main(int argc,char **argv)
{
int num;
if (argc != 2) {
    fprintf(stderr, "usage: %s hostname\n",
            argv[0]);
    exit(1);
}

if ((num = rnusers(argv[1])) < 0) {
    fprintf(stderr, "error: rusers\n");
    exit(1);
}

fprintf(stderr, "%d users on %s\n", num, argv[1] );
exit(0);
}