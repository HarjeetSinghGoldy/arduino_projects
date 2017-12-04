/// tento soubor je zakladnim souborem v projektu, 
/// parti sem jeste soubory functions.ino a messages.ino, 
/// ktere se sem automaticky nainportuji pri kompilaci.

#include "FreeRAM.h"
#include "LedControl.h"

// Piny
const short joyXpin = 2;
const short joyYpin = 3;
const short joyKEYpin = 18;
const short joyVCCpin = 15;
const short joyGNDpin = 14;
const short potPin = 7;

const short DINpin = 11;
const short CLKpin = 9;
const short CSpin  = 10;
const short intensity = 8;

int debugTime = 100;
int messageRefreshTime = 4;


int delka = 3;
int speed = 300;
bool sezrano = true;
bool gameOver = false;
bool dontShowIntro = false;

// primarni souradnice hada
int x = 3;
int y = 4;

int foodX;
int foodY;

const short up     = 0;
const short right  = 1;
const short down   = 2;
const short left   = 3;
int direction = 8;

// pole Map - slouzi jako buffer pro matrix. manipuluje se s timto polem,
// pak az se cele najednou posle na matrix.
bool Map[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}
};

// pole age - urcuje vek kazde bunky (ledky). podle toho se pak temer automaticky zhasinaji
// bunky za hadem.
long age[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 2, 0, 0, 0, 0}, 
    {0, 0, 0, 3, 0, 0, 0, 0}, 
    {0, 0, 0, 4, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}
};

// pole foodMap - obsahuje informaci o tom, kde se nachazi jidlo. 
bool foodMap[8][8];


const short length = 56;
const bool snejkMessage[8][length] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0}
};

const short length2 = 84;
const bool gameOverMessage[8][length2] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0}
};



LedControl MTX = LedControl(DINpin, CLKpin, CSpin, 1);

void(* restart) (void) = 0; // restartovaci funkce

void setup() 
{
    initialize();
    handleGameStates();
    updateMap();
    wait4move();
    generateFood();
    updateMap();
    
    Serial.println(freeram());
}


void loop() 
{
    generateFood();
    
    handleGameStates();
    
    scanJoistyck();   // sleduje pohyb joystku, obstarava i cekani mezi "snimky"
    
    calculateSnake(); // vypocet parametru hada
    
    updateMap();      // aktualizace matrixu
    
}



void handleGameStates()
{
    
    
    while(gameOver)
    {
        if(digitalRead(joyKEYpin))
        {
            delay(250);
            for(int d = 0; d < sizeof(gameOverMessage[0]) - 7; d++) 
            {
                for(int col = 0; col < 8; col++) 
                {
                    delay(messageRefreshTime);
                    for(int row = 0; row < 8; row++) 
                    {
                        int i = col + d;
                        // MTX.setLed(0, row, col, *(arrayy+size*row+i));
                        MTX.setLed(0, row, col, gameOverMessage[row][i]);
                    }
                }
            }
            
            while(digitalRead(joyKEYpin)){}
            restart();
            while(1){Serial.println("never happens");}
            
            //gameOver = false;
            //break;
        }
    }
    
    
    if(digitalRead(joyKEYpin) && !gameOver && !dontShowIntro)
    {
        for(int d = 0; d < sizeof(snejkMessage[0]) - 7; d++) 
        {
            for(int col = 0; col < 8; col++) 
            {
                delay(messageRefreshTime);
                for(int row = 0; row < 8; row++) 
                {
                    int i = col + d;
                    // MTX.setLed(0, row, col, *(arrayy+size*row+i));
                    MTX.setLed(0, row, col, snejkMessage[row][i]);
                }
            }
        }
        dontShowIntro = true;
    }
    
    dontShowIntro = true;
    
}
