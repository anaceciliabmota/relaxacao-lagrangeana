#include "Subgradiente.h"


//colocar o vertice zero na solucao



void adicionaOrigem(vii& solution, double * w, vvi& costs, int nodes){

    for(int i = 0; i < solution.size(); i++){
        solution[i].first++;
        solution[i].second++;
    }
    int v1, v2;
    vector<int> indices(nodes-1);
    for(int i = 1;i < nodes; i++){
        indices[i-1] = i;
    }
    
    sort(indices.begin(), indices.end(), [&costs](int i1, int i2) { return costs[0][i1] < costs[0][i2]; });

    //cout << endl;
    v1 = indices[0];
    v2 = indices[1];

    *w += costs[0][v1];
    *w += costs[0][v2];

    solution.push_back(make_pair(0, v1));
    solution.push_back(make_pair(0, v2));
}

void calculaGrau(vii& solution, int nodes, vector<int>& g){
    vector<int> graus(nodes);
    for(int i = 0; i < nodes; i++){
        graus[i] = 0;
    }
    for(int i = 0; i < solution.size(); i++){
        graus[solution[i].first]++;
        graus[solution[i].second]++;
    }
    g = graus;
}


void refatoraCustos(vector<double>& lambda, int nodes, vvi& costs, vvi& lagrangean_costs, vvi& costs_with_lambda){
    for(int i = 0; i < nodes; i++){
        for(int j = 0; j < nodes; j++){
            if(i != j){
                costs_with_lambda[i][j] = costs[i][j] - lambda[i] - lambda[j];
            }
            if(i != 0 && j != 0){
                lagrangean_costs[i-1][j-1] = costs_with_lambda[i][j];
            }

        }
    }
}

void solve_lagrangian(vvi& original_cost, double upperbound, int nodes, Node * node){
    /////definindo as variaveis de inicio(lambda, epsilon e k)/////
    
    //custo com os arcos proibidos
    vvi costs = original_cost;
    turn_forbidden(node, costs);
    
    //custos que terao os lambdas adicionados 
    vvi costs_with_lambda = costs;

    vector<double> lambda = node->lambdas;
    
    double epsilon = (nodes > 60 ? 2 : 1);

    int k = 0;

    bool continua = true, feasibility = true;

    //custos tirando o vertice zero da arvore geradora minima
    vvi lagrangean_costs(nodes-1, vector<double>(nodes-1));
    for(int i = 1; i < nodes; i++){
        for(int j = 1; j < nodes; j++){
            lagrangean_costs[i-1][j-1] = costs[i][j];
        }
    }

    while(continua){

        refatoraCustos(lambda, nodes, costs, lagrangean_costs, costs_with_lambda);

        Kruskal kr(lagrangean_costs);
        double w = kr.MST(nodes);
        vii solution = kr.getEdges();
        
        //adicionando vertice 0 na solucao
        adicionaOrigem(solution, &w, costs_with_lambda, nodes);

        //incrementando o somatorio de lambda * 2 ao custo (conforme modelo)
        double soma_lambdas = 0;

        //soma necessaria para seguir modelo
        for(int i = 1; i < nodes; i++){
            soma_lambdas += lambda[i];
        }
        w += 2*soma_lambdas;

        //vetor com os graus dos vertices
        vector<int> graus;
        calculaGrau(solution, nodes, graus);

        /*for(int i = 0; i < nodes; i++){
            cout << graus[i] << " ";
        }*/
        
        //calculo do mi
        double soma_restricao = somaGraus(graus, nodes);
        double mi = epsilon*(upperbound - w)/soma_restricao;
        //cout << mi << endl;

        feasibility = true;
        for(int i = 0; i < nodes; i++){
            //cout << graus[i] << " ";
            if(2 - graus[i] != 0){
                feasibility = false;
                break;
            }
        }

        //atualizando lambda
        for(int i = 0; i < nodes; i++){
            lambda[i] = lambda[i] + mi*(2 - graus[i]);
        }

        if(w > node->lower_bound + EPSILON){
            node->feasible = feasibility;
            node->lower_bound = w;
            node->solution = solution;
            node->lambdas = lambda;
            k = 0;
        }else if(feasibility){
            node->feasible = feasibility;
            node->lower_bound = w;
            node->solution = solution;
            node->lambdas = lambda;
            continua = false;
        }
        else{
            k++;
            if(k >= 30){
                k = 0;
                epsilon = epsilon/2;
            }
        }

        if(upperbound - node->lower_bound <= TOL)
            continua = false;
        if(epsilon < EPSILON_MIN)
            continua = false;
    }

}

//faz o somatorio de (b-Ax) ao quadrado
double somaGraus(vector<int>& graus, int nodes){
    
    double soma = 0;

    for(int i = 0; i < nodes; i++){
        soma += (2 - graus[i])*(2 - graus[i]);
    }

    return soma;
}

void turn_forbidden(Node *node, vvi& cost)
{
	for (int i = 0; i < node->forbidden_arcs.size(); i++)
	{
		cost[node->forbidden_arcs[i].first][node->forbidden_arcs[i].second] = numeric_limits<double>::infinity();
        cost[node->forbidden_arcs[i].second][node->forbidden_arcs[i].first] = numeric_limits<double>::infinity();
    }
}