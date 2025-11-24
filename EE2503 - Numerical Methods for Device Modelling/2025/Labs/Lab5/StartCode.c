#include <stdio.h>
#include <math.h>

int main(){
	int NoOfRows, NoOfCols;
	NoOfRows = 840;
	NoOfCols = 840;
	double A[NoOfRows][NoOfCols+1]; // Augmented Matrix
	FILE *file;
    	file = fopen("SystemOfEquation.csv", "r");

    	if (file == NULL) {
        	printf("Error: Could not open file.\n");
        	return 1;
    	}	

	for (int r = 0;r<NoOfRows; r++) {
		for (int c = 0; c<NoOfCols+1; c++){
			fscanf(file, "%lf", &A[r][c]); 
		} 
	} 
	for (int r = 0;r<NoOfRows; r++) {
		for (int c = 0; c<NoOfCols+1; c++){
			printf("%.5e ", A[r][c]);
		} 
		printf("\n");
	} 





	return(0);

}
