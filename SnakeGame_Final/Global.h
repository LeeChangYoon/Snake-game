#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

void gotoxy(int x, int y, const char* s);
void cursor_delete(void);

//Define
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27
 
#define MAP_ADJ_X 3
#define MAP_ADJ_Y 2
#define MAP_X 30
#define MAP_Y 20

//Function
void title(struct _snake* snake); // Game title
void reset(struct _snake* snake); // Reset the game
void draw_map(void);  // drawing the frame of the map
void move(int dir, struct _snake* snake);  // Related to snake movinng
void pause(struct _snake* snake); // Pause the game
void game_over(struct _snake* snake); // Game over 
void food(struct _snake* snake); // Randomly response the food
void status(struct _snake* snake); // Status for developers
void cursor_delete(void); // Function that deletes the cursor
void stage1(struct _snake* snake); // Stage1
void stage2(struct _snake* snake); // Stage2: It occurs when point reaches to 70, and gives bonus 10 points
void stage3(struct _snake* snake); // Stage3: It occurs when point reaches to 200, and gives bonus 50 points
void bomb(struct _snake* snake); // Response the bomb on random place


//Structure
typedef struct _snake
{
	int x[100], y[100]; // Location of snake head, Max size of snake is 100
	int food_x, food_y; // Locatoin of the food
	int bomb_x[100], bomb_y[100]; // Location of the bomb, max number of the bomb is 100
	int num_of_bombs; // Number of the bombs
	int length; // Snake length
	int speed; // Speed of the game
	int score; //score is stored
	int best_score; // Bestscore
	int last_score; // Your score in the last game
	int dir; // Direction
	int key; // input of the key
	int stage; // Stage number
	int status_on; // Status  for developers
	int food_crush_on;

} snake;