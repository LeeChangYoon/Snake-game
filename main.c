#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
 
#define LEFT 75 // Left
#define RIGHT 77 // Right
#define UP 72 // Upward
#define DOWN 80 // Downward
#define PAUSE 112 // Pause -> 'P'
#define ESC 27 // ESC
 
#define MAP_ADJ_X 3 // Map starting point of x 
#define MAP_ADJ_Y 2	// Map starting point of y
#define MAP_X 30 // Horizontal map size
#define MAP_Y 20 // Vertical map size
 
int x[100], y[100]; // Location of snake head, Max size of snake is 100
int food_x, food_y; // Locatoin of food
int length; // Snake length
int speed; // Speed of the game
int score; //score is stored
int best_score=0; // Bestscore
int last_score=0; // Your score in the recent game
int dir; // Direction
int key; // Stdin
int status_on=0; // Status
 
// gotoxy is a function that moves ccursor to selected x, y
void gotoxy(int x,int y, const char* s) 
{ 
    COORD pos={2*x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    printf("%s",s);
}
 
void title(void); // Game title
void reset(void); // Reset the game
void draw_map(void);  // Map drawing
void move(int dir);  // Related to snake movinng
void pause(void); // Pause the game
void game_over(void); // Game over 
void food(void); // Randomly response the food
void status(void); // Shows you the score at the bottom
void cursor_delete(void); // Function that delets the cursor, Identifier
 
////////////////////////////MAIN START//////////////////////////////
int main()
{
    title();
    
    while(1)
	{
        if(kbhit()) do{key=getch();} while(key==224); 
        Sleep(speed);
        
        switch(key)
		{  
            case LEFT:
            case RIGHT:
            case UP:
            case DOWN:
                if( (dir==LEFT&&key!=RIGHT)||(dir==RIGHT&&key!=LEFT)||(dir==UP&&key!=DOWN)||(dir==DOWN&&key!=UP)) 
                    dir=key;
                key=0; 
            break;
            
			case PAUSE: 
                pause();
            break;
            
			case 115: 
                if(status_on==0) status_on=1;
                else status_on=0;
                key=0;
                break;
            
			case ESC: 
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
    
    while (kbhit()) 
		getch(); 
     
    draw_map();    
	cursor_delete();
    for(i=MAP_ADJ_Y+1;i<MAP_ADJ_Y+MAP_Y-1;i++)
	{ 
        for(j=MAP_ADJ_X+1;j<MAP_ADJ_X+MAP_X-1;j++) 
			gotoxy(j,i,"  ");
    }
 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+5,"+--------------------------+");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+6,"|        S N A K E         |");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+7,"+--------------------------+");
 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+9," < PRESS ANY KEY TO START > ");
 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+11,"   ◇ ←,→,↑,↓ : Move    ");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+12,"   ◇ P : Pause             ");    
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+13,"   ◇ ESC : Quit              ");    
 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+17,"  iThings Lab");    
    
    while(1)
	{
        if(kbhit())
		{ 
            key=getch();
			if (key == ESC)
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
            else break; 
        } 

        gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+9," < PRESS ANY KEY TO START > ");
        Sleep(400);
        gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+9,"                            ");
        Sleep(400);
        
    }
    reset();  
}
 
void reset(void)
{
    int i;
    system("cls"); 
    draw_map(); 
    while (kbhit())
		getch(); 
    
    dir=LEFT;   
    speed=100; 
    length=5; 
    score=0; 
    for(i=0;i<length;i++)
	{ 
        x[i]=MAP_X/2+i;
        y[i]=MAP_Y/2;
        gotoxy(MAP_ADJ_X+x[i],MAP_ADJ_Y+y[i],"▣");
    }
    gotoxy(MAP_ADJ_X+x[0],MAP_ADJ_Y+y[0],"▣"); // This part is unnecessary
    food(); 
}
 
void draw_map(void)
{ 
    int i,j;
    for(i=0;i<MAP_X;i++)
	{
        gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y,"■");
    }
    for(i=MAP_ADJ_Y+1;i<MAP_ADJ_Y+MAP_Y-1;i++)
	{
        gotoxy(MAP_ADJ_X,i,"■");
        gotoxy(MAP_ADJ_X+MAP_X-1,i,"■");
    }
    for(i=0;i<MAP_X;i++){
        gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y+MAP_Y-1,"■");
    }
}
 
void move(int dir)
{
    int i;
 
    if(x[0]==food_x&&y[0]==food_y)
	{  
        score+=10;  
        food();  
        length++;  
        x[length-1]=x[length-2];  
        y[length-1]=y[length-2];
    }
    if(x[0]==0||x[0]==MAP_X-1||y[0]==0||y[0]==MAP_Y-1)
	{  
        game_over();
        return;  
    }
    for(i=1;i<length;i++)
	{  
        if(x[0]==x[i]&&y[0]==y[i])
		{
            game_over();
            return;
        }
    }
    
    gotoxy(MAP_ADJ_X+x[length-1],MAP_ADJ_Y+y[length-1],"  ");  
    for(i=length-1;i>0;i--)
	{  
        x[i]=x[i-1];
        y[i]=y[i-1];
    }
    gotoxy(MAP_ADJ_X+x[0],MAP_ADJ_Y+y[0],"▣"); // Unnecessery
    if(dir==LEFT) --x[0];  
    if(dir==RIGHT) ++x[0];
    if(dir==UP) --y[0]; 
    if(dir==DOWN) ++y[0];     
    gotoxy(MAP_ADJ_X+x[i],MAP_ADJ_Y+y[i],"▣");  
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
		gotoxy(MAP_ADJ_X+(MAP_X/2)-4,MAP_ADJ_Y+10,"☆ BEST SCORE ☆");
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
	status(); // Shows the status
    
    while(1)
	{            
        food_crush_on=0;    
        srand((unsigned)time(NULL) + r); // Don't know why r is multiplied
        food_x=(rand()%(MAP_X-2))+1;    
        food_y=(rand()%(MAP_Y-2))+1;
        
        for(i=0;i<length;i++)
		{ 
            if(food_x==x[i]&&food_y==y[i]){
                food_crush_on=1; 
                r++;
				break;	
            }
        }
        
        if(food_crush_on==1) continue; 
            
        gotoxy(MAP_ADJ_X+food_x,MAP_ADJ_Y+food_y,"◆"); 
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
