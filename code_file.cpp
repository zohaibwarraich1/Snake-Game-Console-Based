#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <unistd.h>
#include <conhelper.h>
using namespace std;

//! Prototypes //
void game_setup(string Player_name);
void Display();
void instructions();
void game_starter(const int height, const int width, int snake_x, int snake_y, int fx, int fy, int score, int tailLength, int *pTailX, int *pTailY);
void gettingInput(int &snake_x, int &snake_y, bool &gameOver, int &temp_snake_x, int &temp_snake_y);
void changing_position(int &tailLength, int *pTailX, int *pTailY, int temp_snake_x, int temp_snake_y);
bool checkGameOver(const int height, const int width, int snake_x, int snake_y);
void updation(const int height, const int width, int snake_x, int snake_y, int &fx, int &fy, int &score, int &tailLength);
void scoreboard();
void store_score_in_file(string name, int score);
//! Prototypes //

int main()
{
    srand(time(0));     //*Comment 1: to genreate random numbers.
    string Player_name; //*Comment 2: to ask the name of player
    Display();
    text_color(YELLOW);
    cout << "Enter your name: ";
    text_color(WHITE);
    getline(cin, Player_name);
    text_color(REMOVE);
    game_setup(Player_name); //* Comment 4: to setup the game and decalre variables to be used in game and to give instructions.
    return 0;
}

void Display()
{
    text_color(VIOLET);
    cout << endl;
    cout << "         =============================================================================================================" << endl;
    cout << "         =============================================================================================================" << endl
         << endl;
    cout << "             SSSSSSS    NN     N       AA      K    K   EEEEEE        GGGGGGGG       AA      MMMM    MMMM  EEEEEE" << endl;
    cout << "             S          N  N   N      A  A     K   K    E             G             A  A     M  M    M  M  E  " << endl;
    cout << "             SSSSSSS    N   N  N     AAAAAA    K K      EEE           G   GGGG     AAAAAA    M   M  M   M  EEE " << endl;
    cout << "                   S    N    N N    A      A   K   K    E             G      G    A      A   M    M M   M  E" << endl;
    cout << "             SSSSSSS    N     NN   A        A  K    K   EEEEEE        GGGGGGGG   A        A  M     M    M  EEEEEE" << endl
         << endl;
    cout << "         =============================================================================================================" << endl;
    cout << "         =============================================================================================================" << endl
         << endl;
    text_color(REMOVE);
}

void game_setup(string PLayer_name)
{
    const int height = 20;      //* Comment 1: for border height.
    const int width = 20;       //* Comment 2: for border width.
    int snake_x = width / 2;    //* Comment 3: for snake's position on x-axis.
    int snake_y = height / 2;   //* Comment 4: for snake's position on y-axis.
    int fx = rand() % width;    //* Comment 5: for fruit's position on x-axis.
    int fy = rand() % height;   //* Comment 6: for fruit's position on y-axis.
    bool gameOver = false;      //* Comment 7: to check whether the game is over.
    int score = 0;              //* Comment 8: to calculate the score.
    int tailLength = 1;         //* Comment 9: for snake's tail.
    int *pTailX = new int[100]; //* Comment 10: for snake's tail position on x-axis.
    int *pTailY = new int[100]; //* Comment 11: for snake's tail position on y-axis.
    int store_snake_x = 0;      //* Comment 12: to store the snake's current position on x-axis during execution.
    int store_snake_y = 0;      //* Comment 13: to store the snake's current position on y-axis during execution.
    instructions();             //* Comment 14: Give instructions to user.
    char input;                 //* Comment 15: to ask the user if he is ready to play.
    text_color(YELLOW);
    cout << "\nDo you want to start the game? (Y/N): ";
    text_color(WHITE);
    cin >> input;
    if (input == 'y' || input == 'Y') //* Comment 16: if user is ready to play.
    {
        while (!gameOver) //* Comment 17: to check whether the game is over.
        {
            system("clear"); //* To clear the terminal for different iterations.
            Display();
            game_starter(height, width, snake_x, snake_y, fx, fy, score, tailLength, pTailX, pTailY); //* Comment 17.1: to call the function for starting game.
            gettingInput(snake_x, snake_y, gameOver, store_snake_x, store_snake_y);                   //* Comment 17.2: to call the function for getting indication/direction of snake.
            if (gameOver == true)                                                                     //* Comment 17.3: to check whether the game is over after getting input from player
            {
                break; //* Comment 17.3.1: if game is over the loop will stop and program will be finished.
            }
            changing_position(tailLength, pTailX, pTailY, store_snake_x, store_snake_y); //* Comment 17.4: to call the function for changing position of snake.
            gameOver = checkGameOver(height, width, snake_x, snake_y);                   //* Comment 17.5: to check whether the game is over.
            updation(height, width, snake_x, snake_y, fx, fy, score, tailLength);        //* Comment 17.6: to update the values of snake, fruit and score.
            usleep(100010);                                                              //* Comment 17.7: to call the function for controlling the snake movement.
        }
        system("clear");                         //* Comment 18: To clear the terminal/console.
        store_score_in_file(PLayer_name, score); //* Comment 19: To call the function and open the file and save the score of player.
        Display();
        text_color(LIME);
        cout << "Do you want to check the score board? (Y/N): "; //* Comment 20: to ask the user whether he wants to see the scoreboard.
        char scoreboard_input;
        text_color(WHITE);
        cin >> scoreboard_input;
        if (scoreboard_input == 'Y' || scoreboard_input == 'y') //* Comment 21: if player enter 'Y' then scoreboard will be displayed on the terminal/console.
        {
            system("clear"); //* Comment 21.1: to clear the terminal
            Display();
            scoreboard(); //* Comment 21.2: to call the function and display the score board on console/terminal.
        }
        text_color(LIME);
        cout << "\nThankYou for Playing the Game"; //* Comment 22: to end the game.
    }
    else //* Comment 23: if user is not ready to play.
    {
        text_color(LIME);
        cout << "GOODBYE."; //* Comment 23.1: to end the game.
    }
    delete[] pTailX; //* Comment 24: to delete the dynamically memory allocation for snake's tail position on x-axis.
    delete[] pTailY; //* Comment 25: to delete the dynamically memory allocation for snake's tail position on y-axis.
}

void instructions()
{
    text_color(YELLOW);
    cout << endl;
    cout << "\t\t\t\t\t\t*INSTRUCTIONS TO PLAY THE GAME*" << endl; //* Comment 1: for heading.
    cout << "-> Press 'a' to move 'LEFT' side." << endl;           //* Comment 2: for 'a' movement.
    cout << "-> Press 'd' to move 'RIGHT' side." << endl;          //* Comment 3: for 'd' movement.
    cout << "-> Press 'w' to move 'UP' side." << endl;             //* Comment 4: for 'w' movement.
    cout << "-> Press 's' to move 'DOWN' side." << endl;           //* Comment 5: for 's' movement.
    cout << "-> NOTE: To Quit the game anytime. Press 'q'";        //* Comment 6: to quit the game.
    text_color(REMOVE);
}

void game_starter(const int height, const int width, int snake_x, int snake_y, int fx, int fy, int score, int tailLength, int *pTailX, int *pTailY)
{
    text_color(AZURE);
    for (int i = 0; i < width + 2; i++) //* Comment 2: for creating border width.
    {
        cout << "*";
    }
    cout << endl;
    for (int i = 0; i < height; i++) //* Comment 3: for creating header border.
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) //* Comment 3.1: to create the border on left side.
            {
                cout << "#";
            }
            if (i == snake_y && j == snake_x) //* Comment 3.2: for creating snake's head.
            {
                // text_color(REMOVE);
                text_color(WHITE);
                cout << "S";
                text_color(AZURE);
                // text_color(REMOVE);
            }
            else if (i == fy && j == fx) //* Comment 3.3: for creating fruit's position.
            {
                // text_color(REMOVE);
                text_color(LEMON);
                cout << "F";
                // text_color(REMOVE);
                text_color(AZURE);
            }
            else
            {
                bool printSpace = false;             //* Comment 3.4: to check whether to print the empty space or snake's taillength.
                for (int k = 1; k < tailLength; k++) //* Comment 3.5: to print the snake's tail.
                {
                    if (pTailY[k] == i && pTailX[k] == j) //* Comment 3.6: for priting snake's tail along its head.
                    {
                        text_color(WHITE);
                        cout << "s";
                        text_color(AZURE);
                        printSpace = true; //* Comment 3.7: if snake's tail is to be printed then bool will be true and tail will be printed instead of empty space in that location.
                    }
                }
                if (!printSpace) //* Comment 3.8: if snake's tail is not printed then empty space will be printed in that location.
                    cout << " ";
            }
            if (j == width - 1) //* Comment 3.9: for creating right side border.
            {
                cout << "#";
            }
        }
        cout << endl; //* Comment 3.10: Jump to next line.
    }
    for (int i = 0; i < width + 2; i++) //* Comment 4: for creating footer border.
    {
        cout << "#";
    }
    cout << endl;
    text_color(YELLOW);
    cout << "Score: ";
    text_color(BABY);
    cout << score << endl; //* Comment 5: to display the score.
    text_color(YELLOW);
    cout << "Enter key: "; //* Comment 6: to ask the player to enter key for snake's movement.
    text_color(REMOVE);
}

void gettingInput(int &snake_x, int &snake_y, bool &gameOver, int &temp_snake_x, int &temp_snake_y)
{
    temp_snake_x = snake_x; //* Comment 1: as in game_setup func on 12th comment we decaled it to store the snake's position on x-axis. It will be used to create snake's tail on x-axis.
    temp_snake_y = snake_y; //* Comment 2: as in game_setup func on 13th comment we decaled it to store the snake's position on y-axis. It will be used to create snake's tail.
    // char input;
    // cin >> input;                                                                           //* Comment 3: to ask the user for indication/movement of snake.
    if (kbhit())
    {
        char a = getch();
        while (!(a == 'a' || a == 'd' || a == 's' || a == 'w' || a == 'q')) //* Comment 4: if user enter any other key than the given one this loop will ask the key again.
        {
            cout << "You entered wrong key: "; //* Comment 4.1: to display that user have entered wrong key.
            a = getch();
        }
        switch (a) //* Comment 5: it will check the pressed key by user and then change the snake's position.
        {
        case 'a':
            snake_x--; //* Comment 5.1: to move the snake on left side.
            break;
        case 'd':
            snake_x++; //* Comment 5.2: to move the snake on right side.
            break;
        case 'w':
            snake_y--; //* Comment 5.3: to move the snake upward side.
            break;
        case 's':
            snake_y++; //* Comment 5.4: to move the snake downward side.
            break;
        case 'q':
            gameOver = true; //* Comment 5.5: to finish the game. If user enter 'q'.
            break;
        }
    }
}

void changing_position(int &tailLength, int *pTailX, int *pTailY, int temp_snake_x, int temp_snake_y)
{
    pTailX[0] = temp_snake_x;            //* Comment 1: to store the snake's current position on x-axis for creating tail on x-axis.
    pTailY[0] = temp_snake_y;            //* Comment 2: to store the snake's current position on y-axis for creating tail on y-axis.
    for (int i = tailLength; i > 0; i--) //* Comment 3: to store the snake's position in array's indexes for creating tail.
    {
        pTailX[i] = pTailX[i - 1]; //* Comment 3.1: to create tail on x-axis.
        pTailY[i] = pTailY[i - 1]; //* Comment 3.2: to create tail on y-axis.
    }
}

bool checkGameOver(const int height, const int width, int snake_x, int snake_y)
{
    if (snake_y < 0 || snake_y > height - 1) //* Comment 1: to check whether the snake's head touch the height border and if yes then it will true the gameover.
    {
        return true;
    }
    if (snake_x < 0 || snake_x > width - 1) //* Comment 2: to check whether the snake's head touch the width border and if yes then it will true the gameover.
    {
        return true;
    }
    return false; //* if snake's head doesnt not touch the height/width border it will return false.
}

void updation(const int height, const int width, int snake_x, int snake_y, int &fx, int &fy, int &score, int &tailLength)
{
    if (snake_x == fx && snake_y == fy) //* Comment 1: to check if snake's head position equals to fruit's positions.
    {
        fx = rand() % width;  //* Comment 1.1: to generate new fruit on x-axis using random func.
        fy = rand() % height; //* Comment 1.2: to generate new fruit on y-axis using random func.
        score += 50;          //* Comment 1.3: to update the player's score when snake eat the fruit.
        tailLength++;         //* Comment 1.4: to increase the length of snake's tail when it eats the fruit.
    }
}

void scoreboard()
{
    string *pName = new string[100]; //* Comment 1: to declare a dynamic array for storing the name of players from file.
    int *pScore = new int[100];      //* Comment 2: to declare a dynamic array for storing the score of players from file.
    int m = 0;
    ifstream read_scoreboard;                //* Comment 3: to delcare a object for reading the file.
    read_scoreboard.open("Score Board.txt"); //* Comment 4: to open the file.
    if (read_scoreboard.is_open())           //* Comment 5: to check whether the file is opened.
    {
        while (!read_scoreboard.eof()) //* Comment 6: to get data until it reaches at the end of file.
        {
            string temp; //* Comment 6.1: to store the name of player getting from file.
            getline(read_scoreboard, temp);
            string score; //* Comment 6.2: to store the score of player geeting data from file.
            getline(read_scoreboard, score);
            int Int_Score;                    //* Comment 6.3: to convert the the score of player obtained from file. Because the data stored in file is in the form of string. so we converted that string into integer datatype by this Int_Score variable.
            stringstream(score) >> Int_Score; //* Comment 6.4: converting the string into integer type.
            if (score != "")                  //* Comment 6.5: if there is any data in the line then it wil store the score and name of players in dynamic array from the file.
            {
                pName[m] = temp;
                pScore[m] = Int_Score;
                m++;
            }
        }
        read_scoreboard.close(); //* Comment 7: to close the file.
    }
    else //* Comment 8: if file is not opened.
    {
        cout << "There is not record in file right now." << endl;
    }
    for (int i = 0; i < m; i++) //* Comment 9: used this loop to arrange the score and names of player in descending order.
    {
        for (int j = 0; j < m; j++)
        {
            if (pScore[i] > pScore[j]) //* Comment 10: to arrange the score and name of players for scoreboard in descending order.
            {
                int temp_int = pScore[i]; //* Comment 10.1: to swap the score.
                pScore[i] = pScore[j];
                pScore[j] = temp_int;

                string temp_name = pName[i]; //* Comment 10.2: to swap the names.
                pName[i] = pName[j];
                pName[j] = temp_name;
            }
        }
    }
    text_color(YELLOW);
    for (int i = 0; i < m; i++) //* Comment 11: to display the scoreboard
    {
        text_color(WHITE);
        cout << i + 1;
        text_color(YELLOW);
        cout << ". " << pName[i] << " has ";
        text_color(BABY);
        cout << pScore[i];
        text_color(YELLOW);
        cout << " score." << endl;
    }
    text_color(REMOVE);
    delete[] pScore; //* Comment 12: to delete the dynamically allocated memory for score of players.
    delete[] pName;  //* Comment 13: to delete the dynamically allocated memory for name of players.
}

void store_score_in_file(string name, int score)
{
    ofstream write_score;                          //* Comment 1: to delcare the object for writing in file.
    write_score.open("Score Board.txt", ios::app); //* Comment 2: to open the file in append mode. So that the new score will be written in at end of file without removing the old data of file.
    if (write_score.is_open())                     //* Comment 3: to check whether the file is open.
    {
        write_score << name << endl;  //* Comment 3.1: to write the name of user in file.
        write_score << score << endl; //* Comment 3.2: to write the score of user in file.
        write_score.close();          //* Comment 1: to close the file.
    }
    else //* Comment 4: if file is not opened.
    {
        cout << "File opening error." << endl;
    }
}