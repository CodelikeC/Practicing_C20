#include <iostream>
using namespace std; 
#include <concepts> 
#include <iostream> 
#include <ranges> 
#include <vector>
#include <string> 
#include <algorithm>

template <class Range> 
concept can_reserve = 
ranges :: sized_range<Range> and requires(Range r)
{
    r.reserve(0);
};

template <class Container> 
concept can_insert_back = 
requires(Container c)
{
    back_inserter(c);
}; 

template <can_insert_back Container> 
class store_t 
{
    public: 
    using container_type = Container; 
    using value_type = ranges :: range_value_t <container_type> ; 
    store_t(container_type &output) : output_{output}{}

    template <can_reserve Range> 
    Container& operator() (Range const &input) const 
    {
    output_.reserve(std :: ranges :: size(output_) + std:: ranges :: size(input));
    std ::ranges :: copy(input, std:: back_inserter(output_));
    return output_; 
    }

    private: 
    container_type &output_; 
}; 

template <class T> 
store_t <T> store (T &container) 
{
    return store_t <T> (container); 
}

template<class Ln, class Out> 
Out &operator|(Ln range, store_t <Out> const &storer)
{
    return storer(std ::forward<Ln> (range)); 
}

int main ()
{
    cout <<"Store function template" << endl; 
    vector <string> strings {"this", "is", "a","test", "\n"};
    string str; 
    std ::ranges :: views :: join(strings) | store(str); 
    cout << str ; 
    return 0; 
}



