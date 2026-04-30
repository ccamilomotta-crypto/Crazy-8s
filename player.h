// provided. do not modify. do not submit.
#ifndef PROVIDED_PLAYER_H_
#define PROVIDED_PLAYER_H_

#include <cstddef>
#include <string>
#include <vector>
#include "card.h"

class Player {
    bool is_AI;
    std::vector<Card*> hand;

 public:
    /**
     * Construct a new instance of `Player`.
     *
     * @param is_AI whether the player is a bot (`true`) or human (`false`)
     */
    explicit Player(bool is_AI);

    /**
     * Add a card to the player's hand.
     *
     * @param card a pointer to the card.
     */
    void AddToHand(Card* card);

    /**
     * The number of cards in the player's hand.
     */
    std::size_t GetHandSize();

    /**
     * The player's hand as a string.
     */
    std::string GetHandString();

    /**
     * Choose a card to play from the player's hand.
     * Remove and return it.
     *
     * @param active_rank the rank of the active card.
     * @param active_suit the suit of the active card.
     * @returns a pointer to the card chosen to play.
     */
    Card* PlayCard(
        std::string const& active_rank,
        std::string const& active_suit);

    /**
     * Choose the next suit to declare after playing an 8.
     *
     * @param suits the suits in the deck.
     * @param suit the suit of the 8.
     * @returns the next suit to declare.
     */
    std::string NextSuit(
        std::vector<std::string> const& suits,
        std::string const& suit);
};

#endif  // PROVIDED_PLAYER_H_
