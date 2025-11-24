#include <stdio.h>
#include <math.h>

void NormalizeAndPrintTheWaveFunction(int N, double * X, double * zeta){
	double ModPsi2 = 0;
	double dx;
	for (int i = 0; i<N-1; i++){
		dx = (X[i+1] - X[i]);
		// Trapezoidal method
		ModPsi2 = ModPsi2 + 0.5*(zeta[i]*zeta[i] + zeta[i+1]*zeta[i+1])*dx;
	}
	printf("%lf \n", ModPsi2);
	for (int i = 0; i<N; i++){
		zeta[i] = zeta[i]/sqrt(ModPsi2);
	}

	for (int i = 0; i<N; i++) {
		printf("%lf %lf \n", X[i], zeta[i]);
	}
	
}

int main(){

	// Read File Contents 
	int MAX_ROWS = 56;
	FILE *file;
	double X[MAX_ROWS];
    	double zeta[MAX_ROWS];
    	int i = 0;

    	file = fopen("EV3.dat", "r");

    	if (file == NULL) {
        	printf("Error: Could not open file.\n");
        	return 1;
    	}	

    	// Read two doubles per line
    	while (i < MAX_ROWS) {
		fscanf(file, "%lf %lf", &X[i], &zeta[i]); 
        	i++;
    	}
	
	NormalizeAndPrintTheWaveFunction(MAX_ROWS, X, zeta);

	return(0);
}
