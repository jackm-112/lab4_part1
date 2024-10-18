#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

const int STARTING_CREDITS = 100;

//generates a random number from 1-6 using the current time as the seed
int dice (void) {
    int dieRoll = rand() % 6 + 1;
    return dieRoll;
}

//takes in the two random rolls along with the user's wager
int calculateScore(int roll1, int roll2, int wager) {
    int sum = roll1 + roll2;
    int result = 0;
    int point = 0;

    cout << "Player rolled " << roll1 << " + " << roll2 << " = " << sum << endl;

    //if the first roll is 7, 11, 2, or 3, player wins/loses and exits function
    if (sum == 7 || sum == 11) {
        cout << "Player wins!" << endl;
        result = wager * 2;
    }
    else if (sum == 2 || sum == 3 || sum == 12){
        cout << "Player loses." << endl;
    }
    else {
        //sets the point value and prints it out
        point = sum;
        cout << "Point is " << sum << endl;
        //rerolls the dice to generate a new sum
        while (1) {
            roll1 = dice();
            roll2 = dice();
            sum = roll1 + roll2;
            cout << "Player rolled " << roll1 << " + " << roll2 << " = " << sum << endl;

            if (sum == point) {
                result = wager * 2;
                break;
            }
            if (sum == 7) {
                break;
            }
        }
    }

    if (result > wager) {
        cout << "You won " << result << " credits!" << endl;
    }
    else {
        cout << "You lost " << wager << " credits." << endl;
    }

    return result;
}

//handles user input for the craps game and provides the user with
//their remaining credits
int playGame(int credits) {
    int wagerAmt;

    cout << "You have " << credits << " credits." << " How much would you like to wager? ";
    cin >> wagerAmt;

    if (wagerAmt > credits) {
        cout << "You do not have enough credits." << endl;
    }
    else {
        //if you are wagering an acceptable amount of credits, your updated credit amount is equal
        //to you current amount minus the wager
        credits = credits - wagerAmt;
        credits = credits + calculateScore(dice(), dice(), wagerAmt);

        cout << "Remaining credits: " << credits << endl;
    }

    return credits;
}

int main (void) {
    int credits = STARTING_CREDITS;
    char ans;
    bool done = false;
    srand(time(NULL));

    //repeat the loop so long as the player has credits remaining
    while (!done) {
        credits = playGame(credits);

        if (credits <= 0) {
            cout << "You are out of credits! The game is over." << endl;
            break;
        }

        cout << "Play again? (y/n)";
        cin >> ans;
        if (ans == 'n' || ans == 'N') done = true;
        else done = false;
        cout << endl;
    }
}