// provided. do not modify. do not submit.
#ifndef PROVIDED_GAME_H_
#define PROVIDED_GAME_H_

#include <cstddef>
#include <string>
#include <vector>
#include "player.h"
#include "card.h"

class Game {
    std::vector<Player*> players;
    std::vector<std::string> suits;
    std::vector<Card*> deck;
    std::vector<Card*> draw_pile;
    std::vector<Card*> discard_pile;

 public:
    /**
     * Construct a new instance of `Game` (Crazy 8s).
     * Initially, all attributes are empty.
     * Use methods to initialize attributes.
     */
    Game(): players{}, suits{}, deck{}, draw_pile{}, discard_pile{} {}

    /**
     * Load a deck of cards.
     *
     * @param filename path to file containing deck data.
     * @throws `std::runtime_error` if file cannot be opened.
     * @throws `std::runtime_error` if file format is invalid.
     */
    void LoadDeckFromFile(std::string const& filename);

    /**
     * Add a player to the game.
     *
     * @param is_AI whether the player is a bot (`true`) or human (`false`).
     */
    void AddPlayer(bool is_AI);

    /**
     * Draw a card into a player's hand.
     *
     * @param player a pointer to the player.
     * @throws `std::runtime_error` if the discard pile contains only one card.
     */
    void DrawCard(Player* player);

    /**
     * Discard the top card of the deck and
     * deal the given number of cards to each player.
     *
     * @param num_cards the number of cards to deal to each player.
     * @returns the initially discarded card.
     * @throws `std::runtime_error` if there are not enough cards.
     */
    Card* Deal(size_t num_cards);

    /**
     * The suit which has been played the most times.
     */
    std::string MostPlayedSuit();

    /**
     * Run the game.
     *
     * @returns the index of the winning player.
     */
    int RunGame();

    /**
     * Deallocate all cards and players.
     */
    ~Game() {
        for (Card* card : deck) {
            delete card;
        }
        for (Player* player : players) {
            delete player;
        }
    }
};

#endif  // PROVIDED_GAME_H_
