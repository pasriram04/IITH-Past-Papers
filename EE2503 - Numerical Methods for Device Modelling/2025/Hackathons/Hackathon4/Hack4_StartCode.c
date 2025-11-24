#include <stdio.h>
#include <stdlib.h>

#define N 533

void PrintResults(double InvArr[][N]){
	FILE *file;
	file = fopen("MatInv", "w");

	if (file == NULL){
		printf("ERROR: Could not open the file \n");
		exit(0);
	}
	for (int i = 0; i<N; i++){
		for (int j = 0; j<N; j++){
			fprintf(file,"%.5e ", InvArr[i][j]);	
		}
		fprintf(file,"\n");
	}
}

void ReadArray(double Arr[][N]){
	FILE *file;
	file = fopen("output", "r");
	if (file == NULL){
		printf("ERROR: Could not open the file \n");
		exit(0);
	}
	for (int i = 0; i<N; i++){
		for (int j = 0; j<N; j++){
			fscanf(file, "%lf", &Arr[i][j]);
			printf("%.5e ", Arr[i][j]);
		}
	}
	fclose(file);
}

int main(){
	double Arr[N][N];
	double InvArr[N][N];
	ReadArray(Arr);

	PrintResults(InvArr);
	return(0);
}
