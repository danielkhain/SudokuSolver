//
//  SudokuSolver.cpp
//  Sudoku Solver
//
//  Created by Daniel Khain on 11/22/20.
//  Copyright © 2020 Daniel Khain. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <queue>
#include <string>
#include <numeric>
#include "time.h"

using namespace std;

struct Square{
    vector<int> potentialValues;
    int value;
};

struct Grid{
    vector< vector<Square> > grid;
};

class SudokuSolver{
    private:
    stack<Grid> status;
    Grid grid;
    Grid tempGrid;
    vector< stack< pair<int, int> > > numUnknown;
    int unfilled = 0;
    stack<pair<pair<int, int>, int>> hypothesis;
    int numGuesses =0;
    int numIterations = 0;
    int numFilled = 0;
    clock_t start, end;


    public:

    void initializeGrid(){
        start = clock();
        grid.grid.resize(9);
        for (int i = 0; i < 9; i++){
            grid.grid[i].resize(9);
        }

        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                grid.grid[i][j].potentialValues.resize(9);
                for (int k = 0; k < 9; k++){
                    grid.grid[i][j].potentialValues[k] = 0;
                }
            }
        }
        numUnknown.resize(10);
    }

    void fillGrid(fstream& fin){
        string line;
        int row = 0;
        while (fin >> line) {
            for (int i = 0; i < line.length(); i++){
                grid.grid[row][i].value = stoi(line.substr(i,1));
                if (grid.grid[row][i].value != 0){
                    numFilled++;
                }
                nullifyOptions(row, i);
            }
            row++;
        }
        cout << "Here is your input:\n";
        printGrid();
        cout << "\n\n";
    }

    void nullifyOptions(int row, int col){
        updateByRows(row);
        updateByCols(col);
        updateByBoxes(((row / 3) * 3) + (col / 3));
    }

    void updateByRows(int row){
        // Go through all the columns.
        for (int col = 0; col < 9; col++){
            int tempVal = grid.grid[row][col].value;
            // If value is known, go through row and update potential values.
            if (tempVal != 0){
                for (int upd_col = 0; upd_col < 9; upd_col++){
                    grid.grid[row][upd_col].potentialValues[tempVal - 1] = -1;
                }
            }
        }
    }
    void updateByCols(int col){
        // Go through all the rows.
        for (int row = 0; row < 9; row++){
            int tempVal = grid.grid[row][col].value;
            // If value is known, go through row and update potential values.
            if (tempVal != 0){
                for (int upd_row = 0; upd_row < 9; upd_row++){
                    grid.grid[upd_row][col].potentialValues[tempVal - 1] = -1;
                }
            }
        }
    }

    void updateByBoxes(int box){
        // Go through all the squares in box.
        for (int row = ((box / 3) * 3); row < ((box / 3) * 3 + 3); row++){
            for (int col = ((box % 3) * 3); col < ((box % 3) * 3 + 3); col++){
                int tempVal = grid.grid[row][col].value;
                if (tempVal != 0){
                    for (int upd_row = ((box / 3) * 3); upd_row < ((box / 3) * 3 + 3); upd_row++){
                        for (int upd_col = ((box % 3) * 3); upd_col < ((box % 3) * 3 + 3); upd_col++){
                            grid.grid[upd_row][upd_col].potentialValues[tempVal - 1] = -1;
                        }
                    }
                }
            }
        }
    }

    void updatePotential(){
        for (int i = 0; i < 9; i++){
            updateByRows(i);
            updateByCols(i);
            updateByBoxes(i);
        }
        unfilled = 0;

        for (int i = 0; i < numUnknown.size(); i++){
            while(!numUnknown[i].empty()){
                numUnknown[i].pop();
            }
        }

        for (int row = 0; row < 9; row++){
            for (int col = 0; col < 9; col++){
                if (grid.grid[row][col].value == 0){
                    unfilled++;
                    int sum = accumulate(grid.grid[row][col].potentialValues.begin(), grid.grid[row][col].potentialValues.end(), 0);
                    numUnknown[9 + sum].push({row, col});
                }
            }
        }
    }

    void printGrid(){
        for (int row = 0; row < 9; row++){
            if (row % 3 == 0){
              cout << "______________________\n";
            }
            for (int col = 0; col < 9; col++){
                if (col % 3 == 0){
                    cout << "|";
                }
                cout << grid.grid[row][col].value << " ";
            }
            cout << "|" << endl;
        }
        cout << "______________________\n";
    }

    bool isPossible(){
      return (numUnknown[0].empty());
    }

    void prepSolver(){
      status.push(grid);
    }

    void printStats(){
        end = clock();
        cout << "\nSome statistics:\n";
        cout << "Originally, " << numFilled << "/81 squares were filled.\n";
        cout << "The solver made " << numGuesses << " guesses.\n";
        cout << "The solver went through " << numIterations << " iterations.\n";
        cout << "The time taken was " << double(end-start) / 1000000 << " seconds.\n\n";
    }

    void runSolver(){
        numIterations++;
        updatePotential();
        if (!isPossible()){
            status.pop();
            if (status.empty()){
                cout << "Sorry, your puzzle has no solution...\n\n";
                printStats();
                exit(1);
            }
            grid = status.top();
            int a,b,val = 0;
            if (hypothesis.empty()){
                cout << "Sorry, your puzzle has no solution...\n\n";
                printStats();
                exit(1);
            }
            a = hypothesis.top().first.first;
            b = hypothesis.top().first.second;
            val = hypothesis.top().second;
            hypothesis.pop();
            grid.grid[a][b].potentialValues[val-1] = -1;
            grid.grid[a][b].value = 0;
            status.top().grid[a][b].value = 0;
            status.top().grid[a][b].potentialValues[val-1] = -1;
            runSolver();
        }
        else if (unfilled == 0){
            cout << "Here is the solution:\n";
            printGrid();
            printStats();
            exit(0);
        }
        else{
            for (int idk = 1; idk < numUnknown.size(); idk++){
                if (!numUnknown[idk].empty()){
                    int a,b = 0;
                    a = numUnknown[idk].top().first;
                    b = numUnknown[idk].top().second;
                    numUnknown[idk].pop();
                    if (idk == 1){
                        for (int j = 0; j < 9; j++){
                            if (grid.grid[a][b].potentialValues[j] != -1){
                                grid.grid[a][b].value = j+1;
                                nullifyOptions(a, b);
                                break;
                            }
                            if (j == 8){
                                runSolver();
                            }
                        }
                    }
                    else{
                        for (int j = 0; j < 9; j++){
                            if (grid.grid[a][b].potentialValues[j] != -1){
                                grid.grid[a][b].value = j+1;
                                hypothesis.push({{a,b}, j+1});
                                numGuesses++;
                                status.push(grid);
                                break;
                            }
                        }
                    }
                    runSolver();
                }
            }
          }
    }
};
