#pragma once
#include <stdint.h>
#include <stddef.h>

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

Deck_t * init_empty_deck();

Deck_t * init_full_deck();

void addh_card(Deck_t *d, Card_t *c);

void addt_card(Deck_t *d, Card_t *c);

Card_t * draw_at(Deck_t *d, size_t n);

Card_t * draw_top(Deck_t *d);

void print_deck(Deck_t *d);

void nprint_deck(Deck_t *d, int n);

void free_deck(Deck_t *d);