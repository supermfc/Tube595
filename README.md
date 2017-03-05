# Tube595
A arduino class for the 8* 7 digitals tube display use two 74HC595, one choose which tube works,and one hold the 7 digitals data. 

![module pic](https://github.com/supermfc/Tube595/blob/master/img/module_pic.jpg)

it is very simple and easy to use:

```C
  #include "Tube595.h"
  
  // the first param is DIO pin,data pin.
  // second is SCLK pin, clock pin.
  // the last is RCLK pin ,LATCH the data to the 74HC595 pin
  //
  
  Tube595 Tube(0,2,1);
 ```

  
in the loop function:
  
  `Tube.displayFloat(1234.5678,1);`
   
it will works!
