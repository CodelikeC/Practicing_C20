#include <iostream> 
using namespace std ; 
#include <algorithm> 
#include <iterator> 
#include <system_error>
#include <cerrno>
#include <fstream> 
#include <ranges>

// generic_catefory() : system_error, message() : cerrno 
int main ()
{
    ifstream in {"list1401.in"};
    // tao mot file ten list 1401.in // 
    if (not in)
    {
        cerr <<"List1401:" << endl; // list 1401  
        cerr << generic_category().message(errno) << endl;
        // error category for error code .. //  
    } 
    else 
    {
        ranges :: copy(ranges :: istream_view<int>(in), ostream_iterator<int> {cout, "\n" });
        in.close(); 
    }
    return 0; 
}