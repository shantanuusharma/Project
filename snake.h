/*GAME OF SNAKE. Copyright (C) 2015 SHANTANU SHARMA 111403042

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/


#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<termios.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<time.h>
#include<ctype.h>

#define UP (char)'A' 
#define LEFT (char)'D'
#define RIGHT (char)'C'
#define DOWN (char)'B'

#define ESC 27 //ESC
#define PAUSE 112 //p

#define MAX_SIZE 3000


typedef struct pl {
		int score;
		char name[10];
	}pl;	

int life,score, i, j, n;
int snakelength, globscore;
void clrscr();
void gotoxy(int x, int y);
int getch();
int kbhit();
char returnkey();
int checkkey(int dir);
void welcomescreen();
int getgamespeed();
void pausemenu();
void printrule();
void controls();
void loadgame();
void border(int consolewidth, int consoleheight);
void foodcreate(int foodXY[], int width, int height, int snakeXY[][MAX_SIZE], int snakelength);
void movesnake(int snakeXY[][MAX_SIZE], int snakelength, int dir);
int checkeatfood(int snakeXY[][MAX_SIZE], int foodXY[]);
int touchesbody(int x , int y, int snakeXY[][MAX_SIZE], int snakelength, int check);
int collides(int snakeXY[][MAX_SIZE],int consolewidth, int consoleheight, int snakelength);
int speedscoredisplay(int score, int speed);
void initsnake(int snakeXY[][MAX_SIZE], int snakelength);
void loadsnake(int snakeXY[][MAX_SIZE], int snakelength);
void startgame(int snakeXY[][MAX_SIZE], int foodXY[], int consolewidth, int consoleheight, int snakelength, int dir, int speed, int score);
int selector(int x, int y, int z);
void scoreboard(int score, int speed);
void escape();
int mainmenu();
void gameoverscreen();
void savetofile();
