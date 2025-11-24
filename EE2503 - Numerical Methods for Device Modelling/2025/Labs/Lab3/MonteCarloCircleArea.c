#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool LiesInsideCircle(double x, double y){
	bool TrueOrFalse = false; 
	
	if (x*x + y*y < 1){
		TrueOrFalse = true;
	}

	return (TrueOrFalse);
}

int main(){
	int N = 100000;
	int CounterCircle = 0;
	double AreaOfSquare = 1;
	double AreaOfCircle;
	double x, y;
	srand(time(NULL));
	
	for (int i = 0;i<N;i++){
		x = (double) rand()/(double)RAND_MAX;
		y = (double) rand()/(double)RAND_MAX;

		if (LiesInsideCircle(x,y)){
			CounterCircle++;
		}		
	
	}
	
	AreaOfCircle = 4*AreaOfSquare*CounterCircle/N;
	printf("Area of the Circle is %lf \n", AreaOfCircle);
}
