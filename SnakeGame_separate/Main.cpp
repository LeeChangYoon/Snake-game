#include "Global.h"

//Delclar Structure
snake S1;

////////////////////////////MAIN START//////////////////////////////
int main()
{
	title();

	while (1)
	{
		if (kbhit()) do { S1.key = getch(); } while (S1.key == 224); // Key input
		Sleep(S1.speed); // Controls the speed, function Sleep() stops the program for milli sec

		switch (S1.key) // Apprehend the key and runs the program
		{
		case LEFT:
		case RIGHT:
		case UP:
		case DOWN:
			if ((S1.dir == LEFT && S1.key != RIGHT) || (S1.dir == RIGHT && S1.key != LEFT) || (S1.dir == UP && S1.key != DOWN) ||
				(S1.dir == DOWN && S1.key != UP)) // Need for prevent the 180 degrees rotational movement
				S1.dir = S1.key;
			S1.key = 0; // Reset the key to 0
			break;

		case PAUSE:
			pause();
			break;

		case 115: // input 'S', then status() activated
			if (S1.status_on == 0) S1.status_on = 1;
			else S1.status_on = 0;
			S1.key = 0;
			break;

		case ESC: // Program exits if the input value is ESC
			exit(0);
		}
		move(S1.dir);
		if (S1.status_on == 1) status(); // There are no turning off, because it is i the infinite loop
	}
}
///////////////////////////MAIN END////////////////////////////////