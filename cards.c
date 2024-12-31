#include <stdint.h>
const char CARD_A = 0x10;
const char CARD_2 = 0x20;
const char CARD_3 = 0x30;
const char CARD_4 = 0x40;
const char CARD_5 = 0x50;
const char CARD_6 = 0x60;
const char CARD_7 = 0x70;
const char CARD_8 = 0x80;
const char CARD_9 = 0x90;
const char CARD_10 = 0xA0;
const char CARD_J = 0xB0;
const char CARD_Q = 0xC0;
const char CARD_K = 0xD0;

const char HEARTS = 0x01;
const char CLUBS = 0x02;
const char DIAMOND = 0x04;
const char SPADES = 0x08;

typedef struct Card_t
{
    uint8_t data;
    Card_t *next;
}Card_t;

typedef struct Deck_t
{
    Card_t *head;
}Deck_t;