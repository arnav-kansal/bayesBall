#ifndef BAYES_NET_
#define BAYES_NET_

#include <vector>
#include <random>
#include <string.h>
#include <time.h>
#include <map>


/*
 * Nodes are indexed from 0 through n-1.
 * Each node represents a r.v. with parents
 * of each node stored in a vector.
 */

int pickRandomUnvisitedNode(std::map<int,int> &visited, int root, int numNodes);

typedef struct BayesainNetwork{
	int numNodes; 
    std::vector<std::vector<int> >Parents;
}BNet;

typedef struct queryType{
    int Xi;
    int Xj;
    std::vector<int> Z;
}queryType;

void addtoBNet(char *line, int size, BNet &bNet);
BNet genRandomBN(int n, int k);

int readBayesNet(char infile[], BNet &bNet);
void writeBayesNet(const char oufile[], BNet &bNet);
int checkBayesNet(BNet *bNet);

std::vector<int> activeTrail(int Xi, int Xj, std::vector<int> &Z, BNet &bNet);
bool isdSep(int Xi, int Xj, std::vector<int> &Z);

#endif