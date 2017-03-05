  #include "Tube595.h"
  
  // the first param is DIO pin,data pin.
  // second is SCLK pin, clock pin.
  //  the last is RCLK pin ,LATCH the data to the 74HC595 pin
  //
  Tube595 Tube(0,2,1);

  int i = 0;
  void setup ()
    {
           
    }
    void loop()
    {
		
	 // set the fixed number or a letter in the sepc place
     // Tube.setDigital(0,1);
     // Tube.setDigital(1,8);
     // Tube.setLetter(2,'-');
     // Tube.setLetter(3,'E');
	 
	 
	 // set the point in the sepc place
     // Tube.setPoint(7);
	 
	 //display a int type number
	 // Tube.displayInt(32768);
   
     //display a float num,the second params determines the number of digits after the decimal sign.
	 
	 Tube.displayFloat(1234.5678,1);

    }
    
   
