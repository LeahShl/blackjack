#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "cards.h"

#define DEFAULT_CASH 1000
#define MIN_CASH 10

#define ERR 0
#define OK 1
#define ERR_SIZE 256

#define STATE_DEAL 0
#define STATE_GAME_OVER 1
#define STATE_BLACKJACK 2
#define STATE_PBUST 3
#define STATE_DBUST 4
#define STATE_TIE 5
#define STATE_DWIN 6

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

Blackjack_Gamestate_t * init_blackjack_game(){
    Blackjack_Gamestate_t *gamestate = malloc(sizeof(Blackjack_Gamestate_t));
    if(!gamestate){
        return NULL;
    }

    gamestate->deck = init_full_deck();
    gamestate->dealer_hand = init_empty_deck();
    gamestate->player_hand = init_empty_deck();
    gamestate->cash = DEFAULT_CASH;
    gamestate->pot = 0;
    gamestate->dealer_score = 0;
    gamestate->player_score = 0;
    gamestate->state = STATE_DEAL;

    // init rand seed for random card draw
    srand(time(NULL));

    return gamestate;
}

int player_bet(Blackjack_Gamestate_t *gamestate, int amount){
    if(amount == 0 && gamestate->pot > 0){
        return OK;
    }
    else if(amount > 0 && amount % 10 == 0 && amount <= gamestate->cash){
        gamestate->cash -= amount;
        gamestate->pot += amount;
        return OK;
    }
    strncpy(gamestate->err_msg, "[Betting] Amount to bet must be a non-negative integer divisible by 10", ERR_SIZE);
    return ERR;
}

static void calculate_scores(Blackjack_Gamestate_t *gamestate){
    Card_t *p = gamestate->dealer_hand->head;
    bool has_ace = false;
    int score = 0;

    // Dealer
    while(p){
        uint8_t rank = p->data >> 4;
        if(rank > 10)
            rank = 10;
        if(rank == 1)
            has_ace = true;
        score += rank;
    }
    if(has_ace && score < 12){
        score += 10;
    }
    gamestate->dealer_score = score;

    // Player
    p = gamestate->player_hand->head;
    has_ace = false;
    score = 0;
    while(p){
        uint8_t rank = p->data >> 4;
        if(rank > 10)
            rank = 10;
        if(rank == 1)
            has_ace = true;
        score += rank;
    }
    if(has_ace && score < 12){
        score += 10;
    }

    gamestate->player_score = score;
}

void initial_deal(Blackjack_Gamestate_t *gamestate){
    // Draw 2 random cards for each player
    for (int i = 0; i < 2; i++)
    {
        Card_t *c = draw_at(gamestate->deck, rand() % gamestate->deck->len);
        addt_card(gamestate->dealer_hand, c);
        c = draw_at(gamestate->deck, rand() % gamestate->deck->len);
        addt_card(gamestate->player_hand, c);
    }

    calculate_scores(gamestate);

    // Blackjack check
    if(gamestate->player_score == 21){
        gamestate->state = STATE_BLACKJACK;
        gamestate->cash += gamestate->pot * 2.5;
        gamestate->pot = 0;
    }
}

void hit(Blackjack_Gamestate_t *gamestate){
    Card_t *c = draw_at(gamestate->deck, rand() % gamestate->deck->len);
    addt_card(gamestate->player_hand, c);

    calculate_scores(gamestate);

    // Check for player's bust
    if(gamestate->player_score > 21){
        gamestate->state = STATE_PBUST;
        gamestate->pot = 0;
    }
        
}

void dealer_draw(Blackjack_Gamestate_t *gamestate){
    while(1) {
        if(gamestate->dealer_score >= 17 || gamestate->dealer_score > gamestate->player_score)
            break;
        
        Card_t *c = draw_at(gamestate->deck, rand() % gamestate->deck->len);
        addt_card(gamestate->dealer_hand, c);
        calculate_scores(gamestate);
    }

    // Check for dealer's bust
    if(gamestate->dealer_score > 21){
        gamestate->state = STATE_DBUST;
        gamestate->cash += gamestate->pot * 2;
        gamestate->pot = 0;

    }
    else if(gamestate->dealer_score > gamestate->player_score){
        gamestate->state = STATE_DWIN;
        gamestate->pot = 0;
    }
    else if(gamestate->dealer_score == gamestate->player_score){
        gamestate->state = STATE_TIE;
    }
}

void reset_cards(Blackjack_Gamestate_t *gamestate){
    // Empty dealer's hand to deck
    Card_t *c = draw_top(gamestate->dealer_hand);
    while(c){
        addh_card(gamestate->deck, c);
        c = c->next;
    }

    // Empty player's hand to deck
    c = draw_top(gamestate->player_hand);
    while(c){
        addh_card(gamestate->deck, c);
        c = c->next;
    }
}

void end_game(Blackjack_Gamestate_t *gamestate){
    free_deck(gamestate->deck);
    free_deck(gamestate->dealer_hand);
    free_deck(gamestate->player_hand);
    free(gamestate);
}