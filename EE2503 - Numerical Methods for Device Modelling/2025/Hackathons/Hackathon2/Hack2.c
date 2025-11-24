#include <stdio.h>
#include <math.h>

#define SIZE 3
#define DATALEN 26 

void PrintMatrix(double mat[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%8.4f ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n \n");
}

void PrintVector(double vec[SIZE]){
    for (int j = 0; j < SIZE; j++) {
        printf("%8.4f ",vec[j]);
    }
    printf("\n");
    printf("\n");
    printf("\n");


}

void MatrixInverseCalculation(double mat[SIZE][SIZE], double inverse[SIZE][SIZE]) {
    double aug[SIZE][2 * SIZE];
    double pivot, factor;
    // Step 1: Form the augmented matrix [A | I]
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            aug[i][j] = mat[i][j];
            aug[i][j + SIZE] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Step 2: Gauss-Jordan elimination
    for (int i = 0; i < SIZE; i++) {
        pivot = aug[i][i];

        // Normalize the pivot row
        for (int j = 0; j < 2 * SIZE; j++)
            aug[i][j] /= pivot;

        // Eliminate other entries in current column
        for (int k = 0; k < SIZE; k++) {
            if (k == i) continue;
            factor = aug[k][i];
            for (int j = 0; j < 2 * SIZE; j++)
                aug[k][j] -= factor * aug[i][j];
        }
    }

    // Extract inverse from augmented matrix
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            inverse[i][j] = aug[i][j + SIZE];

}
void SetupLHS(double matrix[SIZE][SIZE], double WaveVector[DATALEN]){

    for (int i = 0 ; i < SIZE ; i++){
        for (int j = 0 ; j < SIZE ; j++){
	    for (int k = 0; k < DATALEN ; k++){
                matrix[i][j] = matrix[i][j] + pow(WaveVector[k], i+j);
    	    }
        }
    }
}

void SetupRHS(double LHS[SIZE], double Energy[DATALEN], double WaveVector[DATALEN]){

    for (int i = 0 ; i < SIZE ; i++){
        for (int k = 0 ; k < DATALEN ; k++){
            LHS[i] = LHS[i] + Energy[k]*pow(WaveVector[k],i);
        }
    }
}
void MatVecMul(double inverse[SIZE][SIZE], double RHS[SIZE], double COEFFS[SIZE]){

    for (int i = 0; i < SIZE; i++){
	for (int j = 0; j< SIZE; j++){
	    COEFFS[i] += inverse[i][j]*RHS[j];
	}
    }

}

int main() {
    double hbar = 1.054E-34;
    double m0 = 9.1E-31;
    double q = 1.6E-19;
    double nm2m = 1E-9;
    double meff;
    double matrix[SIZE][SIZE];
    double inverse[SIZE][SIZE];
    double RHS[SIZE];
    double COEFFS[SIZE];
    // Energy is in eV
    double Energy [] = {1.13682,1.13658,1.13468,1.13236,1.13418,1.13317,1.13132,1.13041,1.13026,1.13132,1.13293,1.13173,1.13102,1.13331,1.13406,1.13303,1.13225,1.13279,1.13425,1.13785,1.13727,1.13766,1.14038,1.14026,1.1442,1.14458};
    // k is the wavevector in 1/nm
    double WaveVector[] = {9.0256,9.0641,9.1027,9.1413,9.1799,9.2184,9.257,9.2956,9.3341,9.3727,9.4113,9.4498,9.4884,9.527,9.5656,9.6041,9.6427,9.6813,9.7198,9.7584,9.797,9.8356,9.8741,9.9127,9.9513,9.9898};

    SetupRHS(RHS, Energy, WaveVector);
    SetupLHS(matrix, WaveVector);

    MatrixInverseCalculation(matrix, inverse);
    MatVecMul(inverse, RHS, COEFFS);

    //E = a0 + a1k + a2k^2
    // The dimensions of a2 is eV nm^2
    // The factor q*nm*nm is to convert it into SI units 
    // The factor (1/m0) converts the effective mass from kg to the units of m0
    meff = (1/m0)*(hbar*hbar)/(2*COEFFS[SIZE-1]*q*nm2m*nm2m);
    
    printf("The effective mass in the units of m0 is %lf \n", meff);

    return 0;
}


