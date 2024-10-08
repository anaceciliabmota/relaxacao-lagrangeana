#include "BranchAndBound.h"

#define EPSILON 1e-5

Solucao BnB (vvi& cost, int branching_strategy, int nodes, double ub){
    list<Node>::iterator it;
    Node root;
	vector<double> lambdas(nodes,0);
	
	root.lambdas = lambdas;
	root.lower_bound = -numeric_limits<double>::infinity();

    solve_lagrangian(cost, ub, nodes, &root);

	//exit(0);
    list<Node> tree;
    tree.push_back(root);

    double upper_bound = ub;
	Solucao s;

    int cont = 0;
	while (!tree.empty())
	{
		
		Node node = select_node(2, tree, it);
		solve_lagrangian(cost, upper_bound, nodes, &node);


		if (node.lower_bound - EPSILON > upper_bound)
		{
			tree.erase(it);
			continue;
		}
		if (node.feasible)
		{	 
			if(node.lower_bound + EPSILON < upper_bound){
				//cout << cont << ": obj = " << node.lower_bound << endl;
				upper_bound = node.lower_bound;
				s.valorObj = node.lower_bound;
				s.arestas = node.solution;
			}
		}
		else
		{
			vector<int> graus;
            calculaGrau(node.solution, nodes, graus);
            auto max_it = max_element(graus.begin(), graus.end());
            int index = distance(graus.begin(), max_it);

            for(int i = 0; i < node.solution.size(); i++){
                if(node.solution[i].first == index || node.solution[i].second == index){
                    Node n;
					n.lambdas = node.lambdas;
					n.lower_bound = -numeric_limits<double>::infinity();
                    n.forbidden_arcs = node.forbidden_arcs;
                    pair<int, int> forbidden_arc = node.solution[i];
                    n.forbidden_arcs.push_back(forbidden_arc);
                    tree.push_back(n);
                }
                
            }
            
		}
		tree.erase(it);
		cont++;
	}
    return s;
}


void exibirSolucao(Solucao *s)
{
	vii solution = s->arestas;

	cout << solution[0].first << " " << solution[0].second << " ";
	int ultimo = solution[0].second;
	solution.erase(solution.begin());
	
	while(!solution.empty()){
		for(int i = 0; i < solution.size(); i++){
			if(solution[i].first == ultimo){
				cout << solution[i].second << " ";
				ultimo = solution[i].second;
				solution.erase(solution.begin()+ i);
				break;
			}else if(solution[i].second == ultimo){
				cout << solution[i].first << " ";
				ultimo = solution[i].first;
				solution.erase(solution.begin()+ i);
				break;
			}
		}
	}
	cout << endl;
	

}


Node select_node(int branchingS, list<Node> &nodes, list<Node>::iterator &i)
{
	if (branchingS == 1)
	{
		// BFS
		i = nodes.begin();
		return nodes.front();
	}
	else if (branchingS == 2)
	{
		// DFS
		i = --nodes.end();
		return nodes.back();
	}
	else if (branchingS == 3)
	{
		// busca pelo menor lower_bound
		Node no;
		no.lower_bound = numeric_limits<double>::infinity();
		for (auto it = nodes.begin(); it != nodes.end(); it++)
		{
			if ((*it).lower_bound < no.lower_bound)
			{
				no = *it;
				i = it;
			}
		}
		return no;
	}
	Node n;
	return n;
}

