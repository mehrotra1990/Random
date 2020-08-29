// Inspired and recreated from following Youtube video:
// https://www.youtube.com/watch?v=E_-lMZDi7Uw (NVitanovic)

#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameover;
const int width = 15;
const int height = 15;

// Where is the head of the snake
int headX, headY;
int tailX[100], tailY[100];
int nLength;

// WHere is the food
int foodX, foodY;

enum Directions
{
    stop = 0,
    left,
    right,
    top,
    down
};

// Where is the snake currently moving
Directions eCurrentDir;

int score;

void addRandomFood()
{    
    // Food can be at any random place
    foodX = rand() % width;
    foodY = rand() % height;
}

void setup()
{
    gameover = false;
    score = 0;
    eCurrentDir = stop;

    // Start position of hte snake (center of the screen)
    headX = width/2;
    headY = height/2;

    addRandomFood();
}

void draw()
{
    // Clear the screen
    system("cls");

    // Draw the top border
    for(int i = 0; i < width + 2; i++) 
        cout<<"#";
    cout<<endl;

    for(int i = 0; i < height; i++)
    {
        // Keeps track of the number of characters printed in the row
       for(int j = 0; j < width + 2; j++)
        {
            // Print the left borders
            if(j == 0 )
            {
                cout<<"#";
                continue;
            }

            // Position of the head
            if(i == headY && j == headX)
            {
                    cout<<"@";
                    continue;
            }
            // Print the food

            if(i == foodY && j == foodX)
            {
                cout<<"*";
                continue;
            }
            int numPrinted = 0;
            // Draw the tail;
            for(int k = 0; k < nLength; k++)
            {
                if(tailX[k] == j && tailY[k] == i)
                {
                    numPrinted++;
                    cout<<"o";
                    continue;
                }
            }
            if(numPrinted)
            {
                // -1 is done here because atkeast one characted is expected to be preinted
                // in each iteration of the width
                j += numPrinted - 1;
                continue;
            }
            if(j == width + 1)
                cout<<"#";
            else
                cout<<" ";

        }
        cout<<endl;
    }

    // Draw the bottom border
    for(int i = 0; i <width + 2; i++)
        cout<<"#";
    cout<<endl;

    // Print score at the bottom
    cout<<"Score: "<< score<<endl;
}

void input()
{
    // If a key is pressed
    if(_kbhit())
    {
        switch (_getch())
        {
        // Use w,a,s,d convention
        case 'w':
            eCurrentDir = Directions::top;
            break;
        case 'a':
            eCurrentDir = Directions::left;
            break;
        case 's':
            eCurrentDir = Directions::down;
            break;
        case 'd':
            eCurrentDir = Directions::right;
            break;
        case 'x':
            gameover = true;
        default:
            break;
        }
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
 
    tailX[0] = headX;
    tailY[0] = headY;

    int prev2X, prev2Y;
    // move the tail
    for(int i = 1; i < nLength; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (eCurrentDir)
    {
    case Directions::top:
        headY--;
        break;
    
    case Directions::down:
        headY++;
        break;
        
    case Directions::left:
        headX--;
        break;
        
    case Directions::right:
        headX++;
        break;

    default:
        break;
    }

    // Handle boundaries. Kill if boundaries are hit
    if(headX < 0 || headX > width || headY < 0 || headY >= height)
        gameover = true;
    for(int i = 0; i < nLength; i++)
    {
        if(tailX[i] == headX && tailY[i] == headY)
        {
            gameover = true;
        }
    }

    // If new position of head its the fruit
    if(headX == foodX && headY == foodY)
    {
        score++;
        addRandomFood();
        nLength++;
    }
}

void startGame()
{
    setup();
    while(!gameover)
    {
        draw();
        input();
        logic();
        Sleep(100);
    }
}
int main()
{
    cout<<"Initializing";
    char ch = 'r';
    startGame();
    do
    {
        if(ch == 'x') break;
        cout<<"**GAME OVER**"<<endl<<"Press 'x' to exit;"<<endl;
    }while (ch = _getch());

    return 0;
}