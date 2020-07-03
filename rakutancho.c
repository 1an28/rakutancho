#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

/*
X: 1~120
Y: 1~30

  ヾヽ
_（ ・l＞
ミ＿ノ
*/

void showBird(int x, int y, int i){
	if (i == 0){
		printf("\x1b[30m");
	}
	else if (i == 1){
		printf("\x1b[31m");
	}
	else if (i == 2){
		printf("\x1b[32m");
	}
	else if (i == 3){
		printf("\x1b[33m");
	}
	else if (i == 4){
		printf("\x1b[34m");
	}
	else if (i == 5){
		printf("\x1b[35m");
	}
	else if (i == 6){
		printf("\x1b[36m");
	}
	else if (i == 7){
		printf("\x1b[37m");
	}
	gotoxy(x, y);
	printf("  ヾヽ");
	gotoxy(x, y + 1);
	printf("_（ ・l＞");
	gotoxy(x, y + 2);
	printf("ミ＿ノ");
	gotoxy(120, 30);
}

void removeBird(int x, int y){
	gotoxy(x, y);
	printf("      ");
	gotoxy(x, y + 1);
	printf("         ");
	gotoxy(x, y + 2);
	printf("      ");
	gotoxy(120, 30);
}

void genBlock(int x, int hole){
	int i;
	
	for (i = 1; i <= 30; i++){
		if (i > hole + 4 ||  i < hole - 4){
			gotoxy(x, i);
			printf("□");
		}
	}
	gotoxy(120, 30);
}

void removeBlock(int x, int hole){
	int i;
	
	for (i = 1; i <= 30; i++){
		if (i > hole + 4 || i < hole - 4){
			gotoxy(x, i);
			printf("  ");
		}
	}
	gotoxy(120, 30);
}

void gameOver(void)
{
	char c;
	
	printf("\x1b[37m");
	gotoxy(55, 13);
	printf("GAME  OVER\n");
	gotoxy(46, 17);
	printf("エンターキーでタイトルに戻る\n");
	gotoxy(120, 30);
	
	while (c != 0x0d){
			c = getch();
	}
}

int main(void)
{
	int gamePlay;
	int birdX, birdY;
	int birdJumped;
	int birdColor;
	int blockAX, blockBX, blockCX, blockDX;
	int blockAHole, blockBHole, blockCHole, blockDHole;
	int blockAShowed, blockBShowed, blockCShowed;
	int score;
	int rainbow;
	int interval;
	char c;
	char pressedKey;
	
    srand((unsigned int) time(0));
	
	while (1){
		system("cls");
		
		/* ゲーム開始画面 */
		gotoxy(29, 10);
		printf("　　　■　　　■　　　　　■　　■　■　　　　　　　　■　　　　　");
		gotoxy(29, 11);
		printf("■■■■■■■■■■　　　　■　■　■　　　　　■■■■■■■　　");
		gotoxy(29, 12);
		printf("　　　■　　　■　　　　　■■■■■■■　　　　■■■■■■■　　");
		gotoxy(29, 13);
		printf("　■■　　■■■■　　　　■　　■　　■　　　　■■■■■■■　　");
		gotoxy(29, 14);
		printf("　　　■■■■■　　　　　■■■■■■■　　　　■　　　　　　　　");
		gotoxy(29, 15);
		printf("　　　　　■　　■■　　　■■■■■■■　　　　■■■■■■■■■");
		gotoxy(29, 16);
		printf("　　■　■■■■■　　　　　　　■　　　　　　　■■■■■■■■　");
		gotoxy(29, 17);
		printf("　■　　■　　　■　　　■■■■■■■■■　　　　　　■　■　■　");
		gotoxy(29, 18);
		printf("　■　　■■■■■　　　　　　　■　　　　　　■　■　■　　　■　");
		gotoxy(29, 19);
		printf("　　　　■　　　■　　　　　　　■　　　　　　　　　　　　■■■　");
		gotoxy(46, 22);
		printf("スペースキーを押してスタート");
		//gotoxy(120, 30);
		
		while (c != ' '){
			c = getch();
		}
		
		c = '0';
		
		system("cls");
		
		gamePlay = 1;
		birdX = 20;
		birdY = 15;
		birdJumped = 0;
		birdColor = 7;
		blockAX = blockBX = blockCX = blockDX = 119;
		blockAHole = (int)((rand() / ((double) RAND_MAX + 1.0)) * 21) + 5;
		blockBHole = (int)((rand() / ((double) RAND_MAX + 1.0)) * 21) + 5;
		blockCHole = (int)((rand() / ((double) RAND_MAX + 1.0)) * 21) + 5;
		blockDHole = (int)((rand() / ((double) RAND_MAX + 1.0)) * 21) + 5;
		blockAShowed = blockBShowed = blockCShowed = 0;
		score = 0;
		rainbow = 0;
		interval = 0;
		
		showBird(birdX, birdY, birdColor);
		
		while(gamePlay){
			if (kbhit()) {
				pressedKey = getch();
				if (pressedKey == ' '){
					birdJumped = 4;
					printf("\x1b[37m");
					gotoxy(birdX - 1, birdY + 3);
					printf("彡彡");
					gotoxy(120, 30);
				}
				else if (pressedKey == 'f'){
					if (interval > -40)
					interval -= 10;
				}
				else if (pressedKey == 's'){
					interval += 10;
				}
				else if (pressedKey >= '0' && pressedKey <= '7'){
					birdColor = pressedKey - 48;
					rainbow = 0;
				}
				else if (pressedKey == '8'){
					birdColor = 1;
					rainbow = 1;
				}
			}
			else {
				if (birdJumped > 0){
					if (birdY > 1){
						Sleep(75 + interval);
						if (birdJumped == 4){
							gotoxy(birdX - 1, birdY + 3);
							printf("    ");
							gotoxy(120, 30);
						}
						removeBird(birdX, birdY);
						birdY--;
						showBird(birdX, birdY, birdColor);
						birdJumped--;
					}
					else {
						Sleep(75 + interval);
						if (birdJumped == 4){
							gotoxy(birdX - 1, birdY + 3);
							printf("    ");
							gotoxy(120, 30);
						}
						removeBird(birdX, birdY);
						showBird(birdX, birdY, birdColor);
						birdJumped--;
					}
				}
				else {
					if (birdY < 28){
						Sleep(50 + interval);
						removeBird(birdX, birdY);
						birdY++;
						showBird(birdX, birdY, birdColor);
					}
					else {
						gameOver();
						gamePlay = 0;
					}
				}
				if (rainbow == 1){
					if (birdColor < 6){
						birdColor++;
					}
					else {
						birdColor = 1;
					}
				}
			}
			printf("\x1b[37m");
			
			removeBlock(blockAX, blockAHole);
			if (blockAX == 1){
				blockAX = 119;
				blockAHole = (int)((rand() / ((double) RAND_MAX + 1.0)) * 21) + 5;
			}
			if (blockAShowed == 0 && blockAX < 89){
				blockAShowed++;
			}
			genBlock(blockAX, blockAHole);
			blockAX--;
			
			if (blockAShowed == 1){
				removeBlock(blockBX, blockBHole);
				if (blockBX == 1){
					blockBX = 119;
					blockBHole = (int)((rand() / ((double) RAND_MAX + 1.0)) * 21) + 5;
				}
				if (blockBShowed == 0 && blockBX < 89){
					blockBShowed++;
				}
				genBlock(blockBX, blockBHole);
				blockBX--;
			}
			
			if (blockBShowed == 1){
				removeBlock(blockCX, blockCHole);
				if (blockCX == 1){
					blockCX = 119;
					blockCHole = (int)((rand() / ((double) RAND_MAX + 1.0)) * 21) + 5;
				}
				if (blockCShowed == 0 && blockCX < 89){
					blockCShowed++;
				}
				genBlock(blockCX, blockCHole);
				blockCX--;
			}
			
			if (blockCShowed == 1){
				removeBlock(blockDX, blockDHole);
				if (blockDX == 1){
					blockDX = 119;
					blockDHole = (int)((rand() / ((double) RAND_MAX + 1.0)) * 21) + 5;
				}
				genBlock(blockDX, blockDHole);
				blockDX--;
			}
			
			if ((birdX == blockAX)
				 || (birdX == blockBX)
				 || (birdX == blockCX)
				 || (birdX == blockDX)
			){
				if (
					((birdY > blockAHole - 5 && birdY + 2 < blockAHole + 5)
					 || (birdY > blockBHole - 5 && birdY + 2 < blockBHole + 5)
					 || (birdY > blockCHole - 5 && birdY + 2 < blockCHole + 5)
					 || (birdY > blockDHole - 5 && birdY + 2 < blockDHole + 5))
				){
					score++;
				}
				else {
					gameOver();
					gamePlay = 0;
				}
			}
			gotoxy(1, 1);
			printf("SCORE: %d", score);
		}
	}
}