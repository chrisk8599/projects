#include "minesweeper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void init_game(struct cell * game, int dim, int * dim_sizes, int num_mines, int ** mined_cells) {

int cells = 1;

    for(int i=0 ; i < dim ; i ++){
      cells = cells * dim_sizes[i];                            // determine number of cells necessary
    }

    if (cells == 0){     // safety check for invalid dim input
      exit(1);
    }


    for(int i = 0 ; i< cells ; i ++){
      game[i].selected = 0;                            // initialise all cells to mined = 0 and selected = 0
      game[i].mined = 0;
      int size = 1;

    for(int j = 0 ; j<dim ; j++){
      if(j == 0){
          game[i].coords[j] = i%dim_sizes[j];
          size = size * dim_sizes[j];                            // apply coordinates to all cells
      }
      else{
          int result = (i/size) % dim_sizes[j];
              game[i].coords[j] = result ;
              size = size * dim_sizes[j];
      }
    }





        for(int k=0; k < num_mines ; k ++){
          int counter = 0 ;
          for(int j = 0 ; j<dim ; j++){
              if(  game[i].coords[j] == *(*(mined_cells + k)+j)){          // discover the cells with mines
                counter++;                                                     // and set mined = 1
              }

          }

          if(counter == dim){
          game[i].mined = 1;
          }

        }
      }

      for(int i=0; i<cells;i++){
        int diff = 0 ;
        int numAdj = 0;

        for(int h = 0 ; h< cells ; h++){
          int flag = 1;
          int counter = 0;
          if(h!=i){

            for(int j =0 ; j< dim; j++){
              diff = game[i].coords[j] - game[h].coords[j];
              if((diff == 0 || diff == 1 || diff == -1)&&flag){                      // find the adjacent cells and how many there are
                counter++;
              }
              else{
                counter = 0 ;
                flag = 0;
              }
            }
            if(counter == dim) {
              game[i].adjacent[numAdj] = &game[h];
              numAdj ++ ;
            }
          }
        }
        game[i].num_adjacent = numAdj;
    }

      for(int i=0; i<cells;i++){
        game[i].hint = find_mines(game[i]);         //apply the hint to all cells beforehand.
      }

    return;
}


int select_cell(struct cell * game, int dim, int * dim_sizes, int * coords) {

  if(coords == NULL || game == NULL || dim <1 || dim_sizes == NULL){           //invalid input checks
    return 0;
  }
  int cells =1;

  for(int i=0 ; i < dim ; i ++){
    cells = cells * dim_sizes[i];                            // determine number of cells necessary
  }

  int offset = 1;
  int size = 1;

  for (int i = 0 ; i<dim ; i++){
    if(i==0){
      offset = coords[0] ;
    }
    else{
      size = size * dim_sizes[i-1];                   //finding the offset from the coordinates given
      offset += size * coords[i];
    }

  }


  if(offset >= cells){
    return 0;
  }
  else if(game[offset].selected ==1){                //invalid input checks
    return 0;
  }

  game[offset].selected = 1;

  if(game[offset].mined == 1){                   // if it is a mine return 1
    return 1;
  }
  else{
    if(find_mines(game[offset]) == 0){
      select_recursion(game[offset]);            //else if it has no surrounding mines, do a recursion.
    }
  }


  int count = 0;
  int num = 0;
  for(int i =0 ; i< cells ; i++){
    if(game[i].selected == 0){
      count++;
    }
    if(game[i].mined ==1){                    //checks if the number of mines equals the number of unselected cells
      num++;                                  // if so then return 2
    }
  }

  if(count == num){
    return 2;
  }

    return 0;
}

int find_mines(struct cell cell){
    int adj = cell.num_adjacent;
    int counter  = 0;
    for(int i = 0 ; i<adj ; i++){                      // finds the number of adjacent mines
      if(cell.adjacent[i]->mined == 1){
        counter++;
      }
    }
    return counter;

}

void select_recursion(struct cell cell){
   if(find_mines(cell) == 0 ){
     for (int i =0 ; i< cell.num_adjacent ; i++){
       if(cell.adjacent[i]->selected == 0){
         cell.adjacent[i]->selected = 1;
         select_recursion(*(cell.adjacent[i]));          // recursively calls and selects all cells with no surrounding mines
       }
     }
   }
   cell.selected = 1;

}
