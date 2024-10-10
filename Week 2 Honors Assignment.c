#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define HAND_SIZE 7
#define NUM_SIMULATIONS 1000000

// Define the suits using an enum
typedef enum {
    Hearts, Diamonds, Clubs, Spades
} Suit;

// Define the card struct with suit and pip values
typedef struct {
    Suit suit;
    short pips;  // 1 to 13, where 1 = Ace, 11 = Jack, 12 = Queen, 13 = King
} Card;

// Function to initialize a deck of 52 cards
void initializeDeck(Card deck[]) {
    int index = 0;
    for (int suit = Hearts; suit <= Spades; suit++) {
        for (int pips = 1; pips <= 13; pips++) {
            deck[index].suit = (Suit)suit;
            deck[index].pips = pips;
            index++;
        }
    }
}

// Function to shuffle the deck 
void shuffleDeck(Card deck[]) {
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Function to count frequencies of pips in a hand
void countPips(int pipsCount[], Card hand[]) {
    for (int i = 0; i < 13; i++) {
        pipsCount[i] = 0; // Initialize all counts to 0
    }
    for (int i = 0; i < HAND_SIZE; i++) {
        pipsCount[hand[i].pips - 1]++; // Increment the corresponding pip count
    }
}

// Function to check if the hand has a flush (all cards of the same suit)
int isFlush(Card hand[]) {
    Suit suit = hand[0].suit;
    for (int i = 1; i < HAND_SIZE; i++) {
        if (hand[i].suit != suit) {
            return 0;
        }
    }
    return 1;
}

// Function to check if the hand has a straight
int isStraight(int pipsCount[]) {
    int consecutive = 0;
    for (int i = 0; i < 13; i++) {
        if (pipsCount[i] > 0) {
            consecutive++;
            if (consecutive == 5) {
                return 1;  // Found a straight
            }
        } else {
            consecutive = 0;
        }
    }
    // Special case: Ace can be low in A, 2, 3, 4, 5
    if (pipsCount[0] > 0 && pipsCount[1] > 0 && pipsCount[2] > 0 && pipsCount[3] > 0 && pipsCount[12] > 0) {
        return 1;
    }
    return 0;
}

// Function to check if the hand has a royal flush
int isRoyalFlush(Card hand[]) {
    int pipsCount[13];
    countPips(pipsCount, hand);
    if (isFlush(hand) && pipsCount[0] > 0 && pipsCount[9] > 0 && pipsCount[10] > 0 && pipsCount[11] > 0 && pipsCount[12] > 0) {
        return 1;
    }
    return 0;
}

// Function to check if the hand has a straight flush
int isStraightFlush(Card hand[]) {
    int pipsCount[13];
    countPips(pipsCount, hand);
    return (isFlush(hand) && isStraight(pipsCount));
}

// Function to determine hand type (no pair, one pair, etc.)
void evaluateHand(Card hand[], int *noPair, int *onePair, int *twoPair, int *threeOfKind, int *fullHouse, int *fourOfKind, int *flush, int *straight, int *straightFlush, int *royalFlush) {
    int pipsCount[13];
    countPips(pipsCount, hand);
    
    int pairCount = 0, threeCount = 0, fourCount = 0;

    // Count pairs, triples, and quadruples
    for (int i = 0; i < 13; i++) {
        if (pipsCount[i] == 2) pairCount++;
        else if (pipsCount[i] == 3) threeCount++;
        else if (pipsCount[i] == 4) fourCount++;
    }

    // Classify the hand based on counts
    if (isRoyalFlush(hand)) {
        (*royalFlush)++;
    } else if (isStraightFlush(hand)) {
        (*straightFlush)++;
    } else if (fourCount == 1) {
        (*fourOfKind)++;
    } else if (threeCount == 1 && pairCount >= 1) {
        (*fullHouse)++;
    } else if (isFlush(hand)) {
        (*flush)++;
    } else if (isStraight(pipsCount)) {
        (*straight)++;
    } else if (threeCount == 1) {
        (*threeOfKind)++;
    } else if (pairCount == 2) {
        (*twoPair)++;
    } else if (pairCount == 1) {
        (*onePair)++;
    } else {
        (*noPair)++;
    }
}

// Main function to simulate the process
int main() {
    srand(time(NULL));

    Card deck[DECK_SIZE];
    Card hand[HAND_SIZE];
    int noPair = 0, onePair = 0, twoPair = 0, threeOfKind = 0, fullHouse = 0, fourOfKind = 0;
    int flush = 0, straight = 0, straightFlush = 0, royalFlush = 0;

    initializeDeck(deck);

    for (int i = 0; i < NUM_SIMULATIONS; i++) {
        shuffleDeck(deck);

        // Deal a 7-card hand
        for (int j = 0; j < HAND_SIZE; j++) {
            hand[j] = deck[j];
        }

        // Evaluate the hand
        evaluateHand(hand, &noPair, &onePair, &twoPair, &threeOfKind, &fullHouse, &fourOfKind, &flush, &straight, &straightFlush, &royalFlush);
    }

    // Print the results
    printf("After %d hands:\n", NUM_SIMULATIONS);
    printf("No Pair: %.6f%%\n", (noPair / (double)NUM_SIMULATIONS) * 100);
    printf("One Pair: %.6f%%\n", (onePair / (double)NUM_SIMULATIONS) * 100);
    printf("Two Pair: %.6f%%\n", (twoPair / (double)NUM_SIMULATIONS) * 100);
    printf("Three of a Kind: %.6f%%\n", (threeOfKind / (double)NUM_SIMULATIONS) * 100);
    printf("Full House: %.6f%%\n", (fullHouse / (double)NUM_SIMULATIONS) * 100);
    printf("Four of a Kind: %.6f%%\n", (fourOfKind / (double)NUM_SIMULATIONS) * 100);
    printf("Flush: %.6f%%\n", (flush / (double)NUM_SIMULATIONS) * 100);
    printf("Straight: %.6f%%\n", (straight / (double)NUM_SIMULATIONS) * 100);
    printf("Straight Flush: %.6f%%\n", (straightFlush / (double)NUM_SIMULATIONS) * 100);
    printf("Royal Flush: %.6f%%\n", (royalFlush / (double)NUM_SIMULATIONS) * 100);

    return 0;
}
