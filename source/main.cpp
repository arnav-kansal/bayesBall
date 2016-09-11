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
    if(argc<2){
        printf("usage: ./a.out <readfile> <outfile> \n");
        goto clean;
    }
    
    if(argc==2)
        strcpy(arr,"output.txt");
    else
        strcpy(arr,argv[2]);
    strcpy(brr,"test.txt");
    if(readBayesNet(argv[1],bNet)==0){
        //writeBayesNet(arr,bNet);
        answerQueries(argv[2],brr,bNet);
    }
clean:
		//printf("start\n");
    //bNet = genRandomBN(10,7);
		//printf("done\n");
    //writeBayesNet("test.txt",bNet);
    return 0;
}