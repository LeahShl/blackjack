#include <stdint.h>
#include <stddef.h>

const uint8_t CARD_A = 0x10;
const uint8_t CARD_2 = 0x20;
const uint8_t CARD_3 = 0x30;
const uint8_t CARD_4 = 0x40;
const uint8_t CARD_5 = 0x50;
const uint8_t CARD_6 = 0x60;
const uint8_t CARD_7 = 0x70;
const uint8_t CARD_8 = 0x80;
const uint8_t CARD_9 = 0x90;
const uint8_t CARD_10 = 0xA0;
const uint8_t CARD_J = 0xB0;
const uint8_t CARD_Q = 0xC0;
const uint8_t CARD_K = 0xD0;

const uint8_t HEARTS = 0x01;
const uint8_t CLUBS = 0x02;
const uint8_t DIAMOND = 0x04;
const uint8_t SPADES = 0x08;

typedef struct Card_t Card_t;
struct Card_t
{
    uint8_t data;
    Card_t *next;
};

typedef struct Deck_t Deck_t;
struct Deck_t
{
    Card_t *head;
    size_t len;
};

/**
 * Initializes an empty deck
 */
Deck_t * init_empty_deck(){
    Deck_t *d = {0};
    d->head = NULL;
    d->len = 0;
    return d;
}

/**
 * Initializes a full deck of 52 cards
 */
Deck_t * init_full_deck(){
    Deck_t *d = init_empty_deck();
    for(uint8_t suit = 0x01; suit <= 0x08; suit *= 0x02){
        for(uint8_t rank = 0x10; rank <= 0xD0; rank += 0x10){
            // TODO: finish after addh_card
        }
    }
    return d;
}

/**
 * Selects the nth card from deck d.
 */
Card_t * draw_at(Deck_t *d, int n);

/**
 * Selects the card at the top of deck d.
 */
Card_t * draw_top(Deck_t *d);

/**
 * Adds card c to the top of deck d.
 */
void addh_card(Deck_t *d, Card_t *c);

/**
 * Adds cards c to the tail of deck d.
 */
void addt_card(Deck_t *d, Card_t *c);

/**
 * Copies a string representation of card c into char array dest.
 * dest needs to point to a char[] with a size of at least 3.
 * 
 */
void card_to_str(Card_t *c, char *dest);

/**
 * Prints an entire deck to stdout
 */
void print_deck(Deck_t *d);

/**
 * Frees the allocated memory for deck d.
 */
void free_deck(Deck_t *d);