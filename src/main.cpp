#include "Subgradiente.h"
#include "BranchAndBound.h"
#include "data.h"
#include <time.h> 
#include <string>

int main(int argc, char **argv){

    clock_t start, end;
    start = clock();

	Data *data = new Data(argc, argv[1]);
	
    double ub = stod(argv[2]);
	data->readData();

    
    int nodes = data->getDimension();

    vvi cost(nodes, vector<double>(nodes));

    for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			cost[i][j] = data->getDistance(i, j);
		}
	}

    Solucao s;
    s = BnB(cost, 1, nodes, ub);
    end = clock();
    
    cout << "Solucao:" << endl;
    exibirSolucao(&s);

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "tempo gasto: " << fixed << time_taken;
    cout << " secs" << endl;


    

    return 0;
}
