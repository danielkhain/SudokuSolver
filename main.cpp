//
//  main.cpp
//  Sudoku Solver
//
//  Created by Daniel Khain on 11/22/20.
//  Copyright © 2020 Daniel Khain. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <queue>
#include <string>
#include "SudokuSolver.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    SudokuSolver solver;
    solver.initializeGrid();
    cout << "\nWelcome to SudokuSolver!\n";
    cout << "Reading input from " << argv[1] << endl;
    fstream fin;
    fin.open(argv[1]);
    solver.fillGrid(fin);
    solver.prepSolver();
    solver.runSolver();
}
