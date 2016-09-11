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
    if(argc<3){
        printf("usage: ./a.out <network file> <query file> \n");
        goto clean;
    }
    strcpy(arr,"out.txt");
    printf("Network File: %s Query File: %s\n",argv[1],argv[2]);
    if(readBayesNet(argv[1],bNet))
        printf("ERROR Reading File\n");
    answerQueries(argv[2],arr,bNet);
clean:
	return 0;
}