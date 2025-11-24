#include <stdio.h>
#include <math.h>

# define q 1.6E-19
# define kB 1.38E-23 
# define Nc_300 3E25
# define Nv_300 1E25
# define ND 1E22
# define EcMinusEd 0.05 
# define Bandgap 1.0


int main(){
	double Temperature = 300.0; //K
	
	printf("Temperature = %lf K \n",Temperature);
	return(0);
}
