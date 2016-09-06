#include "bayesnet.h"
#include <iostream>

#define min(a,b) ((a<b)?(a):(b))

void print(char *line){
    int i=0;
    while(*(line+i) != '\0'){
        if(*(line+i) != '\n')
            putchar(*(line+i));
        i++;
    }
    putchar('\n');
}

int pickRandomUnvisitedNode(std::map<int,int> &visited, int root, int numNodes)
{
    std::uniform_int_distribution<int> randomNode(root+1,numNodes);
    short seedr = clock()%16000;
    std::default_random_engine generator{seedr};
    randomNode(generator);
    int ret;
    do{
        ret = randomNode(generator);
    }while(visited.find(ret) != visited.end());
    visited[ret]=1;
    return ret;
}

/*
 * Generates random bayesian network of given size,
 * n denoting the the number of nodes in the network
 * and k the max-number of children for each node.
 * returns NULL on failure.
 */
BNet genRandomBN(int numNodes, int maxChildren)
{
    short seedr = clock()%15000;
    std::default_random_engine generator{seedr};
    
    std::uniform_int_distribution<int> distribution(0,maxChildren);
    BNet retBN;
    
    retBN.numNodes = numNodes;
    retBN.Parents.resize(numNodes+1);
    retBN.Children.resize(numNodes+1);
    
    distribution(generator);
    int curr = 1;
    
    int numChildren,pickChild;
    while(curr<=numNodes){
        numChildren = distribution(generator);
        pickChild = min(numNodes-curr,numChildren);
        std::map<int,int> visited;
        visited.clear();
        int child;
        while(pickChild){
            child = pickRandomUnvisitedNode(visited,curr,numNodes);
            retBN.Children[curr].push_back(child);
            retBN.Parents[child].push_back(curr);
            pickChild--;
        }
        curr += 1;
    }
    return retBN;
}

/*
 * Reads bayes net from infile to bNet.
 * infile must follow standard mentioned in README.md.
 * infile is assumed to be in same dir as executable.
 */
int readBayesNet(char infile[], BNet &bNet)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    fp = fopen(infile, "r");
    if (fp == NULL)
        return -1;
    if((read = getline(&line, &len, fp)) == -1)
        return -1;
    bNet.numNodes = atoi(line);
    
    bNet.Parents.resize(bNet.numNodes+1);
    bNet.Children.resize(bNet.numNodes+1);
    int parent;
    while ((read = getline(&line, &len, fp)) != -1) {
        addtoBNet(line,read,bNet);
    }
    
    fclose(fp);
    if (line)
        free(line);
    return 0;
}

void addtoBNet(char *line, int size, BNet &bNet)
{
    const char s1[2] = " ";
    const char s2[2] = ",";
    
    char *token;
    
    /* get the first token */
    token = strtok(line, s1);
    
    int node = atoi(token);
    token = strtok(NULL, s1);
    
    token += 1;
    if(token == NULL)
        return;
    if(strlen(token)<=2){
        return;
    }
    
    token[strlen(token)-2] = '\0';
    line = token;
    token = strtok(line, s2);
    
    /* walk through other tokens */
    while( token != NULL && *token<58 && *token>47)
    {
        bNet.Children[node].push_back(atoi(token));
        bNet.Parents[atoi(token)].push_back(node);
        token = strtok(NULL, s2);
    }
}

/*
 * Writes bayes net to outfile.
 * bNet checked for  must follow standard mentioned in README.md.
 */
void writeBayesNet(const char outfile[], BNet &bNet)
{
    //freopen(outfile,"w",stdout);
    printf("%d\n",bNet.numNodes);
    for(int i=1;i<=bNet.numNodes;++i){
        printf("%d [",i);
        if(bNet.Children[i].size() == 0){
            printf("]\n");
        }else{
            for(int j=0;j<bNet.Children[i].size()-1;++j)
                printf("%d,",bNet.Children[i][j]);
            printf("%d",bNet.Children[i][bNet.Children[i].size()-1]);
            printf("]\n");
        }
    }
    fclose (stdout);
}

queryType parse(char *line)
{
    queryType Q;
    const char s1[2] = " ";
    const char s2[2] = ",";
    
    char *token;
    
    /* get the first token */
    token = strtok(line, s1);
    Q.Xi = atoi(token);
    token = strtok(NULL, s1);
    Q.Xj = atoi(token);
    
    token = strtok(NULL, s1);
    token += 1;
    if(token == NULL)
        return Q;
    if(strlen(token)<=2){
        if(*token >47 && *token<58)
            Q.Z.push_back((*token)-48);
        return Q;
    }
    
    token[strlen(token)-2] = '\0';
    line = token;
    token = strtok(line, s2);
    
    /* walk through other tokens */
    while( token != NULL && *token<58 && *token>47)
    {
        Q.Z.push_back(atoi(token));
        token = strtok(NULL, s2);
    }
    return Q;
}

int answerQueries(char infile[], char outfile[], BNet &bNet)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    fp = fopen(infile, "r");
    if (fp == NULL)
        return -1;
    if((read = getline(&line, &len, fp)) == -1)
        return -1;
    freopen(outfile,"w",stdout);
    while ((read = getline(&line, &len, fp)) != -1) {
        print(line);
        queryType Q = parse(line);
        std::vector<int> ans = activeTrail(Q.Xi,Q.Xj,Q.Z,bNet);
        if(ans.size()){
            printf("no [");
            reverse(ans.begin(),ans.end());
            for(int i=0;i<ans.size()-1;++i)
                printf("%d,",ans[i]);
            printf("%d]\n",ans[ans.size()-1]);
        }else{
            printf("yes\n");
        }
    }
    fclose (stdout);
    fclose(fp);
    if (line)
        free(line);
    return 0;
}

/*
 * Checks validity of bayes net specified by bNet,
 * as mentioned in README.md
 */
//TODO
int checkBayesNet(BNet *bNet){
    return 0;
}

/*
 * Given two r.v's Xi,Xj, and some observed r.v's Z,
 * it returns the active trail between the random vars
 * if it exists.
 */
std::vector<int> activeTrail(int Xi, int Xj, std::vector<int> &Z, BNet &bNet)
{
    std::vector<int> activeTrail;
    std::vector<int> Pi(bNet.numNodes+1);
    
    std::set<int> toVisit(Z.begin(),Z.end());
    std::set<int> ancestors;
    
    int Y,d;
    while(!toVisit.empty()){
        Y = *toVisit.begin();
        toVisit.erase(toVisit.begin());
        if(ancestors.find(Y) == ancestors.end())
            tr(bNet.Parents[Y],it)
                toVisit.insert(*it);
        ancestors.insert(Y);
    }
    
    std::set<ii> L;
    L.insert(ii(Xi,1));
    
    std::vector<int> visited[2] = {
        std::vector<int>(bNet.numNodes+1,0),
        std::vector<int>(bNet.numNodes+1,0),
    };
    
    std::set<int> fastZ(Z.begin(),Z.end());
    Pi[Xi] = Xi;
    
    while(!L.empty()){
        Y = (*L.begin()).first;
        d = (*L.begin()).second;
        L.erase(L.begin());
        if(!visited[d][Y]){
            if(fastZ.find(Y) == fastZ.end()){
                if(Y == Xj){
                    do{
                        activeTrail.push_back(Y);
                        Y = Pi[Y];
                    }while(Y != Pi[Y]);
                    if(activeTrail.size())
                        activeTrail.push_back(Xi);
                    return activeTrail;
                }
            }
            visited[d][Y]=1;
            if(d && (fastZ.find(Y) == fastZ.end())){
                tr(bNet.Parents[Y],it){
                    L.insert(ii(*it,1));
                    if(!visited[1][*it])
                        Pi[*it] = Y;
                }
                tr(bNet.Children[Y],it){
                    L.insert(ii(*it,0));
                    if(!visited[0][*it])
                        Pi[*it] = Y;
                }
            }else if(!d){
                if(fastZ.find(Y) == fastZ.end()){
                    tr(bNet.Children[Y],it){
                        L.insert(ii(*it,0));
                        if(!visited[0][*it])
                            Pi[*it] = Y;
                    }
                }
                if(ancestors.find(Y) != ancestors.end()){
                    tr(bNet.Parents[Y],it){
                        L.insert(ii(*it,1));
                        if(!visited[1][*it])
                            Pi[*it] = Y;
                    }
                }
            }
        }
    }
    return activeTrail;
}

bool isdSep(int Xi, int Xj, std::vector<int> &Z, BNet &bNet){
  if(activeTrail(Xi,Xj,Z,bNet).empty())
    return true;
  return false;
}