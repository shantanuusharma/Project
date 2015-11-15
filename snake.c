/*GAME OF SNAKE. Copyright (C) 2015 SHANTANU SHARMA 111403042

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA


GAME OF SNAKE WIHTOUT USING THE NCURSES LIBRARY 

There are few major things which I have changed from my last push to make the game more intressting such as I have made the boundary a variable which allows better control for me to handle the movements 
Also instead of using a strucutre which was causing me a bit of confusion I have used a 2-d array to keep track of the food co-ordinates and the snke's co-ordinates
*/


#include"snake.h"


/* The below four functions are not originally written by me but had to be added  */


void clrscr() {          //clearing the screen
	system("clear");
}

void gotoxy(int x, int y) { 		//getting to co-ordinate x,y
	printf("%c[%d;%df",0x1B,y,x);
	
}

int getch() {		//returns a single character from the keyboard 
	char ch;
	system("stty raw");
	ch = getchar();
	system("stty sane");
	return(ch);
}


/* This function is to read if a character is entered from the keyboard which will be needed to control the snake and the menu */
	
int kbhit() {
	struct termios oldt, newt;
      	int ch;
      	int oldf;
 
      	tcgetattr(STDIN_FILENO, &oldt);
      	newt = oldt;
      	newt.c_lflag &= ~(ICANON | ECHO);
      	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
      	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
      	ch = getchar();
 
      	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      	fcntl(STDIN_FILENO, F_SETFL, oldf);
 
      	if(ch != EOF) {
        	ungetc(ch, stdin);
        	return 1;
      	}
 
      return 0;
}
 

char returnkey() {
	int key;	
	while(!kbhit());
		key = getch();
	
	return((char)key);   //return the character
}


int checkkey(int dir) {    //Basically I need this function to check if the direction specified is valid or not i.e if already down, down will invalid
	int key;
	if(kbhit()) {  // if something is entered
		key = getch();
		if(dir != key) {
			if(key == DOWN && dir != UP)
				dir = key;
			else if(key == UP && dir != DOWN)
				dir = key;
			else if(key == RIGHT && dir != LEFT)
				dir = key;
			else if(key == LEFT && dir != RIGHT)
				dir = key;
			else if(key == ESC || key == PAUSE) 
				pausemenu();
		}	

	}
	return dir;
}

int getgamespeed() {
	int speed;
	clrscr();
	do {
		printf("Select the Speed between 1 - 9 ( 9 is fastest)\n");
		speed = returnkey() - '0';	//should have used atoi but was giving a minor problem

	}while(speed < 1 || speed > 9);
return(speed);

}

void pausemenu() {
	gotoxy(27,22);
	returnkey();
	gotoxy(27,23);	
	printf("         ");

}

/*For those who do not know rules of snake :P */

void printrule() {
	clrscr();
	printf("\nINSTRUCTIONS\n");	
	printf("\nThe player controls a long, thin creature, resembling a snake, which roams around on a bordered plane, picking up food (or some other item), trying to avoid hitting its own tail or the border that surround the playing area. Each time the snake eats a piece of food, its tail grows longer, making the game increasingly difficult. The user controls the direction of the snake's head (up, down, left, or right), and the snake's body follows. The player cannot stop the snake from moving while the game is in progress, and cannot make the snake go in reverse."); 
	printf("Press ESCAPE to quit the game\n");
	printf("Press any key to continue..(ESCAPE AND ENTER TO QUIT)\n");
	if(getchar() == 27) //IF ESC IS ENTERED 
	exit(0);
}

void controls() {
	clrscr();
	printf("Controls\n");
	printf("HERE ARE THE CONTROLS OF THE GAME\n\n");
	printf("MOVEMENTS OF SNAKE ->\n");  
	printf("\t\t\tUP -> UP ARROW\n");
	printf("\t\t\tDOWN -> DOWN ARROW\n");
	printf("\t\t\tLEFT -> LEFT ARROW\n");
	printf("\t\t\tRIGHT -> RIGHT ARROW\n");			
	printf("\t\t\tP/ESC -> PAUSE (YOU MIGHT NEED IT AT SPEED 9 ;)\n");	
	printf("Press any key to continue\n");
	returnkey();	
	return;
}


void border(int consolewidth, int consoleheight) {
	int i = 1,j = 1;	
	clrscr();
	gotoxy(i,j); // I have shifted the boundary to the top as it was difficult to manage the gotoxy function in the middle
	for(;j < consoleheight;j++) {
		gotoxy(i,j);		
		printf("!");	
		gotoxy(consolewidth,j);
		printf("!");
	}
	j = 1;	
	
	for(;i < consolewidth + 1;i++) {
		gotoxy(i,j);
		printf("!");
		gotoxy(i, consoleheight - 4);
		printf("!");
	}	

}

void foodcreate(int foodXY[], int width, int height, int snakeXY[][MAX_SIZE], int snakelength) {
	do {	
		foodXY[0] = rand() % (width - 2) + 2;
		foodXY[1] = rand() % (height - 6) +2;	
	} while(touchesbody(foodXY[0], foodXY[1], snakeXY, snakelength, 0));
	
	gotoxy(foodXY[0],foodXY[1]);
	printf("*");		



/*	
	if(food.x == 0 && food.y == 0) { //creating food for the first time
		food.x = rand() % 30;
		food.y = rand() % 70;
	if(food.x <= 10)
		food.x + 10;
	if(food.y <= 10)
		food.y + 10;		
	}

	if(head.x == food.x && head.y == food.y) {      //food is captured and new food is to be generated
		length++;
		food.x = rand() % 30;
		food.y = rand() % 70;
		if(food.x <= 10)
		food.x++;
		if(food.y <= 10)
		food.y++;
		
	}
	gotoxy(food.y,food.x);
	printf("*"); */


}			

/*TOOK ME A WHILE TO FIGURE THEE BELOW 2 FUNCTIONS OUT  --- FIRST I THOUGHT OF A STRUCUTRE TO KEEP TRACK OF THE SNAKES CO-ORDINATES BUT THEY WERE ONLY CAUSING CONFUSION SO I HAVE USED A 2-D ARRAY WHICH IS MUCH MORE SIMPLER :) I HAVE EXPLAINED THE WORKING BELOW FOR MY NEEDS AS I TEND TO GET CONFUSED 

x 1 2 3 4 
y 1 1 1 1  NOW WHEN I WANT TO MOVE FORWARD  

X 1 1 2 3
Y 1 1 1 1  <- NEW ARRAY 

SIMILARLY FOR RIGHT : 

X 1 2 3 4
Y 1 1 1 1

X 1 2 3 5
Y 1 1 1 1 

I ADD ONE TO THE X (SIMILARLY FOR REST)	*/ 

void movesnake(int snakeXY[][MAX_SIZE], int snakelength, int dir) {
	for(i = snakelength - 1; i >= 1; i--) {
		snakeXY[0][i] = snakeXY[0][i - 1];
		snakeXY[1][i] = snakeXY[1][i - 1];
	}
	switch (dir) {
		case DOWN : snakeXY[1][0]++; 
			break;
		case UP : snakeXY[1][0]--; //upwards the y reduces
			break;
		case RIGHT : snakeXY[0][0]++;
			break;
		case LEFT : snakeXY[0][0]--;
			break;
		//default ?	
	}
}

//Basically displaying the movement of the snake is a 2 step process
//1) displaying a blank (space) on the previous position of the end of the snake 
//2) changing the head to a body part.

void displaymovement(int snakeXY[][MAX_SIZE], int snakelength, int dir) {
	int x,y;
	x = snakeXY[0][snakelength - 1];
	y = snakeXY[1][snakelength - 1];
	gotoxy(x,y);
	printf(" ");
	gotoxy(snakeXY[0][0],snakeXY[1][0]);
	printf("*");
	movesnake(snakeXY, snakelength, dir);
	gotoxy(snakeXY[0][0],snakeXY[1][0]);
	printf("X");
	gotoxy(1,1);
}	


int checkeatfood(int snakeXY[][MAX_SIZE], int foodXY[]) {
	if(snakeXY[0][0] == foodXY[0] && snakeXY[1][0] == foodXY[1]) {   // checks if head == food
		foodXY[0] = 0;
		foodXY[1] = 0;
		return 1;
	}		
	return 0;
}



/* TO CHECK IF GAME IS OVER NUMBER OF LIVES REMAINING SHOULD BE 0 , FOR A LIFE TO DECREASE 2 CONDITIONS 
	1) SNAKE TOUCHES OWN BODY.
	2) HEAD TOUCHES BOUNDARY. */

//This function checks for the first condition 

int touchesbody(int x , int y, int snakeXY[][MAX_SIZE], int snakelength, int check) {
	int dead = 0;	
	for(i = check; i <snakelength; i++)
		if(x == snakeXY[0][i] && y == snakeXY[1][i])
			dead = 1;	
	return (dead);	
}


//This function checks for *second & first* condition

int collides(int snakeXY[][MAX_SIZE],int consolewidth, int consoleheight, int snakelength) {
	int dead = 0;
	if(snakeXY[0][0] == 1 || snakeXY[1][0] == 1 || snakeXY[0][0] == consolewidth || snakeXY[1][0] == consoleheight - 4) 	
		dead = 1;
	else if(touchesbody(snakeXY[0][0], snakeXY[1][0], snakeXY, snakelength, 1)) 
		dead = 1;
	return(dead);
}


int speedscoredisplay(int score, int speed) {
	gotoxy(5,25);
	printf("Score -> %d",score);
	gotoxy(5,26);
	printf("Speed -> %1d\n",speed);	
	gotoxy(1,1);
	return 1;
}

void initsnake(int snakeXY[][MAX_SIZE], int snakelength) {
	int i;
	int snakecoordx = snakeXY[0][0];
	int snakecoordy = snakeXY[1][0];
	for( i = 0 ;i < snakelength; i++) {
		snakeXY[0][i] = snakecoordx + i;
		snakeXY[1][i] = snakecoordy;
	}
}
		

void loadsnake(int snakeXY[][MAX_SIZE], int snakelength) {
	for (i = 0; i < snakelength; i++) {          
        	gotoxy(snakeXY[0][i], snakeXY[1][i]);
        }	printf("*"); 
}

void scoreboard(int score, int speed) {
	gotoxy(5, 26);
	globscore = score;	
	printf("Score : %d",score);
	gotoxy(5, 27);
	printf("Speed : %d", speed);
}	
	
void loadgame() {
	clrscr();
	printf("Loading\n");	
	int i,j;
 	for(i = 0;i < 10;i++) {
    		for(j = 0;j <= 100000000;j++);
    	printf(".");
	}    	
	printf("\nGame is loaded,press enter to play\n");	
	int snakeXY[2][MAX_SIZE];	
	int snakelength = 4;
	int dir = LEFT;
	int foodXY[0];
	int score = 0;
	int consolewidth = 80;
	int consoleheight = 25;
	int speed = getgamespeed();
	snakeXY[0][0] = 40;
	snakeXY[1][0] = 10;
	border(consolewidth, consoleheight);
	initsnake(snakeXY, snakelength);
	loadsnake(snakeXY,snakelength);	
	foodcreate(foodXY,consolewidth,consoleheight,snakeXY,snakelength);
	scoreboard(score,speed);
	startgame(snakeXY, foodXY, consolewidth, consoleheight, snakelength, dir, score, speed);
}

//This game starts the game the setting of speed is done by using the clock() function
void startgame(int snakeXY[][MAX_SIZE], int foodXY[], int consolewidth, int consoleheight, int snakelength, int dir, int score, int speed) {
	int isgameover = 0;
	clock_t endwait;
	int waittime = CLOCKS_PER_SEC-(speed)*(CLOCKS_PER_SEC/10);
	waittime = waittime / 2.5;	
	int tempscore = 10 * speed;
	int olddir;
	int newdir = 1;
	endwait = clock() + waittime;
	do {
		if(newdir) {
			olddir = dir;
			dir = checkkey(dir);
		}
		if(olddir != dir) 
			newdir = 0;
		if(clock() >= endwait) {
			displaymovement(snakeXY,snakelength,dir);
			newdir = 1;
			if(checkeatfood(snakeXY, foodXY)) {
				foodcreate(foodXY, consolewidth, consoleheight, snakeXY, snakelength);
				snakelength++;
				score = score + speed; // I have incremented the score with the speed ( 9 gets the most score)
				 if( score >= 10*speed+tempscore) {
                    			speed = speed * 2;
                    			tempscore = score;
 					if(speed <= 9)
                        			waittime = waittime - (CLOCKS_PER_SEC);
                    			else if(waittime >= 40)
                            			waittime = waittime - (CLOCKS_PER_SEC);
                         			
                   		}
				scoreboard(score, speed);			
			}
			endwait = clock() + waittime;	
		}
		isgameover = collides(snakeXY, consolewidth, consoleheight, snakelength);
		 
		if(snakelength >= MAX_SIZE-5) {
            		isgameover = 2;
            		score+=1500; 
        	}	

	
	} while(!isgameover);
	
	switch(isgameover) {
		case 1: 
			gameoverscreen();
			break;
		default: ;
			break;
	}		
	
	
}
void welcomescreen() {
	
	printf("\n\n\n\nWELCOME TO SNAKE\n\n\n\n");
	printf("\n");   
	printf("\t\t    _________         _________             \n");   
    	printf("\t\t   /         \\       /         \\          \n");   
    	printf("\t\t  /  /~~~~~\\  \\     /  /~~~~~\\  \\           \n");   
    	printf("\t\t  |  |     |  |     |  |     |  |           \n");       
    	printf("\t\t  |  |     |  |     |  |     |  |           \n");
    	printf("\t\t  |  |     |  |     |  |     |  |         / \n");
    	printf("\t\t  |  |     |  |     |  |     |  |       //  \n");
    	printf("\t\t (o  o)    \\  \\_____/  /     \\  \\_____/ /   \n");
    	printf("\t\t  \\__/      \\         /       \\        /     \n");
    	printf("\t\t    |        ~~~~~~~~~         ~~~~~~~~         \n");
    	printf("\t\t    ^                                           \n");
	getchar();
	
}


void gameoverscreen() {  
	int x = 17, y = 3;
	gotoxy(x,y++);
    	printf(":'######::::::'###::::'##::::'##:'########:\n");
    	gotoxy(x,y++);
    	printf("'##... ##::::'## ##::: ###::'###: ##.....::\n");
    	gotoxy(x,y++);
    	printf(" ##:::..::::'##:. ##:: ####'####: ##:::::::\n");
    	gotoxy(x,y++);
    	printf(" ##::'####:'##:::. ##: ## ### ##: ######:::\n");
    	gotoxy(x,y++);
    	printf(" ##::: ##:: #########: ##. #: ##: ##...::::\n");
   	gotoxy(x,y++);
    	printf(" ##::: ##:: ##.... ##: ##:.:: ##: ##:::::::\n");
    	gotoxy(x,y++);
    	printf(". ######::: ##:::: ##: ##:::: ##: ########:\n");
    	gotoxy(x,y++);
    	printf(":......::::..:::::..::..:::::..::........::\n");
    	gotoxy(x,y++);
    	printf(":'#######::'##::::'##:'########:'########::'####:\n");
    	gotoxy(x,y++);
    	printf("'##.... ##: ##:::: ##: ##.....:: ##.... ##: ####:\n");
    	gotoxy(x,y++);
    	printf(" ##:::: ##: ##:::: ##: ##::::::: ##:::: ##: ####:\n");
    	gotoxy(x,y++);
    	printf(" ##:::: ##: ##:::: ##: ######::: ########::: ##::\n");
    	gotoxy(x,y++);
    	printf(" ##:::: ##:. ##:: ##:: ##...:::: ##.. ##::::..:::\n");
    	gotoxy(x,y++);
    	printf(" ##:::: ##::. ## ##::: ##::::::: ##::. ##::'####:\n");
    	gotoxy(x,y++);
    	printf(". #######::::. ###:::: ########: ##:::. ##: ####:\n");
    	gotoxy(x,y++);
    	printf(":.......::::::...:::::........::..:::::..::....::\n");
	returnkey();
 	getch();  	
	gotoxy(25,25);	
	printf("Press Enter to continue\n");
	returnkey();	
	clrscr(); //clear the console
}


#define ENTER_KEY 10

int selector(int x, int y, int z) {
	char cha;
	int i = 0; 
	x = x - 2;
	gotoxy(x,z);
	printf(">");
	gotoxy(1,1);
	do {
		cha = returnkey();
		if(cha == (char)UP) {
			gotoxy(x,z + i);
			printf(" ");	
			if(z >= z + i)
				i = y - z - 2;
			else
				i--;
			gotoxy(x,z + i);
			printf(">");		
		}
		
		else if( cha == (char)DOWN) {
			gotoxy(x,z + i);
			printf(" ");
			if(i + 2 >= y - z)
				i = 0;
			else
				i++;
			gotoxy(x,z + i);
			printf(">");
		}
	}while(cha != (char)ENTER_KEY);
	return (i);
}


int mainmenu() {
	int option;	
	int x = 10, y = 5;
	int z = y;	
	clrscr();	
	gotoxy(x,y++);
	printf("New Game\n");
	gotoxy(x,y++);	
	printf("Controls\n");
	gotoxy(x,y++);	
	gotoxy(x,y++);	
	printf(" ");	
	option = selector(x,y, z);	
	return(option);
}

int main() {
	char ch;
	welcomescreen();	
	printrule();	
	do {
		switch(mainmenu()) {
			case 0 :loadgame();
				break;
			case 1: controls();
				break;
			case 2: ;
				break;
		
			}
	
		printf("\nDo you want to play now ? ( Y OR N)\n");
		scanf("%c",&ch);
		ch = tolower(ch);	
	} while(ch =='y');
		
	clrscr();
	printf("Your score has been saved to Snake.txt\n");
	FILE *fp;
	fp = fopen("Snake.txt", "a");
	fprintf(fp,"Player score : %d\n", globscore);	
	printf("\n\nThanks for playing\n");
	fclose(fp);
return 0 ;

}		






