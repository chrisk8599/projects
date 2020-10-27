#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void printBoard(char board[8][18]);
int moveHuman(char board[8][18],char token[2]);
int moveRobot(char board[8][18],char token[2]);
int main(int argc, char *argv[]){




int seed ;
    if( argc >= 2 )
      {
          seed = atoi(argv[1]);
      }
      else
      {
          printf("No exit seed supplied\n");
          exit(1);
      }
srand(seed);

while(1){
int won = 0;
int lost = 0;

  char x;
  char y;
  int num;
  int xcoord;
  int ycoord;

  char board[8][18];
  for(int i=0 ; i<8 ; i++){
    strcpy(board[i],"| | | | | | | | |");
  }



int ex = rand() % 8;
int ey = rand() % 8;

board[ey][ex*2+1] = 'E';



while(1){
  printf("Human starting point: ");
  scanf(" %c %c", &x ,&y);

  xcoord = x - '0';
  ycoord = y - '0';


  if(isdigit(x) && isdigit(y)){
    if(xcoord<8 && ycoord<8 && ycoord>=0 && xcoord >= 0 ){
      board[ycoord][xcoord*2 +1] = 'H';
      break;
    }
    else{
      printf("Invalid Coordinates, Try again\n");

    }
  }
  else{
    printf("Invalid Coordinates, Try again\n");

  }
}

while(getchar() != '\n');


while(1){

  printf("Number of robots: ");
  int check = scanf("%d",&num);

  if(check != 0 ){
      if(num >=1){

          break;
      }
      else{
          while(getchar() != '\n')
          ;

          printf("Invalid number, Try again\n");
      }

  }
  else{
    printf("Invalid number, Try again\n");
    while(getchar() != '\n')
    ;


  }
}


int numRobots = num;
  char robotX[10];
  char robotY[10];

  for(int i = 0; i <numRobots; i++){
    while(getchar() != '\n');

    while(1){

    int flag = 0;
    printf("Robot %d: ",i+1);
    scanf(" %c %c", &robotX[i], &robotY[i]);

    for(int k=0; k<i;k++){
      if(robotX[i] == robotX[k] && robotY[i] == robotY[k]){
            while(getchar() != '\n');
        printf("Invalid Coordinates, Try again\n");
        flag = 1;
      }
    }

        int rx = robotX[i] - '0';
        int ry = robotY[i] - '0';

    if(!flag){
      if( (rx<xcoord-1 || rx > xcoord+1 ) || (ry<ycoord -1 || ry> ycoord +1) ){
          flag =0 ;
      }
      else {
        flag =1 ;
        while(getchar() != '\n');
        printf("Invalid Coordinates, Try again\n");
      }

    }




    if(!flag){

    if(isdigit(robotX[i]) && isdigit(robotY[i])){

        if(rx<8 && ry<8 && rx >= 0  && ry >=0){
          board[ry][rx*2 +1] = 'R';
          break;
        }
        else{
            while(getchar() != '\n');
          printf("Invalid Coordinates, Try again\n");
        }
    }
    else{
        while(getchar() != '\n');
      printf("Invalid Coordinates, Try again\n");

    }
  }

  }
  }


printf("\n");

  while(1){


    if(won){
      printf("\n");
      printf("\n");
      break;
    }
    else if(lost){
      printf("\n");
      break;
    }

    char buf[15];
  	fgets(buf,15,stdin);
  	char * token = strtok(buf," ");

  	if(!strncmp(token,"display",7)){
      printBoard(board);

    }

    else if(!strncmp(token,"exit",4)){
          exit(0);
    }


    else if(!strncmp(token,"move",4)){
        printf("\n");
        token = strtok(NULL," ");

        if(!strncmp(token,"NT",2)){
          won =moveHuman(board,token);
          lost =moveRobot(board,token);
        }
        else if(!strncmp(token,"ST",2)) {
          won = moveHuman(board,token);
          lost = moveRobot(board,token);
        }
        else if(!strncmp(token,"WT",2)) {
          won = moveHuman(board,token);
          lost = moveRobot(board,token);
        }
        else if(!strncmp(token,"ET",2)) {
          won = moveHuman(board,token);
          lost = moveRobot(board,token);
        }
        else{
          printf("Invalid\n");

        }


    }



  }

}


}

int moveRobot(char board[8][18],char token[2]){
  int trig =0;
  int lost = 0;
  for(int i=0 ; i < 8 ; i++){
    for(int j=0;j<17;j++){
      if(board[i][j] == 'H' && trig ==0){
        int y = i;
        int x = (j-1)/2;
        trig = 1;
        for(int a = 0 ; a<8 ; a++){
          for(int b=0; b<17 ; b++){



              if(board[a][b] == 'R' && lost ==0){




                if(abs(y-a) < abs((x-((b-1)/2)))) {

                 if((x-((b-1)/2))>0){
                   board[a][b] = ' ';
                   if(board[a][b+2] == 'R'){
                     board[a][b+2] = 'D';
                   }
                   else if(board[a][b+2] == 'A'){
                     board[a][b+2] = 'D';
                   }
                   else if(board[a][b+2] == 'H'){
                     printf("The robots got you! We are doomed!\n");
                     lost =1;
                   }
                   else{
                     board[a][b+2] = 'A';
                   }

                 }
                 else{
                   board[a][b] = ' ';
                   if(  board[a][b-2] == 'R'){
                       board[a][b-2] = 'D';
                   }
                   else if(board[a][b-2] == 'A'){
                     board[a][b-2] = 'D';
                   }
                   else if(board[a][b-2] == 'H'){
                     printf("The robots got you! We are doomed!\n");
                     lost =1;
                   }
                   else{
                       board[a][b-2] = 'A';
                   }

                 }
               }

                  else if(abs(y - a) > abs((x-((b-1)/2)))) {
                    if((y - a) > 0 ){
                      board[a][b] = ' ';
                      if(board[a+1][b] == 'R'){
                        board[a+1][b] = 'D';
                      }
                      else if(board[a+1][b] == 'A'){
                        board[a+1][b] = 'D';
                      }
                      else if(board[a+1][b] == 'H'){
                        printf("The robots got you! We are doomed!\n");
                        lost =1;
                      }
                      else{
                        board[a+1][b] = 'A';
                      }

                    }
                    else{
                      board[a][b] = ' ';
                      if(board[a-1][b] == 'R'){
                        board[a-1][b] = 'D';
                      }
                      else if(board[a-1][b] == 'A'){
                        board[a-1][b] = 'D';
                      }
                      else if(board[a-1][b] == 'H'){
                        printf("The robots got you! We are doomed!\n");
                        lost =1;
                      }
                      else{
                        board[a-1][b] = 'A';
                      }

                    }
                  }

                  else if(abs(y-a) == abs((x-((b-1)/2)))){



                    if(!strncmp(token,"NT",2)){

                                  if((x-((b-1)/2)) > 0){
                                       board[a][b] = ' ';
                                       if(board[a][b+2] == 'R'){
                                         board[a][b+2] = 'D';
                                       }
                                       else if(board[a][b+2] == 'A'){
                                         board[a][b+2] = 'D';
                                       }
                                       else if(board[a][b+2] == 'H'){
                                         printf("The robots got you! We are doomed!\n");
                                         lost =1;
                                       }
                                       else{
                                         board[a][b+2] = 'A';
                                       }

                                     }
                                     else{
                                       board[a][b] = ' ';
                                       if(board[a][b-2] == 'R'){
                                         board[a][b-2] = 'D';
                                       }
                                       else if(board[a][b-2] == 'A'){
                                         board[a][b-2] = 'D';
                                       }
                                       else if(board[a][b-2] == 'H'){
                                         printf("The robots got you! We are doomed!\n");
                                         lost =1;
                                       }
                                       else{
                                         board[a][b-2] = 'A';
                                       }
                                     }


                                   }
                                   else if(!strncmp(token,"ST",2)) {
                                     if((x-((b-1)/2))> 0){
                                       board[a][b] = ' ';
                                       if(board[a][b+2] == 'R'){
                                         board[a][b+2] = 'D';
                                       }
                                       else if(board[a][b+2] == 'A'){
                                         board[a][b+2] = 'D';
                                       }
                                       else if(board[a][b+2] == 'H'){
                                         printf("The robots got you! We are doomed!\n");
                                         lost =1;
                                       }
                                       else{
                                         board[a][b+2] = 'A';
                                       }
                                     }
                                     else{
                                       board[a][b] = ' ';
                                       if(  board[a][b-2] == 'R'){
                                           board[a][b-2] = 'D';
                                       }
                                       else if(board[a][b-2] == 'A'){
                                         board[a][b-2] = 'D';
                                       }
                                       else if(board[a][b-2] == 'H'){
                                         printf("The robots got you! We are doomed!\n");
                                         lost =1;
                                       }
                                       else{
                                           board[a][b-2] = 'A';
                                       }

                                     }
                                   }
                                   else if(!strncmp(token,"WT",2)) {
                                     if((y-a) > 0){
                                       board[a][b] = ' ';
                                       if(  board[a+1][b] == 'R'){
                                           board[a+1][b] = 'D';
                                       }
                                       else if(board[a+1][b] == 'A'){
                                         board[a+1][b] = 'D';
                                       }
                                       else if(board[a+1][b] == 'H'){
                                         printf("The robots got you! We are doomed!\n");
                                         lost =1;
                                       }
                                       else{
                                           board[a+1][b] = 'A';
                                       }
                                     }
                                     else{
                                       board[a][b] = ' ';
                                       if(board[a-1][b] == 'R'){
                                         board[a-1][b] = 'D';
                                       }
                                       else if(board[a-1][b] == 'A'){
                                         board[a-1][b] = 'D';
                                       }
                                       else if(board[a-1][b] == 'H'){
                                         printf("The robots got you! We are doomed!\n");
                                         lost =1;
                                       }
                                       else{
                                         board[a-1][b] = 'A';
                                       }
                                     }
                                   }
                                   else if(!strncmp(token,"ET",2)) {
                                     if((y-a) > 0){
                                       board[a][b] = ' ';
                                       if(board[a+1][b] == 'R'){
                                         board[a+1][b] = 'D';
                                       }
                                       else if(board[a+1][b] == 'A'){
                                         board[a+1][b] = 'D';
                                       }
                                       else if(board[a+1][b] == 'H'){
                                         printf("The robots got you! We are doomed!\n");
                                         lost =1;
                                       }
                                       else{
                                         board[a+1][b] = 'A';
                                       }

                                     }
                                     else{
                                       board[a][b] = ' ';
                                       if(board[a-1][b] == 'R'){
                                         board[a-1][b] = 'D';
                                       }
                                       else if(board[a-1][b] == 'A'){
                                         board[a-1][b] = 'D';
                                       }
                                       else if(board[a-1][b] == 'H'){
                                         printf("The robots got you! We are doomed!\n");
                                         lost =1;
                                       }
                                       else{
                                         board[a-1][b] = 'A';
                                       }
                                     }
                                   }


                  }

              }

          }
        }



      }
    }
  }



  for(int i=0 ; i < 8 ; i++){
    for(int j=0 ; j< 17; j++){
      if(board[i][j] == 'A'){
        board[i][j] = 'R';
      }
    }
  }

  if(lost){
    return 1;
  }
  else{
    return 0;
  }

}





int moveHuman(char board[8][18], char token[2]){
  int trig = 0;
  int won =0;
  for(int i=0 ; i < 8 ; i++){
    for(int j=0;j<17;j++){
      if(board[i][j] == 'H' && trig == 0){
        if(!strncmp(token,"NT",2)){

          if((i-1) < 0){
            printf("Invalid\n");
          }
          else{
            board[i][j] = ' ';

            if(board[i-1][j] =='E'){
              printf("Well done! You survived, but it isn't over!\n");
              won =1;
            }
            else{
               board[i-1][j] ='H';
            }


            trig =1;
          }


        }
        else if(!strncmp(token,"ST",2)) {


          if((i+1) > 7){
            printf("Invalid\n");
          }
          else{
            board[i][j] = ' ';
            if(board[i+1][j] =='E'){
              printf("Well done! You survived, but it isn't over!\n");
              won =1;
            }
            else{
               board[i+1][j] ='H';
            }
            trig =1;
          }

        }
        else if(!strncmp(token,"WT",2)) {

          if((j-1) == 0){
            printf("Invalid\n");
          }
          else{
            board[i][j] = ' ';
            if(board[i][j-2] =='E'){
              printf("Well done! You survived, but it isn't over!\n");
              won =1;
            }
            else{
               board[i][j-2] ='H';
            }
            trig =1;
          }
        }
        else if(!strncmp(token,"ET",2)) {

          if(j == 15){
            printf("Invalid\n");
          }
          else{
            board[i][j] = ' ';
            if(board[i][j+2] =='E'){
              printf("Well done! You survived, but it isn't over!\n");
              won =1;
            }
            else{
               board[i][j+2] ='H';
            }
            trig =1;
          }
        }
      }
    }
}

if(won){
  return 1;
}
else{
  return 0;
}

}


void printBoard(char board[8][18]){
  printf("\n");
  for(int i=0;i<8;i++){
    printf("%s\n",board[i]);
  }
  printf("\n");
}
