#include <stdio.h>
#include <math.h>


double EstimateSmallestPositiveNumber(){
	double SmallestPositiveNumber = 1.0;
	while (SmallestPositiveNumber/2.0 > 0){
		SmallestPositiveNumber = SmallestPositiveNumber/2.0;
	}

	return (SmallestPositiveNumber);
}

int CalculateNumberOfTerms(){
	int counter = 1;
	double exponential = 1;
	double x = 1E-3;
	while (1){
		
		exponential = exponential*x/counter;
		counter++;
		if ( (1.0 + exponential*x/(counter+1)) == (1.0 + exponential) ){
			break;
		}
 
	}
	return (counter);
}

int main(){
	int NoOfTerms=0;
	double SmallestPositiveNumber = 0.0;

	SmallestPositiveNumber = EstimateSmallestPositiveNumber();
	NoOfTerms = CalculateNumberOfTerms();

	printf("Smallest Positive number is %.17e \n" , SmallestPositiveNumber);
	printf("Number of terms required in the evaluating the exponential function is %d \n" , NoOfTerms);



return(0);
}
