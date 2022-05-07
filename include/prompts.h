/* Author: Dionisis Nikolopoulos (dennis.nik@protonmail.com)
 * Student Email: ice18390126@uniwa.gr
 * Description: Header files for the prompt functions (part of TUI)
 * License: GPLv3
 * Date Written: April 2022
 */
#include "../src/rpc/rpcvec.h"

void vector_info_prompt(struct sockaddr_in si_other, int slen, int s);
void average_prompt(int choice, struct sockaddr_in si_other, int slen, int s);
void minmax_prompt(int choice, struct sockaddr_in si_other, int slen, int s);
void product_prompt(int choice, struct sockaddr_in si_other, int slen, int s);
