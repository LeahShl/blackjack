#pragma once
#include "cards.h"

/**
 * @brief Error message max size
 */
#define ERR_SIZE 256

/**
 * @brief Possible states for a blackjack game
 */
#define STATE_DEAL 0
#define STATE_GAME_OVER 1
#define STATE_BLACKJACK 2
#define STATE_PBUST 3
#define STATE_DBUST 4
#define STATE_TIE 5
#define STATE_DWIN 6
#define STATE_PWIN 7

/**
 * @brief An object holding data for a single blackjack game
 */
typedef struct Blackjack_Gamestate_t Blackjack_Gamestate_t;
struct Blackjack_Gamestate_t
{
    int cash;
    int pot;
    int dealer_score;
    int player_score;
    int state; // one of possible states defined above
    Deck_t *deck;
    Deck_t *dealer_hand;
    Deck_t *player_hand;
    char err_msg[ERR_SIZE]; //contains a message describing the last error that occured
};

/**
 * @brief Initiates new blackjack game with default values
 * 
 * @return Blackjack_Gamestate_t* Pointer to game object. 
 * @return NULL if allocation unsuccessful.
 */
Blackjack_Gamestate_t * init_blackjack_game();

/**
 * @brief Updates player's bet and checks for errors.
 * 
 * @param gamestate Pointer to game object. 
 * @param amount Amount to bet
 * @return true if data updated successfully.
 * @return false if an error occurred. Error message accessible via gamestate->err_msg
 */
bool player_bet(Blackjack_Gamestate_t *gamestate, int amount);

/**
 * @brief Deals 2 cards for each player. Updates state in case of blackjack.
 * 
 * @param gamestate Pointer to game object. 
 */
void initial_deal(Blackjack_Gamestate_t *gamestate);

/**
 * @brief Draws 1 card for the player. Updates state in case of bust.
 * 
 * @param gamestate Pointer to game object. 
 */
void hit(Blackjack_Gamestate_t *gamestate);

/**
 * @brief Implements dealer's draw stage and updates final game state accordingly.
 * 
 * @param gamestate Pointer to game object. 
 */
void dealer_draw(Blackjack_Gamestate_t *gamestate);

/**
 * @brief Returns all cards to the deck and updates state.
 * 
 * @param gamestate Pointer to game object. 
 */
void reset_cards(Blackjack_Gamestate_t *gamestate);

/**
 * @brief Frees all memory allocated by gamestate.
 * 
 * @param gamestate Pointer to game object. 
 */
void end_game(Blackjack_Gamestate_t *gamestate);