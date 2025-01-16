#pragma once
#include <stdint.h>
#include <stddef.h>

/**
 * @brief A linked-list node type of object that holds playing card data
 */
typedef struct Card_t Card_t;
struct Card_t
{
    uint8_t data;
    Card_t *next;
};

/**
 * @brief A linked-list type of object that represents a deck of cards
 */
typedef struct Deck_t Deck_t;
struct Deck_t
{
    Card_t *head;
    size_t len;
};

/**
 * @brief Creates a new empty deck of cards
 * 
 * @return Deck_t* Pointer to new deck if creation was successful.
 * @return NULL if allocation was unsuccessful.
 */
Deck_t * init_empty_deck();

/**
 * @brief Creates a new full (52 cards) deck of cards 
 * 
 * @return Deck_t* Pointer to new deck if creation was successful.
 * @return NULL if allocation was unsuccessful.
 */
Deck_t * init_full_deck();

/**
 * @brief Adds card to the head of a deck
 * 
 * @param d Pointer to deck
 * @param c Pointer to card
 */
void addh_card(Deck_t *d, Card_t *c);

/**
 * @brief Adds card to the tail of a deck
 * 
 * @param d Pointer to deck
 * @param c Pointer to card
 */
void addt_card(Deck_t *d, Card_t *c);

/**
 * @brief Draws the nth card from a deck
 * 
 * @param d Pointer to deck
 * @param n The place to draw card from
 * @return Card_t* Pointer to the card.
 * @return NULL if n is bigger than the size of d
 */
Card_t * draw_at(Deck_t *d, size_t n);

/**
 * @brief Draws the top card from a deck
 * 
 * @param d Pointer to deck
 * @return Card_t* Pointer to the card.
 * @return NULL if deck is empty
 */
Card_t * draw_top(Deck_t *d);

/**
 * @brief Prints a deck of cards to stdout
 * 
 * @param d Pointer to deck
 */
void print_deck(Deck_t *d);

/**
 * @brief Prints the n first cards in a deck
 * 
 * @param d Pointer to deck
 * @param n Number of cards to print
 */
void nprint_deck(Deck_t *d, size_t n);

/**
 * @brief Frees all allocated memory by a deck of cards
 * 
 * @param d Pointer to deck
 */
void free_deck(Deck_t *d);