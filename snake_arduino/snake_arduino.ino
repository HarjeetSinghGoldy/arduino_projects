
/*
 *      snake.ino
 *
 *      A simple snake game.
 *      When a player hits the wall or the tail of the snake, the score flashes on the screen.
 *
 *      This code is written for use with a 8x8 led matrix, controlled by a MAX7219
 * 
 *      Remember to download and include LedControlMS from
 *      http://controlsoft.nmmu.ac.za/STM32F3-Discovery-Board/Example-programs/HD44780-LCD-%2816x2-LCD%29
 *
 *      Connected Pins:
 *      From Led-Matrix
 *            CLK                 ->        Pin 11
 *            CS                  ->        Pin 10
 *            DIN                 ->        Pin 12
 *            GND                 ->        GND
 *            VCC                 ->        5V
 *
 *      From Joystick:
 *            S-Y                 ->        A1
 *            S-X                 ->        A0
 *            S-K                 ->        Reset
 *            GND for button      ->        A5
 *            GND(X/Y)            ->        GND
 *            VCC(X/Y             ->        3V
 *  
 *  
 *      Created on: 9 feb 2015
 *      Author: Hannes Paulsson
 *      Email: hannes@geeks.nu
 *
 *    You are free to use this code as you please. I wouldn't mind a shout out if you decide to build anything
 *    cool though.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */

#include "LedControl.h"
#include <math.h>
#include <stdlib.h>

#define NBR_MTX 2 
LedControl lc=LedControl(12,11,10, NBR_MTX); //Change these pin numbers if you need to.
  
  //numbers 0-9. Can be combined to write 0-99 by shifting 4 steps on X.
  int n[11][8][8] = {{
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {

  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {

  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {

  {0,0,0,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  },
  {

  {0,0,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {

  {0,0,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {

  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {

  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {

  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  }}; 


const int LRin = A0; //left / right
const int UDin = A1; //up / down.

bool blinkCandy = true; //switch every loop to blink candy.
int moveDir = 0; //0 = right, 1 = up, 2 = left, 3 = down.
int currMoveDir = 0;//Used to keep track of actual current dir, not just last set during a cycle
int length = 1;  //Starting length.
int last[64][2]; //Matrix with enough room for one snake to use all 64 LEDs
int x = 2; //Start pos
int y = 2; //start pos
int lastId = 0; //The position of the snake prevoius step.
bool collision = false; //Set to true if collision.
bool incLength = false;
int candyPos[2];  //Holds the position of the candy. 
bool candyOnScreen = false;

int speed = 150;

void setup() {
  Serial.begin (9600);
  for(int i = 0; i < 64; i++){ //set all positions outside the screen.
    last[i][0] = -1;
    last[i][1] = -1; 
  }
  
  //Set up display
  for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(i,10);
    /* and clear the display */
    lc.clearDisplay(i);
  }

}

//timer. Check for user input every cycle, only render image every 150th cycle
int timer = 0;

void loop() { 
  int looper;
  looper++;
  looper = looper % speed;
  CheckMove();
  if(looper==0) DoMove();
  if(looper==0) checkCollision();
  if(collision) { 
    GameOver();
  }

  candyCollision(); //Check if candy has been eaten

  while(!candyOnScreen) createCandy(); //radnomize new candy position. Keep going until a valid position is set
  
  if(looper % 100 == 0) candyBlink();
  delay(1);
}

  /**
  *
  * Game over. Flash the score until resetbutton in infinite loop.
  *
  */
void GameOver(void){
  while(1){
    lc.clearDisplay(0);
    delay(100);
    PS(length-1);
    delay(500);
  } 
}

  /**
  * Print score. 
  */
void PS(int a){
  int nr1;
  int nr2;
  if(a > 10){
    nr1 = a / 10;
    nr2 = a - (nr1 * 10); 
  }
  else if(a==10){
    nr1 = 1;
    nr2 = 0;
  }
  else{
    digit(a, 2);
    return;

  }
  digit(nr1, 0);
  digit(nr2, 4);
}
 
  /*
  * Print a digit on the display. 
  * offset is offset in x-axis.
  */
void digit(int nr1, int offset){
    for(int x1 = 0; x1 < 8; x1++){
      for(int y1 = 0; y1 < 8; y1++){
        if(n[nr1][x1][y1] == 1) lc.setLed(0,y1+offset,7-x1,true); 
    } 
  }
}

/*Blink the candy*/
void candyBlink(void){
  if(blinkCandy) lc.setLed(0,candyPos[0],candyPos[1],true);
  else lc.setLed(0,candyPos[0],candyPos[1],false);
  blinkCandy = !blinkCandy;
}
  /*
  *  Turn on Led, at position (x,y)
  */
void Led(int x, int y){
  if(!incLength){
    //Turn of the last light at the tail, re arrange array so the new tail is at index 0.
    lc.setLed(0,last[0][0], last[0][1],false); 
    for(int i = 0; i < length; i++){
      last[i][0] = last[i+1][0];
      last[i][1] = last[i+1][1];
    }

  }
  else{ 
    length++;
    incLength = false;
  }

  last[length][0] = x;
  last[length][1] = y;

  lc.setLed(0,last[length][0],last[length][1],true); // turn on led for the next position of the head.

}

/*Read input from joystick*/
void CheckMove(void){
   
  int LR = analogRead(LRin);
  int UD = analogRead(UDin);

  if(LR > 600 && currMoveDir != 0) moveDir = 2; //Go right, if snake is not moving left
  if(LR < 100 && currMoveDir != 2) moveDir = 0; //Go left, if snake is not moving right
  if(UD > 600 && currMoveDir != 1) moveDir = 3; //Go up, if snake is not moving down
  if(UD < 100 && currMoveDir != 3) moveDir = 1; //Go down, if snake is not moving up
}

  /*
  *  Move snake based on currentMoveDir
  */
void DoMove(void){
  currMoveDir = moveDir;
  if(moveDir == 0) MoveRight();
  if(moveDir == 1) MoveUp();
  if(moveDir == 2) MoveLeft();
  if(moveDir == 3) MoveDown();
  Led(x,y); 
}

/*Increment length*/
void IncrementLength(void){
  incLength = true; 
}

void MoveRight(void){
  x++;
}
void MoveLeft(void){
  x--;
}
void MoveUp(void){
  y--;
}
void MoveDown(void){
  y++;
}

/*create candy*/
void createCandy(void){

  int xR = rand() % 8;
  int yR = rand() % 8;

  for(int i = 0; i <= length; i++){
    if(xR == last[i][0] && yR == last[i][1]){
      candyOnScreen = false; 
      return;
    }
  }
  candyPos[0] = xR;
  candyPos[1] = yR;
  candyOnScreen = true;
  lc.setLed(0,xR,yR,true);
}

/*Check for collision with candy*/
void candyCollision(){
  if(last[length][0] == candyPos[0] && last[length][1] == candyPos[1]){
    candyOnScreen = false; 
    IncrementLength();
  }
}


/*Checks collision with snake and wall. */
void checkCollision(){
  int xP = last[length][0];
  int yP = last[length][1];

  if(xP == -1 || xP == 8 || yP == -1 || yP == 8){
    collision = true;
    return;
  }
  else{
    for(int i = 0; i < length; i++){
      if(last[i][0] == xP && last[i][1] == yP){
        collision = true;
        return;
      }
    }
  }
}
