#ifndef UTILITIES_
#define UTILITIES_

#include "bayesnet.h"

void print(char *line);
int readBayesNet(char infile[], BNet &bNet);
void addtoBNet(char *line, int size, BNet &bNet);
void writeBayesNet(const char outfile[], BNet &bNet);
queryType parse(char *line);
#endif