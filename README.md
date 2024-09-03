
# Lagrangian Relaxation

This project is an implementation of the Lagrangian Relaxation method.

## About
The Lagrangian Relaxation is a relaxation method used to find high-quality lower bounds for combinatorial optimization problems. In this project, the lower bound was used to solve the Travelling Salesman Problem using the Branch-and-Bound algorithm.

- **Input**: The Application receives two arguments in the command line: 
    1. the path to the `.tsp` file with the TSP problem data.
    2. an upper bound to be used in the Branch-and-Bound algorithm.

    Example:

    ```bash
    ./solve path/to/file.tsp upperbound_value
    ```

- **Output**: The optimal value.

## Instances
The [instances](instances) directory contains `.tsp` files used to test and validate the solver.

## Credits
**[Igor Malheiros](https://github.com/igormalheiros)**: For providing the [Kruskal.cpp](src/Kruskal.cpp) and [Kruskal.h](src/Kruskal.h) files to find a Minimum Spanning Tree solution.
