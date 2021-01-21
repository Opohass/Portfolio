#include <stdio.h>
extern double compute_approx(double (*f)(double), double (*fd)(double),double x0,
   double x);
extern double approx_range( double (*f)(double), double (*fd)(double),double x0,
double epsilon1, double epsilon2);


double f(double x)
{
  double fx;
  fx = 2.0*x*x + 5.0*x + 10.0;   //f(x) = 2x^2+5x+10 
  return fx;
} 

double fd(double x)
{
  double fdx;
  fdx = 4.0*x + 5.0;       //f'(x) = 4x+5
  return fdx;
} 

int main()
{
  double epsilon1, epsilon2, x_star, x0;
 epsilon1 = 0.0001;
 epsilon2 = 0.001;
 x0 = 1.0;
 x_star=  approx_range( f, fd, x0, epsilon1, epsilon2);
 printf("x0 = %lf, f(%lf)= %lf, epsilon1 = %lf, epsilon2 = %lf\n",
        x0, x0, f(x0), epsilon1, epsilon2);
 printf("x_star = %lf, approx = %lf\n", x_star, compute_approx(f, fd, x0,
x_star));
 
return 0;
} // main
