#include <stdio.h>

void SelfConsistentSolution (double * Unknown, double * RHS, double * LHS){
	int Iteration = 0;
	int MaxIteration = 10;
	double OldSol0, OldSol1;
	double Tolerance = 0.01;

	Unknown[0] = 0;
	Unknown[1] = 0;
	
	// Perform while loop provided the iteration count is less than the MaxIteration
	while(Iteration < MaxIteration){
		// Initializing the old solution that will be used to calculate the error	
		OldSol0 = Unknown[0];
		OldSol1 = Unknown[1];

		// Solve the system of equation
		// Write the unknowns as discussed in the class
		Unknown[0] = 

		// Convergence Check by calculating the approximate relative error 
		// Include the check for the second variable as well
		if( fabs((OldSol0 - Unknown[0])/Unknown[0]< Tolerance)){
			break;
		}
		
		// Incrementing the iteration count
		Iteration++;
	}
}

// Start of the Program
int main(){
// Declarations and Initializations
double Unknowns[2];
// The Left hand side Matrix
double LHS[2][2] = {{2, 1},
			{1,2 }};
// The right hand side vector
double RHS[2] = {8, 1};
// Calling the function to do find the self-consistent solution.
SelfConsistentSolution(Unknowns, RHS, (double *) LHS);

}


