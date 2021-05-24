# SudokuSolver
Advanced Sudoku Puzzle Solver - Improved Backtracking Algorithm

### About The Project
This project solves Sudoku puzzles. Unlike most Sudoku solving algorithms which use a naive Backtracking algorithm, this approach utilizes the same strategy that a human would. The solver first fills squares that can accept only one options. Then the solver uses Backracking, starting with the squares that can accept the fewest options.

### Installation
1. Clone the repo ```git clone https://github.com/danielkhain/SudokuSolver.git```
2. Create `sudoku` executable ```./make_sudoku_exe```
3. Run the program with an input file ```./sudoku input/input[#].txt```
4. For custom input, create a `.txt` file and fill it with the Sudoku puzzle initial values; put a zero for unknown squares. Use the provided input files as an example.

### Acknowledgments
Thank you to https://www.sudoku-solutions.com/ for providing Sudoku puzzles and solutions to test the program.
