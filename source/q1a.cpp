/* Bayes Net driver program.
 * Author Arnav Kansal 2016
 * This is free software.
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "bayesnet.h"

int main(int argc, char *argv[]){
    BNet bNet;
    srand(time(NULL));
    char arr[256];
    char brr[256];
    if(argc<3){
        printf("usage: ./a.out <no. of nodes> <max children> \n");
        goto clean;
    }
    strcpy(arr,"bn.txt");
    printf("Generating Random Bayesian Network with %d nodes and %d max children per node\n",atoi(argv[1]),atoi(argv[2]) );
    bNet = genRandomBN(atoi(argv[1]),atoi(argv[2]));
    writeBayesNet(arr,bNet);
clean:
	return 0;
}