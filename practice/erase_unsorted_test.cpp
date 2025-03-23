#include <iostream> 
#include <string> 
#include <algorithm> 
#include <initializer_list>
#include <iterator> 
#include <ranges> 
#include <vector> 

using namespace std; 

template <class Container> 
void erase_unsorted(Container &cont)
{
    auto prev {cont.end()}; 
    auto next{cont.begin()};
    while (next != cont.end())
    {
        if (prev != cont.end() and *next < *prev)
        next = cont.erase(next); 
        else 
        {
            prev = next; 
            ++next; 
        }
    }
}

template<class Container> 
requires std :: ranges :: range <Container> 

void print(string const &label, Container const &container)
{
    cout << label ; 
    using value_type = std:: ranges :: range_value_t<Container>; 
    std :: ranges :: copy(container, ostream_iterator <value_type> (cout, ""));
    cout << endl ;  
}

// test erase unsorted by extracting intergers from a string 
// into a container and calling erase unsorted, Print the container.. // 
void test(initializer_list<int> numbers)
{
    vector<int> data{numbers}; 
    erase_unsorted(data); 
    if (not std :: is_sorted (data.begin(), data.end()))
    print("Failed ", data); 
}

int main ()
{
    test({2, 3,7, 11, 13, 17, 23, 29, 31, 37}); 
    test({37 , 31,29, 23, 17, 13, 11, 7, 3, 2});
    test({});
    test({42});
    test({10,20,30,40,0, 50});
}
 