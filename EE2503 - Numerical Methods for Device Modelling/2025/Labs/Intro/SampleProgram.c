#include <stdio.h>
#include <math.h>

// Prototype of the function call
void SelfConsistentSolution(double* , double* , double* );

// Start of the main program
int main(){

	printf("This program solves a system of 2x2 equations \n");
 
	double RHS[2] = {8, 1};
	double Unknown[2] = {0, 0};
	double LHS[2][2] = {{2, 1}, 
			    {1, 2}}; 

	// Calling the function for solving the system of equations
	SelfConsistentSolution(Unknown, RHS, (double *)LHS);

	return(0);
}

void SelfConsistentSolution(double* Unknown, double* RHS, double* LHS){
	int MaxIteration = 10; // Maximum number of times we want to try 
	int Iteration = 0; // Counter to keep a track of number of trials done
	double OldSol0, OldSol1; // Storage variables to keep a track of previous solutions
	printf("%lf, %lf \n", Unknown[0], Unknown[1]); // Printing the initial guess
	while (Iteration < MaxIteration){ // While loop runs untill the counter reaches the maximum
		OldSol0 = Unknown[0];
		OldSol1 = Unknown[1];
		Unknown[0] = (RHS[0]- *(LHS+0*2+1) *Unknown[1])/ *(LHS+0*2+0);
		Unknown[1] = (RHS[1]- *(LHS+1*2+0) *Unknown[0])/ *(LHS+1*2+1);
		printf("%d, %lf, %lf \n", Iteration, Unknown[0], Unknown[1]);
		
		// Checking the convergence	
		if ( (100*fabs(OldSol0-Unknown[0])/Unknown[0] < 0.5) && (100*fabs(OldSol1-Unknown[1])/Unknown[1] < 0.5) ){
			printf("Convergence Reached. Terminating the sol. calculations \n");
			break;
		}

		Iteration++;	
	}	
}

