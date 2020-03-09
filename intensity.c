/*
 *  =================================================
 *  EMMANUEL CHRISTIANOS z5206513 DATE: 11th MAY 2018
 *  =================================================
 *  UNSW COMP1511 SEM 1 ASSIGNMENT 2 RELEASED VER 1.0
 *  =================================================
 *  VER 1.15 FINISHED STRATEGY NOW ADDING ASSERTS IN!
 *  =================================================
 *
*/

#include <stdio.h>
#include <assert.h>
#include <string.h>

/*
 * ==============
 * GIVEN #DEFINES
 * ==============
 */

#define ACTION_PLAYER_NAME    0

#define ACTION_DISCARD        1

#define ACTION_PLAY_CARD      2

#define ACTION_UNIT_TESTS     3

#define N_CARDS              40

#define N_CARDS_INITIAL_HAND 10

#define N_PLAYERS             4

#define N_CARDS_DISCARDED     3

#define CARD_MIN             10

#define CARD_MAX             49

/*
 * ===========
 * MY #DEFINES
 * ===========
 */

#define N_CARDS_RECEIVED 3

#define MAX_PREVIOUSLY_PLAYED_CARDS 3

#define BUFFALO 47

/*
 * =========================
 * GIVEN FUNCTION PROTOTYPES
 * =========================
 */

void print_player_name(void);

void choose_discards(void);

void choose_card_to_play(void);

void run_unit_tests(void);


/*
 * ======================
 * MY FUNCTION PROTOTYPES
 * ======================
 */

int holdingValid(int firstCardPlayed, int hand[N_CARDS_INITIAL_HAND], int numCardsInHand);

int holdingBuffalo(int hand[], int numOfCardsInHand);

int highestCalfOverThirtyFive(int hand[], int numCardsInHand);

int highestNonCalfOverThirtyFive(int hand[], int numCardsInHand);

int highestNonDiscriminantCard(int hand[], int numCardsInHand);

int *fillPossiblePlayableCards(int hand[], int playableCardsArray[], int firstCardPlayed, int cardsInHand);

int *sortSmallestToLargest(int array[], int size);

int *readInCardsFromInput(int *hand, int numOfCardsInHand);

int playableUnderTheMax(int hand[], int sizeOfArray, int maxCardAlreadyPlayed);

int findHighestLegalCard(int firstCardInTheRound, int cardsPlayedThisRound[], int amountOfCardsPlayedThisRound);

int *
findPossibleCardsNotPlayedYet(int possibleCardsNotPlayedYet[], int cardsPlayedInHistory[], int numCardsPlayedInHistory,
                              int cardsPlayedThisRound[], int firstCardPlayedThisRound, int hand[], int numCardsInHand);

int countElementsInArray(int array[], int sizeOfArray);

int howManyUnderMax(int possiblePlayable[], int possiblePlayableSize, int max);

int highestCardIHaveUnderMax(int hand[], int handSize, int max);

int *possiblePlayableAboveMax(int arrayOfPossibleCards[], int max,int newArrayToStore[]);

int findLowestElement(int array[], int arraySize);

int highestValueIHaveInRange(int lower, int upper, int hand[], int numCardsInHand);

int lowestLegalCard(int hand[], int numCardsInHand, int maxLegalCardThisRound);

int buffaloHasBeenPlayed(int cardsPlayedThisRound[], int size);

int firstPossiblePlayableAboveMax(int possiblePlayablesIdontHave[], int sizeOfPossible, int maxCardPlayed);

int calfPreviouslyPlayed(int allPreviouslyPlayedCards[]);

int *calfsInMyHand(int calfsInMyHand[], int hand[], int numCardsInhand);

int findKeyTipOverCalf(int calfsThatHaventBeenPlayed[], int numOfCalfsThatHaventBeenPlayed, int calfsInMyhand[],
                       int numOfCalfsInHand);

int lowestCalf(int hand[], int numCardsInHand);

void playGoodNonCalfFirstCard(int hand[], int numCardsInHand, int previousCardsPlayedArray[],
                              int numPreviouslyPlayedCards, int cardsPlayedThisRound[], int numCardsPlayedThisRound);

int highestNonCalfBuffalo(int hand[], int numCardsInHand);

void firstPlayerPosition(int hand[],int numCardsInHand,int cardsInHistory[]);

/*
 * =============
 * MAIN FUNCTION
 * =============
 */

int main(void) {

    int which_action = 0;

    scanf("%d", &which_action);

    if (which_action == ACTION_PLAYER_NAME) {

        print_player_name();

    } else if (which_action == ACTION_DISCARD) {

        choose_discards();

    } else if (which_action == ACTION_PLAY_CARD) {

        choose_card_to_play();

    } else {

        run_unit_tests();
    }

    return 0;
}

void print_player_name(void) {

    /*
     * ==============
     * MY PLAYER NAME
     * ==============
     */

    printf("MINNIE MOO IS COMING FOR YOU");

}

void choose_discards() {

    /*
        ==================
        DISCARDING 3 CARDS
        ==================
     */

    int discardedArray[3] = {0};
    int hand[N_CARDS_INITIAL_HAND] = {0};

    /*      DISCARDING
     * ~~~~~~~~~~~~~~~~~~~~~~~~
     * READING IN CARDS IN HAND
     * ~~~~~~~~~~~~~~~~~~~~~~~~
     */

    readInCardsFromInput(hand, N_CARDS_INITIAL_HAND);

    /*

     * -------
     * TESTING
     * -------

    for (int k = 0; k < 10; ++k) {

        printf("%d\n", hand[k]);
    }
    */
    int discarded = 0;

    int fourtiesCounter = 0;

    for (int l = 0; l < N_CARDS_INITIAL_HAND; ++l) {

        if(hand[l]!=0){


            if(hand[l]/10 == 4 && hand[l]%10 < 4) {

                fourtiesCounter++;
            }
        }
    }

    //printf("Fourties Counter = %d\n",fourtiesCounter);

    if(fourtiesCounter <= 2){

        if(holdingBuffalo(hand,N_CARDS_INITIAL_HAND) == 1){

            printf("%d\n",BUFFALO);
            discardedArray[discarded] = BUFFALO;
            discarded++;
        }
    }


    /*              DISCARDING
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * FINDING MY TOP THREE CALFS OVER 35 IN MY HAND!
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */

    int maxCalfOver35 = 0;
    int secondHighestCalfOver35 = 0;
    int thirdHighestCalfOver35 = 0;

    for (int j = 0; j < N_CARDS_INITIAL_HAND; ++j) {

        if (hand[j] > 35 && hand[j] < 40) {

            if (hand[j] > maxCalfOver35) {

                int oldMax = maxCalfOver35;
                maxCalfOver35 = hand[j];

                int oldSec = secondHighestCalfOver35;
                secondHighestCalfOver35 = oldMax;

                thirdHighestCalfOver35 = oldSec;

            } else if (hand[j] > secondHighestCalfOver35) {

                int oldSec = secondHighestCalfOver35;
                secondHighestCalfOver35 = hand[j];

                thirdHighestCalfOver35 = oldSec;

            } else if (hand[j] > thirdHighestCalfOver35) {

                thirdHighestCalfOver35 = hand[j];
            }
        }
    }

    /*                     DISCARDING
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * CHECKING TO SEE IF MY TOP THREE CALFS HAVE BEEN FOUND,
     * AND DISCARDING THOSE THAT HAVE (PRINTING THEM OUT)
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */

    if (maxCalfOver35 != 0) {

        printf("%d\n", maxCalfOver35);

        discardedArray[discarded] = maxCalfOver35;

        discarded++;

        if (secondHighestCalfOver35 != 0) {

            printf("%d\n", secondHighestCalfOver35);

            discardedArray[discarded] = secondHighestCalfOver35;

            discarded++;

            if (thirdHighestCalfOver35 != 0 && discarded < 3) {

                printf("%d\n", thirdHighestCalfOver35);

                discardedArray[discarded] = thirdHighestCalfOver35;

                discarded++;

            }
        }
    }

    /*                              DISCARDING
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * IF I STILL HAVENT DISCARDED THREE CARDS AFTER DISCARDING MY TOP CALFS
     * BETWEEN 35 AND 40, THEN I NEED TO DISCARD MY HIGHEST NON CALFS BETWEEN
     * 35 AND 40!
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */

    if (discarded < 3) {

        int iteration = 0;

        /*                    DISCARDING
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * LOOP TO DISCARD ANY NON CALFS OVER ONE'S VALUE OF 5
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        while (discarded < 3 && iteration < 10) {

            int maximumNonCalf = 0;

            for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

                if (hand[i] / 10 != 3) {

                    if (hand[i] % 10 > maximumNonCalf % 10) {

                        if (hand[i] != discardedArray[0] && hand[i] != discardedArray[1] &&
                            hand[i] != discardedArray[2]) {

                            if (hand[i] % 10 >= 5) {

                                maximumNonCalf = hand[i];

                            }
                        }
                    }
                }
            }

            if (maximumNonCalf != 0 && discarded < 3) {

                discardedArray[discarded] = maximumNonCalf;

                printf("%d\n", maximumNonCalf);

                discarded++;
            }

            iteration++;
        }

        /*              DISCARDING
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * IF DISCARDED STILL != 3, I WANT TO SEE IF I CAN
         * ELIMINATE A WHOLE GROUP OF CARDS WITH MY REMAI-
         * NING DISCARDS, EXCLUDING 30'S AND 40'S SINCE I
         * DONT WANT TO BE STUCK NOT BEING ABLE TO PLAY A
         * LOW 30'S OR 40'S CARD.
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        if (discarded < 3) {

            int tens = 0;
            int twenties = 0;

            //int thirties = 0; COME BACK AND TEST THIS WHEN YOU FINISH TO SEE IF AI PLAYS BETTER WHEN U GET RID OF LOW THIRTIES!
            //int forties = 0; COME BACK AND TEST THIS WHEN YOU FINISH TO SEE IF AI PLAYS BETTER WHEN U GET RID OF LOW FOURTIES!

            /*              DISCARDS
             * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             * COUNTING HOW MANY TENS AND TWENTIES I HAVE
             * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             */

            int tensFlag = 0;
            int twentiesFlag = 0;

            for (int j = 0; j < N_CARDS_INITIAL_HAND; ++j) {

                if (hand[j] / 10 == 1) {

                    tens++;

                    if (hand[j] % 10 != 0) {
                        tensFlag = 1;
                    }


                } else if (hand[j] / 10 == 2) {

                    twenties++;

                    if (hand[j] % 10 != 0) {

                        twentiesFlag = 1;
                    }
                }
            }

            /*              DISCARDS
             * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             * CHECKING TO SEE IF I CAN DISCARD ALL
             * OF ONE TENS VALUE EITHER 10'S OR 20'S
             * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             */

            if (tens <= 3 - discarded && tens != 0 && tensFlag == 0) {

                for (int j = 0; j < N_CARDS_INITIAL_HAND; ++j) {

                    if (hand[j] / 10 == 1) {

                        printf("%d\n", hand[j]);

                        discarded++;
                    }
                }
            } else if (twenties <= 3 - discarded && twenties != 0 && twentiesFlag == 0) {

                for (int j = 0; j < N_CARDS_INITIAL_HAND; ++j) {

                    if (hand[j] / 10 == 2) {

                        printf("%d\n", hand[j]);

                        discarded++;
                    }
                }
            } else {

                /*            DISCARDING
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 * IF I CANT GET RID OF ALL OF ONE TENS
                 * GROUP OR I HAVE AND I STILL HAVE
                 * SOME DISCARDS LEFT THEN I WILL START
                 * DISCARDING FROM MY HIGHEST VALUE
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 */

                while (discarded < 3) {

                    int lastResortMax = 0;

                    for (int j = 0; j < N_CARDS_INITIAL_HAND; ++j) {

                        if (hand[j] != discardedArray[0] && hand[j] != discardedArray[1] &&
                            hand[j] != discardedArray[2]) {

                            lastResortMax = hand[j];
                        }
                    }

                    for (int k = 0; k < N_CARDS_INITIAL_HAND; ++k) {

                        if (hand[k] != discardedArray[0] && hand[k] != discardedArray[1] &&
                            hand[k] != discardedArray[2]) {

                            if (hand[k] % 10 > lastResortMax % 10) {

                                lastResortMax = hand[k];

                            } else if (hand[k] % 10 == lastResortMax % 10) {

                                if (hand[k] / 10 < lastResortMax / 10) {

                                    lastResortMax = hand[k];
                                }
                            }
                        }
                    }

                    discardedArray[discarded] = lastResortMax;

                    printf("%d\n", lastResortMax);

                    discarded++;
                }
            }
        }
    }
}

void choose_card_to_play(void) {
    /*
        =======================
        CHOOSING A CARD TO PLAY
        =======================
     */

    /*              PICK A CARD
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * SCANNING IN THE NUMBER OF CARDS IN MY HAND
     * THE CARDS THAT HAVE ALREADY BEEN PLAYED
     * THIS ROUND AND MY TABLE POSITION
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */

    int numOfCardsInHand = 10;
    int cardsPlayedAlready = 0;
    int tablePosition = 0;

    scanf("%d%d%d", &numOfCardsInHand, &cardsPlayedAlready, &tablePosition);

    /*         PICK A CARD
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * READING IN CARDS IN MY HAND
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */

    int hand[N_CARDS_INITIAL_HAND] = {0};

    readInCardsFromInput(hand, numOfCardsInHand);

    /*
     * -------
     * TESTING
     * -------
     */

/*    printf("NUM CARDS IN HAND: %d\nCARDS PLAYED ALREADY: %d\nTABLE POSITION: %d\n", numOfCardsInHand,
           cardsPlayedAlready, tablePosition);*/

    /*for (int j = 0; j < numOfCardsInHand; ++j) {

        printf("CARDS %d IS %d\n", j, hand[j]);
    }*/

    /*             PICK A CARD
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * READING IN THE CARDS THAT HAVE BEEN
     * PLAYED THIS ROUND
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */
    int playedCurrentRoundArray[3] = {0};

    readInCardsFromInput(playedCurrentRoundArray, cardsPlayedAlready);

    /*
     * -------
     * TESTING
     * -------
     */

//    for (int j = 0; j < cardsPlayedAlready; ++j) {
//
//        printf("CARD ALREADY PLAYED ARE: %d\n", playedCurrentRoundArray[j]);
//    }

    /*                      PICK A CARD
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * READ IN CARDS PLAYED IN TOTAL HISTORY OF THE GAME,
     * ONLY IF IT IS NOT THE FIRST ROUND OF GAME.
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */

    int cardsInHistory = 4 * (10 - numOfCardsInHand);
    int cardsInHistoryArray[N_CARDS] = {0};

    //printf("Cards in history: %d\n", cardsInHistory);

    if (cardsInHistory != 0) {

        readInCardsFromInput(cardsInHistoryArray, cardsInHistory);

        /*
         * -------
         * TESTING
         * -------
         */
//        for (int j = 0; j < cardsInHistory; ++j) {
//
//            printf("THE CARDS THAT HAVE PREVIOUSLY BEEN PLAYED ARE: %d\n", cardsInHistoryArray[j]);
//        }
    }

    /*     PICK A CARD
     * ~~~~~~~~~~~~~~~~~~~
     * READ IN MY DISCARDS
     * ~~~~~~~~~~~~~~~~~~~
     */

    int discardedCards[N_CARDS_DISCARDED] = {0};

    readInCardsFromInput(discardedCards, N_CARDS_DISCARDED);

    /*
     * -------
     * TESTING
     * -------
     */

//    for (int m = 0; m < N_CARDS_DISCARDED; ++m) {
//
//        printf("MY DISCARDED CARDS WERE: %d\n", discardedCards[m]);
//    }

    /*      PICK A CARD
     * ~~~~~~~~~~~~~~~~~~~~~~
     * READ IN CARDS RECEIVED
     * ~~~~~~~~~~~~~~~~~~~~~~
     */

    int receivedCardsArray[N_CARDS_RECEIVED] = {0};

    readInCardsFromInput(receivedCardsArray, N_CARDS_RECEIVED);

    /*
     * -------
     * TESTING
     * -------
     */

//    for (int m = 0; m < N_CARDS_DISCARDED; ++m) {
//
//        printf("MY RECEIVED CARDS WERE: %d\n", receivedCardsArray[m]);
//    }

    /*          PICK A CARD
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * STRATEGY FOR PICKING A CARD TO PLAY
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * IM JUST THAT GOOD
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * FIRST:CAN I PLAY A VALID CARD OR NO
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */

    if (cardsPlayedAlready != 0 && holdingValid(playedCurrentRoundArray[0], hand, numOfCardsInHand) == 0) {

        /*                      PICK A CARD
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * CANT PLAY VALID CARD, CHECK IF I AM HOLDING BUFFALO,
         * IF SO PAY IT IF NOT PLAY MY HIGHEST CALF CARD OVER 35
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        if (holdingBuffalo(hand, numOfCardsInHand) == 1) {

            printf("%d",BUFFALO);

        } else {

            if (highestCalfOverThirtyFive(hand, numOfCardsInHand) != -1) {

                printf("%d\n", highestCalfOverThirtyFive(hand, numOfCardsInHand));

            } else {

                /*                      PICK A CARD
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 * IF I DONT HAVE A CALF OVER 35 TO PLAY THEN I WANT TO
                 * PLAY A NON CALF OVER 35.
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 */

                if (highestNonCalfOverThirtyFive(hand, numOfCardsInHand) != -1) {

                    printf("%d\n", highestNonCalfOverThirtyFive(hand, numOfCardsInHand));

                } else {

                    /*                      PICK A CARD
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     * IF I DONT HAVE A CALF OR NON CALF WITH A ONES VALUE
                     * OVER 5 THEN START DISCARDING MY CARDS WITH THE
                     * HIGHEST ONE VALUE
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     */

                    printf("%d\n", highestNonDiscriminantCard(hand, numOfCardsInHand));
                }
            }
        }
    } else if ((cardsPlayedAlready == 1 || cardsPlayedAlready == 2) &&
               holdingValid(playedCurrentRoundArray[0], hand, numOfCardsInHand) != 0) {

        /*          PICK A CARD
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * IF IM IN 2ND OR 3RD POSITION AND
         * I DO HAVE A VALID CARD TO PLAY
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        int playableCards[N_CARDS_INITIAL_HAND] = {0};
        int maxCardAlreadyPlayed = 0;
        int possibleCardsIDontHave[N_CARDS_INITIAL_HAND] = {0};

        /*              PICK A CARD
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * FILLING AN ARRAY WITH THE POSSIBLE CARDS
         * I CAN PLAY DEPENDING ON WHAT CARD THE
         * FIRST PLAYER PLAYED.
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */
        fillPossiblePlayableCards(hand, playableCards, playedCurrentRoundArray[0], numOfCardsInHand);


        /*              PICK A CARD
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * FINDING THE HIGHEST LEGAL VALUE CARD
         * THAT HAS ALREADY BEEN PLAYED.
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        maxCardAlreadyPlayed = findHighestLegalCard(playedCurrentRoundArray[0], playedCurrentRoundArray,
                                                    cardsPlayedAlready);

        /*            PICK A CARD
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * STRATEGY FOR PLAYER IN FIRST POSITION
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        /*
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * IF THE BUFFALO HASNT BEEN PLAYED THEN
         * GO ABOUT NORMAL STRATEGY ELSE, PLAY
         * YOUR HIGHEST CARD UNDER THE MAX
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        if (buffaloHasBeenPlayed(playedCurrentRoundArray,MAX_PREVIOUSLY_PLAYED_CARDS) == 1) {

            if (cardsPlayedAlready == 1) {

                /*            PICK A CARD
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 * IF I HAVE A LEGAL PLAYABLE CARD UNDER
                 * THE VALUE OF THE HIGHEST CARD ALREADY
                 * PLAYED.
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 *
                 */

                if (playableUnderTheMax(hand, numOfCardsInHand, maxCardAlreadyPlayed) == 1) {

                    /*               PICK A CARD
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     * FINDING ALL PLAYABLE CARDS LEFT NOT IN MY HAND
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     */
                    int cardsIdontHave[N_CARDS_INITIAL_HAND] = {0};

                    findPossibleCardsNotPlayedYet(cardsIdontHave, cardsInHistoryArray, cardsInHistory,
                                                  playedCurrentRoundArray, playedCurrentRoundArray[0], hand,
                                                  numOfCardsInHand);



                    /*              PICK A CARD
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     * FINDING OUT HOW MANY POSSIBLE PLAYABLE
                     * CARDS UNDER CURRENT MAX I DONT HAVE
                     * THAT CAN BE PLAYED.
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     */

                    if (howManyUnderMax(cardsIdontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) >= 2) {

                        /*              PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * IF THERE IS 2 OR GREATER CARDS THAT CAN
                         * BE PLAYED BELOW MAX THAT I DONT HAVE,
                         * THEN PLAY HIGHEST CARD UNDER MAX THAT I
                         * HAVE.
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */

                        printf("%d\n", highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                    } else if (howManyUnderMax(cardsIdontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) ==
                               1) {

                        /*                      PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * IF THERE IS LESS THAN TWO CARDS BELOW THE MAX THAT
                         * CAN STILL POSSIBLY BE PLAYED THEN CHECK WHAT CARDS
                         * ABOVE THE MAX CAN POSSIBLY BE PLAYED!
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */

                        int PPoverHalfWay[N_CARDS_INITIAL_HAND] = {0};

                        possiblePlayableAboveMax(cardsIdontHave, maxCardAlreadyPlayed,PPoverHalfWay);



                        /*                  PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * IF I HAVE AN ELEMENT BELOW ALL THE POSSIBLE PLAYABLE
                         * CARDS ABOVE THE MAX THEN PLAY THE HIGHEST ELEMENT IN
                         * THAT RANGE, IF I DONT, THEN PLAY THE HIGHEST CARDS I
                         * HAVE BELOW THE MAX CARD.
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */


                        int lowestElementAboveMax = findLowestElement(PPoverHalfWay, N_CARDS_INITIAL_HAND);


                        if (highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand,
                                                     numOfCardsInHand) == -1) {


                            printf("%d\n", highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                        } else if (highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand,
                                                            numOfCardsInHand) != -1) {

                            if(buffaloHasBeenPlayed(cardsInHistoryArray,N_CARDS) == 1) {

                                printf("%d\n",
                                       highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand,
                                                                numOfCardsInHand));
                            } else {

                                printf("%d\n", highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                            }
                        }
                    } else if (howManyUnderMax(cardsIdontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) ==
                               0) {

                        /*              PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * NO POSSIBLE CARDS UNDER THE MAX TO PLAY, SO NOW SEE IF YOU
                         * HAVE A CARD ABOVE THE MAX AND ABOVE THE FIRST POSSIBLE
                         * PLAYABLE CARD AFTER THE MAX BUT BELOW THE REST. THEN IF SO
                         * PLAY THE HIGHEST CARD IN THAT RANGE, IF NOT PLAY YOUR HIGHEST
                         * CARDS ABOVE MAX BUT UNDER ALL OTHER POSSIBLE PLAYABLE, IF
                         * STILL NO CARDS IN THAT RANGE THEN PLAY YOUR HIGHEST UNDER MAX.
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */

                        int firstPPAboveMax = firstPossiblePlayableAboveMax(cardsIdontHave,
                                                                            N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed);
                        int secondPPAboveMax = firstPossiblePlayableAboveMax(cardsIdontHave,
                                                                             N_CARDS_INITIAL_HAND, firstPPAboveMax);

                        if (buffaloHasBeenPlayed(cardsInHistoryArray, N_CARDS) == 1){

                            if (highestValueIHaveInRange(firstPPAboveMax, secondPPAboveMax, hand, numOfCardsInHand) != -1) {

                                printf("%d\n", highestValueIHaveInRange(firstPPAboveMax, secondPPAboveMax, hand, numOfCardsInHand));

                            } else {

                                if (highestValueIHaveInRange(maxCardAlreadyPlayed, firstPPAboveMax, hand, numOfCardsInHand) != -1) {

                                    printf("%d\n", highestValueIHaveInRange(maxCardAlreadyPlayed, firstPPAboveMax, hand, numOfCardsInHand));

                                } else {

                                    printf("%d\n", highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed));
                                }
                            }
                        } else {

                            printf("%d\n", highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed));
                        }
                    }
                } else {

                    /*                     PICK A CARD
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     * WHEN YOU DONT HAVE ANY LEGAL PLAYABLE CARDS UNDER
                     * THE MAX BUT YOU DO HAVE SOME OVER THE MAX, IF THE
                     * NUMBER OF PLAYABLE CARDS BELOW THE MAX IS EQUAL TO
                     * ONE THEN YOU SEE IF YOU HAVE A PLAYABLE CARS ABOVE
                     * MAX AND BELOW ALL OTHER POSSIBLE PLAYABLE CARDS.
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     */
                    //printf("I DONT HAVE ANY LEGAL PLAYABLE UNDER THE MAX BUT I HAVE SOME OVER\n");

                    int iDontHave[N_CARDS_INITIAL_HAND] = {0};

                    findPossibleCardsNotPlayedYet(iDontHave, cardsInHistoryArray, cardsInHistory,
                                                  playedCurrentRoundArray, playedCurrentRoundArray[0], hand,
                                                  numOfCardsInHand);

                    if (howManyUnderMax(iDontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) >= 2) {

                        /*                      PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * PLAY L0WEST LEGAL CARD THAT I CAN FOR THIS ROUND!
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */

                        printf("%d\n", lowestLegalCard(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                    } else if (howManyUnderMax(iDontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) == 1) {

                        /*                      PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * POSSIBLE PLAYABLE CARDS UNDER THE MAX IS LESS THAN
                         * TWO, SO I CHECK IF I HAVE A CARD LESS THAN ALL THE
                         * POSSIBLE PLAYABLE CARDS ABOVE THE MAX BUT STILL ABOVE
                         * THE MAX SINCE I DONT HAVE ANY BELOW AT THIS POINT.
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */

                        int PPover35[N_CARDS_INITIAL_HAND] = {0};

                        possiblePlayableAboveMax(iDontHave, maxCardAlreadyPlayed,PPover35);

                        /*                      PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * IF I HAVE AN ELEMENT BELOW ALL THE POSSIBLE PLAYABLE
                         * CARDS ABOVE THE MAX THEN PLAY THE HIGHEST ELEMENT IN
                         * THAT RANGE, IF I DONT, THEN PLAY THE HIGHEST CARDS I
                         * HAVE BELOW THE MAX CARD.
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */
                        int lowestElementAboveMax = findLowestElement(PPover35, N_CARDS_INITIAL_HAND);

                        if (highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand, numOfCardsInHand) == -1) {

                            printf("%d\n", lowestLegalCard(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                        } else if (highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand,
                                                            numOfCardsInHand) != -1) {

                            if (buffaloHasBeenPlayed(cardsInHistoryArray, N_CARDS) == 1) {

                                printf("%d\n", highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand,
                                                                        numOfCardsInHand));
                            } else {

                                printf("%d\n", lowestLegalCard(hand, numOfCardsInHand, maxCardAlreadyPlayed));
                            }
                        }
                    } else if (howManyUnderMax(iDontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) == 0) {

                        //printf("THERE IS ZERO PLAYABLE UNDER THE MAX\n");

                        /*              PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * IF I DONT HAVE A VALID UNDER THE MAX
                         * AND THERE IS NO POSSIBLE PLAYABLE
                         * UNDER THE MAX.
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */

                       /* for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

                            printf("POSSIBLE PLAYABLE CARDS: %d\n",iDontHave[i]);

                        }*/

                        /*for (int j = 0; j < 40; ++j) {

                            if(cardsInHistoryArray[j]!= 0){

                                printf("ALL CARDS IN HISTORY: %d\n",cardsInHistoryArray[j]);
                            }

                        }*/

                        int firstPPAboveMax = firstPossiblePlayableAboveMax(iDontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed);

                        int secondPPAboveMax = firstPossiblePlayableAboveMax(iDontHave, N_CARDS_INITIAL_HAND, firstPPAboveMax);

                        if (buffaloHasBeenPlayed(cardsInHistoryArray, N_CARDS) == 1) {

                            //f("THIS IS MY FIRST PP ABOVE MAX: %d\nTHIS IS MY SECOND PP ABOVE MAX: %d\nTHIS IS MY HIGHEST VALUE IN THAT RANGE: %d\n",firstPPAboveMax,secondPPAboveMax,highestValueIHaveInRange(firstPPAboveMax, secondPPAboveMax, hand, numOfCardsInHand));

                            if (highestValueIHaveInRange(firstPPAboveMax, secondPPAboveMax, hand, numOfCardsInHand) != -1) {

                                //printf("NOT MEANT TO BE IN HERE, VALUE BETWEEN FIRST PP OVER MAX AND SECOND PP OVER MAX\n");

                                printf("%d\n", highestValueIHaveInRange(firstPPAboveMax, secondPPAboveMax, hand, numOfCardsInHand));

                            } else {

                                if (highestValueIHaveInRange(maxCardAlreadyPlayed, firstPPAboveMax, hand, numOfCardsInHand) != -1) {

                                    //printf("NOT MEANT TO BE IN HERE, VALUE BETWEEN MAX AND FIRST PP ABOVE MAX\n");

                                    printf("%d\n", highestValueIHaveInRange(maxCardAlreadyPlayed, firstPPAboveMax, hand, numOfCardsInHand));

                                } else {

                                    //printf("YOU ARE MEANT TO BE IN HERE\n");
                                    printf("%d\n", lowestLegalCard(hand, numOfCardsInHand, maxCardAlreadyPlayed));
                                }
                            }
                        } else {

                            printf("%d\n", lowestLegalCard(hand, numOfCardsInHand, maxCardAlreadyPlayed));
                        }
                    }
                }
            } else if (cardsPlayedAlready == 2) {

                //printf("im in p2 [%d]\n",howManyUnderMax(possibleCardsIDontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed));

                int dontHave[N_CARDS_INITIAL_HAND] = {0};

                findPossibleCardsNotPlayedYet(dontHave, cardsInHistoryArray, cardsInHistory, playedCurrentRoundArray,
                                              playedCurrentRoundArray[0], hand, numOfCardsInHand);

                /*for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {
                    printf("PP: %d\n",dontHave[i]);
                }*/

                /*          PICK A CARD
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 * I AM IN THE 3 PLAYER POSITION
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 */

                if (playableUnderTheMax(hand, numOfCardsInHand, maxCardAlreadyPlayed) == 1) {
                    /*              PICK A CARD
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     * I HAVE CARDS UNDER THE MAX I CAN PLAY
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     */

                    if (howManyUnderMax(dontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) >= 1) {

                        /*        PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~
                         * IF THERE IS ONE OR MORE
                         * POSSIBLE UNDER THE MAX
                         * ~~~~~~~~~~~~~~~~~~~~~~~
                         */

                        printf("%d\n", highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                    } else if (howManyUnderMax(dontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) == 0) {

                        /*          PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~
                         * IF THERE IS NO POSSIBLE
                         * PLAYABLE UNDER THE MAX
                         * ~~~~~~~~~~~~~~~~~~~~~~~
                         */
                        int PPover35[N_CARDS_INITIAL_HAND] = {0};

                        possiblePlayableAboveMax(dontHave, maxCardAlreadyPlayed,PPover35);

                        /*                     PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * IF I HAVE AN ELEMENT BELOW ALL THE POSSIBLE PLAYABLE
                         * CARDS ABOVE THE MAX THEN PLAY THE HIGHEST ELEMENT IN
                         * THAT RANGE, IF I DONT, THEN PLAY THE HIGHEST CARDS I
                         * HAVE BELOW THE MAX CARD.
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */
                        int lowestElementAboveMax = findLowestElement(PPover35, N_CARDS_INITIAL_HAND);

                        if (highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand, numOfCardsInHand) == -1) {

                            printf("%d\n", highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                        } else if (highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand, numOfCardsInHand) != -1) {

                            if (buffaloHasBeenPlayed(cardsInHistoryArray, N_CARDS) == 1) {

                                printf("%d\n", highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand, numOfCardsInHand));

                            } else {

                                printf("%d\n", highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                            }
                        }
                    }
                } else {

                    /*          PICK A CARD
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     * IF I DONT HAVE A CARD UNDER
                     * THE MAX TO PLAY
                     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                     */

                    if (howManyUnderMax(dontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) >= 1) {

                        /*      PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~
                         * IF THERE IS ONE OR MORE
                         * POSSIBLE UNDER THE MAX
                         * ~~~~~~~~~~~~~~~~~~~~~~~
                         */

                        printf("%d\n", lowestLegalCard(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                    } else if (howManyUnderMax(dontHave, N_CARDS_INITIAL_HAND, maxCardAlreadyPlayed) == 0) {

                        /*      PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~
                         * IF THERE IS NO POSSIBLE
                         * PLAYABLE UNDER THE MAX
                         * ~~~~~~~~~~~~~~~~~~~~~~~
                         */
                        int PPover35[N_CARDS_INITIAL_HAND] = {0};

                        possiblePlayableAboveMax(dontHave, maxCardAlreadyPlayed,PPover35);

                        /*                      PICK A CARD
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         * IF I HAVE AN ELEMENT BELOW ALL THE POSSIBLE PLAYABLE
                         * CARDS ABOVE THE MAX THEN PLAY THE HIGHEST ELEMENT IN
                         * THAT RANGE, IF I DONT, THEN PLAY THE HIGHEST CARDS I
                         * HAVE BELOW THE MAX CARD.
                         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                         */
                        int lowestElementAboveMax = findLowestElement(PPover35, N_CARDS_INITIAL_HAND);

                        if (highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand, numOfCardsInHand) == -1) {

                            printf("%d\n", lowestLegalCard(hand, numOfCardsInHand, maxCardAlreadyPlayed));

                        } else if (highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand, numOfCardsInHand) != -1) {

                            if (buffaloHasBeenPlayed(cardsInHistoryArray, N_CARDS) == 1) {

                                printf("%d\n", highestValueIHaveInRange(maxCardAlreadyPlayed, lowestElementAboveMax, hand, numOfCardsInHand));
                            }
                        }
                    }
                }
            }
        } else {

            /*              PICK A CARD
             * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             * BUFFALO HASNT BEEN PLAYED THIS ROUND, AIR
             * ON THE SIDE OF CAUTION AND PLAYING MY
             * HIGHEST CARD UNDER THE MAX.
             * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             */

            if (playableUnderTheMax(hand, numOfCardsInHand, maxCardAlreadyPlayed) == 1) {

                printf("%d\n", highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed));

            } else {

                /*              PICK A CARD
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 * IF BUFFALO HASNT BEEN PLAYED, BUT I DONT
                 * HAVE A PLAYABLE UNDER THE MAX THEN
                 * PLAY MY LOWEST LEGAL CARD.
                 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                 */

                int cardsICanPlay[N_CARDS_INITIAL_HAND] = {0};
                fillPossiblePlayableCards(hand,cardsICanPlay,playedCurrentRoundArray[0],numOfCardsInHand);

                if(lowestLegalCard(hand,numOfCardsInHand,maxCardAlreadyPlayed) == BUFFALO){

                    int holder = 99;

                    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

                        if(cardsICanPlay[i] != 0){

                            if(cardsICanPlay[i]%10 > BUFFALO%10 && cardsICanPlay[i]%10 <= holder%10){

                              holder = cardsICanPlay[i];

                            }
                        }
                    }

                    if(holder == 99){

                        printf("%d\n",BUFFALO);
                    } else {

                        printf("%d\n",holder);
                    }

                } else {

                    printf("%d\n", lowestLegalCard(hand, numOfCardsInHand, maxCardAlreadyPlayed));
                }
            }
        }
    } else if (cardsPlayedAlready == 3) {

        /*
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * I AM IN THE LAST POSITION TO PLAY
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        int playableCards[N_CARDS_INITIAL_HAND] = {0};
        int maxCardAlreadyPlayed = 0;

        fillPossiblePlayableCards(hand, playableCards, playedCurrentRoundArray[0], numOfCardsInHand);

        maxCardAlreadyPlayed = findHighestLegalCard(playedCurrentRoundArray[0], playedCurrentRoundArray,
                                                    cardsPlayedAlready);


        /* for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {
             printf("Playable Cards: %d\n",playableCards[i]);
         }

         printf("Max Legal cards Already Played: %d",maxCardAlreadyPlayed);*/

        /*
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * IF IM HOLDING BUFFALO, IT IS A LEGAL
         * CARDS TO PLAY, AND IT IS LOWER THAN
         * THE MAX LEGAL CARD THEN PLAY BUFFALO
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        if (holdingBuffalo(hand, numOfCardsInHand) == 1 && maxCardAlreadyPlayed / 10 == 4 &&
            maxCardAlreadyPlayed > BUFFALO) {

            printf("%d\n", BUFFALO);

        } else {

            /*
             * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             * IF I CANT PLAY BUFFALO, FOR WHATEVER
             * REASON, I DONT HAVE IT, I WILL WIN
             * ETC PLAY MY HIGHEST LEGAL CARD
             * UNDER MAX IF I HAVE ONE, IF I DONT
             * THE PLAY MY LOWEST LEGAL CARD.
             * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             */

            if (playableUnderTheMax(hand, numOfCardsInHand, maxCardAlreadyPlayed) == 1) {

                int highestLegalUnderMax = highestCardIHaveUnderMax(hand, numOfCardsInHand, maxCardAlreadyPlayed);

                printf("%d\n", highestLegalUnderMax);


            } else {


                int PPCards[N_CARDS_INITIAL_HAND] = {0};

                fillPossiblePlayableCards(hand, PPCards, playedCurrentRoundArray[0], numOfCardsInHand);

                sortSmallestToLargest(PPCards, N_CARDS_INITIAL_HAND);

                if(PPCards[9] != BUFFALO) {

                    int highestLegalIAmHolding = PPCards[9];

                    printf("%d\n", highestLegalIAmHolding);

                } else {

                    if(PPCards[8]!= 0){

                        int highestLegalIAmHolding = PPCards[8];

                        printf("%d\n", highestLegalIAmHolding);

                    } else {

                        printf("%d",PPCards[9]);
                    }
                }
            }
        }

    } else if (cardsPlayedAlready == 0) {

        /*
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         * WHEN I AM IN THE FIRST PLAYER POSITION
         * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         */

        if(numOfCardsInHand >= 6){

            int fourtiesCounter = 0;

            for (int i = 0; i < cardsInHistory; ++i) {

                if(cardsInHistoryArray[i] != 0){

                    if(cardsInHistoryArray[i]/10 == 4){

                        fourtiesCounter++;
                    }
                }
            }

            if(fourtiesCounter < 3 && fourtiesCounter > 0){


                int fourtiesInMyHand[N_CARDS_INITIAL_HAND] = {0};

                fillPossiblePlayableCards(hand,fourtiesInMyHand,40,numOfCardsInHand);

                if (countElementsInArray(fourtiesInMyHand,N_CARDS_INITIAL_HAND) != 0){

                    if(lowestLegalCard(hand,numOfCardsInHand,49) <= 43){

                        printf("%d",lowestLegalCard(hand,numOfCardsInHand,49));

                    } else {

                        /*
                         * ~~~~~~~~~~~~~~~
                         * PLAY AS NORMAL
                         * ~~~~~~~~~~~~~~
                         */
                        firstPlayerPosition(hand,numOfCardsInHand,cardsInHistoryArray);
                    }
                } else {

                    /*
                     * ~~~~~~~~~~~~~~
                     * PLAY AS NORMAL
                     * ~~~~~~~~~~~~~~
                     */
                    firstPlayerPosition(hand,numOfCardsInHand,cardsInHistoryArray);
                }
            } else {

                /*
                 * ~~~~~~~~~~~~~~
                 * PLAY AS NORMAL
                 * ~~~~~~~~~~~~~
                 */
                firstPlayerPosition(hand,numOfCardsInHand,cardsInHistoryArray);
            }
        } else {

            /*
             * ~~~~~~~~~~~~~~
             * PLAY AS NORMAL
             * ~~~~~~~~~~~~~~
             */
            firstPlayerPosition(hand,numOfCardsInHand,cardsInHistoryArray);
        }
    }
}

/*                   ASSERTS
 * =================================================
 * TESTING STRATEGY FOR MY ASSERTS!
 * =================================================
 * STARTING OF I WILL TEST THE EDGE CASES FOR EACH
 * FUNCTION MAKING SURE THEY WORK AS EXPECTED, I
 * WILL ALSO THEN  TEST THE EXPECTED OUT PUT FOR
 * EACH SECTION OF THE PROGRAM, FROM NAME OUTPUT
 * TO DISCARDS AND THROUGH TO PICK A CARDS, THEN
 * FINALLY I WILL TEST THE STRATEGY SPECIFIC CASES
 * FOR EACH SECTION OF THE PROGRAM FROM DISCARDS
 * THROUGH EACH SECTION OF PICK A CARD.
 * ===============================================
 */

void run_unit_tests(void) {

    /*
     * =========================
     * THESE ARE MY ASSERTS HERE
     * =========================
     */

    //FOR HOLDING VALID FUNCTION

    int holdingValidHandArray[N_CARDS_INITIAL_HAND] = {10,11,12,13,14,15,16,17,18,19};
    assert(holdingValid(20,holdingValidHandArray,N_CARDS_INITIAL_HAND) == 0);
    assert(holdingValid(30,holdingValidHandArray,N_CARDS_INITIAL_HAND) == 0);
    assert(holdingValid(40,holdingValidHandArray,N_CARDS_INITIAL_HAND) == 0);
    assert(holdingValid(10,holdingValidHandArray,N_CARDS_INITIAL_HAND) == 1);

    //HOLDING BUFFALO FUNCTION

    int holdingBuffaloHandArray[N_CARDS_INITIAL_HAND] = {10,11,12,13,14,15,16,17,18,19};
    assert(holdingBuffalo(holdingBuffaloHandArray,N_CARDS_INITIAL_HAND) == 0);
    holdingBuffaloHandArray[9] = 47;
    assert(holdingBuffalo(holdingBuffaloHandArray,N_CARDS_INITIAL_HAND) == 1);

    //HIGHEST CALF OVER THIRTY FUNCTION

    int highestCalfOverThirtyFiveHandArray[N_CARDS_INITIAL_HAND] = {10,11,12,13,30,31,32,33,37,35};
    assert(highestCalfOverThirtyFive(highestCalfOverThirtyFiveHandArray,N_CARDS_INITIAL_HAND) == 37);
    highestCalfOverThirtyFiveHandArray[8] = 11;
    assert(highestCalfOverThirtyFive(highestCalfOverThirtyFiveHandArray,N_CARDS_INITIAL_HAND) == 35);
    highestCalfOverThirtyFiveHandArray[9] = 12;

    assert(highestCalfOverThirtyFive(highestCalfOverThirtyFiveHandArray,N_CARDS_INITIAL_HAND) == -1);

    //HIGHEST NON CALF OVER THIRTY FIVE
    int highestNonCalfOverThirtyFiveHandArray[N_CARDS_INITIAL_HAND] = {10,11,12,18,30,31,32,33,37,35};
    assert(highestNonCalfOverThirtyFive(highestNonCalfOverThirtyFiveHandArray,N_CARDS_INITIAL_HAND) == 18);

    //HIGHEST NON DISCRIMINANT OVER THIRTY FIVE
    int highestNonDiscriminantCardHandArray[N_CARDS_INITIAL_HAND] = {10,11,12,18,30,31,32,33,37,35};
    assert(highestNonDiscriminantCard(highestNonDiscriminantCardHandArray,N_CARDS_INITIAL_HAND) == 37);

    //FILL POSSIBLE PLAYABLE CARDS
    int firstCardPlayed = 20;
    int fillPossiblePlayableHandArray[N_CARDS_INITIAL_HAND] = {10,11,12,13,14,15,16,17,18,21};
    int possibePlayable[N_CARDS_INITIAL_HAND] = {0};
    assert(fillPossiblePlayableCards(fillPossiblePlayableHandArray,possibePlayable,firstCardPlayed,N_CARDS_INITIAL_HAND) == possibePlayable);

    //SORT SMALLEST TO LARGEST
    int smallestToLargestArray[3] = {20,10,9};
    int sorted[3] = {9,10,20};
    assert(sortSmallestToLargest(smallestToLargestArray,3) == smallestToLargestArray);

    //PLAYABLE UNDER THE MAX
    int maxForPlayableUnderTheMax = 45;
    int handForPlayableUnderTheMax[N_CARDS_INITIAL_HAND] = {10,11,12,13,14,15,16,17,18,41};
    assert(playableUnderTheMax(handForPlayableUnderTheMax,N_CARDS_INITIAL_HAND,maxForPlayableUnderTheMax) == 1);
    handForPlayableUnderTheMax[9] = 47;
    assert(playableUnderTheMax(handForPlayableUnderTheMax,N_CARDS_INITIAL_HAND,maxForPlayableUnderTheMax) == 0);

    //FIND HIGHEST LEGAL CARD
    int highestLegalCardHandArray[N_CARDS_INITIAL_HAND] = {10,11,12,13,14,15,16,17,18,41};
    int legalCard = 10;
    assert(findHighestLegalCard(legalCard,highestLegalCardHandArray,N_CARDS_INITIAL_HAND) == 18);
    highestLegalCardHandArray[8] = 44;
    assert(findHighestLegalCard(legalCard,highestLegalCardHandArray,N_CARDS_INITIAL_HAND) == 17);

    //COUNT ELEMENTS IN ARRAY
    int arrayForCountElementsInArray[N_CARDS_INITIAL_HAND] = {10,11,12,0,0};
    assert(countElementsInArray(arrayForCountElementsInArray,5) == 3);
    int arrayForCountElementsInArray2[N_CARDS_INITIAL_HAND] = {10,11,12};
    assert(countElementsInArray(arrayForCountElementsInArray2,3) == 3);

    //HOW MANY UNDER MAX
    int PPForHowManyUnderMax[5] = {10,11,12,13,14};
    assert(howManyUnderMax(PPForHowManyUnderMax,5,15) == 5);

    //HIGHEST CARD I HAVE UNDER MAX
    int PPForHighestUnderMax[5] = {10,11,12,13,14};
    assert(highestCardIHaveUnderMax(PPForHighestUnderMax,5,15) == 14);

    //FIND LOWEST ELEMENT
    int arrayForLowestElement[N_CARDS_INITIAL_HAND] = {10,11,12,13,14,15,16,17,18,41};
    assert(findLowestElement(arrayForLowestElement,N_CARDS_INITIAL_HAND) == 10);

    //HIGHEST VALUE I HAVE IN RANGE
    int arrayForHighestValueInRange[N_CARDS_INITIAL_HAND] = {10,11,12,13,14,15,16,17,18,41};
    assert(highestValueIHaveInRange(10,18,arrayForHighestValueInRange,N_CARDS_INITIAL_HAND) == 17);

    //LOWEST LEGAL CARD
    int arrayForLowestLegalCard[N_CARDS_INITIAL_HAND] = {10,11,12,13,14,15,16,17,18,41};
    assert(lowestLegalCard(arrayForLowestLegalCard,N_CARDS_INITIAL_HAND,18) == 10);

    //BUFFALO HAS BEEN PLAYED
    int cardsInHistoryForBuffaloPlayed[N_CARDS_INITIAL_HAND] = {10,11,12,13,14,15,16,17,18,47};
    int cardsThisRoundForBuffaloPlayed[MAX_PREVIOUSLY_PLAYED_CARDS] = {40,42,45};
    assert(buffaloHasBeenPlayed(cardsInHistoryForBuffaloPlayed,N_CARDS_INITIAL_HAND) == 1);
    assert(buffaloHasBeenPlayed(cardsThisRoundForBuffaloPlayed,MAX_PREVIOUSLY_PLAYED_CARDS) == 0);

    //FIRST POSSIBLE PLAYABLE ABOVE MAX
    int maxForFirstPossiblePlayableAboveMax = 29;
    int dontHaveForFirstPossiblePlayableAboveMax[N_CARDS_INITIAL_HAND] = {20,22,23,24,25,26,27,28};
    assert(firstPossiblePlayableAboveMax(dontHaveForFirstPossiblePlayableAboveMax,8,maxForFirstPossiblePlayableAboveMax) == -1);

    //CALF PREVIOUSLY PLAYED
    int previouslyPlayedForCalfsPreviouslyPlayed[N_CARDS_INITIAL_HAND] = {20,22,23,24,25,26,27,28};
    assert(calfPreviouslyPlayed(previouslyPlayedForCalfsPreviouslyPlayed) == 0);

}


/*
 * ======================
 * THESE ARE MY FUNCTIONS
 * ======================
 */

int holdingValid(int firstCardPlayed, int hand[N_CARDS_INITIAL_HAND], int numCardsInHand) {

    int flag = 0;

    //LOOPING THROUGH MY HAND TO SEE IF I HAVE ANY VALID CARDS TO PLAY IN RELATION TO THE FIRST PLAYERS CARD.
    for (int i = 0; i < numCardsInHand; ++i) {

        if (hand[i] / 10 == firstCardPlayed / 10) {

            flag = 1;
        }
    }

    return flag;
}

int holdingBuffalo(int hand[N_CARDS_INITIAL_HAND], int numOfCardsInHand) {

    int flag = 0;

    for (int i = 0; i < numOfCardsInHand; ++i) {

        if (hand[i] == BUFFALO) {

            flag = 1;

        }
    }
    return flag;
}

int highestCalfOverThirtyFive(int hand[N_CARDS_INITIAL_HAND], int numCardsInHand) {

    int highestCalf = 0;

    for (int i = 0; i < numCardsInHand; ++i) {

        if (hand[i] >= 35 && hand[i] < 40) {

            if (hand[i] > highestCalf) {

                highestCalf = hand[i];

            }
        }
    }

    if (highestCalf == 0) {

        return -1;
    }
    return highestCalf;
}

int highestNonCalfOverThirtyFive(int hand[N_CARDS_INITIAL_HAND], int numCardsInHand) {

    int highestNonCalf = 0;

    for (int i = 0; i < numCardsInHand; ++i) {

        if (hand[i] / 10 != 3) {

            if (hand[i] % 10 >= 5) {

                if (hand[i] % 10 > highestNonCalf % 10) {

                    highestNonCalf = hand[i];
                }
            }
        }
    }

    if (highestNonCalf == 0) {

        return -1;
    }
    return highestNonCalf;
}

int highestNonDiscriminantCard(int hand[N_CARDS_INITIAL_HAND], int numCardsInHand) {

    int highestCard = 0;

    for (int i = 0; i < numCardsInHand; ++i) {

        if (hand[i] > highestCard) {

            highestCard = hand[i];
        }
    }

    return highestCard;
}

int * fillPossiblePlayableCards(int hand[], int playableCardsArray[], int firstCardPlayed, int cardsInHand) {

    int playableCardsCounter = 0;

    for (int i = 0; i < cardsInHand; ++i) {

        if (hand[i] / 10 == firstCardPlayed / 10 && hand[i] != 0) {

            playableCardsArray[playableCardsCounter] = hand[i];

            playableCardsCounter++;
        }
    }

    sortSmallestToLargest(playableCardsArray, playableCardsCounter);

    return playableCardsArray;
}

int *sortSmallestToLargest(int array[], int size) {

    int notSorted = 0;

    while (notSorted == 0) {

        int flag = 0;

        for (int i = 1; i < size; i++) {

            if (array[i] < array[i - 1]) {

                int temp = array[i];

                array[i] = array[i - 1];

                array[i - 1] = temp;

                flag = 1;
            }
        }

        if (flag == 0) {
            notSorted = 1;
        }
    }

    return array;
}

int *readInCardsFromInput(int *hand, int numOfCardsInHand) {

    for (int i = 0; i < numOfCardsInHand; ++i) {

        scanf("%d", &hand[i]);

    }

    return hand;
}

int playableUnderTheMax(int hand[], int sizeOfArray, int maxCardAlreadyPlayed) {

    int flag = 0;

    for (int i = 0; i < sizeOfArray; ++i) {

        if (hand[i] / 10 == maxCardAlreadyPlayed / 10) {

            if (hand[i] % 10 < maxCardAlreadyPlayed % 10) {

                flag = 1;

            }
        }
    }

    if (flag == 1) {

        return 1;
    }
    return 0;
}

int findHighestLegalCard(int firstCardInTheRound, int cardsPlayedThisRound[], int amountOfCardsPlayedThisRound) {

    for (int i = 0; i < amountOfCardsPlayedThisRound; ++i) {

        if (cardsPlayedThisRound[i] != firstCardInTheRound) {

            if (cardsPlayedThisRound[i] / 10 == firstCardInTheRound / 10) {

                if (cardsPlayedThisRound[i] > firstCardInTheRound) {

                    firstCardInTheRound = cardsPlayedThisRound[i];

                }
            }
        }
    }
    return firstCardInTheRound;
}

int *
findPossibleCardsNotPlayedYet(int possibleCardsNotPlayedYet[], int cardsPlayedInHistory[], int numCardsPlayedInHistory,
                              int cardsPlayedThisRound[], int firstCardPlayedThisRound, int hand[],
                              int numCardsInHand) {

    int relativeTensGroup[N_CARDS_INITIAL_HAND] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int multiplier = ((firstCardPlayedThisRound / 10));
    multiplier = multiplier * 10;
    int newPositionCounter = 0;


    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

        relativeTensGroup[i] += multiplier;
        //printf("MY RELATIVE: %d",relativeTensGroup[i]);
    }

    for (int j = 0; j < numCardsPlayedInHistory; ++j) {

        for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

            if (relativeTensGroup[i] == cardsPlayedInHistory[j]) {

                relativeTensGroup[i] = 0;
            }
        }
    }

    for (int k = 0; k < MAX_PREVIOUSLY_PLAYED_CARDS; ++k) {

        for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

            if (cardsPlayedThisRound[k] != 0) {

                if (relativeTensGroup[i] == cardsPlayedThisRound[k]) {

                    relativeTensGroup[i] = 0;
                }
            }
        }
    }

    for (int m = 0; m < numCardsInHand; ++m) {

        for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

            if (relativeTensGroup[i] != 0) {

                if (relativeTensGroup[i] == hand[m]) {

                    relativeTensGroup[i] = 0;
                }
            }
        }
    }

    for (int l = 0; l < N_CARDS_INITIAL_HAND; ++l) {

        if (relativeTensGroup[l] != 0) {

            possibleCardsNotPlayedYet[newPositionCounter] = relativeTensGroup[l];
            newPositionCounter++;
        }
    }

    sortSmallestToLargest(possibleCardsNotPlayedYet, newPositionCounter + 1);

    return possibleCardsNotPlayedYet;
}

int countElementsInArray(int array[], int sizeOfArray) {

    int elements = 0;

    for (int i = 0; i < sizeOfArray; ++i) {

        if (array[i] != 0) {

            elements++;

        }
    }

    return elements;
}

int howManyUnderMax(int possiblePlayable[], int possiblePlayableSize, int max) {

    int counter = 0;

    for (int i = 0; i < possiblePlayableSize; ++i) {

        if (possiblePlayable[i] != 0) {

            if (possiblePlayable[i]%10 < max%10) {

                counter++;
            }
        }
    }
    return counter;
}

int highestCardIHaveUnderMax(int hand[], int handSize, int max) {

    int highestCardIHave = 0;

    for (int i = 0; i < handSize; ++i) {

        if (hand[i] != 0) {

            if (hand[i] / 10 == max / 10) {

                if (hand[i] > highestCardIHave && hand[i] < max) {

                    highestCardIHave = hand[i];

                }
            }
        }
    }
    return highestCardIHave;
}

int *possiblePlayableAboveMax(int arrayOfPossibleCards[], int max, int newArrayToStore[]) {

    int counter = 0;

    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

        if (arrayOfPossibleCards[i] != 0) {

            if (arrayOfPossibleCards[i]%10 > max%10) {

                newArrayToStore[counter] = arrayOfPossibleCards[i];
                counter++;
            }
        }
    }
    return arrayOfPossibleCards;
}

int findLowestElement(int array[], int arraySize) {

    int lowest = 99;

    for (int i = 0; i < arraySize; ++i) {

        if (array[i] != 0) {

            if (array[i]%10 <= lowest%10) {

                lowest = array[i];
            }
        }
    }
    return lowest;
}

int highestValueIHaveInRange(int lower, int upper, int hand[], int numCardsInHand) {

    int highestValue = 0;

    for (int i = 0; i < numCardsInHand; ++i) {

        if (hand[i] > lower && hand[i] < upper) {

            if (hand[i] > highestValue) {

                highestValue = hand[i];

            }
        }
    }

    if (highestValue == 0) {
        return -1;
    }

    return highestValue;
}

int lowestLegalCard(int hand[], int numCardsInHand, int maxLegalCardThisRound) {

    int lowestLegal = 99;

    for (int i = 0; i < numCardsInHand; ++i) {

        if (hand[i]/10 == maxLegalCardThisRound/10) {

            if (hand[i]%10 <= lowestLegal%10) {

                lowestLegal = hand[i];
            }
        }
    }

    if(lowestLegal == 99){
        return -1;
    }
    return lowestLegal;
}

int buffaloHasBeenPlayed(int cardsPlayedThisRound[], int size) {

    int flag = 0;

    for (int i = 0; i < size; ++i) {

        if (cardsPlayedThisRound[i] == 47) {

            flag = 1;
        }
    }
    if (flag == 1) {

        return 1;

    }
    return 0;
}

int firstPossiblePlayableAboveMax(int possiblePlayablesIdontHave[], int sizeOfPossible, int maxCardPlayed) {

    int finalArray[N_CARDS_INITIAL_HAND] = {0};

    int arrayCounter = 0;

    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

        if(possiblePlayablesIdontHave[i] != 0){

            if(possiblePlayablesIdontHave[i] %10 > maxCardPlayed%10){

                finalArray[arrayCounter] = possiblePlayablesIdontHave[i];
                arrayCounter++;
            }
        }
    }

    sortSmallestToLargest(finalArray,N_CARDS_INITIAL_HAND);

    if(countElementsInArray(finalArray,N_CARDS_INITIAL_HAND) != 0) {

        int reduce = N_CARDS_INITIAL_HAND - countElementsInArray(finalArray, N_CARDS_INITIAL_HAND);

        return finalArray[reduce];
    }
    return -1;
}

int calfPreviouslyPlayed(int allPreviouslyPlayedCards[]) {

    int flag = 0;

    for (int i = 0; i < N_CARDS; ++i) {

        if (allPreviouslyPlayedCards[i] != 0) {

            if (allPreviouslyPlayedCards[i] / 10 == 3) {

                flag = 1;

            }
        }
    }
    return flag;
}

int *calfsInMyHand(int calfsInMyHand[], int hand[], int numCardsInhand) {

    int counter = 0;

    for (int i = 0; i < numCardsInhand; ++i) {

        if (hand[i] != 0) {

            if (hand[i] / 10 == 3) {

                calfsInMyHand[counter] = hand[i];
                counter++;
            }
        }
    }
    return calfsInMyHand;
}

int findKeyTipOverCalf(int calfsThatHaventBeenPlayed[], int numOfCalfsThatHaventBeenPlayed, int calfsInMyhand[],
                       int numOfCalfsInHand) {

    int tipOver = 0;
    int backUp = 0;

    int starterNumber = 0;

    for (int l = 0; l < numOfCalfsThatHaventBeenPlayed; ++l) {

        if (calfsThatHaventBeenPlayed[l] != 0) {

            starterNumber = calfsThatHaventBeenPlayed[l];
        }
    }

    starterNumber = starterNumber / 10;
    starterNumber = (starterNumber * 10) + 2;

    int endNumber = starterNumber + 8;

    for (int i = starterNumber; i < endNumber; ++i) {

        int counter = 0;
        int inHandCounter = 0;

        for (int j = 0; j < numOfCalfsThatHaventBeenPlayed; ++j) {

            if (calfsThatHaventBeenPlayed[j] < i) {

                for (int k = 0; k < numOfCalfsInHand; ++k) {

                    if (calfsInMyhand[k] != 0) {

                        if (calfsInMyhand[k] < i) {

                            inHandCounter++;
                        }
                    }
                }
                counter++;
            }
        }

        if (counter - inHandCounter == 2) {

            tipOver = i;

        } else if (counter - inHandCounter == 1) {

            backUp = i;
        }
    }

    if (tipOver == 0) {

        if (backUp == 0) {

            return -1;

        } else {

            return backUp;

        }
    }

    return tipOver;
}

int lowestCalf(int hand[], int numCardsInHand) {

    int lowest = 100;

    for (int i = 0; i < numCardsInHand; ++i) {

        if (hand[i] / 10 == 3) {

            if (hand[i] < lowest) {

                lowest = hand[i];
            }
        }
    }
    return lowest;
}

void playGoodNonCalfFirstCard(int hand[], int numCardsInHand, int previousCardsPlayedArray[],
                              int numPreviouslyPlayedCards, int cardsPlayedThisRound[], int numCardsPlayedThisRound) {

    /*
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * CHECK IF IM HOLDING A CARD IN EACH
     * TENS GROUP EXCLUDING 30'S AND IF
     * SO FILL AN ARRAY WITH ALL THE CARDS
     * I HAVE IN EACH TENS GROUP.
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */

    //10'S

    int arrayOfTensIHave[N_CARDS_INITIAL_HAND] = {0};

    if (holdingValid(10, hand, numCardsInHand) == 1) {

        fillPossiblePlayableCards(hand, arrayOfTensIHave, 10, numCardsInHand);
    }


    int tensThatHaventBeenPlayed[N_CARDS_INITIAL_HAND] = {0};

    findPossibleCardsNotPlayedYet(tensThatHaventBeenPlayed, previousCardsPlayedArray, numPreviouslyPlayedCards,
                                  cardsPlayedThisRound, 10, hand, numCardsInHand);

    //20's
    int arrayOfTwentiesIHave[N_CARDS_INITIAL_HAND] = {0};

    if (holdingValid(20, hand, numCardsInHand) == 1) {

        fillPossiblePlayableCards(hand, arrayOfTwentiesIHave, 20, numCardsInHand);
    }

    int twentiesThatHaventBeenPlayed[N_CARDS_INITIAL_HAND] = {0};

    findPossibleCardsNotPlayedYet(twentiesThatHaventBeenPlayed, previousCardsPlayedArray, numPreviouslyPlayedCards,
                                  cardsPlayedThisRound, 20, hand, numCardsInHand);

    //40's
    int arrayOfFourtiesIHave[N_CARDS_INITIAL_HAND] = {0};

    if (holdingValid(40, hand, numCardsInHand) == 1) {

        fillPossiblePlayableCards(hand, arrayOfFourtiesIHave, 40, numCardsInHand);
    }

    int fourtiesThatHaventBeenPlayed[N_CARDS_INITIAL_HAND] = {0};

    findPossibleCardsNotPlayedYet(fourtiesThatHaventBeenPlayed, previousCardsPlayedArray, numPreviouslyPlayedCards,
                                  cardsPlayedThisRound, 40, hand, numCardsInHand);

    //AMOUNT OF EACH TENS GROUP I HAVE.
    int numOfTensIHave = countElementsInArray(arrayOfTensIHave, N_CARDS_INITIAL_HAND);

    int numOfTwentiesIHave = countElementsInArray(arrayOfTwentiesIHave, N_CARDS_INITIAL_HAND);

    int numOfFourtiesIHave = countElementsInArray(arrayOfFourtiesIHave, N_CARDS_INITIAL_HAND);


    //MEDIANS FOR EACH GROUP

    int medianForTen = findKeyTipOverCalf(tensThatHaventBeenPlayed, N_CARDS_INITIAL_HAND, arrayOfTensIHave,
                                          numOfTensIHave);

    int medianForTwenty = findKeyTipOverCalf(twentiesThatHaventBeenPlayed, N_CARDS_INITIAL_HAND, arrayOfTwentiesIHave,
                                             numOfTwentiesIHave);

    int medianForFourties = findKeyTipOverCalf(fourtiesThatHaventBeenPlayed, N_CARDS_INITIAL_HAND, arrayOfFourtiesIHave,
                                               numOfFourtiesIHave);


    int tenFlag = 0;

    int twentyFlag = 0;

    int fourtyFlag = 0;

    if (numOfTensIHave >= numOfFourtiesIHave && numOfTensIHave >= numOfTwentiesIHave) {

        if (medianForTen != -1) {

            int play = highestCardIHaveUnderMax(hand, numCardsInHand, medianForTen);

            printf("%d\n", play);

        } else {

            tenFlag = 1;
        }
    } else if (numOfTwentiesIHave >= numOfTensIHave && numOfTwentiesIHave >= numOfFourtiesIHave) {

        if (medianForTwenty != -1) {

            int play = highestCardIHaveUnderMax(hand, numCardsInHand, medianForTwenty);

            printf("%d\n", play);
        } else {

            twentyFlag = 1;
        }
    } else if (numOfFourtiesIHave >= numOfTensIHave && numOfFourtiesIHave >= numOfTwentiesIHave) {

        if (medianForFourties != -1) {

            int play = highestCardIHaveUnderMax(hand, numCardsInHand, medianForFourties);

            printf("%d\n", play);
        } else {

            fourtyFlag = 1;
        }
    }

    if (tenFlag == 1) {

        if (medianForTwenty == -1) {

            if (medianForFourties == -1) {

                int play = findLowestElement(hand, numCardsInHand);

                printf("%d\n", play);
            } else {

                int play = highestCardIHaveUnderMax(hand, numCardsInHand, medianForFourties);

                printf("%d\n", play);

            }
        } else {
            int play = highestCardIHaveUnderMax(hand, numCardsInHand, medianForTwenty);

            printf("%d\n", play);
        }
    } else if (twentyFlag == 1) {

        if (medianForFourties == -1) {

            if (medianForTen == -1) {

                int play = findLowestElement(hand, numCardsInHand);

                printf("%d\n", play);

            } else {

                int play = highestCardIHaveUnderMax(hand, numCardsInHand, medianForTen);

                printf("%d\n", play);

            }
        } else {

            int play = highestCardIHaveUnderMax(hand, numCardsInHand, medianForFourties);

            printf("%d\n", play);

        }
    } else if (fourtyFlag == 1) {

        if (medianForTen == -1) {

            if (medianForTwenty == -1) {

                int play = findLowestElement(hand, numCardsInHand);

                printf("%d\n", play);

            } else {

                int play = highestCardIHaveUnderMax(hand, numCardsInHand, medianForTwenty);

                printf("%d\n", play);

            }
        } else {

            int play = highestCardIHaveUnderMax(hand, numCardsInHand, medianForTen);

            printf("%d\n", play);

        }
    }
    /*//////TESTING
    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

        printf("THIS IS MY ARRAY OF TENS: %d\n",arrayOfTensIHave[i]);
    }
    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

        printf("THESE ARE TENS NOT PLAYED YET: %d\n",tensThatHaventBeenPlayed[i]);
    }
    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

        printf("THIS IS MY ARRAY OF TWENTIES: %d\n",arrayOfTwentiesIHave[i]);
    }
    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

        printf("THESE ARE TWENTIES NOT PLAYED YET: %d\n",twentiesThatHaventBeenPlayed[i]);
    }
    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

        printf("THIS IS MY ARRAY OF FOURTIES: %d\n",arrayOfFourtiesIHave[i]);
    }
    for (int i = 0; i < N_CARDS_INITIAL_HAND; ++i) {

        printf("THESE ARE FOURTIES THAT HAVENT BEEN PLAYED YET: %d\n",fourtiesThatHaventBeenPlayed[i]);
    }
    printf("I HAVE THIS MANY TENS: %d\nTHIS MANY TWENTIES: %d\nAND THIS MANY FOURTIES:%d\n",numOfTensIHave,numOfTwentiesIHave,numOfFourtiesIHave);
    printf("MEDIAN FOR TENS: %d\nMEDIAN FOR TWENTIES: %d\nMEDIAN FOURTIES:%d\n",medianForTen,medianForTwenty,medianForFourties);*/
}

int highestNonCalfBuffalo(int hand[], int numCardsInHand) {

    int highest = 0;
    int highestCalf = 0;


    for (int i = 0; i < numCardsInHand; ++i) {

        if (hand[i] / 10 != 3 && hand[i] != 47) {

            if (hand[i] > highest) {

                highest = hand[i];
            }
        } else if (hand[i] / 10 == 3) {

            if (hand[i] > highestCalf) {

                highestCalf = hand[i];
            }
        }
    }
    if (highest == 0) {

        return highestCalf;
    } else if (highest == 0 && highestCalf == 0) {

        return BUFFALO;
    }
    return highest;
}

void firstPlayerPosition(int hand[],int numCardsInHand,int cardsInHistory[]){

    /*
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * FINDING LEAST PLAYED TENS GROUP
     * IN HISTORY
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     */

    int tensPlayed = 0;
    int twentiesPlayed = 0;
    int thirtiesPlayed = 0;
    int fourtiesPlayed = 0;

    for (int j = 0; j < N_CARDS; ++j) {

        if(cardsInHistory[j]!= 0){

            if(cardsInHistory[j]/10 == 1){

                tensPlayed++;

            } else if(cardsInHistory[j]/10 == 2){

                twentiesPlayed++;

            } else if (cardsInHistory[j]/10 == 3) {

                thirtiesPlayed++;

            } else if (cardsInHistory[j]/10 == 4){

                fourtiesPlayed++;

            }
        }
    }
    int sizeArray[4] = {tensPlayed,twentiesPlayed,thirtiesPlayed,fourtiesPlayed};

    sortSmallestToLargest(sizeArray,4);

    int playableTens[N_CARDS_INITIAL_HAND] = {0};
    fillPossiblePlayableCards(hand,playableTens,10,numCardsInHand);

    int playableTwenties[N_CARDS_INITIAL_HAND] = {0};
    fillPossiblePlayableCards(hand,playableTwenties,10,numCardsInHand);

    int playableThirties[N_CARDS_INITIAL_HAND] = {0};
    fillPossiblePlayableCards(hand,playableThirties,10,numCardsInHand);

    int playableFourties[N_CARDS_INITIAL_HAND] = {0};
    fillPossiblePlayableCards(hand,playableFourties,10,numCardsInHand);

    int tensFlag = playableUnderTheMax(playableTens,numCardsInHand,14);
    int twentiesFlag = playableUnderTheMax(playableTwenties,numCardsInHand,24);
    int thirtiesFlag = playableUnderTheMax(playableThirties,numCardsInHand,34);
    int fourtiesFlag = playableUnderTheMax(playableFourties,numCardsInHand,44);

    if(fourtiesFlag == 1){

        printf("%d\n",highestCardIHaveUnderMax(playableFourties,numCardsInHand,44));
    } else if(thirtiesFlag == 1 && calfPreviouslyPlayed(cardsInHistory) == 1){

        printf("%d\n",highestCardIHaveUnderMax(playableThirties,numCardsInHand,34));
    } else if(tensPlayed < twentiesPlayed && twentiesFlag == 1){

        printf("%d\n",highestCardIHaveUnderMax(playableTwenties,numCardsInHand,24));
    } else if(tensPlayed > twentiesPlayed && tensFlag == 1){

        printf("%d\n",highestCardIHaveUnderMax(playableTens,numCardsInHand,14));
    } else {

        sortSmallestToLargest(hand, numCardsInHand);

        int position = 99;

        if (calfPreviouslyPlayed(cardsInHistory) == 1) {

            position = findLowestElement(hand, numCardsInHand);

        } else {

            for (int i = 0; i < numCardsInHand; ++i) {

                if (hand[i] != 0 && hand[i] / 10 != 3) {

                    if (hand[i] % 10 <= position % 10) {

                        position = hand[i];
                    }
                }
            }
        }
        printf("%d\n", position);
    }
}
