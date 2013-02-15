
#include <math.h>

//double execute( double &a, double &b) {
//
//   a=a*cos(b);
//
//    return a+b;
//}

void func1( double *a, double b) {
    
    for(int i=0; i<64; i++) {
        a[i]=b;
    }
}

void func2( double *a, double b) {
    
    for(int i=0; i<64; i++) {
        a[i]+=b;
    }
}


double execute() {

    double a[64];
    
    func1(a, 10.0);
    func2(a, 20.0);

    return a[50];
}


