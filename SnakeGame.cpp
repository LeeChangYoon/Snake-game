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
#define MAP_X 30 
#define MAP_Y 20 
 
int x[100], y[100]; // Location of snake head, Max size of snake is 100
int food_x, food_y; // Locatoin of food
int length; // Snake length
int speed; // Speed of the game
int score; //score is stored
int best_score=0; // Bestscore
int last_score=0; // Your score in the last game
int dir; // Direction
int key; // input of the key
int status_on=0; // Status  for developers
 
// gotoxy is a function that moves cursor to selected x, y
void gotoxy(int x,int y, const char* s) 
{ 
    COORD pos={2*x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    printf("%s",s);
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
    
    while(1)
	{
        if(kbhit()) do{key=getch();} while(key==224); // Key input
        Sleep(speed);
        
        switch(key) // Apprehend the key and runs the program
		{  
            case LEFT:
            case RIGHT:
            case UP:
            case DOWN:
                if( (dir==LEFT&&key!=RIGHT)||(dir==RIGHT&&key!=LEFT)||(dir==UP&&key!=DOWN)||
					(dir==DOWN&&key!=UP)) // Need for prevent the 180 degrees rotational movement
                    dir=key;
                key=0; // Reset the key to 0
            break;
            
			case PAUSE: 
                pause();
            break;
            
			case 115: // input 'S', then status() activated
                if(status_on==0) status_on=1;
                else status_on=0;
                key=0;
                break;
            
			case ESC: // Program exits if the input value is ESC
                exit(0);
        }
        move(dir); 
        
        if(status_on==1) status(); 
    }    
}
///////////////////////////MAIN END////////////////////////////////

void title(void)
{
    int i,j;
    
    while (kbhit()) // Takes off the value whicj is in buffer
		getch(); 
     
    draw_map();    
	cursor_delete();
    for(i=MAP_ADJ_Y+1;i<MAP_ADJ_Y+MAP_Y-1;i++) // Fills the inside of frame with blanks
	{ 
        for(j=MAP_ADJ_X+1;j<MAP_ADJ_X+MAP_X-1;j++) 
			gotoxy(j,i,"  ");
    }
 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+5,"+--------------------------+");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+6,"|        S N A K E         |");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+7,"+--------------------------+");
 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+9," < PRESS ANY KEY TO START > ");
 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+11,"   ¡Þ ¡ç,¡æ,¡è,¡é : Move    ");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+12,"   ¡Þ P : Pause             ");    
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+13,"   ¡Þ ESC : Quit              ");    
 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+17,"  iThings Lab");    
    
    while(1)
	{
        if(kbhit())
		{ 
            key=getch();
			if (key == ESC) // If ESC, program exits
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
            else break; // If not ESC, then continues
        } 

        gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+9," < PRESS ANY KEY TO START > ");
        Sleep(400);
        gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+9,"                            ");
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
    
    dir=LEFT; // Initialization of the values
    speed=100; 
    length=5; 
    score=0; 
    for(i=0;i<length;i++)
	{ 
        x[i]=MAP_X/2+i;
        y[i]=MAP_Y/2;
        gotoxy(MAP_ADJ_X+x[i],MAP_ADJ_Y+y[i],"¢Ã");
    }
    gotoxy(MAP_ADJ_X+x[0],MAP_ADJ_Y+y[0],"¢Ã"); // Actually, this part is for snakes' head. But it is unneccesery in this code
    food(); 
}
 
void draw_map(void)
{ 
    int i,j;
    for(i=0;i<MAP_X;i++)
	{
        gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y,"¡á");
    }
    for(i=MAP_ADJ_Y+1;i<MAP_ADJ_Y+MAP_Y-1;i++)
	{
        gotoxy(MAP_ADJ_X,i,"¡á");
        gotoxy(MAP_ADJ_X+MAP_X-1,i,"¡á");
    }
    for(i=0;i<MAP_X;i++){
        gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y+MAP_Y-1,"¡á");
    }
}
 
void move(int dir)
{
    int i;
 
    if(x[0]==food_x&&y[0]==food_y) // Case when it hits with food
	{  
        score+=10;  
        food();  
        length++;  
        x[length-1]=x[length-2];  
        y[length-1]=y[length-2];
    }
    if(x[0]==0||x[0]==MAP_X-1||y[0]==0||y[0]==MAP_Y-1) // Case when it hits the wall
	{  
        game_over();
        return;  
    }
    for(i=1;i<length;i++) // Case when it hits itself
	{  
        if(x[0]==x[i]&&y[0]==y[i])
		{
            game_over();
            return;
        }
    }
    
    gotoxy(MAP_ADJ_X+x[length-1],MAP_ADJ_Y+y[length-1],"  "); // Delets it's last one
    for(i=length-1;i>0;i--) // Move the coordinates one by one
	{  
        x[i]=x[i-1];
        y[i]=y[i-1];
    }
    gotoxy(MAP_ADJ_X+x[0],MAP_ADJ_Y+y[0],"¢Ã"); // Part that changes head to body. But in this code, it is unnecessery
    if(dir==LEFT) --x[0];  
    if(dir==RIGHT) ++x[0];
    if(dir==UP) --y[0]; 
    if(dir==DOWN) ++y[0];     
    gotoxy(MAP_ADJ_X+x[i],MAP_ADJ_Y+y[i],"¢Ã"); // Part that puts new head. But unnecessery in this code

	if (score == 70) // If score reaches to 70, goes to stage 2
		stage2();
	if (score == 200) // if score reaches to 200, goes to stage 3
		stage3();
}
 
void pause(void)
{ 
    while(1)
	{
        if(key==PAUSE)
		{
            gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y,"< PAUSE : PRESS ANY KEY TO RESUME > ");
            Sleep(400);
            gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y,"                                    ");
            Sleep(400);
        }
        else
		{
            draw_map();
            return;
        } 
        if(kbhit())
		{
            
                do
				{
                    key=getch();
                }
                while(key==224);
        }
            
    }
}
 
void game_over(void)
{  
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"|      GAME OVER..     |");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+8," YOUR SCORE : ");
    printf("%d", last_score=score);
    
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+12," Press any keys to restart.. ");
    
    if(score>best_score)
	{
        best_score=score;
		gotoxy(MAP_ADJ_X+(MAP_X/2)-4,MAP_ADJ_Y+10,"¡Ù BEST SCORE ¡Ù");
    }
    Sleep(500);
    while (kbhit()) 
		getch();
    key=getch();
    title();
}
 
void food(void)
{
    int i;
    
    int food_crush_on=0;
    int r=0; 
    gotoxy(MAP_ADJ_X,MAP_ADJ_Y+MAP_Y," YOUR SCORE: "); 
    printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", score, last_score, best_score);
    
    while(1)
	{            
        food_crush_on=0;    
        srand((unsigned)time(NULL) + r); // Creates random number table
        food_x=(rand()%(MAP_X-2))+1;    
        food_y=(rand()%(MAP_Y-2))+1;
        
        for(i=0;i<length;i++)
		{ 
            if(food_x==x[i]&&food_y==y[i]){ // Check if the food is coordinated with the snake
                food_crush_on=1; 
                r++;
				break;	
            }
        }
        
        if(food_crush_on==1) continue; // If coordinates, do the while statement again
            
        gotoxy(MAP_ADJ_X+food_x,MAP_ADJ_Y+food_y,"¡ß"); 
        speed-=3; 
        break;
        
    }
}
 
void status(void){ 
    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y,"head= ");
    printf("%2d,%2d",x[0],y[0]);
    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+1,"food= ");
    printf("%2d,%2d",food_x,food_y);
    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+2,"leng= ");
    printf("%2d",length);
    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+3,"key= ");
    printf("%3d",key);
    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+4,"spd= ");
    printf("%3d",speed);
    gotoxy(MAP_ADJ_X+MAP_X+1,MAP_ADJ_Y+6,"score= ");
    printf("%3d",score);  
}

void cursor_delete(void)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
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

		gotoxy(MAP_ADJ_X + (MAP_X / 2) -6, MAP_ADJ_Y + 10, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 10, "                            ");
		Sleep(400);

	}
	reset(); // Resets the game
}

void stage2(void)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|          S T A G E 2        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "|                             |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 8, "|         B O N U S +30       |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "+-----------------------------+");
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
	reset(); // Resets the game
	speed = 70;
	score = 100;
}

void stage3(void)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|          S T A G E 3        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "|                             |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 8, "|         B O N U S +50       |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "+-----------------------------+");
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
	reset(); // Resets the game
	speed = 30;
	score = 250;
}
