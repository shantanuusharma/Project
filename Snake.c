/* GAME OF SNAKE WIHTOUT USING THE NCURSES LIBRARY */


#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>


#define UP 119	//w
#define DOWN 115 //s
#define LEFT 97 //a
#define RIGHT 100 //d

#define EXIT 27 //ESC
#define PAUSE 112 //p

typedef struct coordinate {
	int x;
	int y;
	int dir;
}coordinate;

coordinate head, food, body[10];

typedef struct pl {
		int score;
		char name[10];
	}pl;	


int life,score, i, j, n;
int length;

void clrscr() {
	system("clear");
}

void gotoxy(int x, int y) {
	printf("%c[%d;%df",0x1B,y,x);
	
}

/* This function is to read which character is entered from the keyboard which will be needed to control the snake and the menu */
	
void getkey() {
	;
}

void init() {
	life = 3;
	score = 0;
	length = 4;
	head.dir = RIGHT;
	head.x = 20;             
	head.y = 20;
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

void exitscreen() {
	clrscr();	
	printf("SORRY GAME OVER\n");          //NEED TO INSERT SOME CRAZY ART
	exit(0);
}


void printrule() {
	clrscr();
	printf("\nINSTRUCTIONS\n");	
	printf("\nThe player controls a long, thin creature, resembling a snake, which roams around on a bordered plane, picking up food (or some other item), trying to avoid hitting its own tail or the border that surround the playing area. Each time the snake eats a piece of food, its tail grows longer, making the game increasingly difficult. The user controls the direction of the snake's head (up, down, left, or right), and the snake's body follows. The player cannot stop the snake from moving while the game is in progress, and cannot make the snake go in reverse."); 
	printf("Press ESCAPE to quit the game\n");
	printf("Press any key to continue..(ESCAPE TO QUIT)\n");
	if(getchar() == 27) //IF ESC IS ENTERED 
	exit(0);
}

void controls() {
	clrscr();
	printf("HERE ARE THE CONTROLS OF THE GAME\n\n");
	printf("MOVEMENTS OF SNAKE ->   UP -> W\n");
	printf("\t\t\tDOWN -> S\n");
	printf("\t\t\tLEFT -> A\n");
	printf("\t\t\tRIGHT -> D\n");			 
	getchar();
	clrscr();
}

void loadgame() {        //This function is essentially to create the feel of a game being loaded 	
	clrscr();
	printf("Loading\n");	
	int i,j;
 	for(i = 0;i < 10;i++) {
    		for(j = 0;j <= 100000000;j++);
    	printf(".");
	}    	
	getchar();

}

void border() {
	int i,j;	
	clrscr();
	for(i=10;i<71;i++) {
		gotoxy(i,10);
		printf("!");     //top boundary
       		gotoxy(i,30);
           	printf("!");	//bottom boundar
    	}
	for(i=10;i<31;i++) {
		gotoxy(10,i);
           	printf("!");	//left boundary
       		gotoxy(70,i);
       		printf("!");	//right boundary
   	}
}

void foodcreate() {
		
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
	printf("*");
}			

void moveright() {
;}

void moveleft() {
 ;}

void moveup() {
;}

void movedown() {
;}


void mover() {       //HAVE TO USE RECURSION END WHEN CHECKGAMEOVER() IS TRUE 
	 
	for( i = 0; i < 30; i++) {  
			body[i].x = 0;
			body[i].y = 0;
			if (i == length)
			break;		
	}	
	
	if(head.dir == RIGHT)             /* WRITE THE DIRECTION MOVEMENTS */
		moveright();
	if(head.dir == LEFT)
		moveleft();
	if(head.dir == UP)
		moveup();
	if(head.dir == DOWN)
		movedown();
	
	// DO WHILE A KEY IS ENTERED 


}  

/*TO CHECK IF GAME IS OVER NUMBER OF LIVES REMAINING SHOULD BE 0 , FOR A LIFE TO DECREASE 2 CONDITIONS 
	1) SNAKE TOUCHES OWN BODY.
	2) HEAD TOUCHES BOUNDARY. */

void checkgameover() {
	int fcond =0, scond = 0, flag = 0 ;	

//CHCECKING FOR CONDITION 1		
	
	for(i = 0;i < length; i++) {
		if(body[0].x == body[i].x || body[0].y == body[i].y)      //body[0] is basically head 
			fcond = 1;
		if(i == length && flag != 0)	
			break;
	}

/*
(10,10)	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (70,10)
    	!					! 
	!					!						
	!					!
	!					!
	!		*> (20,20)				!
	!					!
(10,30)	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (70,30)
                                                          */

/*CHECKING FOR CONDITION 2 : THE DIMENSTIONS OF MY BOUNDARY ARE 10 - 30 LENGTH AND 10 - 70 BREADTH SO CHECKING IF HEAD COLLIDES WITH THEM */ 	
	if(head.x <= 10|| head.x >= 70 || head.y <= 10 || head.y >= 30)
		scond = 1;
	if(fcond > 0 || scond >> 0)
		life--;
	if(life == 0) {
		
		exitscreen();        
	}	
	else {
		clrscr();		
		//GO BACK TO START 
	}

}				

int lifescoredisplay() {
	int score;
//	score = length - 5;          
	printf("Your score is : %d",score);
	printf("No. of lives are : %d",life);	
	return score;
}


int getscore() {
	
	score = lifescoredisplay();
	return score;
}

int sortfile(pl a[],int n) {
	
	int i, j, flag, temp;	
	if(n == 0)
		return 0;
	char t[10];	
	for(i = 0;i < n;i++) {
		flag = 0;
		for(j = 0;j < n - 1 - i; j++) {
			if(a[j].score < a[j + 1].score) {
				flag = 1;				
				temp = a[j].score;
				strcpy(t,a[j].name);
				a[j].score = a[j + 1].score;				
				strcpy(a[j].name,a[j + 1].name);
				a[j + 1].score = temp;				
				strcpy(a[j + 1].name,t);
			}
		}
		if(!flag)
			return 1;			
	}
	return 1;
}

void savetofile() {
	char playername[10],ch, c;
	printf("Enter the Name of the player\n");
	scanf("%[^\n]",playername);
	FILE *fp;
	fp = fopen("snake.txt","a");
	fprintf(fp,"Player name :%s\n",playername);
	fprintf(fp,"Player score :%d\n",getscore());   
	fclose(fp);
	pl player[10];	
	fp = fopen("snake.txt","r");
	if(!fp) {
		printf("Unable to open file/n");
		perror("fopen");
	}
	while(fscanf(fp, "%s%d", player[i].name, &(player[i].score)) != EOF)
		i++;
	n = i;	
	sortfile(player, n);	 
	printf("\nSORTED\n");
	for(i = 0; i < n; i++)
		printf("%s	%d\n", player[i].name, player[i].score);
	
}

int main() {
	welcomescreen();	
	printrule();
	controls();
	loadgame();
	border();
	foodcreate();
	gotoxy(30,70);	
	printf("\n");
}



