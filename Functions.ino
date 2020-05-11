bool selectTFTorientation() // because LCD orientation is unknown
{ if(upButton.on() && downButton.on()) // change between 1<->3 when up and down are pressed during power up
  { if(orientation==1) orientation=3; // orientation can only be either 1 or 3
    else orientation=1; // if 0, 2, 3...
    eeprom.write();
    TFTinit();
    return 1;
  }
  return 0;
}

bool selectContinuously()
{ if(downButton.on() && selectButton.on()) 
  { continuously = 1;  
    return 1;
  }
  return 0;
}

void weldControl() // runs in a loop
{ if(continuously) weldContinuously();
  else if(weldButton.pushed() || footSwitch.pushed()) weldCyclus();
}

void weldCyclus()
{ pollAll(); pollAll(); // reset all buttons because polling was interrupted during delay functions
  weldPulse(menuItems[0].upDownValueTable);
  pollAll(); pollAll();
  delay(menuItems[1].upDownValueTable);
  pollAll(); pollAll();
  weldPulse(menuItems[2].upDownValueTable);
  pollAll(); pollAll();
}

void weldContinuously() // runs in a loop 
{ if(weldButton.pushed()) waitForSinusmax(); // use pushed() because do only once 
  weld(weldButton.on());
}

void weldPulse(int ms)
{ waitForSinusmax();
  if(ms) weld(1);// do not trigger for 0 ms
  delay(ms); // weldPin is continuous high now
  weld(0);
  //Serial << ms << endl;
}

void weld(bool b)
{ digitalWrite(weldPin, b);
  menu.displayDot(b);
  //if(b) Serial << F("weld ");
}

void setpinModes()
{ pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(selectButtonPin, INPUT_PULLUP);
  pinMode(weldButtonPin, INPUT_PULLUP);
  pinMode(weldPin, OUTPUT);
  pinMode(zeroCrossPin, INPUT);
  pinMode(footSwitchPin, INPUT_PULLUP);
}

void pollAll()
{ weldButton.poll();
  upButton.poll();
  downButton.poll();
  selectButton.poll();
  footSwitch.poll();
  zeroCrossCounter.poll();
}

void printValuesToSerial()
{  Serial << F("\npreweld ") << menuItems[0].upDownValueTable << F("ms, pause ") << menuItems[1].upDownValueTable << F("ms, weldTime ")
   << menuItems[2].upDownValueTable << F("ms, continuously ") << continuously << F(", Orientation ") << orientation << endl;
}

void drawColorTextLine(int line, int left, String str, uint16_t textColor, uint16_t backgroundColor) 
{ const int fontSize=4, fontHeight=26;
  const int vertOffset=3; // 240-9*26)/2
  tft.setTextColor(textColor, backgroundColor);
  tft.drawString(str.c_str(), left, fontHeight*line+vertOffset, fontSize);
}

void TFTinit()
{ tft.init();
  tft.setRotation(orientation);
}

void waitForSinusmax()
{ waitForZeroCross(); 
  delayMicroseconds(sinusMax_us); // prevent high inrush current, turn-on at the sinus max
}

bool waitForZeroCross() 
{ const int waitForZeroCrossTime_ms = 50;  // 1 period = 0.5/50Hz=10ms, take 50ms (15ms gives problems)
  bool level, lastLevel;
  lastLevel = digitalRead(zeroCrossPin);
  unsigned long timeOut_ms = millis() + waitForZeroCrossTime_ms; 
  while(millis() < timeOut_ms) // works also without AC mains
  { level = digitalRead(zeroCrossPin);
    if(level != lastLevel) return 1; // return on zero cross time
    lastLevel = level;  
  }  
  return 0; // return on random time, no transient detected
}

void beepCallbackFunction(void* s) 
{ tone(3, 2400, 5); // is non-blocking 
  //Serial.print("BeepCallback: "); Serial.println((char*)s);
}
