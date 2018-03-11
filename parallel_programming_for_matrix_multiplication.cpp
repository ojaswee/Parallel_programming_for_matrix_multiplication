/*
To use openMP in visual studio, we have to enable it first:
1) Click on project (in solution explorer -> below Solution'your_solution_name')
2) Then click on Project (available in Toolbar)
3) Properties->C/C++->language->OpenMP support:yes

In this program we have 2 matrix, and we want to multiply them
First we try sequncial method and calulate the time taken
then we do it by parallelize the task and record the time taken
Now we compare the speedup
Speedup = (time taken by sequential code)/(time taken by parellel code)

In this program I have parallelized matrix multiplication loops in 2 ways
1) outmost loop  is parallelized
2) second loop is parallelized

I see better results with second loop is parallelized, this is beacuse when we do
matrix multiplication we need to multiply row of one matrix with column of another matrix so
it will have a overhead if we will divide both matrix.

For details in speedup please refer to excel sheet
*/
#include <omp.h>
#include <iostream>
#include <random>
#include <vector>
#include <ctime>

using namespace std;

#define NUM_THREADS 8

//Print the matrix
void printMatrix(vector<vector <int>>mat){
	int row = mat.size(),
		col = mat[0].size();
	for (int i = 0; i<row; i++) {
		for (int j = 0; j<col; j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//create matrix with vector
vector <vector <int>> makeMatrix(int row, int col) {
	vector<vector<int>> matrix(row, vector<int>(col));
	for (int i = 0; i<row; i++){
		for (int j = 0; j<col; j++){
			matrix[i][j] = rand() % 5;
		}
	}
	return matrix;
}

//matrixmultiplication considering outermost loop parallelized
vector <vector <int>> matrixMultiplication(vector<vector <int>>matA, vector<vector<int>>matB) {
	int rowA = matA.size(), rowB = matB.size(), colA = matA[0].size(), colB = matB[0].size();
	if (colA != rowB) {
		cout << "column of matrix 1 isnot equal to row of matrix 2, cannot compute\n";
	}
	else {
		vector <vector <int>> result;
		result = makeMatrix(rowA, colB);
		//cout << "Result of matrix multiplication:\n";
		omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for
		for (int row = 0; row < rowA; row++) {//row of result
			//#pragma omp for schedule (dynamic[,rowA/threads]) // dealout blocks of iteration of size chunck to each thread
			for (int col = 0; col < colB; col++) {//col of result
				result[row][col] = 0;
				for (int i = 0; i < rowB; i++) //rowB=colA 
					result[row][col] = result[row][col] + matA[row][i] * matB[i][col];
			}
		}
		return result;
	}
}


//matrixmultiplication considering second loop parallelized
//vector <vector <int>> matrixMultiplication(vector<vector <int>>matA, vector<vector<int>>matB){
//	int rowA = matA.size(), rowB = matB.size(), colA = matA[0].size(), colB = matB[0].size();
//	if (colA != rowB) {
//		cout << "column of matrix 1 isnot equal to row of matrix 2, cannot compute\n";
//	}
//	else {
//		vector <vector <int>> result;
//		result = makeMatrix(rowA, colB);
//		//cout << "Result of matrix multiplication:\n";
//		int row = 0;
//		for (row; row < rowA; row++) {//row of result
//		omp_set_num_threads(NUM_THREADS);
//#pragma omp parallel for
////#pragma omp for schedule (dynamic[,rowA/threads]) // dealout blocks of iteration of size chunck to each thread
//			for (int col = 0; col < colB; col++) {//col of result
//				result[row][col] = 0;
//				for (int i = 0; i < rowB; i++) //rowB=colA 
//					result[row][col] = result[row][col] + matA[row][i] * matB[i][col];
//			}
//		}
//		return result;
//	}
//}

int main() {
	//create 2 matrices
	vector <vector <int>> matrixA, matrixB, finalMatrix;
	int rowA = 500, colA = 500, rowB = 500, colB = 500;
	/*cout << "Enter number of rows/columns for 1st matrix: ";
	cin >> rowA >> colA;
	cout << "Enter number of rows/columns for 2nd matrix: ";
	cin >> rowB >> colB;*/

	//cout << "Matrix 1\n";
	matrixA = makeMatrix(rowA, colA);
	//printMatrix(matrixA);
	//cout << "Matrix 2\n";
	matrixB = makeMatrix(rowB, colB);
	//printMatrix(matrixB);

	/*compute matrix multiplication
	timer starts here*/

	double duration = 0.00; 
	clock_t start;

	start = clock();
	finalMatrix = matrixMultiplication(matrixA, matrixB);
	duration = (clock() - start) / (double)CLOCKS_PER_SEC; 
	//printMatrix(finalMatrix);
	cout << "Total Time to compute matrix multiplication: "<<duration <<" seconds" << endl; //total seconds passed
	system("pause");
}

