#include <iostream> 
using namespace std; 
#include <future>
#include <iosfwd> 
#include <array> 
#include <algorithm>
#include <ranges> 
#include <random> 

#include <deque>
// represent a standard western playing card . . //

export class card
{
    public: 
    using suit = char;
    static constexpr suit const spades {4}; 
    static constexpr suit const hearts {3}; 
    static constexpr suit const clubs  {2};
    static constexpr suit const diamonds {1}; 

    using rank = char ;
    static constexpr rank const ace {14}; 
    static constexpr rank const king {13}; 
    static constexpr rank const queen {12}; 
    static constexpr rank const jack {11}; 

    const void assign (rank r, suit s); 
    constexpr card() : rank_{0}, suit_{0} {}
    constexpr card (rank r  , suit s) : rank_{r}, suit_{s} {}
    constexpr suit get_suit() const 
    {
        return suit_; 
    }

    constexpr suit get_rank() const 
    {
        return rank_; 
    }

    private : 
    rank rank_; 
    suit suit_;
}; 

export bool operator==(card a, card b ); 
export bool operator!=(card a, card b); 
export std ::ostream &operator<<(ostream &out, card c); 
export std ::istream &operator>>(istream &in, card &c); 

export bool acehigh_less(card a, card b); 
export bool acelow_less(card a , card b); 

export class card_generator
{
    public: 
    card_generator();
    card operator()(); 

    private: 
    card card_; 
}; 

export class randomint
{
    public : 
    using result_type  = default_random_engine:: result_type; 
    random_device random_device_;

    randomint(result_type low, result_type high)
        : dist_{low, high}, re_{random_device_()}
    {}

    result_type operator()()
    {
        return dist_(re_);
    }

    private:
    uniform_int_distribution<result_type> dist_;
    default_random_engine re_;
}; 


int main ()
{
    deque<card> deck(52); 
    ranges :: generate(deck, card_generator{});
    for (int i {0}; i != 10 ; ++i)
    {
        auto pick
        {
            deck.begin() + randomint{0, deck.size()-1}()
        }; 
        card computer_card{*pick};
        deck.erase(pick); 
        cout <<"I picked" << computer_card << endl; 
        pick = deck.begin() + randomint{0, deck.size() - 1}();
        card user_card{
            *pick
        } ; 
        deck.erase(pick); 
        cout << "You picked" << user_card << endl;
        if (acehigh_less(computer_card , user_card))
        cout << "You win" << endl; 
        else 
        cout <<" I win" << endl; 
    } 
    return 0 ; 
}