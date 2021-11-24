#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

// Draw the gallows and tha hanging man
std::string drawHangman(int numGuesses) {

    // Initializes the matrix with spaces
    std::string output;
    const int ROW_SIZE = 8;
    const int COL_SIZE = 8;
    char matrix[ROW_SIZE][COL_SIZE];
    for (unsigned int i = 0; i < ROW_SIZE; ++i) {
        for (unsigned int j = 0; j < COL_SIZE; ++j) {
            matrix[i][j] = ' ';
        }
    }

    // Add the gallows to the matrix
    matrix[0][2] = '_';
    matrix[0][3] = '_';
    matrix[0][4] = '_';
    matrix[1][1] = '|';
    matrix[1][5] = '|';
    matrix[2][5] = '|';
    matrix[3][5] = '|';
    matrix[4][5] = '|';
    matrix[5][5] = '|';
    matrix[6][3] = '_';
    matrix[6][4] = '_';
    matrix[6][5] = '|';
    matrix[6][6] = '_';
    matrix[6][7] = '_';

    // Depending on how many wrong guesses the user has had, adds the appropriate body parts
    if (numGuesses >= 1) {
        matrix[2][1] = 'O';
    }
    if (numGuesses >= 2) {
        matrix[3][1] = '|';
        matrix[4][1] = '|';
    }
    if (numGuesses >= 3) {
        matrix[3][0] = '\\';
    }
    if (numGuesses >= 4) {
        matrix[3][2] = '/';
    }
    if (numGuesses >= 5) {
        matrix[5][0] = '/';
    }
    if (numGuesses >= 6) {
        matrix[5][2] = '\\';
    }

    // Puts the matrix into a string to be outputted
    for (unsigned int i = 0; i < ROW_SIZE; ++i) {
        for (unsigned int j = 0; j < COL_SIZE; ++j) {
            output += matrix[i][j];
        }
        output += '\n';
    }
    return output;
}

// Checks to see if a letter has already been guessed
bool letterExists(char myLetter, std::vector<char> workingGuess, std::vector<char> incorrectGuesses) {
    for (unsigned int i = 0; i < workingGuess.size(); ++i) {
        if (workingGuess.at(i) == myLetter) {
            std::cout << "You already guessed this letter." << std::endl << std::endl;
            return true;
        }
    }
    for (unsigned int i = 0; i < incorrectGuesses.size(); ++i) {
        if (incorrectGuesses.at(i) == myLetter) {
            std::cout << "You already guessed this letter." << std::endl <<std::endl;
            return true;
        }
    }
    return false;
}

// Gets a letter from the user
char getLetter() {
    char letter;
    std::cout << "Guess a letter: ";
    std::cin >> letter;
    return letter;
}

// The play hangman function
void playHangman() {
    // Gets a random word
    srand(time(NULL));
    std::string wordList[10] = {"macaroni", "armadillo", "basketball", "playground", "walrus", "jazz", "locksmith", "treasure", "quirky", "ham"};
    int randomIndex = rand() % 10;
    std::string word = wordList[randomIndex];

    // Initializes the vectors that store the working guesses and incorrect guesses
    std::vector<char> workingGuess;
    std::vector<char> incorrectGuesses;
    for (unsigned int i = 0; i < word.size(); ++i) {
        workingGuess.push_back('_');
    }
    // Outputs the number of letters in the word
    std::cout << "The word has " << word.size() << " letters" << std::endl << std::endl;

    char letter;
    bool incomplete = true;
    int numCorrectGuess = 0;
    int numIncorrectGuess = 0;

    // Keeps looping until the word is fully guessed
    while (incomplete) {
        std::vector<int> letterIndexes;
        letter = getLetter();
        bool found = false;

        // Checks if a letter has already been guessed
        if (letterExists(letter, workingGuess, incorrectGuesses)) {
            letter = getLetter();
        }

        // Finds the indexes from the original word where the guessed letter is
        for (unsigned int i = 0; i < word.size(); ++i) {
            if (letter == word[i]) {
                found = true;
                letterIndexes.push_back(i);
            }
        }

        // If the letter is part of the word
        if (found) {
            for (unsigned int i = 0; i < letterIndexes.size(); ++i) {
                workingGuess.at(letterIndexes.at(i)) = letter;
            }
            for (unsigned int i = 0; i < workingGuess.size(); ++i) {
                std::cout << workingGuess.at(i) << " ";
            }
            std::cout << std::endl;
            ++numCorrectGuess;
        }

            // If the letter isn't part of the word
        else {
            std::cout << letter << " is not in the word" << std::endl;
            incorrectGuesses.push_back(letter);
            ++numIncorrectGuess;
            std::cout << drawHangman(numIncorrectGuess);
            std::cout << "Incorrect Guesses: ";
            for (unsigned int i = 0; i < incorrectGuesses.size(); ++i) {
                std::cout << incorrectGuesses.at(i) << " ";
            }
            std::cout << std::endl;
            if (numIncorrectGuess == 6) {
                break;
            }
        }

        // Outputs the number of correct and incorrect guesses
        std::cout << "# of Correct Guesses: " << std::to_string(numCorrectGuess) << std::endl;
        std::cout << "# of Incorrect Guesses: " << std::to_string(numIncorrectGuess) << std::endl << std::endl;

        // Checks if there are any more letters to be guessed
        for (unsigned int i = 0; i < workingGuess.size(); ++i) {
            if (workingGuess.at(i) == '_') {
                incomplete = true;
                break;
            }
            else {
                incomplete = false;
            }
        }
    }
    int totalGuesses = numCorrectGuess + numIncorrectGuess;

    //  Wins if word is fully guessed before hangman is fully drawn, game over if the hangman is fully drawn before the word is fully guessed
    if (!incomplete) {
        std::cout << "You have correctly guessed the word: " << word << std::endl;
        std::cout << "Total number of guesses: " << std::to_string(totalGuesses) << std::endl << std::endl;
    }
    else {
        std::cout << "You were not able to guess the word. Game over :(" << std::endl << std::endl;
    }

    // Asks the player to play again
    std::string playAgain;
    std::cout << "Would you like to play again? (y/n) ";
    std::cin >> playAgain;
    if (playAgain == "y") {
        playHangman();
    }
    else {
        std::cout << "Thanks for playing! Goodbye :)";
        return;
    }
}

int main() {
    std::string play;
    std::cout << "Welcome to Hangman! Would you like to play? (y/n) ";
    std::cin >> play;
    if (play == "y") {
        playHangman();
    }
    return 0;
}


