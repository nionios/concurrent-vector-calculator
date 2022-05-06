/* Description: Prompts for the tui
 *  License: GPLv3
 * Author: Dionisis Nikolopoulos
 *  Date Written: April 2022
*/
/*
   Simple udp client
   Silver Moon (m00n.silv3r@gmail.com)
   */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <prompts.h>
#include <sanitary.h>

#define BUFLEN 512  //Max length of buffer


int main(int argc, char *argv[])
{
    struct sockaddr_in si_other;
    struct sockaddr_in cli_addr;
    int s, i, portno, slen=sizeof(si_other);
    int testint;
    float testfloat;
    char buf[BUFLEN];
    char *cur;
    struct hostent *server;

    s=socket(AF_INET, SOCK_DGRAM, 0);

    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(0);
    cli_addr.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *) &cli_addr, sizeof(cli_addr));

    bzero((char *) &si_other, sizeof(si_other));
    si_other.sin_family = AF_INET;

    server = gethostbyname(argv[1]);
    bcopy((char *)server->h_addr,
            (char *)&si_other.sin_addr.s_addr,
            server->h_length);

    portno = atoi(argv[2]);
    si_other.sin_port = htons(portno);

    // inet_aton("192.168.0.70", &si_other.sin_addr);

    fprintf(stdout,"*** Concurrent Vector Calculator ***");
    // Take the basic info of the vector from the user
    vector_info_prompt(si_other, slen, s);
    unsigned int choice;

    while (1) {
        fprintf(stdout,"\nPlease choose calculation to make or exit:"\
                "\n 0. Exit program"\
                "\n 1. Average of vector"\
                "\n 2. Minimum and Maximum element of vector"\
                "\n 3. Product of vector with a real number"\
                "\nChoice: ");
        scanf("%d",&choice);
        // Separate functions for prompting user for more info, depending on
        // choice.
        switch (choice) {
            case 0:
                fprintf(stdout,"--> Exiting...");
                return 0;
            case 1:
                average_prompt(choice, si_other, slen, s);
                break;
            case 2:
                minmax_prompt(choice, si_other, slen, s);
                break;
            case 3:
                product_prompt(choice, si_other, slen, s);
                break;
            default:
                fprintf(stdout,
                        "Your choice was not 0-3, please try again...");
        }
        close(s);
    }
}
