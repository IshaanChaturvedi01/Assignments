#include <iostream>
#include<limits.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int lowerLimit = 1;
    int upperLimit = 100;
    int secretNumber;
    int guess;
    int attempts = 0;
    int bestScore = INT_MAX;  
    int totalAttempts = 0;
    int gamesPlayed = 0;
    bool warmer = false;

    cout << "Welcome to the Number Guessing Game!" << endl;

    while (true) {
        cout << "Choose a difficulty level:" << endl;
        cout << "1. Easy (1-50)" << endl;
        cout << "2. Medium (1-100)" << endl;
        cout << "3. Hard (1-1000)" << endl;
        cout << "4. Custom Range" << endl;
        cout << "5. Quit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 5) {
            cout << "Thanks for playing. Goodbye!" << endl;
            break;
        } else if (choice == 4) {
            cout << "Enter custom lower limit: ";
            cin >> lowerLimit;
            cout << "Enter custom upper limit: ";
            cin >> upperLimit;
        } else if (choice < 1 || choice > 5) {
            cout << "Invalid choice. Please select a valid option." << endl;
            continue; // Ask for the difficulty level again
        } else {
            lowerLimit = 1;
            upperLimit = (choice == 1) ? 50 : ((choice == 2) ? 100 : 1000);
        }

        secretNumber = rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
        attempts = 0;
        warmer = false;

        cout << "I'm thinking of a number between " << lowerLimit << " and " << upperLimit << "." << endl;

        do {
            cout << "Enter your guess: ";
            cin >> guess;
            attempts++;

            if (guess < lowerLimit || guess > upperLimit) {
                cout << "Please guess a number within the range " << lowerLimit << " and " << upperLimit << "." << endl;
            } else if (guess < secretNumber) {
                cout << "Too low! Try again." << endl;
            } else if (guess > secretNumber) {
                cout << "Too high! Try again." << endl;
            } else {
                cout << "Congratulations! You guessed the correct number (" << secretNumber << ") in " << attempts << " attempts!" << endl;

                if (attempts < bestScore) {
                    bestScore = attempts;
                    cout << "New best score: " << bestScore << " attempts!" << endl;
                }

                totalAttempts += attempts;
                gamesPlayed++;

                if (gamesPlayed > 1) {
                    int avgAttempts = totalAttempts / gamesPlayed;
                    cout << "Average attempts per game: " << avgAttempts << endl;
                }

                cout << "Do you want to play again? (1 = Yes, 2 = No): ";
                int playAgain;
                cin >> playAgain;
                if (playAgain != 1) {
                    cout << "Thanks for playing. Goodbye!" << endl;
                    break;
                } else {
                    cout << "Starting a new game..." << endl;
                }
            }

            
            if (abs(guess - secretNumber) < abs(secretNumber - (guess - 1))) {
                if (!warmer) {
                    cout << "Warmer!" << endl;
                    warmer = true;
                }
            } else if (abs(guess - secretNumber) > abs(secretNumber - (guess - 1))) {
                if (warmer) {
                    cout << "Colder!" << endl;
                    warmer = false;
                }
            }

        } while (guess != secretNumber);
    }

    return 0;
}
