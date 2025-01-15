#pragma once
#include "cards.h"

#define ERR_SIZE 256

#define STATE_DEAL 0
#define STATE_GAME_OVER 1
#define STATE_BLACKJACK 2
#define STATE_PBUST 3
#define STATE_DBUST 4
#define STATE_TIE 5
#define STATE_DWIN 6
#define STATE_PWIN 7

typedef struct Blackjack_Gamestate_t Blackjack_Gamestate_t;
struct Blackjack_Gamestate_t
{
    int cash;
    int pot;
    int dealer_score;
    int player_score;
    int state;
    Deck_t *deck;
    Deck_t *dealer_hand;
    Deck_t *player_hand;
    char err_msg[ERR_SIZE]; //contains a message describing the last error that occured
};

Blackjack_Gamestate_t * init_blackjack_game();
bool player_bet(Blackjack_Gamestate_t *gamestate, int amount);

void initial_deal(Blackjack_Gamestate_t *gamestate);

void hit(Blackjack_Gamestate_t *gamestate);

void dealer_draw(Blackjack_Gamestate_t *gamestate);

void reset_cards(Blackjack_Gamestate_t *gamestate);

void end_game(Blackjack_Gamestate_t *gamestate);