// dpl.fxlms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fftw3.h>
// #include <iostream>

	/*
	 * Compile with the following arguments:
	 *      gcc fftw3_r2c_usage.c -o fftw3_r2c_usage -lfftw3 -lm
	 *
	 * Make sure that you installed fftw3 in your machine first.
	 */

int main(int argc, char* argv[])
{
	int N = 8;
	
	double in[] = { 1, 0, -1, 0, 1, 0, -1, 0 };	/* Example input */

	fftw_complex* out; /* the output */
	fftw_plan p; /* the plan */

	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (N / 2 + 1) );

	/*
	 * An fftw plan cares only about the size of in and out,
	 * not about actual values. Can (and should) be re-used.
	 * Daniel: How to reuse when in and out are part of the definition?
	 */
	p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
	
	/*
	 * Execute the dft as indicated by the plan
	 */
	fftw_execute(p);

	/*
	 * Print the N/2+1 complex values computed by the DFT function.
	 */
	for (int i = 0; i < N / 2 + 1; i++) {
		printf("out[%d] = %f i%f\n", i, out[i][0], out[i][1]);
	}

	/*
	 * Clean routine
	 */
	fftw_destroy_plan(p); 
	fftw_free(out);

	return 1;
}


// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
