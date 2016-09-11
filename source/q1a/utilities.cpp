#include "bayesnet.h"

void print(char *line){
    int i=0;
    while(*(line+i) != '\0'){
        if(*(line+i) != '\n')
            putchar(*(line+i));
        i++;
    }
    putchar('\n');
}

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
    freopen(outfile,"w",stdout);
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
