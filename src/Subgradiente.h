#ifndef SUBGRADIENTE_H
#define SUBGRADIENTE_H

#include "Kruskal.h"
#include <limits>
#include <numeric>
#include <algorithm>
#include <iomanip>

struct Node
{
    vii solution;
    vector<double> lambdas;
	vector<pair<int, int>> forbidden_arcs;
    bool feasible;
	double lower_bound;
} typedef Node;


void solve_lagrangean(vvi& costs, double upperbound, int nodes, Node * node);
bool criterioParada(double epsilon, vii& solution, int nodes,  vector<double>& lambda);
void calculaGrau(vii& solution, int nodes, vector<int>& graus);
void refatoraCustos(vector<double>& lambda, int nodes, vvi& costs, vvi& lagrangean_costs, vvi& costs2);
double somaGraus(vii& solution, int nodes);
void adicionaOrigem(vii& solution, double * w, vvi& costs, int nodes);
bool compare(int i1, int i2, vector<double>& cost);
void turn_forbidden(Node *node, vvi& cost);


#endif