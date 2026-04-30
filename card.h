// provided. do not modify. do not submit.
#ifndef PROVIDED_CARD_H_
#define PROVIDED_CARD_H_

#include <cstddef>
#include <iostream>
#include <string>

class Card {
    std::string rank_;
    std::string suit_;
    std::size_t times_played_;

 public:
    /**
     * Construct a new instance of `Card`.
     *
     * @param rank the rank of the card, e.g. Ace.
     * @param suit the suit of the card, e.g. Spades.
     * @throws `std::invalid_argument` if `rank` or `suit` are empty.
     * or contain non-alphanumeric characters.
     */
    Card(std::string rank, std::string suit);

    /**
     * The rank of the card.
     */
    std::string rank() const;

    /**
     * The suit of the card.
     */
    std::string suit() const;

    /**
     * The number of times the card has been played.
     */
    std::size_t times_played() const;

    /**
     * Whether the card can be played.
     *
     * @param rank the rank of the active card.
     * @param suit the suit of the active card.
     * @returns `true` if this card can be played on the active card.
     */
    bool CanBePlayed(std::string const& rank, std::string const& suit) const;

    /**
     * @brief Play the card.
     *
     * Increment the number of times the card has been played.
     */
    void Play() { times_played_ += 1; }
};

/**
 * Insert a `Card` into an output stream.
 *
 * @param os the output stream.
 * @param card the `Card`.
 * @returns the updated output stream.
 */
std::ostream& operator<<(std::ostream& os, Card const& card);

#endif  // PROVIDED_CARD_H_
