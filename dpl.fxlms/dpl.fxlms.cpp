// dpl.fxlms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// #include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#define PI 3.1415926536

double AWGN_generator()
{
    /* Generates additive white Gaussian Noise samples with zero mean and a standard deviation of 1. */
    
    double temp1;
    double temp2;
    double result;
    int p;
    
    p = 1;
    
    while( p > 0 )
    {
        temp2 = ( rand() / ( (double)RAND_MAX ) ); /*  rand() function generates an
                                                    integer between 0 and  RAND_MAX,
                                                    which is defined in stdlib.h.
                                                    */
        if ( temp2 == 0 )
        {// temp2 is >= (RAND_MAX / 2)
            p = 1;
        }// end if
        else
        {// temp2 is < (RAND_MAX / 2)
            p = -1;
        }// end else
        
    }// end while()
    
    temp1 = cos( ( 2.0 * (double)PI ) * rand() / ( (double)RAND_MAX ) );
    result = sqrt( -2.0 * log( temp2 ) ) * temp1;
    
    return result;    // return the generated random sample to the caller
    
}// end AWGN_generator()

int main(int argc, char* argv[])
{
	int N = 8;
	
	double ref[] = { 1, 0, -1, 0, 1, 0, -1, 0 };    // reference signal
    double sHat[] = { 0,1,0,0,0,0,0,0 };
    
    fftw_complex* refOut;
    fftw_complex* sHatOut;
    fftw_complex* Fx;
    fftw_plan refPlan;
    fftw_plan sHatPlan;

	refOut = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (N / 2 + 1) );
    sHatOut = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (N / 2 + 1) );
    refPlan = fftw_plan_dft_r2c_1d(N, ref, refOut, FFTW_ESTIMATE);
    sHatPlan = fftw_plan_dft_r2c_1d(N, sHat, sHatOut, FFTW_ESTIMATE);
    
    fftw_execute(refPlan);
    fftw_execute(sHatPlan);

    for (int i = 0; i < N-1; i++ ){
        printf("test: %f %f", Fx[0][i] , Fx[1][i]); // = refOut[i] * sHatOut[i];
    }
    
	/*
	 * Print FFT Out
	 */
	for (int i = 0; i < N / 2 + 1; i++){
		printf("Fx[%d] = %f i%f\n", i, Fx[i][0], Fx[i][1]);
	}
    
	fftw_destroy_plan(refPlan);
    fftw_destroy_plan(sHatPlan);
	fftw_free(refOut);
    fftw_free(sHatOut);
    fftw_free(Fx);

	return 1;
}

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
