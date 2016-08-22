#include "bayesnet.h"

/*
 * Generates random bayesian network of given size,
 * n denoting the the number of nodes in the network
 * and k the max-number of children for each node.
 * returns NULL on failure.
 */
struct BayesianNetwork* genRandomBN(int n, int k){

}

/*
 * Reads bayes net from infile to bNet.
 * infile must follow standard mentioned in README.md.
 * infile is assumed to be in same dir as executable.
 */
int readBayesNet(char *infile, struct BayesianNetwork *bNet){

}

/*
 * Writes bayes net to outfile.
 * bNet checked for  must follow standard mentioned in README.md.
 */
int writeBayesNet(char *oufile, struct BayesianNetwork *bNet){

}

/*
 * Checks validity of bayes net specified by bNet,
 * as mentioned in README.md
 */
int checkBayesNet(struct BayesianNetwork *bNet){

}

/*
 * Given two r.v's Xi,Xj, and some observed r.v's Z,
 * it returns the active trail between the random vars
 * if it exists.
 */
vector<int> activeTrail(int Xi, int Xj, vector<int> Z){

}

bool isdSep(int Xi, int Xj, vector<int> Z){
  if(activeTrail.isempty())
    return true;
  return false;
}