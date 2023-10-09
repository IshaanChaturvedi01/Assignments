#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class RockPaperScissors {
public:
    RockPaperScissors() {
        choices = {"rock", "paper", "scissors"};
        player_score = 0;
        computer_score = 0;
    }

    string get_player_choice() {
        string choice;
        while (true) {
            cout << "Enter your choice (rock/paper/scissors): ";
            cin >> choice;
            for (const string &valid_choice : choices) {
                if (choice == valid_choice) {
                    return choice;
                }
            }
            cout << "Invalid! Please choose rock, paper, or scissors only." << endl;
        }
    }

    string get_computer_choice() {
        return choices[rand() % 3];
    }

    string determine_winner(const string &player_choice, const string &computer_choice) {
        if (player_choice == computer_choice) {
            return "tie";
        } else if ((player_choice == "rock" && computer_choice == "scissors") ||
                   (player_choice == "paper" && computer_choice == "rock") ||
                   (player_choice == "scissors" && computer_choice == "paper")) {
            return "player";
        } else {
            return "computer";
        }
    }

    void play_round() {
        string player_choice = get_player_choice();
        string computer_choice = get_computer_choice();
        cout << "Computer chooses: " << computer_choice << endl;
        string winner = determine_winner(player_choice, computer_choice);
        if (winner == "player") {
            player_score++;
            cout << "You win this round!" << endl;
        } else if (winner == "computer") {
            computer_score++;
            cout << "Computer wins this round!" << endl;
        } else {
            cout << "It's a tie this round!" << endl;
        }
        cout << "Scores - Player: " << player_score << ", Computer: " << computer_score << endl;
    }

    void play_game(int rounds) {
        cout << "Welcome to Rock-Paper-Scissors!" << endl;
        for (int round_num = 1; round_num <= rounds; round_num++) {
            cout << "\nRound " << round_num << "/" << rounds << endl;
            play_round();
        }
        cout << "\nGame Over!" << endl;
        if (player_score > computer_score) {
            cout << "Congratulations! You win the game!" << endl;
        } else if (computer_score > player_score) {
            cout << "Computer wins the game!" << endl;
        } else {
            cout << "It's a tie game!" << endl;
        }
    }

private:
    vector<string> choices;
    int player_score;
    int computer_score;
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    int rounds;
    cout << "Enter the number of rounds: ";
    cin >> rounds;
    RockPaperScissors game;
    game.play_game(rounds);
    return 0;
}
