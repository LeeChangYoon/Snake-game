#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define LEFT 75 
#define RIGHT 77 
#define UP 72 
#define DOWN 80 
#define PAUSE 112 // Keyboard iinput 'P'
#define ESC 27 

#define MAP_ADJ_X 3 // Starting x point of the map
#define MAP_ADJ_Y 2	// starting y point of the map
#define MAP_X 30 // Vertical map size 
#define MAP_Y 20 // Horizontal map size

int x[100], y[100]; // Location of snake head, Max size of snake is 100
int food_x, food_y; // Locatoin of the food
int bomb_x[100], bomb_y[100]; // Location of the bomb, max number of the bomb is 100
int num_of_bombs; // Number of the bombs
int length; // Snake length
int speed; // Speed of the game
int score; //score is stored
int best_score = 0; // Bestscore
int last_score = 0; // Your score in the last game
int dir; // Direction
int key; // input of the key
int stage = 1; // Stage number
int status_on = 0; // Status  for developers

				   // gotoxy is a function that moves cursor to selected x, y
void gotoxy(int x, int y, const char* s)
{
	COORD pos = { 2 * x,y }; // Structure which contains the x, and y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // Function that seets the position of console
	printf("%s", s);
}

void title(void); // Game title
void reset(void); // Reset the game
void draw_map(void);  // drawing the frame of the map
void move(int dir);  // Related to snake movinng
void pause(void); // Pause the game
void game_over(void); // Game over 
void food(void); // Randomly response the food
void status(void); // Status for developers
void cursor_delete(void); // Function that deletes the cursor
void stage1(void); // Stage1
void stage2(void); // Stage2: It occurs when point reaches to 70, and gives bonus 10 points
void stage3(void); // Stage3: It occurs when point reaches to 200, and gives bonus 50 points
void bomb(void); // Response the bomb on random place

				 ////////////////////////////MAIN START//////////////////////////////
int main()
{
	title();

	while (1)
	{
		if (kbhit()) do { key = getch(); } while (key == 224); // Key input
		Sleep(speed); // Controls the speed, function Sleep() stops the program for milli sec

		switch (key) // Apprehend the key and runs the program
		{
		case LEFT:
		case RIGHT:
		case UP:
		case DOWN:
			if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) ||
				(dir == DOWN && key != UP)) // Need for prevent the 180 degrees rotational movement
				dir = key;
			key = 0; // Reset the key to 0
			break;

		case PAUSE:
			pause();
			break;

		case 115: // input 'S', then status() activated
			if (status_on == 0) status_on = 1;
			else status_on = 0;
			key = 0;
			break;

		case ESC: // Program exits if the input value is ESC
			exit(0);
		}
		move(dir);
		if (status_on == 1) status(); // There are no turning off, because it is i the infinite loop
	}
}
///////////////////////////MAIN END////////////////////////////////

void title(void)
{
	int i, j;

	while (kbhit()) // Takes off the value in buffer 
		getch(); // Gets the value in buffer

	draw_map();
	cursor_delete();
	for (i = MAP_ADJ_Y + 1; i<MAP_ADJ_Y + MAP_Y - 1; i++) // Fills the inside of frame with blanks
	{
		for (j = MAP_ADJ_X + 1; j<MAP_ADJ_X + MAP_X - 1; j++)
			gotoxy(j, i, "  ");
	}

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+--------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|         S N A K E        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "+--------------------------+");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, " < PRESS ANY KEY TO START > ");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 11, "   ¡Þ ¡ç,¡æ,¡è,¡é : Move    ");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 12, "   ¡Þ P : Pause             ");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 13, "   ¡Þ ESC : Quit            ");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 17, "      < iThings Lab >       ");

	while (1)
	{
		if (kbhit()) // If keyboard is hit
		{
			key = getch(); // Gets the value of the buffer
			if (key == ESC) // If ESC, program exits
			{
				system("cls"); // Clear the current console
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "                            ");
		Sleep(400);

	}
	stage1();
}

void reset(void)
{
	int i;
	system("cls");
	draw_map();
	while (kbhit())
		getch();

	dir = LEFT; // Initialization of the values
	length = 5;

	switch (stage) // Changes the initial number of score, speed, and number of bombs
	{
	case 1:
		score = 0;
		speed = 100;
		num_of_bombs = 3;
		break;

	case 2:
		score = 150;
		speed = 70;
		num_of_bombs = 5;
		break;

	case 3:
		score = 350;
		speed = 50;
		num_of_bombs = 7;
		break;
	}

	for (i = 0; i<length; i++) // Draws the body of snake
	{
		x[i] = MAP_X / 2 + i;
		y[i] = MAP_Y / 2;
		gotoxy(MAP_ADJ_X + x[i], MAP_ADJ_Y + y[i], "¢Ã");
	}
	gotoxy(MAP_ADJ_X + x[0], MAP_ADJ_Y + y[0], "¢Ã"); // Actually, this part is for snakes' head. But it is unneccesery in this code
	food(); // Creates the food
	bomb(); // Creates the bomb
}

void draw_map(void) // Draws the map
{
	int i, j;
	for (i = 0; i<MAP_X; i++)
	{
		gotoxy(MAP_ADJ_X + i, MAP_ADJ_Y, "¡á");
	}
	for (i = MAP_ADJ_Y + 1; i<MAP_ADJ_Y + MAP_Y - 1; i++)
	{
		gotoxy(MAP_ADJ_X, i, "¡á");
		gotoxy(MAP_ADJ_X + MAP_X - 1, i, "¡á");
	}
	for (i = 0; i<MAP_X; i++) {
		gotoxy(MAP_ADJ_X + i, MAP_ADJ_Y + MAP_Y - 1, "¡á");
	}
}

void move(int dir)
{
	int i, j;

	if (x[0] == food_x && y[0] == food_y) // Case when it hits with food
	{
		score += 10;
		food();
		length++;
		x[length - 1] = x[length - 2];
		y[length - 1] = y[length - 2];
	}
	for (j = 0; j < num_of_bombs; j++)
	{
		if (x[0] == bomb_x[j] && y[0] == bomb_y[j]) // Case when it hits with bomb
		{
			score -= 10;

			for (j = 0; j < num_of_bombs; j++)
				gotoxy(MAP_ADJ_X + bomb_x[j], MAP_ADJ_Y + bomb_y[j], " "); // Delets the lastest bombs

			bomb();
			gotoxy(MAP_ADJ_X + x[length - 1], MAP_ADJ_Y + y[length - 1], " "); // Delets the last body of the snake
			length--;
		}
	}
	if (x[0] == 0 || x[0] == MAP_X - 1 || y[0] == 0 || y[0] == MAP_Y - 1) // Case when it hits the wall
	{
		game_over();
		return;
	}
	for (i = 1; i<length; i++) // Case when it hits itself
	{
		if (x[0] == x[i] && y[0] == y[i])
		{
			game_over();
			return;
		}
	}

	gotoxy(MAP_ADJ_X + x[length - 1], MAP_ADJ_Y + y[length - 1], "  "); // Delets it's last one
	for (i = length - 1; i>0; i--) // Move the coordinates one by one
	{
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
	gotoxy(MAP_ADJ_X + x[0], MAP_ADJ_Y + y[0], "¢Ã"); // Part that changes head to body. But in this code, it is unnecessery
	if (dir == LEFT) --x[0];
	if (dir == RIGHT) ++x[0];
	if (dir == UP) --y[0];
	if (dir == DOWN) ++y[0];
	gotoxy(MAP_ADJ_X + x[i], MAP_ADJ_Y + y[i], "¢Ã"); // Part that puts new head. But unnecessery in this code

	if (length < 2) // If length goes down below 2, gmae is over
		game_over();

	// Beccause it was too hard to change stages by recent score, I gave additional points for it
	if (score == 100) // 50 additional points
	{
		score = 150;
		stage2();
	}

	if (score == 250) // 100 additional points
	{
		score = 350;
		stage3();
	}
}

void pause(void)
{
	while (1)
	{
		if (key == PAUSE) // By using Sleep function, I made program to pause 
		{
			gotoxy(MAP_ADJ_X + (MAP_X / 2) - 9, MAP_ADJ_Y, "< PAUSE : PRESS ANY KEY TO RESUME > ");
			Sleep(400);
			gotoxy(MAP_ADJ_X + (MAP_X / 2) - 9, MAP_ADJ_Y, "                                    ");
			Sleep(400);
		}
		else
		{
			draw_map();
			return;
		}
		if (kbhit())
		{

			do
			{
				key = getch();
			} while (key == 224);
		}

	}
}

void game_over(void) // UI when game is over
{
	int i;

	for (i = 0; i < length; i++) // Delets the body of the snake, only head lefts
		gotoxy(MAP_ADJ_X + x[i], MAP_ADJ_Y + y[i], " ");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 5, "+----------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 6, "|      GAME OVER..     |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 7, "+----------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 8, " YOUR SCORE : ");
	printf("%d", last_score = score);

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 12, " Press any keys to restart.. ");

	if (score>best_score)
	{
		best_score = score;
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 4, MAP_ADJ_Y + 10, "¡Ù BEST SCORE ¡Ù");
	}
	Sleep(500);
	while (kbhit())
		getch();
	key = getch();
	title();
}

void food(void)
{
	int i;

	int food_crush_on = 0;
	int r = 0;
	gotoxy(MAP_ADJ_X, MAP_ADJ_Y + MAP_Y, " YOUR SCORE: "); // Displays Scores 
	printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", score, last_score, best_score);

	while (1)
	{
		food_crush_on = 0;
		srand((unsigned)time(NULL) + r); // Creates random number table
		food_x = (rand() % (MAP_X - 2)) + 1;
		food_y = (rand() % (MAP_Y - 2)) + 1;

		for (i = 0; i<length; i++)
		{
			if (food_x == x[i] && food_y == y[i]) // Check if the food is coordinated with the snake
			{
				food_crush_on = 1;
				r++;
				break;
			}

			else if (food_x == bomb_x[i] && food_y == bomb_y[i]) // Check if the bomb coordinates with the snake
			{
				food_crush_on = 1;
				r++;
				break;
			}
		}
		if (food_crush_on == 1) continue; // If coordinates, do the while statement again

		gotoxy(MAP_ADJ_X + food_x, MAP_ADJ_Y + food_y, "¡ß");
		speed -= 3;
		break;
	}
}

void bomb(void) // As new bombs are duplicated, others are fake bombs
{
	int i, j;
	int bomb_crush_on = 0;
	int r = 0;
	char* map; // Birngs the map by pointer of map array

	gotoxy(MAP_ADJ_X, MAP_ADJ_Y + MAP_Y, " YOUR SCORE: "); // Displays Scores 
	printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", score, last_score, best_score);

	while (1)
	{
		bomb_crush_on = 0;
		srand((unsigned)time(NULL) + r); // Creates random number table

		for (j = 0; j < num_of_bombs; j++)
		{
			bomb_x[j] = (rand() % (MAP_X - 2)) + 1; // Random number between 1 ~ 28
			bomb_y[j] = (rand() % (MAP_Y - 2)) + 1; // Random number between 1 ~ 18
		}
		for (j = 0; j < num_of_bombs; j++)
		{
			for (i = 0; i < length; i++)
			{
				if (bomb_x[j] == x[i] && bomb_y[j] == y[i]) // Check if the bomb coordinates with the snake
				{
					bomb_crush_on = 1;
					r++;
					break;
				}

				else if (bomb_x[j] == food_x && bomb_y[j] == food_y) // Check if the bomb coordinates with the snake
				{
					bomb_crush_on = 1;
					r++;
					break;
				}
			}
		}

		if (bomb_crush_on == 1) continue; // If coordinates, do the while statement again

		for (j = 0; j < num_of_bombs; j++) // Creates bombs
			gotoxy(MAP_ADJ_X + bomb_x[j], MAP_ADJ_Y + bomb_y[j], "¡Þ");

		speed -= 5;
		break;
	}
}

void status(void)
{
	int i;

	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y, "head= ");
	printf("%2d,%2d", x[0], y[0]);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 1, "food= ");
	printf("%2d,%2d", food_x, food_y);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 1, "bomb= "); // Shows the locations of real bombs
	for (i = 0; i < num_of_bombs; i++) printf("(%2d,%2d) ", bomb_x[i], bomb_y[i]);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 2, "leng= ");
	printf("%2d", length);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 3, "key= ");
	printf("%3d", key);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 4, "stage= ");
	printf("%1d", stage);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 5, "spd= ");
	printf("%3d", speed);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 6, "score= ");
	printf("%3d", score);
}

void stage1(void)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+--------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|        S T A G E 1       |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "+--------------------------+");

	while (1)
	{
		if (kbhit())
		{
			key = getch();
			if (key == ESC) // If ESC, program exits
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 10, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 10, "                            ");
		Sleep(400);

	}
	stage = 1;
	reset(); // Resets the game
}

void stage2(void)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|          S T A G E 2        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "|        B O N U S + 5 0      |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 8, "+-----------------------------+");
	while (1)
	{
		if (kbhit())
		{
			key = getch();
			if (key == ESC) // If ESC, program exits
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, "                            ");
		Sleep(400);
	}
	stage = 2;
	reset(); // Resets the game

}

void stage3(void)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|          S T A G E 3        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "|        B O N U S + 100      |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 8, "+-----------------------------+");
	while (1)
	{
		if (kbhit())
		{
			key = getch();
			if (key == ESC) // If ESC, program exits
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, "                            ");
		Sleep(400);
	}
	stage = 3;
	reset(); // Resets the game
}

void cursor_delete(void)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
