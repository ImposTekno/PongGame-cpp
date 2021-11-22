#include <iostream>
#include <cmath>
#include <string>
#include <conio.h>
#include <ctime>
#include <windows.h>
using namespace std;

void ClearScreen()
{
	//prevent console screen from flickering
	COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

int main()
{

	srand(time(NULL));

	// Game loop switch
	bool run = true;

	// Playfield dimensions
	int height = 30;
	int width = 60;

	// left pad position
	int pos1 = height / 2 + 3;
	int pos2 = height / 2 - 3;

	// right pad position
	int sop1 = height / 2 + 3;
	int sop2 = height / 2 - 3;

	// Direction of the ball
	/*
		0 ---> LEFT UP
		1 ---> LEFT DOWN

		----------------

		2 ---> RIGHT UP
		3 ---> RIGHT DOWN

	*/

	// initial direction that the ball will have at the beginning 
	int curDir = rand() % 3;


	// initial position of a ball (center of the playfield)
	int ballPosY = height / 2;
	int ballPosX = width / 2;

	// number of total bounces
	int bounces = 0;

	// score 
	int player1 = 0;
	int player2 = 0;


	// game loop
	while (run)
	{
		// obviously screen clearing method from above :P 
		ClearScreen();


		// Handler for keyboard input such as moving peds up and down 
		if (_kbhit())
		{
			switch (_getch())
			{
				// move left ped
			case 'w': pos1 -= 2; pos2 -= 2; break;
			case 's': pos1 += 2; pos2 += 2; break;

				// move right ped
			case '8': sop1 -= 2; sop2 -= 2; break;
			case '5': sop1 += 2; sop2 += 2; break;

				// reset
			case 'r': ballPosX = width / 2; ballPosY = height / 2; bounces = 0; curDir = 0; player1 = 0; player2 = 0; break;

				// close game 
			case 'p':run = false; break;
			}
		}

		// Based on a value (0-3) what direction will the ball have  
		switch (curDir)
		{

		case 0:	ballPosX -= 1; ballPosY -= 1; break; // left up
		case 1: ballPosX -= 1; ballPosY += 1; break; // left down

		case 2: ballPosX += 1; ballPosY -= 1; break; // right up
		case 3: ballPosX += 1; ballPosY += 1; break; // right down


		}

		// Screen draw
		for (int i = 0; i < height; i++)
		{
			cout << endl;
			for (int j = 0; j < width; j++)
			{

				if (j == 0 || (j >= 0 && i == 0) || j == 59 || (j >= 0 && i == 29))
				{
					cout << "#";
				}
				else if (j == 5 && (i < pos1 && i > pos2))
				{
					cout << "#";
				}
				else if (j == 55 && (i< sop1 && i > sop2))
				{
					cout << "#";
				}
				else if (j == ballPosX && i == ballPosY)
				{
					cout << "O";

					// Check if the ball is coliding with the pedals
					if (ballPosX == 6 && (ballPosY < pos1 && ballPosY > pos2) && curDir == 1)
					{
						curDir = 3;
						bounces++;
					}
					else if (ballPosX == 6 && (ballPosY < pos1 && ballPosY > pos2) && curDir == 0)
					{
						curDir = 2;
						bounces++;
					}
					else if (ballPosX == 54 && (ballPosY < sop1 && ballPosY > sop2) && curDir == 3)
					{
						curDir = 1;
						bounces++;
					}
					else if (ballPosX == 54 && (ballPosY < sop1 && ballPosY > sop2) && curDir == 2)
					{
						curDir = 0;
						bounces++;
					}
					else if (ballPosY == 1 && curDir == 2)
					{
						// if the direction is right up change it to right down
						curDir = 3;
					}
					else if (ballPosY == 28 && curDir == 3)
					{
						// if the direction is right down change it to right up
						curDir = 2;
					}
					else if (ballPosY == 1 && curDir == 0)
					{
						// if the direction is left up change it to left down
						curDir = 1;
					}
					else if (ballPosY == 28 && curDir == 1)
					{
						// if the direction is left down change it to left up
						curDir = 0;
					}


					// Check if scored 
					if (ballPosX <= 1)
					{
						player2++;
						Sleep(1000);
						ballPosX = width / 2;
						ballPosY = height / 2;
						curDir = rand() % 3;
					}
					else if (ballPosX >= 58)
					{
						player1++;
						Sleep(1000);
						ballPosX = width / 2;
						ballPosY = height / 2;
						curDir = rand() % 3;
					}

				}
				else
				{
					cout << " ";
				}

			}
		}

		// score output 
		cout << "\n\n\n";
		cout << "Score: " << "\n"
			<< "Player 1: " << player1 << "\n"
			<< "Player 2: " << player2 << "\n";


	}





	cin.get();
	return 0;
}


