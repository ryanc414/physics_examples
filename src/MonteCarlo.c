#include <stdio.h>
#include <cmath>
#include <gsl/gsl_rng.h>
/* Perform 8-dimensional integral using Monte-Carlo methods */


double[8] generate_random_point()
{
    return 2
:}


double IntEst(int N, gsl_rng*& rng)
{
    double pi = 3.14159265359;
    double s = pi/8;
    double V = pow(s,8);
    double fsum = 0.0;
    std::vector<double> r(8);
    double result;

    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<8; j++)
	    {
	        //generate random points in 8D space within integration limits
            point[j] = s * gsl_rng_uniform(rng);
	    }
        fsum += sin(r[0]+r[1]+r[2]+r[3]+r[4]+r[5]+r[6]+r[7]);
        //running total of intergrand
    }
result = fsum/N * V;
//fsum/N is the mean value of f; multiplying by V estimates the integral
return pow(10,6) * result;
}

int main()
{
 int nt = 25;
 int n = 7;
 double IntVal;
 double IntSum = 0;
 double SqSum = 0;
 int N;
 std::vector<double> mean(n);
 std::vector<double> error(n);

 gsl_rng* rng = gsl_rng_alloc( gsl_rng_default );
 
 for(int i = 0; i < n; i++)
   {
     N = pow(10,i+1);
     IntSum = 0;
     SqSum = 0;
     //initialise sums to 0 each iteration

     for(int j = 0; j < nt; j++)
       {
	 IntVal = IntEst(N,rng);
	 IntSum += IntVal;
	 SqSum += IntVal * IntVal;
	 //estimate integral and keep running sum of the estimates and squares
       }
     mean[i] = IntSum / nt;
     error[i] = sqrt(SqSum/nt - (IntSum/nt)*(IntSum/nt));
     //for each value of N output the mean and std dev into seperate arrays
   }

 for(int i = 0; i < n; i++)
   {
     std::cout << pow(10,i+1) << "\t" << i+1 << "\t" <<  mean[i] << "\t" << error[i] << "\t" << log10(error[i]) << "\n";
   }
 //outputs N, log(N), mean and error of integral, and log(error) seperated by tabs

 gsl_rng_free( rng );
 return 0;

}
