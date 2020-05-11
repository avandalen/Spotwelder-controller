void test()
{ //ok testDS18B20();
  //testMCP3425();
  
  if(downButton.on() && upButton.on())
  { while(1) 
    { delay(100);
      weldCyclus();
    }
  }
  
  //test_optionalOutput();

}

void test_optionalOutput()
{ pinMode(optionalOutput, OUTPUT);
  digitalWrite(optionalOutput, HIGH);   // sets the LED on
  delay(1000);                  // waits for a second
  digitalWrite(optionalOutput, LOW);    // sets the LED off
  delay(1000);                  // waits for a second
}
