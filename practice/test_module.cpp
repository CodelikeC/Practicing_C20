module;

#define _POSIX_C_SOURCE 2000809L
#include <stdlib.h>
#include <iostream> 
#include <ctime> 
using namespace std; 

export double weak_random()
{
    timespec ts; 
    timespec_get (&ts, TIME_UTC); 
    srand(ts.tv_nsec);  

    return double(rand() %100)/ RAND_MAX; 
}; 

int main ()
{
    cout << "random numeber:" << weak_random() << endl;
    return 0 ;
}