#include<stdlib.h>
#include<process.h>
#include<stdlib.h>

typedef struct coordinate {
	int x;
	int y;
	int dir;
}coordinate;

coordinate head,food,body[10] ;
int life,length,score;

void printrule() {

	printf("Welcome to Snake\nPress any key to continue\n");
	getchar();
	printf("*RULES*\n\n\nGOAL -> A food item will be displayed on the monitor which you have to capture using the snake\n\nTo control the 		snake use the arrow keys, everytime you capture a food item the length and score of the snake will increase by one unit \nIf the head 		of your snake touches the body or the head of the snake touches the boundary the game will be over\n\nYou are provided with 3 lives\nBEST OF LUCK\n");
	printf("Press ESCAPE to quit the game\n");
	printf("Press any key to continue..(ESCAPE TO QUIT)\n");
	if(getchar() == 27) {
	exit(0);
}

void init() {
	life = 3;
	length = 5;
	head.x = 10;
	head.y = 10;
	score = 0;
	body[0].x = 0;
	body[0].y =0;

}	

void loadgame() {        //This function is essentially to create the feel of a game being loaded 	
	system("clear");
	printf("Loading, Please wait\n");
	int i,j;	
	while(i < 10){
		printf(".");
		for(j = 0;j < 100000000; j++);
		i++;
	}		
	printf(" THE GAME IS READY, ARE YOU ? press enter to continue\n");	
	getchar();
}

void border() {
	int i,j;	
	system("clear");
	for(i=0;i<=20;i++){
      		gotoxy(i,0);
      		gotoxy(i,20);
 	}	    
	for(i=0;i<=20;i++){
		gotoxy(0,i);
     		gotoxy(20,i);
    	}
	gotoxy(0,0);
	gotoxy(0,20);
	gotoxy(20,0);
	gotoxy(20,20);
		
}
void food() {
		
	if(food.x == food.y == 0) { //creating food for the first time
		food.x = rand() % 20;
		food.y = rand() % 20;
	if(food.x == 0)
		food.x++;
	if(food.y == 0)
		food.y++;		
	}

	if(head.x == food.x && head.y == food.y) {      //food is captured and new food is to be generated
		length++;
		food.x = rand() % 20;
		food.y = rand() % 20;
		if(food.x == 0)
		food.x++;
		if(food.y == 0)
		food.y++;
		
	}
	gotoxy(food.x,food.y);
	printf("*");

}			
	
//void displaysnake() { this function is a trial function and will be changed I have made this to check the display of the snake//
//}


int lifescoredisplay() {
	int score;
	score = length - 5;
	printf("Your score is : %d",score);
	printf("No. of lives are : %d",life);	
	return score;
}

int getscore() {
	system("clear");	
	score = lifescoredisplay();
	return score;
}


void savetofile() {
	char playername[10],ch;
	printf("Enter the Name of the player\n");
	scanf("%[^\n]",playername);
	FILE *fp;
	fp = fopen("game.txt","a");
	fprintf(fp,"Player name :%s\n",playername);
	fprintf(fp,"Player score :%d\n",getsore());   
	fclose(fp);
	printf("Do you wish to see your highscores ( Y OR N)?\n");   //I will attempt to sort this file to show top 3 scores as of now it 										shows all the scores
	scanf("%c",&ch);
	if(ch == 'Y' || ch == 'y')
		fp = fopen("game.txt","r");
		while(ch != EOF)
			putchar(c = getchar(fp));
		fclose(fp);
}

int main() {
	printrule();
	init();
	loadgame();
	border();
	food();
	
}	
