#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cards.h"
#include "blackjack.h"

// Max number of attempts to get user input before aborting program
#define MAX_ATTEMPTS 5

const char *welcome_msg = 
"\n\
+===============================================================+\n\
|          ░█▀▄░█░░░█▀█░█▀▀░█░█░▀▀█░█▀█░█▀▀░█░█░░░░█▀▀          |\n\
|          ░█▀▄░█░░░█▀█░█░░░█▀▄░░░█░█▀█░█░░░█▀▄░░░░█░░          |\n\
|          ░▀▀░░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀░░▀░▀░▀▀▀░▀░▀░▀░░▀▀▀          |\n\
+===============================================================+\n\
Welcome to Blackjack.c - a lightweight command-line game!\n\
Start game? [Y] for yes, any other key to quit...\n";

/**
 * @brief Prints state and scores aesthetucally to stdout
 * 
 * @param gamestate The blackjack game to get info from
 * @param hidden Hide dealer's data? true for yes, false fo no
 */
void print_stats(Blackjack_Gamestate_t *gamestate, bool hidden);

/**
 * @brief clears stdin buffer for a clean scanf
 */
void clear_stdin_buf();

int main(void) {
    char user_choice;
    printf("%s", welcome_msg);
    scanf(" %c", &user_choice);
    clear_stdin_buf();
    if(user_choice == 'y' || user_choice == 'Y'){
        printf("\nOK - let's start!");
        Blackjack_Gamestate_t *game = init_blackjack_game();
        if(game == NULL){
            printf("ERROR: could not initiate game. Exiting...\n");
            exit(1);
        }
        while(true){
            if(game->state == STATE_GAME_OVER){
                printf("Out of cash! GAME OVER\n");
                break;
            }

            // Betting
            int bet = -1; // A negative value will raise an error upon scanf failure
            int attempt = 0;
            bool result;
            printf("\n\nYou have %d in cash and a pot of %d from previous bets.\nHow much are you willing to bet? ", game->cash, game->pot);
            scanf(" %d", &bet);
            clear_stdin_buf();
            result = player_bet(game, bet);
            while(!result && attempt < MAX_ATTEMPTS){
                printf("\n%s\n\nBet again? ", game->err_msg);
                scanf(" %d", &bet);
                clear_stdin_buf();
                result = player_bet(game, bet);
                attempt++;
            }
            if (attempt == MAX_ATTEMPTS)
            {
                printf("\nToo many unsuccessful attempts. Exiting...\n");
                exit(1);
            }

            // Deal cards
            initial_deal(game);

            // Blackjack check
            print_stats(game, true);
            if(game->state == STATE_BLACKJACK){
                printf("\nBlackjack! Your won!\n");
                reset_cards(game);
            }
            // Hit or stand
            else{
                printf("\nHit or stand? [H]/[S]: ");
                scanf(" %c", &user_choice);
                clear_stdin_buf();
                attempt = 0;
                while (user_choice != 'H' && user_choice != 'h' &&
                       user_choice != 'S' && user_choice != 's' &&
                       attempt < MAX_ATTEMPTS)
                {
                    printf("\nInvalid choice. Hit or stand? [H]/[S]: ");
                    scanf(" %c", &user_choice);
                    clear_stdin_buf();
                    attempt++;
                }
                if (attempt == MAX_ATTEMPTS)
                {
                    printf("\nToo many unsuccessful attempts. Exiting...\n");
                    exit(1);
                }
                

                // Hit
                while(user_choice == 'H' || user_choice == 'h'){
                    hit(game);
                    print_stats(game, true);
                    if(game->state == STATE_PBUST){
                        printf("Busted! You lost your bet.\n");
                        reset_cards(game);
                        break;
                    }
                    else{
                        attempt = 0;
                        printf("\nHit or stand? [H]/[S]: ");
                        scanf(" %c", &user_choice);
                        clear_stdin_buf();
                        while (user_choice != 'H' && user_choice != 'h' &&
                               user_choice != 'S' && user_choice != 's' && 
                               attempt < MAX_ATTEMPTS)
                        {
                            printf("\nInvalid choice. Hit or stand? [H]/[S]: ");
                            scanf(" %c", &user_choice);
                            clear_stdin_buf();
                            attempt++;
                        }
                        if (attempt == MAX_ATTEMPTS)
                        {
                            printf("\nToo many unsuccessful attempts. Exiting...\n");
                            exit(1);
                        }
                    }
                }

                // Stand
                if(user_choice == 'S' || user_choice == 's'){
                    dealer_draw(game);
                    print_stats(game, false);
                    if(game->state == STATE_DBUST){
                        printf("Dealer busted! You won!\n");
                        reset_cards(game);
                    }
                    else if(game->state == STATE_DWIN){
                        printf("Dealer won! You lost your bet.\n");
                        reset_cards(game);
                    }
                    else if(game->state == STATE_TIE){
                        printf("Tie!\n");
                        reset_cards(game);
                    }
                    else if (game->state == STATE_PWIN)
                    {
                        printf("You won!\n");
                        reset_cards(game);
                    }
                    
                    else{
                        printf("Gamestate error. Exiting...\n");
                        exit(1);
                    }
                }
            }
        }
        end_game(game);
    }

    printf("\nGoodbye!\n\n");

    return 0;
}

void print_stats(Blackjack_Gamestate_t *gamestate, bool hidden){
    printf("\n===============================================================\nPlayer's hand: ");
    print_deck(gamestate->player_hand);
    printf("\nScore: %d \t Cash: %d \t Pot: %d\n\n",gamestate->player_score, gamestate->cash, gamestate->pot);

    printf("Dealer's hand: ");
    if(hidden){
        nprint_deck(gamestate->dealer_hand, 1);
        printf("[ ???? ]\nScore: ??\n");
    }
    else{
        print_deck(gamestate->dealer_hand);
        printf("\nScore: %d\n", gamestate->dealer_score);
    }
    printf("===============================================================\n");
}

void clear_stdin_buf(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}