#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "game.h"

using std::string, std::vector;

void Game::LoadDeckFromFile(string const& filename) {
    // TODO(student) initialize suits, deck, and draw_pile from the given file
    std::ifstream ifs(filename);
    if(!ifs.is_open()){
        throw std::runtime_error("could not open file");
    }
    suits.clear();
    deck.clear();
    draw_pile.clear();
    discard_pile.clear();
    string line;
    while(std::getline(ifs,line)){
        std::istringstream iss(line);
        string rank;
        string suit;
        string extra;
        if(!(iss>>rank>>suit)||(iss>>extra)){
            throw std::runtime_error("invalid file format");
        }
        Card* card=nullptr;
        try{
            card=new Card(rank,suit);
        }catch (std::invalid_argument const&){
            throw std::runtime_error("invalid file format");
        }
        deck.push_back(card);
        draw_pile.insert(draw_pile.begin(),card);

        bool found=false;
        for(std::size_t i=0;i<suits.size();++i){
            if(suits.at(i)==suit){
                found=true;
                break;
            }
        }
        if(!found){
            suits.push_back(suit);
        }}}

void Game::AddPlayer(bool is_AI) {
    // TODO(student) add a new player to the game
    players.push_back(new Player(is_AI));
}

void Game::DrawCard(Player* player) {
    // TODO(student) Move the top card of the draw pile to the Player's hand
    // If the draw pile is empty, flip the discard pile to create a new one
    if(draw_pile.empty()){
        if(discard_pile.size()<=1){
            throw std::runtime_error("cannot draw card");
        }
        std::cout<<"Draw pile empty, flipping the discard pile."<<std::endl;

        Card* top_discard=discard_pile.back();
        for(std::size_t i=discard_pile.size()-1;i>0;--i){
            draw_pile.push_back(discard_pile.at(i-1));
        }
        discard_pile.clear();
        discard_pile.push_back(top_discard);
    }

    player->AddToHand(draw_pile.back());
    draw_pile.pop_back();
}

Card* Game::Deal(size_t num_cards) {
    // TODO(student) Flip the top card of the draw pile as the initial discard
    // then deal num_cards many cards to each player
    Card* initial_card = draw_pile.back();
    draw_pile.pop_back();
    discard_pile.push_back(initial_card);
    for(size_t card_num=0;card_num<num_cards;++card_num){
        for(size_t player_num=0;player_num<players.size();++player_num){
            DrawCard(players.at(player_num));
        }
    }
    return initial_card;
}

string Game::MostPlayedSuit() {
    // TODO(student) Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
    string most_played="";
    std::size_t max_count=0;
    for(std::size_t i=0;i<suits.size();++i){
        std::size_t current_count=0;
        for(std::size_t j=0;j<deck.size();++j){
            if(deck.at(j)->suit()==suits.at(i)){
                current_count += deck.at(j)->times_played();
            }}

        if(i==0||current_count>max_count){
            max_count=current_count;
            most_played=suits.at(i);
        }}

    return most_played;
}

int Game::RunGame() {
    // TODO(student) Run the game and return the number of the winning player
    string current_rank=discard_pile.back()->rank();
    string current_suit =discard_pile.back()->suit();

    std::size_t player_turn =0;
    while(true){
        std::cout<<"Player "<<player_turn<<"'s turn!" << std::endl;
        Card* played_card =players.at(player_turn)->PlayCard(current_rank, current_suit);
        if(played_card==nullptr){
            try{
                DrawCard(players.at(player_turn));
                std::cout<<"Player "<<player_turn<<" draws a card."<<std::endl;
            }catch(std::runtime_error const&){
                std::cout<<"Player "<<player_turn<<" cannot draw a card."<<std::endl;
                return -1;
            }
        }else{
            discard_pile.push_back(played_card);

            if(played_card->rank()=="8"){
                string declared_suit=players.at(player_turn)->NextSuit(suits, played_card->suit());
                std::cout<<"Player "<<player_turn <<" plays " <<*played_card<<" and changes the suit to " <<declared_suit <<"."<<std::endl;
                current_rank =played_card->rank();
                current_suit =declared_suit;
            }else{
                std::cout <<"Player "<<player_turn <<" plays "<<*played_card <<"." << std::endl;
                current_rank =played_card->rank();
                current_suit =played_card->suit();
            }
            if(players.at(player_turn)->GetHandSize() ==0){
                return static_cast<int>(player_turn);
            }
        }

        player_turn =(player_turn+1)%players.size();
    }}
