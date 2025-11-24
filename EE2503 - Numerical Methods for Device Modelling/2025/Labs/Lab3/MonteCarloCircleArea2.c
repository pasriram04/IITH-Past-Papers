#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

int main(){
	int N = 100000;
	int CounterCircle = 0;
	double AreaOfSquare = 1;
	double AreaOfCircle;
	double x, y, favg;
	srand(time(NULL));
	favg = 0.0;
	for (int i = 0;i<N;i++){
		x = (double) rand()/(double)RAND_MAX;
		
		favg = favg + sqrt(1-x*x);		

	
	}
	favg = favg/N;	
	AreaOfCircle = 4*(1-0)*favg;
	printf("Area of the Circle is %lf \n", AreaOfCircle);
}
