# Parallel_programming_for_matrix_multiplication

To use OpenMP in visual studio, we have to enable it first: 
1) Click on project (in solution explorer -> below Solution'your_solution_name')
2) Then click on Project (available in Toolbar)  
3) Properties->C/C++->language->OpenMP support:yes

In this program, we have 2 matrices, and we want to multiply them.
First, we try the sequential method and calculate the time taken
then we do it by parallelize the task and record the time taken
Now we compare the speedup

Speedup = (time taken by sequential code)/(time taken by parallel code)

In this program, I have parallelized matrix multiplication loops in 2 ways
1) outmost loop  is parallelized 
2) the second loop is parallelized

-----------
In the excel sheet, I have compared speedup between 2 things
1)	number of threads (1,2,4 and 8)
2)	outermost loop parallelization vs second loop parallelization

I see better results with the second loop is parallelized, this is because when we do 
matrix multiplication we need to multiply a row of one matrix with a column of another matrix. This will have an overhead if we will divide both matrices. 
