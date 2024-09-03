#ifndef SUBGRADIENTE_H
#define SUBGRADIENTE_H

#include "Kruskal.h"
#include <limits>
#include <numeric>
#include <algorithm>
#include <iomanip>

#define TOL 0.00001
#define EPSILON_MIN 0.0005
#define EPSILON 1e-5


struct Node
{
    vii solution;
    vector<double> lambdas;
	vector<pair<int, int>> forbidden_arcs;
    bool feasible;
	double lower_bound;
} typedef Node;


void solve_lagrangian(vvi& costs, double upperbound, int nodes, Node * node);
bool criterioParada(double epsilon);
void calculaGrau(vii& solution, int nodes, vector<int>& graus);
void refatoraCustos(vector<double>& lambda, int nodes, vvi& costs, vvi& lagrangean_costs, vvi& costs2);
double somaGraus(vector<int>& graus, int nodes);
void adicionaOrigem(vii& solution, double * w, vvi& costs, int nodes);
void turn_forbidden(Node *node, vvi& cost);


#endif