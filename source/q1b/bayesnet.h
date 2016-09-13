#ifndef BAYES_NET_
#define BAYES_NET_

#include <vector>
#include <random>
#include <string.h>
#include <time.h>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <queue>
#include <functional>

typedef std::pair<int,int> ii;
typedef std::vector<ii> vii;
typedef std::vector<vii> vvii;
typedef std::set<int> set;
typedef std::pair<std::pair<int,int>,std::vector<int> > samaan;

#define tr(c,i) for( std::vector<int>::iterator i = (c).begin(); i != (c).end(); i++)

/*
 * Nodes are indexed from 0 through n-1.
 * Each node represents a r.v. with parents
 * of each node stored in a vector.
 */

int pickRandomUnvisitedNode(std::map<int,int> &visited, int root, int numNodes);

typedef struct BayesainNetwork{
	int numNodes; 
    std::vector<std::vector<int> >Parents;
    std::vector<std::vector<int> >Children;
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
int answerQueries(char infile[], char outfile[], BNet &bNet);
queryType parse(char *line);
#endif