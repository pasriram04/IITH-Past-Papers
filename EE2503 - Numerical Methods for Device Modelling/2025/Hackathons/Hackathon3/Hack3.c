#include <stdio.h>
#include <math.h>

# define q 1.6E-19
# define kB 1.38E-23 
# define Nc_300 3E25
# define Nv_300 1E25
# define ND 1E22
# define EcMinusEd 0.05 
# define Bandgap 1.0

double Residual(double T, double n){
	double T1, T2, T3;
	double F;
	double kBT = kB*T;
	double Nc, Nv;
	Nc = Nc_300*pow((T/300.0),1.5);	
	Nv = Nv_300*pow((T/300.0),1.5);	

	T1 = ND*Nc/(Nc + 2.0*n*exp(q*EcMinusEd/kBT));
	T2 = (Nc*Nv/n)*exp(-q*Bandgap/kBT);
	T3 = -n;

	F = T1+T2+T3;

	return(F);
}

double SecantMethodSolver(double n){
	double Resi, Resi_dT, Derivative;
	double T = 300.0;
	double deltaT;
	int MaxIterations = 500;
	int counter = 0;

	while (counter < MaxIterations){
		deltaT = 0.1;
		Resi = Residual(T, n); 
		Resi_dT = Residual(T + deltaT, n); 
		Derivative = (Resi_dT-Resi)/deltaT;
		T = T - 1*Resi/Derivative; 
		
		printf("%d %lf %.5e\n", counter, T, Resi/Derivative);
		
		if (fabs(Resi/Derivative) < 0.5){
			break;
			printf("Convergence Reached \n");
		}

		counter++;
	}

	return(T);
}

int main(){
	double n = 10*ND;
	double Temp;
	Temp = SecantMethodSolver(n);

	return(0);
}
