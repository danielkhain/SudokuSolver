//
//  main.cpp
//  Sudoku Solver
//
//  Created by Daniel Khain on 11/22/20.
//  Copyright © 2020 Daniel Khain. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "SudokuSolver.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    cout << "\nWelcome to SudokuSolver!\n";

    // Create solver instance.
    SudokuSolver solver;
    solver.initializeGrid();

    // Confirm that input is good.
    if (argc != 2){
        cout << "Bad input.\n";
        cout << "Please write './sudoku [input_file]'\n";
        exit(1);
    }
    fstream fin;
    fin.open(argv[1]);
    if (!fin){
        cout << "Unable to open file.\n";
        exit(1);
    }
    cout << "Reading input from " << argv[1] << endl;

    // Prep and run the solver.
    solver.fillGrid(fin);
    solver.prepSolver();
    solver.runSolver();
}
