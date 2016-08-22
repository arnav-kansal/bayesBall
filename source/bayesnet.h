#ifndef BAYES_NET_
#define BAYES_NET_

#include <queue>
#include <vector>

/*
 * Nodes are indexed from 0 through n-1.
 * Each node represents a r.v. with parents
 * of each node stored in a vector.
 */

struct BayesainNetwork{
	int numNodes; 
  std::vector<std::vector<int> >Parents;
};

struct BayesianNetwork* genRandomBN(int n, int k);

int readBayesNet(char *filedir, struct BayesianNetwork *bNet);
int writeBayesNet(char *);
int checkBayesNet(struct BayesianNetwork *bNet);

vector<int> activeTrail(int Xi, int Xj, vector<int> Z);
bool isdSep(int Xi, int Xj, vector<int> Z);

#endif