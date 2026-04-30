// provided. do not modify. do not submit.
#include <iostream>
#include <string>
#include "card.h"
#include "game.h"
#include "player.h"

using std::cin, std::cout, std::endl, std::string;

/**
 * Load a deck of cards into a game.
 * Prompt the user for a filename from which to load the deck.
 *
 * @param game the game into which to load the deck.
 * @returns `true` if the deck was loaded successfully, `false` otherwise.
 */
bool LoadDeck(Game& game) {
    string filename;
    cout << "Choose a file to load the deck from:" << endl;
    string line;
    getline(cin, filename);
    try {
        game.LoadDeckFromFile(filename);
    } catch (std::runtime_error const&) {
        cout << "The file was invalid. Aborting..." << endl;
        return false;
    }
    return true;
}

/**
 * Read a positive number from standard input.
 * Reprompt until success.
 * A positive number is strictly greater than 0.
 *
 * @returns a positive number.
 */
int ReadPositiveNumber() {
    int n;
    bool valid = false;
    while (!valid) {
        string line;
        getline(cin, line);
        try {
            n = stoi(line);
            valid = n > 0;
        } catch (...) {}
        if (!valid) {
            cout << "Please enter a positive number." << endl;
        }
    }
    return n;
}

/**
 * Get the number of players from the user.
 *
 * @returns the number of players.
 */
int GetPlayerCount() {
    cout << "Enter number of players:" << endl;
    return ReadPositiveNumber();
}

/**
 * Is `str` is one of `"y"` or `"n"`?
 */
bool y_or_n(const string& str) {
    return str.length() == 1 && (str == "y" || str == "n");
}

/**
 * Add players to a game.
 * Prompt the user for the type of the players.
 *
 * @param game the game to which to add players
 * @param num_players the number of players to add.
 */
void SetupPlayers(Game& game, int num_players) {
    for (int i = 0; i < num_players; i++) {
        cout << "Is player " << i << " an AI? (y/n)" << endl;
        string line;
        getline(cin, line);
        while (!y_or_n(line)) {
            cout << "Please enter y or n." << endl;
            getline(cin, line);
        }
        game.AddPlayer(line == "y");
    }
}

/**
 * Deal the initial hands to the players.
 *
 * @param game the game in which to deal cards.
 */
void SetupGame(Game& game) {
    cout << "How many cards should each player start with?" << endl;
    int num_cards = ReadPositiveNumber();

    Card* card = game.Deal(num_cards);
    cout << "The initial discard is " << *card << "." << endl;
}

/**
 * Create a game of Crazy 8s.
 * Load a deck.
 * Setup the players.
 * Deal the initial hands.
 * Run the game.
 * Report the winner and the most played suit.
 */
int main() {
    Game game;
    if (!LoadDeck(game)) {
        return 1;
    }
    int num_players = GetPlayerCount();
    SetupPlayers(game, num_players);
    try {
        SetupGame(game);
    } catch(...) {
        cout << "Too many cards dealt. Aborting..." << endl;
        return 1;
    }
    int winner = game.RunGame();
    if (winner != -1) {
        cout << "Player " << winner << " wins!" << endl;
    } else {
        cout << "The game is a draw!" << endl;
    }
    cout << "The most played suit was "
              << game.MostPlayedSuit() << "." << endl;
    return 0;
}
