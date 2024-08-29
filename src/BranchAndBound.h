#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include "Subgradiente.h"

#include <list>

typedef struct Solucao
{
	vii arestas;
	double valorObj;
} Solucao;

Solucao BnB (vvi& cost, int branching_strategy, int nodes, double ub);

Node select_node(int branchingS, list<Node> &nodes, list<Node>::iterator &i);

void exibirSolucao(Solucao *s);



#endif