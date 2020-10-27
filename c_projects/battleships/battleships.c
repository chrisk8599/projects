#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void printBoard(char top[9][4],char aBoard[9][4],char bBoard[9][4] ,char cBoard[9][4],char dBoard[9][4],char eBoard[9][4],char fBoard[9][4],char gBoard[9][4],char hBoard[9][4]);
int setShip(char x,int y,char orient,char* type, int board[8][8], int posBoard[8][8]);

int main(){
	int counter  = 1;
	int flag = 0;

	char carrierX1,carrierOrient1,battleX1,battleOrient1,destroyerX1,destroyerOrient1,submarineX1,submarineOrient1,patrolX1,patrolOrient1;
	int carrierY1,battleY1,destroyerY1,submarineY1,patrolY1;


  char carrierX2,carrierOrient2,battleX2,battleOrient2,destroyerX2,destroyerOrient2,submarineX2,submarineOrient2,patrolX2,patrolOrient2;
  int carrierY2,battleY2,destroyerY2,submarineY2,patrolY2;

	int carrierLife1 = 5;
	int carrierLife2 = 5;
	int battleLife1 = 4;
	int battleLife2 = 4;
	int destroyerLife1 = 3;
	int destroyerLife2 = 3;
	int submarineLife1 = 2;
	int submarineLife2 = 2;
	int patrolLife1 = 2;
	int patrolLife2 = 2;

	int cSunk1 = 0;
	int cSunk2 = 0;
	int bSunk1 = 0;
	int bSunk2 = 0;
	int dSunk1 = 0;
	int dSunk2 = 0;
	int sSunk1 = 0;
	int sSunk2 = 0;
	int pSunk1 = 0;
	int pSunk2 = 0;


	char top1[9][4];
	char Aboard1[9][4];
	char Bboard1[9][4];
	char Cboard1[9][4];
	char Dboard1[9][4];
	char Eboard1[9][4];
	char Fboard1[9][4];
	char Gboard1[9][4];
	char Hboard1[9][4];

	strcpy(top1[0],"  ");
	strcpy(top1[1],"1 ");
	strcpy(top1[2],"2 ");
	strcpy(top1[3],"3 ");
	strcpy(top1[4],"4 ");
	strcpy(top1[5],"5 ");
	strcpy(top1[6],"6 ");
	strcpy(top1[7],"7 ");
	strcpy(top1[8],"8");

	strcpy(Aboard1[0],"A|");
	for(int i=1;i<9;i++){
		strcpy(Aboard1[i]," |");
	}
	strcpy(Bboard1[0],"B|");
	for(int i=1;i<9;i++){
		strcpy(Bboard1[i]," |");
	}
strcpy(Cboard1[0],"C|");
	for(int i=1;i<9;i++){
		strcpy(Cboard1[i]," |");
	}
	strcpy(Dboard1[0],"D|");
	for(int i=1;i<9;i++){
		strcpy(Dboard1[i]," |");
	}
	strcpy(Eboard1[0],"E|");
	for(int i=1;i<9;i++){
		strcpy(Eboard1[i]," |");
	}
	strcpy(Fboard1[0],"F|");
	for(int i=1;i<9;i++){
		strcpy(Fboard1[i]," |");
	}
	strcpy(Gboard1[0],"G|");
	for(int i=1;i<9;i++){
		strcpy(Gboard1[i]," |");
	}
	strcpy(Hboard1[0],"H|");
	for(int i=1;i<9;i++){
		strcpy(Hboard1[i]," |");
	}
	char top2[9][4];
	char Aboard2[9][4];
	char Bboard2[9][4];
	char Cboard2[9][4];
	char Dboard2[9][4];
	char Eboard2[9][4];
	char Fboard2[9][4];
	char Gboard2[9][4];
	char Hboard2[9][4];

	strcpy(top2[0],"  ");
	strcpy(top2[1],"1 ");
	strcpy(top2[2],"2 ");
	strcpy(top2[3],"3 ");
	strcpy(top2[4],"4 ");
	strcpy(top2[5],"5 ");
	strcpy(top2[6],"6 ");
	strcpy(top2[7],"7 ");
	strcpy(top2[8],"8");

	strcpy(Aboard2[0],"A|");
	for(int i=1;i<9;i++){
		strcpy(Aboard2[i]," |");
	}
	strcpy(Bboard2[0],"B|");
	for(int i=1;i<9;i++){
		strcpy(Bboard2[i]," |");
	}
	strcpy(Cboard2[0],"C|");
	for(int i=1;i<9;i++){
		strcpy(Cboard2[i]," |");
	}
	strcpy(Dboard2[0],"D|");
	for(int i=1;i<9;i++){
		strcpy(Dboard2[i]," |");
	}
	strcpy(Eboard2[0],"E|");
	for(int i=1;i<9;i++){
		strcpy(Eboard2[i]," |");
	}
	strcpy(Fboard2[0],"F|");
	for(int i=1;i<9;i++){
		strcpy(Fboard2[i]," |");
	}
	strcpy(Gboard2[0],"G|");
	for(int i=1;i<9;i++){
		strcpy(Gboard2[i]," |");
	}
	strcpy(Hboard2[0],"H|");
	for(int i=1;i<9;i++){
		strcpy(Hboard2[i]," |");
	}


	int board1[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
	int board2[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
	int posBoard1[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
	int posBoard2[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};

	printf("Player 1, please set up your ships (y, x, orientation)\n");

while(1){
	printf("Carrier: ");
	scanf(" %c %d %c",&carrierX1,&carrierY1,&carrierOrient1);

	if(carrierX1=='A' || carrierX1 == 'B'|| carrierX1 == 'C'||
	carrierX1 == 'D'|| carrierX1 == 'E'|| carrierX1 == 'F'||
	carrierX1 == 'G'|| carrierX1 == 'H'){
		if(carrierY1 == 1 || carrierY1 == 2
	   || carrierY1 == 3|| carrierY1 == 4|| carrierY1 ==5|| carrierY1 == 6||
	 	carrierY1 == 7|| carrierY1 == 8){
			if(carrierOrient1 == 'H' || carrierOrient1 =='V'){

				if(setShip(carrierX1,carrierY1,carrierOrient1,"carrier",board1,posBoard1)){

					break;
				}


			}
	}
}
printf("Invalid ship configuration\n");
}

while(1){
	printf("Battleship: ");
	scanf(" %c %d %c",&battleX1,&battleY1,&battleOrient1);

	if(battleX1=='A' || battleX1 == 'B'|| battleX1 == 'C'||
	battleX1 == 'D'|| battleX1 == 'E'|| battleX1 == 'F'||
	battleX1 == 'G'|| battleX1 == 'H'){
		if(battleY1 == 1 || battleY1 == 2
	   || battleY1 == 3|| battleY1 == 4|| battleY1 ==5|| battleY1 == 6||
	 	battleY1 == 7|| battleY1 == 8){
			if(battleOrient1 == 'H' || battleOrient1 =='V'){
				if(setShip(battleX1,battleY1,battleOrient1,"battleship",board1,posBoard1)){

					break;
				}
			}
	}
}
printf("Invalid ship configuration\n");
}

while(1){
	printf("Destroyer: ");
	scanf(" %c %d %c",&destroyerX1,&destroyerY1,&destroyerOrient1);

	if(destroyerX1=='A' || destroyerX1 == 'B'|| destroyerX1 == 'C'||
	destroyerX1 == 'D'|| destroyerX1 == 'E'|| destroyerX1 == 'F'||
	destroyerX1 == 'G'|| destroyerX1 == 'H'){
		if(destroyerY1 == 1 || destroyerY1 == 2
	   || destroyerY1 == 3|| destroyerY1 == 4|| destroyerY1 ==5|| destroyerY1 == 6||
	 	destroyerY1 == 7|| destroyerY1 == 8){
			if(destroyerOrient1 == 'H' || destroyerOrient1 =='V'){
				if(setShip(destroyerX1,destroyerY1,destroyerOrient1,"destroyer",board1,posBoard1)){

					break;
				}
			}
	}
}
printf("Invalid ship configuration\n");
}

while(1){
	printf("Submarine: ");
	scanf(" %c %d %c",&submarineX1,&submarineY1,&submarineOrient1);

	if(submarineX1=='A' || submarineX1 == 'B'|| submarineX1 == 'C'||
	submarineX1 == 'D'|| submarineX1 == 'E'|| submarineX1 == 'F'||
	submarineX1 == 'G'|| submarineX1 == 'H'){
		if(submarineY1 == 1 || submarineY1 == 2
	   || submarineY1 == 3|| submarineY1 == 4|| submarineY1 ==5|| submarineY1 == 6||
	 	submarineY1 == 7|| submarineY1 == 8){
			if(submarineOrient1 == 'H' || submarineOrient1 =='V'){
				if(setShip(submarineX1,submarineY1,submarineOrient1,"submarine",board1,posBoard1)){

					break;
				}
			}
	}
}
printf("Invalid ship configuration\n");
}

while(1){
	printf("Patrol Boat: ");
	scanf(" %c %d %c",&patrolX1,&patrolY1,&patrolOrient1);

	if(patrolX1=='A' || patrolX1 == 'B'|| patrolX1 == 'C'||
	patrolX1 == 'D'|| patrolX1 == 'E'|| patrolX1 == 'F'||
	patrolX1 == 'G'|| patrolX1 == 'H'){
		if(patrolY1 == 1 || patrolY1 == 2
	   || patrolY1 == 3|| patrolY1 == 4|| patrolY1 ==5|| patrolY1 == 6||
	 	patrolY1 == 7|| patrolY1 == 8){
			if(patrolOrient1 == 'H' || patrolOrient1 =='V'){
				if(setShip(patrolX1,patrolY1,patrolOrient1,"patrol",board1,posBoard1)){

					break;
				}
			}
	}
}
printf("Invalid ship configuration\n");
}

printf("\n\n");

printf("Player 2, please set up your ships (y, x, orientation)\n");

while(1){
	printf("Carrier: ");
	scanf(" %c %d %c",&carrierX2,&carrierY2,&carrierOrient2);

	if(carrierX2=='A' || carrierX2 == 'B'|| carrierX2 == 'C'||
	carrierX2 == 'D'|| carrierX2 == 'E'|| carrierX2 == 'F'||
	carrierX2 == 'G'|| carrierX2 == 'H'){
		if(carrierY2 == 1 || carrierY2 == 2
	   || carrierY2 == 3|| carrierY2 == 4|| carrierY2 ==5|| carrierY2 == 6||
	 	carrierY2 == 7|| carrierY2 == 8){
			if(carrierOrient2 == 'H' || carrierOrient2 =='V'){
				if(setShip(carrierX2,carrierY2,carrierOrient2,"carrier",board2,posBoard2)){

					break;
				}
			}
	}
}
printf("Invalid ship configuration\n");
}

while(1){
	printf("Battleship: ");
	scanf(" %c %d %c",&battleX2,&battleY2,&battleOrient2);

	if(battleX2=='A' || battleX2 == 'B'|| battleX2 == 'C'||
	battleX2 == 'D'|| battleX2 == 'E'|| battleX2 == 'F'||
	battleX2 == 'G'|| battleX2 == 'H'){
		if(battleY2 == 1 || battleY2 == 2
	   || battleY2 == 3|| battleY2 == 4|| battleY2 ==5|| battleY2 == 6||
	 	battleY2 == 7|| battleY2 == 8){
			if(battleOrient2 == 'H' || battleOrient2 =='V'){
				if(setShip(battleX2,battleY2,battleOrient2,"battleship",board2,posBoard2)){

					break;
				}
			}
	}
}
printf("Invalid ship configuration\n");
}

while(1){
	printf("Destroyer: ");
	scanf(" %c %d %c",&destroyerX2,&destroyerY2,&destroyerOrient2);

	if(destroyerX2=='A' || destroyerX2 == 'B'|| destroyerX2 == 'C'||
	destroyerX2 == 'D'|| destroyerX2 == 'E'|| destroyerX2 == 'F'||
	destroyerX2 == 'G'|| destroyerX2 == 'H'){
		if(destroyerY2 == 1 || destroyerY2 == 2
	   || destroyerY2 == 3|| destroyerY2 == 4|| destroyerY2 ==5|| destroyerY2 == 6||
	 	destroyerY2 == 7|| destroyerY2 == 8){
			if(destroyerOrient2 == 'H' || destroyerOrient2 =='V'){
				if(setShip(destroyerX2,destroyerY2,destroyerOrient2,"destroyer",board2,posBoard2)){

					break;
				}
			}
	}
}
printf("Invalid ship configuration\n");
}

while(1){
	printf("Submarine: ");
	scanf(" %c %d %c",&submarineX2,&submarineY2,&submarineOrient2);

	if(submarineX2=='A' || submarineX2 == 'B'|| submarineX2 == 'C'||
	submarineX2 == 'D'|| submarineX2 == 'E'|| submarineX2 == 'F'||
	submarineX2 == 'G'|| submarineX2 == 'H'){
		if(submarineY2 == 1 || submarineY2 == 2
	   || submarineY2 == 3|| submarineY2 == 4|| submarineY2 ==5|| submarineY2 == 6||
	 	submarineY2 == 7|| submarineY2 == 8){
			if(submarineOrient2 == 'H' || submarineOrient2 =='V'){
				if(setShip(submarineX2,submarineY2,submarineOrient2,"submarine",board2,posBoard2)){

					break;
				}
			}
	}
}
printf("Invalid ship configuration\n");
}

while(1){
	printf("Patrol Boat: ");
	scanf(" %c %d %c",&patrolX2,&patrolY2,&patrolOrient2);

	if(patrolX2=='A' || patrolX2 == 'B'|| patrolX2 == 'C'||
	patrolX2 == 'D'|| patrolX2 == 'E'|| patrolX2 == 'F'||
	patrolX2 == 'G'|| patrolX2 == 'H'){
		if(patrolY2 == 1 || patrolY2 == 2
	   || patrolY2 == 3|| patrolY2 == 4|| patrolY2 ==5|| patrolY2 == 6||
	 	patrolY2 == 7|| patrolY2 == 8){
			if(patrolOrient2 == 'H' || patrolOrient2 =='V'){
				if(setShip(patrolX2,patrolY2,patrolOrient2,"patrol",board2,posBoard2)){

					break;
				}
			}
	}
}
printf("Invalid ship configuration\n");
}



printf("\n");
printf("All boats set up, Player 1 can now strike.\n\n");

while(1){



	char buf[15];
	fgets(buf,15,stdin);
	char * token = strtok(buf," ");

	if(!strncmp(token,"shots",5)){
			flag = 1;
			if(counter%2 != 1){
				printBoard(top1,Aboard1,Bboard1,Cboard1,Dboard1,Eboard1,Fboard1,Gboard1,Hboard1);

			}
			else {
					printBoard(top2,Aboard2,Bboard2,Cboard2,Dboard2,Eboard2,Fboard2,Gboard2,Hboard2);

			}
	}

	else if(!strncmp(token,"fire",5)){
			flag = 1;
			token = strtok(NULL," ");

			if(counter%2 != 1){

				if(!strncmp(token,"A",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Aboard1[i],"0|",2) || !strncmp(Aboard1[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board1[0][i-1] == 1){

										printf("\n");
								if(posBoard1[0][i-1] == 1){
									 carrierLife1 -= 1;
								}
								else if(posBoard1[0][i-1] == 2){
									battleLife1 -= 1;
								}
								else if(posBoard1[0][i-1] == 3){
									destroyerLife1 -= 1;
								}
								else if(posBoard1[0][i-1] == 4){
									submarineLife1 -= 1;
								}
								else if(posBoard1[0][i-1] == 5){
									patrolLife1 -= 1;
								}
								strcpy(Aboard1[i],"X|");

								if(carrierLife1 == 0 && cSunk1 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk1 = 1;
								}
								else if(battleLife1 == 0 && bSunk1 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk1 = 1;
								}
								else if(destroyerLife1 == 0 && dSunk1 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk1 =1;
								}
								else if(submarineLife1 == 0 && sSunk1 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk1 = 1;
								}
								else if(patrolLife1 == 0 && pSunk1 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk1 = 1;
								}

								else {
									printf("We have hit the target!\n\n");

								}

								if(cSunk1 == 1 && bSunk1 ==1 && dSunk1 ==1 && sSunk1 ==1 && pSunk1 ==1){
									printf("Player 2 wins!\n");
									break;
								}
							}
							else{
								printf("\nYou have missed!\n\n");

								strcpy(Aboard1[i],"0|");
							}
							counter++;
							printf("Player 1's turn\n\n");
						}
					}
						else {
								printf("Invalid coordinates\n");
						}

					}



				else if(!strncmp(token,"B",1)){

					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Bboard1[i],"0|",2) || !strncmp(Bboard1[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board1[1][i-1] == 1){

									printf("\n");
								if(posBoard1[1][i-1] == 1){
									 carrierLife1 -= 1;
								}
								else if(posBoard1[1][i-1] == 2){
									battleLife1 -= 1;
								}
								else if(posBoard1[1][i-1] == 3){
									destroyerLife1 -= 1;
								}
								else if(posBoard1[1][i-1] == 4){
									submarineLife1 -= 1;
								}
								else if(posBoard1[1][i-1] == 5){
									patrolLife1 -= 1;
								}
								strcpy(Bboard1[i],"X|");
								if(carrierLife1 == 0 && cSunk1 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk1 = 1;
								}
								else if(battleLife1 == 0 && bSunk1 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk1 = 1;
								}
								else if(destroyerLife1 == 0 && dSunk1 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk1 =1;
								}
								else if(submarineLife1 == 0 && sSunk1 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk1 = 1;
								}
								else if(patrolLife1 == 0 && pSunk1 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk1 = 1;
								}

								else{
									printf("We have hit the target!\n\n");


								}
								if(cSunk1 == 1 && bSunk1 ==1 && dSunk1 ==1 && sSunk1 ==1 && pSunk1 ==1){
									printf("Player 2 wins!\n");
									break;
								}

							}
							else
								{
									printf("\nYou have missed!\n\n");
									strcpy(Bboard1[i],"0|");

								}
								counter++;
								printf("Player 1's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"C",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Cboard1[i],"0|",2) || !strncmp(Cboard1[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board1[2][i-1] == 1){


									printf("\n");
								if(posBoard1[2][i-1] == 1){
									 carrierLife1 -= 1;
								}
								else if(posBoard1[2][i-1] == 2){
									battleLife1 -= 1;
								}
								else if(posBoard1[2][i-1] == 3){
									destroyerLife1 -= 1;
								}
								else if(posBoard1[2][i-1] == 4){
									submarineLife1 -= 1;
								}
								else if(posBoard1[2][i-1] == 5){
									patrolLife1 -= 1;
								}
								strcpy(Cboard1[i],"X|");

								if(carrierLife1 == 0 && cSunk1 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk1 = 1;
								}
								else if(battleLife1 == 0 && bSunk1 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk1 = 1;
								}
								else if(destroyerLife1 == 0 && dSunk1 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk1 =1;
								}
								else if(submarineLife1 == 0 && sSunk1 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk1 = 1;
								}
								else if(patrolLife1 == 0 && pSunk1 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk1 = 1;
								}

								else {
									printf("We have hit the target!\n\n");

								}
								if(cSunk1 == 1 && bSunk1 ==1 && dSunk1 ==1 && sSunk1 ==1 && pSunk1 ==1){
									printf("Player 2 wins!\n");
									break;
								}

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Cboard1[i],"0|");
							}
						counter++;
						printf("Player 1's turn\n\n");
					}}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"D",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Dboard1[i],"0|",2) || !strncmp(Dboard1[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board1[3][i-1] == 1){

									printf("\n");
								if(posBoard1[3][i-1] == 1){
									 carrierLife1 -= 1;
								}
								else if(posBoard1[3][i-1] == 2){
									battleLife1 -= 1;
								}
								else if(posBoard1[3][i-1] == 3){
									destroyerLife1 -= 1;
								}
								else if(posBoard1[3][i-1] == 4){
									submarineLife1 -= 1;
								}
								else if(posBoard1[3][i-1] == 5){
									patrolLife1 -= 1;
								}
								strcpy(Dboard1[i],"X|");

								if(carrierLife1 == 0 && cSunk1 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk1 = 1;
								}
								else if(battleLife1 == 0 && bSunk1 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk1 = 1;
								}
								else if(destroyerLife1 == 0 && dSunk1 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk1 =1;
								}
								else if(submarineLife1 == 0 && sSunk1 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk1 = 1;
								}
								else if(patrolLife1 == 0 && pSunk1 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk1 = 1;
								}

								else {
									printf("We have hit the target!\n\n");
								}
								if(cSunk1 == 1 && bSunk1 ==1 && dSunk1 ==1 && sSunk1 ==1 && pSunk1 ==1){
									printf("Player 2 wins!\n");
									break;
								}

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Dboard1[i],"0|");
							}
							counter++;
							printf("Player 1's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"E",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Eboard1[i],"0|",2) || !strncmp(Eboard1[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board1[4][i-1] == 1){

									printf("\n");
								if(posBoard1[4][i-1] == 1){
									 carrierLife1 -= 1;
								}
								else if(posBoard1[4][i-1] == 2){
									battleLife1 -= 1;
								}
								else if(posBoard1[4][i-1] == 3){
									destroyerLife1 -= 1;
								}
								else if(posBoard1[4][i-1] == 4){
									submarineLife1 -= 1;
								}
								else if(posBoard1[4][i-1] == 5){
									patrolLife1 -= 1;
								}
								strcpy(Eboard1[i],"X|");

								if(carrierLife1 == 0 && cSunk1 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk1 = 1;
								}
								else if(battleLife1 == 0 && bSunk1 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk1 = 1;
								}
								else if(destroyerLife1 == 0 && dSunk1 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk1 =1;
								}
								else if(submarineLife1 == 0 && sSunk1 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk1 = 1;
								}
								else if(patrolLife1 == 0 && pSunk1 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk1 = 1;
								}

								else {
									printf("We have hit the target!\n\n");
								}
								if(cSunk1 == 1 && bSunk1 ==1 && dSunk1 ==1 && sSunk1 ==1 && pSunk1 ==1){
									printf("Player 2 wins!\n");
									break;
								}

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Eboard1[i],"0|");
							}
							counter++;
							printf("Player 1's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"F",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Fboard1[i],"0|",2) || !strncmp(Fboard1[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board1[5][i-1] == 1){


									printf("\n");
								if(posBoard1[5][i-1]== 1){
									 carrierLife1 -= 1;
								}
								else if(posBoard1[5][i-1] == 2){
									battleLife1 -= 1;
								}
								else if(posBoard1[5][i-1] == 3){
									destroyerLife1 -= 1;
								}
								else if(posBoard1[5][i-1] == 4){
									submarineLife1 -= 1;
								}
								else if(posBoard1[5][i-1] == 5){
									patrolLife1 -= 1;
								}
								strcpy(Fboard1[i],"X|");
								if(carrierLife1 == 0 && cSunk1 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk1 = 1;
								}
								else if(battleLife1 == 0 && bSunk1 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk1 = 1;
								}
								else if(destroyerLife1 == 0 && dSunk1 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk1 =1;
								}
								else if(submarineLife1 == 0 && sSunk1 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk1 = 1;
								}
								else if(patrolLife1 == 0 && pSunk1 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk1 = 1;
								}

								else {
									printf("We have hit the target!\n\n");

								}
								if(cSunk1 == 1 && bSunk1 ==1 && dSunk1 ==1 && sSunk1 ==1 && pSunk1 ==1){
									printf("Player 2 wins!\n");
									break;
								}

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Fboard1[i],"0|");
							}
							counter++;
							printf("Player 1's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"G",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Gboard1[i],"0|",2) || !strncmp(Gboard1[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board1[6][i-1] == 1){


									printf("\n");
								if(posBoard1[6][i-1] == 1){
									 carrierLife1 -= 1;
								}
								else if(posBoard1[6][i-1] == 2){
									battleLife1 -= 1;
								}
								else if(posBoard1[6][i-1] == 3){
									destroyerLife1 -= 1;
								}
								else if(posBoard1[6][i-1] == 4){
									submarineLife1 -= 1;
								}
								else if(posBoard1[6][i-1] == 5){
									patrolLife1 -= 1;
								}

								strcpy(Gboard1[i],"X|");
								if(carrierLife1 == 0 && cSunk1 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk1 = 1;
								}
								else if(battleLife1 == 0 && bSunk1 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk1 = 1;
								}
								else if(destroyerLife1 == 0 && dSunk1 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk1 =1;
								}
								else if(submarineLife1 == 0 && sSunk1 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk1 = 1;
								}
								else if(patrolLife1 == 0 && pSunk1 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk1 = 1;
								}

								else{
									printf("We have hit the target!\n\n");

								}
								if(cSunk1 == 1 && bSunk1 ==1 && dSunk1 ==1 && sSunk1 ==1 && pSunk1 ==1){
									printf("Player 2 wins!\n");
									break;
								}

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Gboard1[i],"0|");
							}
							counter++;
							printf("Player 1's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"H",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Hboard1[i],"0|",2) || !strncmp(Hboard1[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board1[7][i-1] == 1){


									printf("\n");
								if(posBoard1[7][i-1] == 1){
									 carrierLife1 -= 1;
								}
								else if(posBoard1[7][i-1] == 2){
									battleLife1 -= 1;
								}
								else if(posBoard1[7][i-1] == 3){
									destroyerLife1 -= 1;
								}
								else if(posBoard1[7][i-1] == 4){
									submarineLife1 -= 1;
								}
								else if(posBoard1[7][i-1] == 5){
									patrolLife1 -= 1;
								}

								strcpy(Hboard1[i],"X|");

								if(carrierLife1 == 0 && cSunk1 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk1 = 1;
								}
								else if(battleLife1 == 0 && bSunk1 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk1 = 1;
								}
								else if(destroyerLife1 == 0 && dSunk1 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk1 =1;
								}
								else if(submarineLife1 == 0 && sSunk1 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk1 = 1;
								}
								else if(patrolLife1 == 0 && pSunk1 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk1 = 1;
								}

								else{
									printf("We have hit the target!\n\n");

								}
								if(cSunk1 == 1 && bSunk1 ==1 && dSunk1 ==1 && sSunk1 ==1 && pSunk1 ==1){
									printf("Player 2 wins!\n");
									break;
								}

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Hboard1[i],"0|");
							}
							counter++;
							printf("Player 1's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else{
					printf("Invalid coordinates\n");
				}

			}
			else {
				if(!strncmp(token,"A",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Aboard2[i],"0|",2) || !strncmp(Aboard2[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board2[0][i-1] == 1){


									printf("\n");
								if(posBoard2[0][i-1] == 1){
									 carrierLife2 -= 1;
								}
								else if(posBoard2[0][i-1] == 2){
									battleLife2 -= 1;
								}
								else if(posBoard2[0][i-1] == 3){
									destroyerLife2 -= 1;
								}
								else if(posBoard2[0][i-1] == 4){
									submarineLife2 -= 1;
								}
								else if(posBoard2[0][i-1] == 5){
									patrolLife2 -= 1;
								}
								strcpy(Aboard2[i],"X|");

								if(carrierLife2 == 0 && cSunk2 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk2 = 1;
								}
								else if(battleLife2 == 0 && bSunk2 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk2 = 1;
								}
								else if(destroyerLife2 == 0 && dSunk2 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk2 =1;
								}
								else if(submarineLife2 == 0 && sSunk2 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk2 = 1;
								}
								else if(patrolLife2 == 0 && pSunk2 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk2 = 1;
								}

								else{
									printf("We have hit the target!\n\n");

								}
								if(cSunk2 == 1 && bSunk2 ==1 && dSunk2 ==1 && sSunk2 ==1 && pSunk2 ==1){
								 printf("Player 1 wins!\n");
								 break;
							 }

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Aboard2[i],"0|");
							}counter++;
							printf("Player 2's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

					}



				else if(!strncmp(token,"B",1)){

					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Bboard2[i],"0|",2) || !strncmp(Bboard2[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board2[1][i-1] == 1){


									printf("\n");
								if(posBoard2[1][i-1] == 1){
									 carrierLife2 -= 1;
								}
								else if(posBoard2[1][i-1] == 2){
									battleLife2 -= 1;
								}
								else if(posBoard2[1][i-1] == 3){
									destroyerLife2 -= 1;
								}
								else if(posBoard2[1][i-1] == 4){
									submarineLife2 -= 1;
								}
								else if(posBoard2[1][i-1] == 5){
									patrolLife2 -= 1;
								}

								strcpy(Bboard2[i],"X|");

								if(carrierLife2 == 0 && cSunk2 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk2 = 1;
								}
								else if(battleLife2 == 0 && bSunk2 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk2 = 1;
								}
								else if(destroyerLife2 == 0 && dSunk2 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk2 =1;
								}
								else if(submarineLife2 == 0 && sSunk2 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk2 = 1;
								}
								else if(patrolLife2 == 0 && pSunk2 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk2 = 1;
								}

								else{
									printf("We have hit the target!\n\n");

								}
								if(cSunk2 == 1 && bSunk2 ==1 && dSunk2 ==1 && sSunk2 ==1 && pSunk2 ==1){
								 printf("Player 1 wins!\n");
								 break;
							 }

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Bboard2[i],"0|");
						}counter++;
						printf("Player 2's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"C",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Cboard2[i],"0|",2) || !strncmp(Cboard2[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board2[2][i-1] == 1){


									printf("\n");
								if(posBoard2[2][i-1] == 1){
									 carrierLife2 -= 1;
								}
								else if(posBoard2[2][i-1] == 2){
									battleLife2 -= 1;
								}
								else if(posBoard2[2][i-1] == 3){
									destroyerLife2 -= 1;
								}
								else if(posBoard2[2][i-1] == 4){
									submarineLife2 -= 1;
								}
								else if(posBoard2[2][i-1] == 5){
									patrolLife2 -= 1;
								}
								strcpy(Cboard2[i],"X|");

								if(carrierLife2 == 0 && cSunk2 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk2 = 1;
								}
								else if(battleLife2 == 0 && bSunk2 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk2 = 1;
								}
								else if(destroyerLife2 == 0 && dSunk2 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk2 =1;
								}
								else if(submarineLife2 == 0 && sSunk2 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk2 = 1;
								}
								else if(patrolLife2 == 0 && pSunk2 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk2 = 1;
								}

								else{
									printf("We have hit the target!\n\n");

								}
								if(cSunk2 == 1 && bSunk2 ==1 && dSunk2 ==1 && sSunk2 ==1 && pSunk2 ==1){
								 printf("Player 1 wins!\n");
								 break;
							 }

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Cboard2[i],"0|");
							}counter++;
							printf("Player 2's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"D",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Dboard2[i],"0|",2) || !strncmp(Dboard2[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board2[3][i-1] == 1){


									printf("\n");
								if(posBoard2[3][i-1] == 1){
									 carrierLife2 -= 1;
								}
								else if(posBoard2[3][i-1] == 2){
									battleLife2 -= 1;
								}
								else if(posBoard2[3][i-1] == 3){
									destroyerLife2 -= 1;
								}
								else if(posBoard2[3][i-1] == 4){
									submarineLife2 -= 1;
								}
								else if(posBoard2[3][i-1] == 5){
									patrolLife2 -= 1;
								}

								strcpy(Dboard2[i],"X|");

								if(carrierLife2 == 0 && cSunk2 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk2 = 1;
								}
								else if(battleLife2 == 0 && bSunk2 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk2 = 1;
								}
								else if(destroyerLife2 == 0 && dSunk2 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk2 =1;
								}
								else if(submarineLife2 == 0 && sSunk2 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk2 = 1;
								}
								else if(patrolLife2 == 0 && pSunk2 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk2 = 1;
								}

								else {
									printf("We have hit the target!\n\n");

								}
								if(cSunk2 == 1 && bSunk2 ==1 && dSunk2 ==1 && sSunk2 ==1 && pSunk2 ==1){
								 printf("Player 1 wins!\n");
								 break;
							 }

							}
							else
							{	printf("\nYou have missed!\n\n");
								strcpy(Dboard2[i],"0|");
							}counter++;
							printf("Player 2's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"E",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Eboard2[i],"0|",2) || !strncmp(Eboard2[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board2[4][i-1] == 1){


									printf("\n");
								if(posBoard2[4][i-1] == 1){
									 carrierLife2 -= 1;
								}
								else if(posBoard2[4][i-1] == 2){
									battleLife2 -= 1;
								}
								else if(posBoard2[4][i-1] == 3){
									destroyerLife2 -= 1;
								}
								else if(posBoard2[4][i-1] == 4){
									submarineLife2 -= 1;
								}
								else if(posBoard2[4][i-1] == 5){
									patrolLife2 -= 1;
								}

								strcpy(Eboard2[i],"X|");

								if(carrierLife2 == 0 && cSunk2 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk2 = 1;
								}
								else if(battleLife2 == 0 && bSunk2 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk2 = 1;
								}
								else if(destroyerLife2 == 0 && dSunk2 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk2 =1;
								}
								else if(submarineLife2 == 0 && sSunk2 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk2 = 1;
								}
								else if(patrolLife2 == 0 && pSunk2 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk2 = 1;
								}

								else {
									printf("We have hit the target!\n\n");

								}
								if(cSunk2 == 1 && bSunk2 ==1 && dSunk2 ==1 && sSunk2 ==1 && pSunk2 ==1){
								 printf("Player 1 wins!\n");
								 break;
							 }

							}
							else
							{	printf("\nYou have missed!\n\n");
								strcpy(Eboard2[i],"0|");
							}counter++;
							printf("Player 2's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"F",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Fboard2[i],"0|",2) || !strncmp(Fboard2[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board2[5][i-1] == 1){


									printf("\n");
								if(posBoard2[5][i-1] == 1){
									 carrierLife2 -= 1;
								}
								else if(posBoard2[5][i-1] == 2){
									battleLife2 -= 1;
								}
								else if(posBoard2[5][i-1] == 3){
									destroyerLife2 -= 1;
								}
								else if(posBoard2[5][i-1] == 4){
									submarineLife2 -= 1;
								}
								else if(posBoard2[5][i-1] == 5){
									patrolLife2 -= 1;
								}

								strcpy(Fboard2[i],"X|");

								if(carrierLife2 == 0 && cSunk2 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk2 = 1;
								}
								else if(battleLife2 == 0 && bSunk2 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk2 = 1;
								}
								else if(destroyerLife2 == 0 && dSunk2 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk2 =1;
								}
								else if(submarineLife2 == 0 && sSunk2 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk2 = 1;
								}
								else if(patrolLife2 == 0 && pSunk2 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk2 = 1;
								}

								else{
									printf("We have hit the target!\n\n");

								}
								if(cSunk2 == 1 && bSunk2 ==1 && dSunk2 ==1 && sSunk2 ==1 && pSunk2 ==1){
								 printf("Player 1 wins!\n");
								 break;
							 }

							}
							else
								{printf("\nYou have missed!\n\n");
								strcpy(Fboard2[i],"0|");
							}counter++;
							printf("Player 2's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else if(!strncmp(token,"G",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Gboard2[i],"0|",2) || !strncmp(Gboard2[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board2[6][i-1] == 1){


									printf("\n");
								if(posBoard2[6][i-1] == 1){
									 carrierLife2 -= 1;
								}
								else if(posBoard2[6][i-1] == 2){
									battleLife2 -= 1;
								}
								else if(posBoard2[6][i-1] == 3){
									destroyerLife2 -= 1;
								}
								else if(posBoard2[6][i-1] == 4){
									submarineLife2 -= 1;
								}
								else if(posBoard2[6][i-1] == 5){
									patrolLife2 -= 1;
								}
									strcpy(Gboard2[i],"X|");

								if(carrierLife2 == 0 && cSunk2 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk2 = 1;
								}
								else if(battleLife2 == 0 && bSunk2 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk2 = 1;
								}
								else if(destroyerLife2 == 0 && dSunk2 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk2 =1;
								}
								else if(submarineLife2 == 0 && sSunk2 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk2 = 1;
								}
								else if(patrolLife2 == 0 && pSunk2 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk2 = 1;
								}

								else{
									printf("We have hit the target!\n\n");

								}
								if(cSunk2 == 1 && bSunk2 ==1 && dSunk2 ==1 && sSunk2 ==1 && pSunk2 ==1){
								 printf("Player 1 wins!\n");
								 break;
							 }

							}
							else{
								printf("\nYou have missed!\n\n");
								strcpy(Gboard2[i],"0|");

							}counter++;
							printf("Player 2's turn\n\n");
						}
					}
						else {
								printf("Invalid coordinates\n");
						}
					}


				else if(!strncmp(token,"H",1)){
					token = strtok(NULL," ");

					int i = atoi(token);

					if(i==1 || i==2|| i==3|| i==4|| i==5|| i==6|| i==7|| i==8 ){

					if (!strncmp(Hboard2[i],"0|",2) || !strncmp(Hboard2[i],"X|",2)){
						printf("You have already fired at this location\n");
					}
					else{
							if(board2[7][i-1] == 1){


									printf("\n");
								if(posBoard2[7][i-1] == 1){
									 carrierLife2 -= 1;
								}
								else if(posBoard2[7][i-1] == 2){
									battleLife2 -= 1;
								}
								else if(posBoard2[7][i-1] == 3){
									destroyerLife2 -= 1;
								}
								else if(posBoard2[7][i-1] == 4){
									submarineLife2 -= 1;
								}
								else if(posBoard2[7][i-1] == 5){
									patrolLife2 -= 1;
								}
								strcpy(Hboard2[i],"X|");
								if(carrierLife2 == 0 && cSunk2 == 0){
									printf("We have sunk your Carrier!\n\n");
									cSunk2 = 1;
								}
								else if(battleLife2 == 0 && bSunk2 == 0){
									printf("We have sunk your Battleship!\n\n");
									bSunk2 = 1;
								}
								else if(destroyerLife2 == 0 && dSunk2 == 0){
									printf("We have sunk your Destroyer!\n\n");
									dSunk2 =1;
								}
								else if(submarineLife2 == 0 && sSunk2 == 0){
									printf("We have sunk your Submarine!\n\n");
									sSunk2 = 1;
								}
								else if(patrolLife2 == 0 && pSunk2 ==0){
									printf("We have sunk your Patrol Boat!\n\n");
									pSunk2 = 1;
								}

								else{
									printf("We have hit the target!\n\n");

								}
								if(cSunk2 == 1 && bSunk2 ==1 && dSunk2 ==1 && sSunk2 ==1 && pSunk2 ==1){
								 printf("Player 1 wins!\n");
								 break;
							 }

							}
							else
							{	printf("\nYou have missed!\n\n");
								strcpy(Hboard2[i],"0|");
							}counter++;
							printf("Player 2's turn\n\n");
							}
						}
						else {
								printf("Invalid coordinates\n");
						}

				}
				else{
					printf("Invalid coordinates\n");
				}

			}


	}

	else if (!strncmp(token,"exit",4)){
		break;
	}
	else if (flag){
		printf("Unrecognised command\n\n");
	}

	}
}

int setShip(char x,int y, char orient, char* type, int board[8][8], int posBoard[8][8]){
	if(!strncmp(type,"carrier",7)){
		switch(x) {
		 case 'A' :

		 		if(orient == 'H'){
					if(y>4){

						return 0;
					}
						for (int i=0 ;i<5;i++){
							if(board[0][y+i-1] == 1){

								return 0;
							}
						}

						for (int i=0 ;i<5;i++){
								board[0][y+i-1] = 1;
								posBoard[0][y+i-1] = 1;
						}
					return 1;
				}
				else{
					for (int i=0 ;i<5;i++){
						if(board[i][y-1] == 1){

							return 0;
						}
					}

					for (int i=0 ;i<5;i++){
						board[i][y-1] = 1;
						posBoard[i][y-1] = 1;
					}

					return 1;
				}
		 case 'B' :

		 if(orient == 'H'){
			 if(y>4){

				 return 0;
			 }
				 for (int i=0 ;i<5;i++){
					 if(board[1][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<5;i++){
						 board[1][y+i-1] = 1;
						 posBoard[1][y+i-1] = 1;
				 }
			 return 1;
		 }
		 else{
			 for (int i=1 ;i<6;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=1 ;i<6;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 1;
			 }

			 return 1;
		 }

		 case 'C' :

		 if(orient == 'H'){
			 if(y>4){

				 return 0;
			 }
				 for (int i=0 ;i<5;i++){
					 if(board[2][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<5;i++){
						 board[2][y+i-1] = 1;
						 posBoard[2][y+i-1] = 1;
				 }
			 return 1;
		 }
		 else{
			 for (int i=2 ;i<7;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=2 ;i<7;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 1;
			 }

			 return 1;
		 }

		 case 'D' :

		 if(orient == 'H'){
			 if(y>4){

				 return 0;
			 }
				 for (int i=0 ;i<5;i++){
					 if(board[3][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<5;i++){
						 board[3][y+i-1] = 1;
						 posBoard[3][y+i-1] = 1;
				 }
			 return 1;
		 }
		 else{
			 for (int i=3 ;i<8;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=3 ;i<8;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 1;
			 }

			 return 1;
		 }


		 case 'E' :

		 if(orient == 'H'){
			 if(y>4){

				 return 0;
			 }
				 for (int i=0 ;i<5;i++){
					 if(board[4][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<5;i++){
						 board[4][y+i-1] = 1;
						 posBoard[4][y+i-1] = 1;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }


		 case 'F' :
		 if(orient == 'H'){
			 if(y>4){

				 return 0;
			 }
				 for (int i=0 ;i<5;i++){
					 if(board[5][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<5;i++){
						 board[5][y+i-1] = 1;
						 posBoard[5][y+i-1] = 1;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }
		 case 'G' :

		 if(orient == 'H'){
			 if(y>4){

				 return 0;
			 }
				 for (int i=0 ;i<5;i++){
					 if(board[6][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<5;i++){
						 board[6][y+i-1] = 1;
						 posBoard[6][y+i-1] = 1;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }


		 case 'H' :

		 if(orient == 'H'){
			 if(y>4){

				 return 0;
			 }
				 for (int i=0 ;i<5;i++){
					 if(board[7][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<5;i++){
						 board[7][y+i-1] = 1;
						 posBoard[7][y+i-1] = 1;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }


	}
	}
	else if(!strncmp(type,"battleship",10)){
		switch(x) {
		 case 'A' :

		 		if(orient == 'H'){
					if(y>5){

						return 0;
					}
						for (int i=0 ;i<4;i++){
							if(board[0][y+i-1] == 1){

								return 0;
							}
						}

						for (int i=0 ;i<4;i++){
								board[0][y+i-1] = 1;
								posBoard[0][y+i-1] = 2;
						}
					return 1;
				}
				else{
					for (int i=0 ;i<4;i++){
						if(board[i][y-1] == 1){

							return 0;
						}
					}

					for (int i=0 ;i<4;i++){
						board[i][y-1] = 1;
						posBoard[i][y-1] = 2;
					}

					return 1;
				}
		 case 'B' :

		 if(orient == 'H'){
			 if(y>5){

				 return 0;
			 }
				 for (int i=0 ;i<4;i++){
					 if(board[1][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<4;i++){
						 board[1][y+i-1] = 1;
						 posBoard[1][y+i-1] = 2;
				 }
			 return 1;
		 }
		 else{
			 for (int i=1 ;i<5;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=1 ;i<5;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 2;
			 }

			 return 1;
		 }

		 case 'C' :

		 if(orient == 'H'){
			 if(y>5){

				 return 0;
			 }
				 for (int i=0 ;i<4;i++){
					 if(board[2][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<4;i++){
						 board[2][y+i-1] = 1;
						 posBoard[2][y+i-1] = 2;
				 }
			 return 1;
		 }
		 else{
			 for (int i=2 ;i<6;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=2 ;i<6;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 2;
			 }

			 return 1;
		 }

		 case 'D' :

		 if(orient == 'H'){
			 if(y>5){

				 return 0;
			 }
				 for (int i=0 ;i<4;i++){
					 if(board[3][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<4;i++){
						 board[3][y+i-1] = 1;
						 posBoard[3][y+i-1] = 2;
				 }
			 return 1;
		 }
		 else{
			 for (int i=3 ;i<7;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=3 ;i<7;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 2;
			 }

			 return 1;
		 }


		 case 'E' :

		 if(orient == 'H'){
			 if(y>5){

				 return 0;
			 }
				 for (int i=0 ;i<4;i++){
					 if(board[4][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<4;i++){
						 board[4][y+i-1] = 1;
						 posBoard[4][y+i-1] = 2;
				 }
			 return 1;
		 }
		 else{

			 for (int i=4 ;i<8;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=4 ;i<8;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 2;
			 }

			 return 1;

		 }


		 case 'F' :
		 if(orient == 'H'){
			 if(y>5){

				 return 0;
			 }
				 for (int i=0 ;i<4;i++){
					 if(board[5][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<4;i++){
						 board[5][y+i-1] = 1;
						 posBoard[5][y+i-1] = 2;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }
		 case 'G' :

		 if(orient == 'H'){
			 if(y>5){

				 return 0;
			 }
				 for (int i=0 ;i<4;i++){
					 if(board[6][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<4;i++){
						 board[6][y+i-1] = 1;
						  posBoard[6][y+i-1] = 2;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }


		 case 'H' :

		 if(orient == 'H'){
			 if(y>5){

				 return 0;
			 }
				 for (int i=0 ;i<4;i++){
					 if(board[7][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<4;i++){
						 board[7][y+i-1] = 1;
						  posBoard[7][y+i-1] = 2;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }


	}
	}

	else if(!strncmp(type,"destroyer",9)){
		switch(x) {
		 case 'A' :

		 		if(orient == 'H'){
					if(y>6){

						return 0;
					}
						for (int i=0 ;i<3;i++){
							if(board[0][y+i-1] == 1){

								return 0;
							}
						}

						for (int i=0 ;i<3;i++){
								board[0][y+i-1] = 1;
								posBoard[0][y+i-1] = 3;
						}
					return 1;
				}
				else{
					for (int i=0 ;i<3;i++){
						if(board[i][y-1] == 1){

							return 0;
						}
					}

					for (int i=0 ;i<3;i++){
						board[i][y-1] = 1;
						posBoard[i][y-1] = 3;
					}

					return 1;
				}
		 case 'B' :

		 if(orient == 'H'){
			 if(y>6){

				 return 0;
			 }
				 for (int i=0 ;i<3;i++){
					 if(board[1][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<3;i++){
						 board[1][y+i-1] = 1;
						 posBoard[1][y+i-1] = 3;
				 }
			 return 1;
		 }
		 else{
			 for (int i=1 ;i<4;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=1 ;i<4;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 3;
			 }

			 return 1;
		 }

		 case 'C' :

		 if(orient == 'H'){
			 if(y>6){

				 return 0;
			 }
				 for (int i=0 ;i<3;i++){
					 if(board[2][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<3;i++){
						 board[2][y+i-1] = 1;
						 posBoard[2][y+i-1] =3;
				 }
			 return 1;
		 }
		 else{
			 for (int i=2 ;i<5;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=2 ;i<5;i++){
				 board[i][y-1] = 1;
				 					posBoard[i][y-1] = 3;
			 }

			 return 1;
		 }

		 case 'D' :

		 if(orient == 'H'){
			 if(y>6){

				 return 0;
			 }
				 for (int i=0 ;i<3;i++){
					 if(board[3][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<3;i++){
						 board[3][y+i-1] = 1;
						 posBoard[3][y+i-1] = 3;
				 }
			 return 1;
		 }
		 else{
			 for (int i=3 ;i<6;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=3 ;i<6;i++){
				 board[i][y-1] = 1;
				 					posBoard[i][y-1] = 3;
			 }

			 return 1;
		 }


		 case 'E' :

		 if(orient == 'H'){
			 if(y>6){

				 return 0;
			 }
				 for (int i=0 ;i<3;i++){
					 if(board[4][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<3;i++){
						 board[4][y+i-1] = 1;
						 posBoard[4][y+i-1] = 3;
				 }
			 return 1;
		 }
		 else{

			 for (int i=4 ;i<7;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=4 ;i<7;i++){
				 board[i][y-1] = 1;
				 					posBoard[i][y-1] = 3;
			 }

			 return 1;

		 }


		 case 'F' :
		 if(orient == 'H'){
			 if(y>6){

				 return 0;
			 }
				 for (int i=0 ;i<3;i++){
					 if(board[5][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<3;i++){
						 board[5][y+i-1] = 1;
						 posBoard[5][y+i-1] = 3;
				 }
			 return 1;
		 }
		 else{

			 for (int i=5 ;i<8;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=5 ;i<8;i++){
				 board[i][y-1] = 1;
				 					posBoard[i][y-1] = 3;
			 }

			 return 1;
		 }
		 case 'G' :

		 if(orient == 'H'){
			 if(y>6){

				 return 0;
			 }
				 for (int i=0 ;i<3;i++){
					 if(board[6][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<3;i++){
						 board[6][y+i-1] = 1;
						 posBoard[6][y+i-1] = 3;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }


		 case 'H' :

		 if(orient == 'H'){
			 if(y>6){

				 return 0;
			 }
				 for (int i=0 ;i<3;i++){
					 if(board[7][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<3;i++){
						 board[7][y+i-1] = 1;
						 posBoard[7][y+i-1] = 3;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }


	}
	}
	else if(!strncmp(type,"submarine",9)){
		switch(x) {
		 case 'A' :

				if(orient == 'H'){
					if(y>7){

						return 0;
					}
						for (int i=0 ;i<2;i++){
							if(board[0][y+i-1] == 1){

								return 0;
							}
						}

						for (int i=0 ;i<2;i++){
								board[0][y+i-1] = 1;
								posBoard[0][y+i-1] =4;
						}
					return 1;
				}
				else{
					for (int i=0 ;i<2;i++){
						if(board[i][y-1] == 1){

							return 0;
						}
					}

					for (int i=0 ;i<2;i++){
						board[i][y-1] = 1;
						posBoard[i][y-1] = 4;
					}

					return 1;
				}
		 case 'B' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[1][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[1][y+i-1] = 1;
						 posBoard[1][y+i-1] = 4;
				 }
			 return 1;
		 }
		 else{
			 for (int i=1 ;i<3;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=1 ;i<3;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 4;
			 }

			 return 1;
		 }

		 case 'C' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[2][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[2][y+i-1] = 1;
						 posBoard[2][y+i-1] = 4;
				 }
			 return 1;
		 }
		 else{
			 for (int i=2 ;i<4;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=2 ;i<4;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 4;
			 }

			 return 1;
		 }

		 case 'D' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[3][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[3][y+i-1] = 1;
						 posBoard[3][y+i-1] = 4;
				 }
			 return 1;
		 }
		 else{
			 for (int i=3 ;i<5;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=3 ;i<5;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 4;
			 }

			 return 1;
		 }


		 case 'E' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[4][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[4][y+i-1] = 1;
						 posBoard[4][y+i-1] = 4;
				 }
			 return 1;
		 }
		 else{

			 for (int i=4 ;i<6;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=4 ;i<6;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 4;
			 }

			 return 1;

		 }


		 case 'F' :
		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[5][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[5][y+i-1] = 1;
						 posBoard[5][y+i-1] = 4;
				 }
			 return 1;
		 }
		 else{

			 for (int i=5 ;i<7;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=5 ;i<7;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 4;
			 }

			 return 1;
		 }
		 case 'G' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[6][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[6][y+i-1] = 1;
						 posBoard[6][y+i-1] = 4;
				 }
			 return 1;
		 }
		 else{

			 for (int i=6 ;i<8;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=6 ;i<8;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 4;
			 }

			 return 1;
		 }


		 case 'H' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[7][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[7][y+i-1] = 1;
						 posBoard[7][y+i-1] =4;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }


	}
	}

	else if( !strncmp(type,"patrol",6)){
		switch(x) {
		 case 'A' :

				if(orient == 'H'){
					if(y>7){

						return 0;
					}
						for (int i=0 ;i<2;i++){
							if(board[0][y+i-1] == 1){

								return 0;
							}
						}

						for (int i=0 ;i<2;i++){
								board[0][y+i-1] = 1;
								posBoard[0][y+i-1] =5;
						}
					return 1;
				}
				else{
					for (int i=0 ;i<2;i++){
						if(board[i][y-1] == 1){

							return 0;
						}
					}

					for (int i=0 ;i<2;i++){
						board[i][y-1] = 1;
						posBoard[i][y-1] = 5;
					}

					return 1;
				}
		 case 'B' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[1][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[1][y+i-1] = 1;
						 posBoard[1][y+i-1] = 5;
				 }
			 return 1;
		 }
		 else{
			 for (int i=1 ;i<3;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=1 ;i<3;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 5;
			 }

			 return 1;
		 }

		 case 'C' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[2][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[2][y+i-1] = 1;
						 posBoard[2][y+i-1] = 5;
				 }
			 return 1;
		 }
		 else{
			 for (int i=2 ;i<4;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=2 ;i<4;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 5;
			 }

			 return 1;
		 }

		 case 'D' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[3][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[3][y+i-1] = 1;
						 posBoard[3][y+i-1] = 5;
				 }
			 return 1;
		 }
		 else{
			 for (int i=3 ;i<5;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=3 ;i<5;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 5;
			 }

			 return 1;
		 }


		 case 'E' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[4][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[4][y+i-1] = 1;
						 posBoard[4][y+i-1] = 5;
				 }
			 return 1;
		 }
		 else{

			 for (int i=4 ;i<6;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=4 ;i<6;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 5;
			 }

			 return 1;

		 }


		 case 'F' :
		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[5][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[5][y+i-1] = 1;
						 posBoard[5][y+i-1] = 5;
				 }
			 return 1;
		 }
		 else{

			 for (int i=5 ;i<7;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=5 ;i<7;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 5;
			 }

			 return 1;
		 }
		 case 'G' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[6][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[6][y+i-1] = 1;
						 posBoard[6][y+i-1] = 5;
				 }
			 return 1;
		 }
		 else{

			 for (int i=6 ;i<8;i++){
				 if(board[i][y-1] == 1){

					 return 0;
				 }
			 }

			 for (int i=6 ;i<8;i++){
				 board[i][y-1] = 1;
				 posBoard[i][y-1] = 5;
			 }

			 return 1;
		 }


		 case 'H' :

		 if(orient == 'H'){
			 if(y>7){

				 return 0;
			 }
				 for (int i=0 ;i<2;i++){
					 if(board[7][y+i-1] == 1){

						 return 0;
					 }
				 }

				 for (int i=0 ;i<2;i++){
						 board[7][y+i-1] = 1;
						 posBoard[7][y+i-1] =5;
				 }
			 return 1;
		 }
		 else{

			 return 0;
		 }


	}
	}


	return 1;
}



void printBoard(char top[9][4],char aBoard[9][4],char bBoard[9][4] ,char cBoard[9][4],char dBoard[9][4],char eBoard[9][4],char fBoard[9][4],char gBoard[9][4],char hBoard[9][4]){
		printf("\n");
	for(int i=0;i<9;i++){
		printf("%s",top[i]);
	}
		printf("\n");
	for(int i=0;i<9;i++){
		printf("%s",aBoard[i]);
	}
	printf("\n");
	for(int i=0;i<9;i++){
		printf("%s",bBoard[i]);
	}
	printf("\n");
	for(int i=0;i<9;i++){
		printf("%s",cBoard[i]);
	}
		printf("\n");
	for(int i=0;i<9;i++){
		printf("%s",dBoard[i]);
	}
		printf("\n");
	for(int i=0;i<9;i++){
		printf("%s",eBoard[i]);
	}
		printf("\n");
	for(int i=0;i<9;i++){
		printf("%s",fBoard[i]);
	}
		printf("\n");
	for(int i=0;i<9;i++){
		printf("%s",gBoard[i]);
	}
		printf("\n");
	for(int i=0;i<9;i++){
		printf("%s",hBoard[i]);
	}
		printf("\n");
				printf("\n");

}
