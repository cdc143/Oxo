#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <libintl.h>


void boardInit(int *board){
  int i=0;
  for (i=0; i<9;i++){ //fill board with garbage data
    board[i] = i+2;
  }
  srand(time(NULL)); //set up random number gen here
}

void drawBoard() {
  int i=0;
  int j=0;
  for (i=0;i<=6;i++){ //fill in the column boundries
    mvaddch(i,0,'|');
    mvaddch(i,4,'|');
    mvaddch(i,8,'|');
    mvaddch(i,12,'|');

    if(i%2 == 0){
      for (j=0;j<=12;j++) { //fill in the row boundries
        mvaddch(i,j,'-');
      }
    }
  }

    refresh();
  }

int updateBoard(int *board, int x, int y, int token){
//Check that the square the player or ai wishes to write to is empty.
//If it is, update the array containing game data
  if(y==1){
    if(x==2){
      if(board[0] > 1){
        board[0]=token;
        return 1;
      }
    }
    else if (x==6){
      if(board[1] > 1){
        board[1]=token;
        return 1;
      }
    }
    else if (x==10){
      if(board[2] > 1){
        board[2]=token;
        return 1;
      }
    }
  }
else if(y==3){
  if(x==2){
    if(board[3] > 1){
      board[3]=token;
      return 1;
    }
  }
  else if (x == 6){
    if(board[4] > 1){
      board[4]=token;
      return 1;
    }
  }
  else if (x == 10){
    if(board[5] > 1){
      board[5]=token;
      return 1;
    }
  }
}

else if(y==5){
  if(x==2){
    if(board[6] > 1){
      board[6]=token;
      return 1;
    }
  }
  else if (x == 6){
    if(board[7] > 1){
      board[7]=token;
      return 1;
    }
  }
  else if (x == 10){
    if(board[8] > 1){
      board[8]=token;
      return 1;
    }
  }
}
  return 0;
}

int checkWin(int *board){
  //check rows
  if(board[0] == board[1] && board[1] == board[2]){
    return 1;
  }
  else if(board[3] == board[4] && board[4] == board[5]){
    return 1;
  }
  else if (board[6] == board[7] && board[7] == board[8]){
    return 1;
  }
  //check columns
  else if (board[0] == board[3] && board[3] == board[6]){
    return 1;
  }
  else if (board[1] == board[4] && board[4] == board[7]){
    return 1;
  }
  else if (board[2] == board[5] && board[5] == board[8]){
    return 1;
  }
  //check diagonals
  else if (board[0] == board[4] && board[4] == board[8]){
    return 1;
  }
  else if (board[2] == board[4] && board[4] == board[6]){
    return 1;
  }

  return 0;
}

int gameLoop() {
  int okay;
  int inputChar = 0;
  int board[9];
  int squaresFilled = 0;
  int player = 1;
  int winFlag = 0;
  int y = 1; //start in top leftmost square
  int x = 2;
  boardInit(board);

  mvprintw(8,0,gettext("It is your turn. Please place an X on the board"));
  while(inputChar !='q'){ //if input char isn't q, stay in game loop
    move(y,x);
    if(squaresFilled == 9){ //Check for tie
      move(8,0);
      deleteln();
      mvprintw(8,0, gettext("Tie Game! Press any key to quit"));
      inputChar = getch();
      return 0;
    }

    if(player == 1){
      inputChar = getch();
      move(9,0); //Clear any error messages
      deleteln();
      move(y,x);
    }

    if(inputChar != 'x' && player == 1){ //if not x, then player is moving around the board
    switch(inputChar){
      //Each square is 2 units high and 4 units wide
      case KEY_DOWN:
        if(y== 1 || y ==3){
          move(y+=2,x);
        }
        break;
      case KEY_UP:
        if(y==3 || y == 5){
          move(y-=2,x);
        }
        break;
      case KEY_LEFT:
        if(x== 10 || x == 6){
          move(y,x-=4);
        }
        break;
      case KEY_RIGHT:
      if(x == 2 || x == 6){
        move(y,x+=4);
      }
        break;
      default: //user entered an invalid character
        mvprintw(9,0, gettext("I didn't recognize that key. Try again"));
        break;

    }
  }
  else if (inputChar == 'x' && player == 1) {
  //check if move okay
    okay = updateBoard(board,x,y,1);
    if(okay){
      mvaddch(y,x,'X'); //if move okay, update board
      squaresFilled = squaresFilled+1;
      winFlag = checkWin(board); //Check if move caused win
      if(winFlag == 1){
        move(8,0);
        deleteln();
        mvprintw(8,0,gettext("You win!!! Press any key to quit"));
        inputChar = getch();
        return 0;

      }
      player = 0;
    }
  }
  else { //It's the ai's move
    do{
      int y = rand() % 5; //y = 1,3,5
      if((y & 0x1) == 0){
        y++;
      }
      int x = rand() % 5; //x=2,6,10
      if((x & 0x1) == 0){
        x++;
      }
      x*=2;

      okay = updateBoard(board,x,y,0); //Check to see if computer move valid, if not, try another
      if(okay){
        mvaddch(y,x,'O');
        squaresFilled= squaresFilled + 1;
        winFlag = checkWin(board); //Check if computer move caused it to win
        if(winFlag == 1){
          move(8,0);
          deleteln();
          mvprintw(8,0,gettext("Bertie wins!!! Press any key to quit"));
          inputChar = getch();
          return 0;
        }
        player = 1;
        refresh();
      }
    }while(!okay);
  }
  move(y,x); //Move back to where player was
  refresh();

  }
  return 0;
}
