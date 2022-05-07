/* Author        : Dionisis Nikolopoulos (dennis.nik@protonmail.com)
 * Student Email : ice18390126@uniwa.gr
 * Description   : TUI for the concurrent vector calculator
 * License       : GPLv3
 * Date Written  : April 2022
 * Some code based on "Simple udp server" by Silver Moon (m00n.silv3r@gmail.com)
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
#include <unistd.h>    //for close()

#define BUFLEN 512  //Max length of buffer

int main(int argc, char *argv[])
{
    struct sockaddr_in si_me;
    struct sockaddr_in si_other;
    int s, i, portno, slen=sizeof(si_me);
    int testint;
    float testfloat;
    char buf[BUFLEN];
    char *cur;
    struct hostent *server;

    // Check for arguments and store them if they are not provided
    if (argc < 3) {
        fprintf(stderr,
                "rpcvec_client - usage: %s [server_host] [port_number] \n",
                argv[0]);
        exit(1);
    }

    fprintf(stdout,"*** Concurrent Vector Calculator ***");
    s=socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        fprintf(stderr,"\nError: Socket could not be opened");
        exit(2);
    } else fprintf(stdout,"\n* Socket opened...");

    bzero((char *) &si_other, sizeof(si_other));
    si_other.sin_family = AF_INET;

    server = gethostbyname(argv[1]);
    bcopy((char *)server->h_addr,
            (char *)&si_other.sin_addr.s_addr,
            server->h_length);
    // Get server port from arguments
    portno = atoi(argv[2]);
    si_other.sin_port = htons(portno);

    fprintf(stdout,"\n* Connecting to server...");
    if (connect(s, (struct sockaddr *) &si_other, sizeof(si_other)) < 0) {
        fprintf(stderr,"\nError: Cannot connect to server in port %d", portno);
        exit(2);
    } else fprintf(stdout,"\n* Connected to server!");

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
