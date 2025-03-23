#include <iostream> 
using namespace std; 
#include <list> 

#include <algorithm> 
#include <ranges> 

export module A;

// hello() will be visible by transalation units improvement
export char const *hello()
{
    return "hello";
}

// world() will not be visible.. // 
char const *world()
{
    return "world";
}

export{
    int one()
    {
        return 1; 
    }
    int zero()
    {
        return 0; 
    }
}

// exporting namespaces also works.. 
export namespace hi 
{
    char const *english()
    {
        return "hi"; 
    }
    char const *french()
    {
        return "Salut"; 
    }
}

// exporting classes also works..
export class A
{
    public :
    A()
    {
        cout <<"A is a function" << endl; 
    }
    void print()
    {
        cout << "A : print()" << endl;
    }
}; 

// exporting functions also works.. 
export void print()
{
    cout <<"Print()" << endl;
}

// variabels can also be exported.. // 
export int x = 10  ;

int main ()
{
    cout << "Main" << endl; 
    cout << hello() << endl; 
    cout << world() << endl;
    cout << one() << endl; 
    cout << zero() << endl;
    cout << hi :: english() << endl; 
    cout << hi :: french() << endl; 
    A a ; 
    a.print();
    print();
    cout << x << endl; // 10 
    return 0; 
}