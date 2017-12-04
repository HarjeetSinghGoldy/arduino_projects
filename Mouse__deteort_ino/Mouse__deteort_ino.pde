
import processing.serial.*;

int new_sX, old_sX;
int nX, nY;
Serial myPort;

void setup(){
  size( 900, 400 );
  strokeWeight( 10 );
 
  //Open the serial port for communication with the Arduino
  //Make sure the COM port is correct
  myPort = new Serial(this, "/dev/ttyACM1", 9600);
  myPort.bufferUntil('\n'); 
}

// Draw the Window on the computer screen
void draw(){
  
  // Fill canvas grey
  background( 0 );
    
  // Set the stroke colour to white
  stroke(127,255,0); 
  
  // Draw a circle at the mouse location

  
textSize(20);

fill(0,100,0);
rect(70, 0, 90, 800);
fill(0);
text("START", 85, 200);

fill(230, 230, 0);
rect(385, 0, 90, 800);

fill(230, 0, 0);
rect(700, 0, 90, 800);
fill(0);
text("END", 723, 200); 
  //Draw Line from the top of the page to the bottom of the page
  //in line with the mouse.
    ellipse( nX, nY, 10, 10 );
  line(nX,0,nX,height);  
}


// Get the new mouse location and send it to the arduino
void mouseMoved(){
  nX = mouseX;
  nY = mouseY; 
  
  //map the mouse x coordinates to the LEDs on the Arduino.
  new_sX=(int)map(nX,0,800,0,10);
  print(new_sX);
  if(new_sX==old_sX){
    //do nothing
  } else {
    //only send values to the Arduino when the new X coordinates are different.
    old_sX = new_sX;
    myPort.write(""+new_sX);
  }
}
