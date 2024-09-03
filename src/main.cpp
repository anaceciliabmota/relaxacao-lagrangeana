#include "Subgradiente.h"
#include "BranchAndBound.h"
#include "data.h"
#include <time.h> 
#include <string>

int main(int argc, char **argv){

    clock_t start, end;
    start = clock();


    double ub;
    if(argv[2])
        ub = stod(argv[2]);
    else{
         cout << "Missing upperbound" << endl;
         exit(0);
    }
    
	Data *data = new Data(argc, argv[1]);

    //cout << "Reading data..." << endl;
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

    //cout << "Solving..." << endl;
    s = BnB(cost, 1, nodes, ub);
    end = clock();
    
    cout << "OPTIMAL SOLUTION FOUND" << endl;
    cout << "Z = "  << s.valorObj << endl;
    //exibirSolucao(&s);

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "TIME USED: " << fixed << time_taken;
    cout << " secs" << endl;

    delete data;

    return 0;
}
