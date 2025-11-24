#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define q 1.6E-19 
#define PI 3.1415
#define kBT 4.16E-21 
#define MaxIterations 10
#define STATS "MB" // Valid options FD or MB

double FermiDiracIntegral_1_2(double ymax, double ymin, double eta, int N){
	double F1_2, y, dy;
	int index;
	index = 0;
	F1_2 = 0;
	y = 0;
	dy = fabs(ymax-ymin)/N;
	while (index < N){
		F1_2 += (sqrt(y)/(1.0+exp(y + eta)))*dy;
		y += dy; 
		index++;
	}
	
	return(F1_2);
}

double CalculateElectronConc(double EcMinusEf, double Nc){
	double n, F1_2;
	double Emin = 0;
	double Emax = 5.0*q;
	int N = 1000;
	double Prefactor = Nc*2.0/sqrt(PI);

	F1_2 = FermiDiracIntegral_1_2(Emax/kBT, Emin/kBT, EcMinusEf/kBT, N);

	return(Prefactor*F1_2);

}
double CalculateHoleConc(double EcMinusEf, double Nv, double Bandgap){
	double p, F1_2;
	double Emin = -5.0*q;
	double Emax = 0;
	int N = 1000;
	double EvMinusEf = EcMinusEf-Bandgap;
	double Prefactor = Nv*2.0/sqrt(PI);
	F1_2 = FermiDiracIntegral_1_2(Emax/kBT, Emin/kBT, -EvMinusEf/kBT, N);	

	return(Prefactor*F1_2);
}

double ChargeNeutralityEquation(double EcMinusEf, double Nc, double Nv, double Bandgap, double ND){
	double n, p;
	if (STATS == "FD"){
		n = CalculateElectronConc(EcMinusEf, Nc);
		p = CalculateHoleConc(EcMinusEf, Nv, Bandgap);
	}
	else if (STATS == "MB"){
		n = Nc*exp(-EcMinusEf/kBT);
		p = Nv*exp((EcMinusEf-Bandgap)/kBT);
	}
	return(ND+p-n);
}

double ChargeNeutralityEquationDerivative(double EcMinusEf, double Nc, double Nv, double Bandgap, double ND){
	double Jacobian;
	double n, p;
	if (STATS == "FD"){
		n = CalculateElectronConc(EcMinusEf, Nc);
		p = CalculateHoleConc(EcMinusEf, Nv, Bandgap);
	}
	else if (STATS == "MB"){
		n = Nc*exp(-EcMinusEf/kBT);
		p = Nv*exp((EcMinusEf-Bandgap)/kBT);
	}
	
	return((1/kBT)*(n+p));
}

double BisectionMethod(double ND, double Nc, double Nv){
	int counter;
	double EcMinusEfLower = -3*q;
	double EcMinusEfUpper = 3*q;
	double EcMinusEfNew, DeltaE;
	double Resi, n , p;
	double Bandgap = 1.1*q;
	double ResiLower = ChargeNeutralityEquation(EcMinusEfLower, Nc, Nv, Bandgap, ND);
	double ResiUpper = ChargeNeutralityEquation(EcMinusEfUpper, Nc, Nv, Bandgap, ND);
	double Check = ResiLower*ResiUpper;

	if (Check < 0){
		printf("Solution lies between the initial guesses \n");
	}
	else {
		printf("Solution does not lie between the initial guesses. Terminating the run \n");
		exit(0);
	}
	
	counter = 0;
	printf("Iteration EcMinusEfNew/q n p\n");			
	while(counter < MaxIterations){
		ResiLower = ChargeNeutralityEquation(EcMinusEfLower, Nc, Nv, Bandgap, ND);
	        ResiUpper = ChargeNeutralityEquation(EcMinusEfUpper, Nc, Nv, Bandgap, ND);
		
		EcMinusEfNew = 0.5*(EcMinusEfLower + EcMinusEfUpper);
	        Resi = ChargeNeutralityEquation(EcMinusEfNew, Nc, Nv, Bandgap, ND);
		
		DeltaE = fabs(EcMinusEfNew - EcMinusEfUpper);	

		if (ResiLower*Resi < 0 ){
			EcMinusEfUpper = EcMinusEfNew;
		}
		else if (ResiUpper*Resi < 0 ) {
			EcMinusEfLower = EcMinusEfNew;
		}
		counter++;
		n = CalculateElectronConc(EcMinusEfNew, Nc);
		p = CalculateHoleConc(EcMinusEfNew, Nv, Bandgap);
		
		// Update the code with the Error check

		printf("%d %lf %.5e %.5e\n", counter, EcMinusEfNew/q, n, p);			
	}
	
	return(EcMinusEfNew);
}

double NewtonRaphsonMethod(double ND, double Nc, double Nv){
	int counter = 0;
	double f, fprime, Update, n, p;
	double EcMinusEf = 0*q;
	double Bandgap = 1.1*q;
	
	printf("Iteration EcMinusEf/q n p\n");				
	while (counter < MaxIterations){
		
		f = ChargeNeutralityEquation(EcMinusEf, Nc, Nv, Bandgap, ND);
		fprime = ChargeNeutralityEquationDerivative(EcMinusEf, Nc, Nv, Bandgap, ND);
			
		EcMinusEf = EcMinusEf - f/fprime;
		
		n = CalculateElectronConc(EcMinusEf, Nc);
		p = CalculateHoleConc(EcMinusEf, Nv, Bandgap);
		
		// Update the code with the Error check

		printf("%d %lf %.5e %.5e\n", counter, EcMinusEf/q, n, p);				
		counter++;
	}
	return(EcMinusEf);
}

int main(){
	double ND = 1E26;
	double Nc = 3E25;
	double Nv = 3E25;
	double EcMinusEf = 0;
	EcMinusEf = BisectionMethod(ND, Nc, Nv);
	
	EcMinusEf = NewtonRaphsonMethod(ND, Nc, Nv);

	printf("\nSummary %.5e %.5e %.5e \n",EcMinusEf, EcMinusEf/q, EcMinusEf/kBT);
}
