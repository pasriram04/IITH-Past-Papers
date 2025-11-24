#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(){
	double PI = 3.1416;
	double Aold, Anew, R;
	int Counter = 0;
	double Tolerance = 1.0/100.0;
	int MaxCounter = 100;
	int NumberOfSectors = 3;
	double Angle;
	Aold = 0;
	R = 0.5;	
	while(1 && Counter < MaxCounter){
		Angle = 2.0*PI/NumberOfSectors;
		Anew = NumberOfSectors*sin(Angle)*R*R/2.0;
		printf("%d %d %.5e %0.5e %.5e %.5e\n", Counter, NumberOfSectors, Aold, Anew, fabs((Aold - Anew)/Anew), Tolerance);

		if(fabs((Aold - Anew)/Anew) < Tolerance) {
			break;
		}
		Aold = Anew;
		NumberOfSectors++;
		Counter++;
	
	}
	
	printf("Area of the Circle is %lf \n", Anew);
}
