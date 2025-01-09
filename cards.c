#include <stdint.h>
#include <stddef.h>

// RANK CONSTS
const uint8_t R_MASK = 0xF0;
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

// SUIT CONSTS
const uint8_t S_MASK = 0x0F;
const uint8_t HEARTS = 0x01;
const uint8_t CLUBS = 0x02;
const uint8_t DIAMOND = 0x04;
const uint8_t SPADES = 0x08;

// STRUCT DEFINES
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

//////////////////////////////////
//            FUNCS             //
//////////////////////////////////

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
 * Adds card c to the top (head) of deck d.
 * Will override whatever next card c is pointing to.
 */
void addh_card(Deck_t *d, Card_t *c){
    c->next = d->head;
    d->head = c;
}

/**
 * Adds card c to the tail of deck d.
 */
void addt_card(Deck_t *d, Card_t *c){
    Card_t *p = d->head;
    for (size_t i = 0; i < d->len; i++)
    {
        p = p->next;
    }
    
}

/**
 * Copies a string representation of card c into string s.
 * dest needs to point to a char[] with a size of at least 6.
 */
/**
 * Creates a null-terminated string representing card c
 */
void card_str(Card_t *c, char *s){
    size_t i = 0;
    uint8_t rank = c->data & R_MASK;
    uint8_t suit = c->data & S_MASK;

    if (rank == CARD_A) {
        s[i++] = 'A';
    } else if (rank == CARD_2) {
        s[i++] = '2';
    } else if (rank == CARD_3) {
        s[i++] = '3';
    } else if (rank == CARD_4) {
        s[i++] = '4';
    } else if (rank == CARD_5) {
        s[i++] = '5';
    } else if (rank == CARD_6) {
        s[i++] = '6';
    } else if (rank == CARD_7) {
        s[i++] = '7';
    } else if (rank == CARD_8) {
        s[i++] = '8';
    } else if (rank == CARD_9) {
        s[i++] = '9';
    } else if (rank == CARD_10) {
        s[i++] = '1';
        s[i++] = '0';
    } else if (rank == CARD_J) {
        s[i++] = 'J';
    } else if (rank == CARD_Q) {
        s[i++] = 'Q';
    } else if (rank == CARD_K) {
        s[i++] = 'K';
    } else {
        return;
    }
    s[i++] = '_';

    if (suit == HEARTS) {
        s[i++] = '<';
        s[i++] = '3';
    } else if (suit == CLUBS) {
        s[i++] = '-';
        s[i++] = '%';
    } else if (suit == DIAMOND) {
        s[i++] = '<';
        s[i++] = '>';
    } else if (suit == SPADES) {
        s[i++] = '{';
        s[i++] = '>';
    }else {
        return;
    }

    s[i] = '\0';
}

/**
 * Prints an entire deck to stdout
 */
void print_deck(Deck_t *d);

/**
 * Frees the allocated memory for deck d.
 */
void free_deck(Deck_t *d);