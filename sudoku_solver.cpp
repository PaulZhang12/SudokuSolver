// A Backtracking program in C++ to solve Sudoku problem  
//#include <bits/stdc++.h> 
#include<iostream>
#include <fstream>
#include <vector>
using namespace std;


/* TODO: Declare helpter functions if needed, optional*/

bool isValid(int (&grid)[9][9]); //check if sudoku board is valid
bool evaluateRows(int (&grid)[9][9]); //helpers for isVald
bool evaluateCols(int (&grid)[9][9]);
bool evaluateSections(int (&grid)[9][9]);

void printGrid(int grid[9][9]);


/* TODO: implement the function that takes in a 9 by 9 array of ints, 
modifies the grid so that it is filled with no 0s,
and returns whether it is solvable or not */
bool SolveSudoku(int (&grid)[9][9])
{
	for(int i = 0; i < 9; i++){ //loop through the board
		for(int j = 0; j < 9; j++){
				if(grid[i][j] == 0){ //if cell is unassigned
					for(int value = 1; value < 10; value++){ //for each potential value
						grid[i][j] = value; //set that cell to the value
						if(isValid(grid)){ //if the grid is still a valid sudoku board with the value added
							if(SolveSudoku(grid)) //then attempt to solve the board with the value added onto the grid
								return true; //if the previous solve was true, from the top of the stack, then return true to the bottom
						}
					} 
					grid[i][j] = 0; //if no values work, set it back to zero
					return false; //return false, so the values for the previous cells can change
				}
			}
		}
	return true;
}

/* A utility function to print grid */
void printGrid(int grid[9][9])
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
			cout << grid[row][col] << " ";
		cout << endl;
	}
	cout << endl;
}


int main()
{

	
	
	//start out with easy grid!
	int easy[9][9] = { 
	{1, 2, 3, 0, 5, 6 ,7 ,8, 9},
	{0, 5, 6, 7, 8, 9, 1, 2, 3},
	{7, 8, 0, 1, 2, 3, 4, 5, 6},
	{2, 1, 4, 3, 6, 5, 0, 9 ,7},
	{3, 0, 5, 8, 9, 7, 2, 1, 4},
	{8, 9, 7, 2, 1, 4, 3, 6, 0},
	{5, 3, 1, 6, 4, 2, 9, 0, 8},
	{6 ,4 ,2, 9, 0, 8, 5, 3, 1},
	{9, 7, 8, 0, 3, 1, 6, 4, 2} };

	if (SolveSudoku(easy) == true)
		printGrid(easy);
	else
		cout << "No solution exists" << endl << endl;
	
	
	//this grid's solution is in the spec for reference
	int A[9][9] = { {1, 0, 0, 3, 0, 0, 0, 8, 0},
				  {3, 0, 0, 9, 0, 0, 6, 0, 0},
				  {0, 0, 0, 7, 4, 8, 1, 0, 5},
				  {4, 2, 6, 0, 0, 0, 7, 0, 0},
				  {0, 7, 8, 4, 0, 9, 3, 6, 0},
				  {0, 0, 3, 0, 0, 0, 4, 5, 8},
				  {2, 0, 1, 8, 9, 4, 0, 0, 0},
				  {0, 0, 4, 0, 0, 6, 0, 0, 9},
				  {0, 3, 0, 0, 0, 5, 0, 0, 6} };
	if (SolveSudoku(A) == true)
		printGrid(A);
	else
		cout << "No solution exists" << endl << endl;
	
	int B[9][9] = { {3, 0, 6, 5, 0, 8, 4, 0, 0},
					  {5, 2, 0, 0, 0, 0, 0, 0, 0},
					  {0, 8, 7, 0, 0, 0, 0, 3, 1},
					  {0, 0, 3, 0, 1, 0, 0, 8, 0},
					  {9, 0, 0, 8, 6, 3, 0, 0, 5},
					  {0, 5, 0, 0, 9, 0, 6, 0, 0},
					  {1, 3, 0, 0, 0, 0, 2, 5, 0},
					  {0, 0, 0, 0, 0, 0, 0, 7, 4},
					  {0, 0, 5, 2, 0, 6, 3, 0, 0} };
	if (SolveSudoku(B) == true)
		printGrid(B);
	else
		cout << "No solution exists" << endl << endl;





	int C[9][9] = { {0, 0, 6, 0, 3, 0, 8, 5, 0},
			  {0, 5, 0, 0, 0, 0, 0, 0, 2},
			  {3, 4, 0, 5, 0, 0, 0, 0, 0},
			  {0, 0, 0, 1, 4, 0, 0, 0, 0},
			  {4, 9, 1, 0, 0, 0, 6, 7, 5},
			  {0, 0, 0, 0, 5, 6, 0, 0, 0},
			  {0, 0, 0, 0, 0, 5, 0, 6, 4},
			  {6, 0, 0, 0, 0, 0, 0, 8, 0},
			  {0, 7, 5, 0, 1, 0, 3, 0, 0} };
	if (SolveSudoku(C) == true)
		printGrid(C);
	else
		cout << "No solution exists" << endl << endl;
	
 
	
	
	return 0;
}



bool isValid(int (&grid)[9][9]){
	if(evaluateSections(grid) && evaluateRows(grid) && evaluateCols(grid)){ //evaluate each different section for validity
		return true;
	}
	else{
		return false;
	}
}

bool evaluateSections(int (&grid)[9][9]){ //each 3x3 section
	for(int sectionx = 0; sectionx < 3; sectionx++){
		for(int sectiony = 0; sectiony < 3; sectiony++){
			int occurance[10] = {0};

			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					if(grid[3*sectionx+i][3*sectiony+j] == 0)
						continue;
					else if(occurance[grid[3*sectionx+i][3*sectiony+j]-1] == 0)
						occurance[grid[3*sectionx+i][3*sectiony+j]-1]++;
					else{
						return false;
					}
				}
			}

		}
	}

	return true;

}

bool evaluateCols(int (&grid)[9][9]){ //evaluating each row (cols as j increases first)
	for(int i = 0; i < 9; i++){
		int occurance[10] = {0};
		for(int j = 0; j < 9; j++){
			if(grid[i][j] == 0)
				continue;
			else if(occurance[grid[i][j]-1] == 0){
				occurance[grid[i][j]-1]++;
			}
			else{
				return false;
			}
		}
	}
	return true;
}

bool evaluateRows(int (&grid)[9][9]){ //evaluating each column
	for(int j = 0; j < 9; j++){
		int occurance[10] = {0};
		for(int i = 0; i < 9; i++){
			if(grid[i][j] == 0)
				continue;
			else if(occurance[grid[i][j]] == 0){
				occurance[grid[i][j]]++;
			}
			else{
				return false;
			}
		}
		
	}
	return true;
}
