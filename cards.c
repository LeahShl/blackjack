#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "cards.h"

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

// OTHER CONSTS
const size_t CARD_STR_SIZE = 6;

//////////////////////////////////
//            FUNCS             //
//////////////////////////////////

/**
 * Creates a new card.
 * Doesn't check data for correctness.
 */
static Card_t * new_card(uint8_t rank, uint8_t suit){
    Card_t *c = malloc(sizeof(Card_t));
    if(!c){
        return NULL;
    }
    c->data = rank | suit;
    c->next = NULL;
    return c;
}

/**
 * Creates a null-terminated string representing card c
 */
static void card_str(Card_t *c, char *s){
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

Deck_t * init_empty_deck(){
    Deck_t *d = malloc(sizeof(Deck_t));
    if(!d){
        return NULL;
    }
    d->head = NULL;
    d->len = 0;
    return d;
}

Deck_t * init_full_deck(){
    Deck_t *d = init_empty_deck();
    if(!d){
        return NULL;
    }
    for(uint8_t suit = 0x01; suit <= 0x08; suit *= 0x02){
        for(uint8_t rank = 0x10; rank <= 0xD0; rank += 0x10){
            Card_t *c = new_card(rank, suit);
            if(!c){
                free_deck(d);
                return NULL;
            }
            addh_card(d, c);
        }
    }
    return d;
}

void addh_card(Deck_t *d, Card_t *c){
    c->next = d->head;
    d->head = c;
    d->len += 1;
}

void addt_card(Deck_t *d, Card_t *c){
    Card_t *p = d->head;
    if(p == NULL){
        addh_card(d, c);
    }
    else {
        while(p->next)
        {
            p = p->next;
        }
        p->next = c;
        c->next = NULL;
        d->len += 1;
    }
}

Card_t * draw_at(Deck_t *d, size_t n){
    Card_t *curr = d->head, *prev = NULL;
    for (size_t i = 0; curr != NULL && i < n; i++)
    {
        prev = curr;
        curr = curr->next;
    }
    
    // n bigger than size of deck
    if(curr == NULL){
        return NULL;
    }

    if(prev == NULL){
        d->head = curr->next; 
    }
    else{
        prev->next = curr->next; 
    }

    curr->next = NULL;
    d->len -= 1;
    return curr;
}

Card_t * draw_top(Deck_t *d){
    return draw_at(d, 0);
}

void print_deck(Deck_t *d){
    Card_t *c = d->head;
    while(c){
        char s[CARD_STR_SIZE];
        card_str(c, s);
        printf("[ %s ] ", s);
        c = c->next;
    }
}

/**
 * Prints the first n elements of deck d
 */
void nprint_deck(Deck_t *d, size_t n){
    Card_t *c = d->head;
    size_t count = n;
    while(c && count){
        char s[CARD_STR_SIZE];
        card_str(c, s);
        printf("[ %s ] ", s);
        c = c->next;
        count--;
    }
}

/**
 * Frees the allocated memory for deck d.
 */
void free_deck(Deck_t *d){
    Card_t *c = d->head;
    while(c){
        d->head = d->head->next;
        free(c);
        c = d->head;
    }
    free(d);
}