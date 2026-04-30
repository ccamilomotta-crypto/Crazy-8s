#include <stdexcept>
#include <string>
#include "card.h"

// TODO(student) Initialize attributes
Card::Card(std::string rank, std::string suit) : rank_{rank}, suit_{suit}, times_played_{0} {
    // TODO(student) Implement constructor checks
    if(rank.empty()||suit.empty()){
        throw std::invalid_argument("rank or suit is empty");
    }
    for(std::size_t i=0;i<rank.size();++i){
        char ch =rank.at(i);
        bool is_alnum =(ch >='a'&&ch<='z')||(ch >='A' &&ch<='Z')||(ch >='0'&&ch <='9');
        if(!is_alnum){
            throw std::invalid_argument("rank has non-alphanumeric characters");
        }}

    for(std::size_t i=0;i <suit.size();++i){
        char ch =suit.at(i);
        bool is_alnum =(ch>='a'&&ch<='z')||(ch >='A'&&ch<='Z')||(ch >='0'&&ch<='9');
        if(!is_alnum){
            throw std::invalid_argument("suit has non-alphanumeric characters");
        }}}

std::string Card::rank() const {
    // TODO(student) Implement getter
    return rank_;
}

std::string Card::suit() const {
    // TODO(student) Implement getter
    return suit_;
}

std::size_t Card::times_played() const {
    // TODO(student) Implement getter
    return times_played_;
}

bool Card::CanBePlayed(std::string const& rank, std::string const& suit) const {
    // TODO(student) Return whether or not this card can legally be played
    // given the previous card's rank and suit
    return rank_=="8"||rank_==rank||suit_==suit;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    return os<<card.rank()<<" "<<card.suit();
}
