#include "LedControl.h"

// Create a new LedControl for 5 devices... 
LedControl lc1=LedControl(12,11,10,5); 

void setup() {
  for(int index=0;index<lc1.getDeviceCount();index++) {
      lc1.shutdown(index,false);
  }
}
