#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "player.h"

using std::vector, std::string, std::size_t;

// TODO(student) Initialize attributes
Player::Player(bool is_AI):is_AI{is_AI},hand{}{}

void Player::AddToHand(Card* c) {
    // TODO(student) Add the card c to the player's hand
    hand.push_back(c);
}

size_t Player::GetHandSize() {
    // TODO(student) Implement getter
    return hand.size();
}

std::string Player::GetHandString() {
    // TODO(student) Implement getter
    std::ostringstream oss;

    for(size_t i=0;i<hand.size();++i){
        oss<<*hand.at(i);
        if(i+1<hand.size()){oss<<", ";
        }
    }

    return oss.str();
}

Card* Player::PlayCard(string const& active_rank, string const& active_suit) {
    // TODO(student) Choose a card to play and return the chosen card.
    if(is_AI){
        for(size_t i=0;i<hand.size();++i){
            if(hand.at(i)->CanBePlayed(active_rank, active_suit)){
                Card* chosen=hand.at(i);
                chosen->Play();
                hand.erase(hand.begin()+i);
                return chosen;
            }
        }
        return nullptr;
    }

    std::cout<<"Your hand contains: "<< GetHandString()<< "." << std::endl;
    std::cout<< "The next card played must be a "<<active_rank<<" or "<<active_suit<<"." << std::endl;
    std::cout<<"What would you like to play? (enter \"draw card\" to draw a card)"<<std::endl;

    string line;
    while(std::getline(std::cin,line)){
        if(line=="draw card"){
            return nullptr;
        }
        std::istringstream iss(line);
        string rank;
        string suit;
        string extra;
        iss>>rank>>suit>>extra;
        bool found =false;
        size_t index =0;

        if(!rank.empty()&&!suit.empty()&&extra.empty()){
            for(size_t i=0;i<hand.size();++i){
                if(hand.at(i)->rank()==rank&&hand.at(i)->suit()==suit){
                    found=true;
                    index=i;
                    break;
                }}}

        if(!found){
            std::cout<<"That's not a card you have. Try again."<<std::endl;
            continue;
        }

        if(!hand.at(index)->CanBePlayed(active_rank,active_suit)){
            std::cout<<"You can't play that card. Try again."<<std::endl;
            continue;
        }
        Card* chosen=hand.at(index);
        chosen->Play();
        hand.erase(hand.begin()+index);
        return chosen;
    }

    return nullptr;
}

std::string Player::NextSuit(vector<string> const& suits, string const& suit) {
    // TODO(student) Choose the next suit (after playing an 8)
    if(is_AI){
        return suit;
    }

    std::cout<<"What suit would you like to declare?"<<std::endl;

    string line;
    while(std::getline(std::cin,line)){
        for(size_t i=0;i<suits.size();++i){
            if(suits.at(i)==line){
                return line;
            }}
        std::cout<<"That's not a suit in this deck. Try again."<<std::endl;
    }

    return suit;
}
