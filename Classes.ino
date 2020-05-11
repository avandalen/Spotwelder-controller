#include "Classes.h"
#include <Arduino.h>

void Menu::start()
{ displayIntrotext();  
  unsigned long start_ms = millis();
  while(millis()-start_ms < 2000)
  { pollAll();
    if(selectTFTorientation()) break; 
    if(selectContinuously()) break;
  }
  if(!continuously) displayItems();
  else displayContinuously();
}

void Menu::control()
{ if(!editValueMode)
  { if(upButton.pushed())
    { displayValue(WeldItemNr, menuItems[WeldItemNr].upDownValueTable, 0, editValueMode); // un-focus old item
      displayValue(WeldItemNr, menuItems[WeldItemNr.down()].upDownValueTable, 1, editValueMode); // focus
      return;
    }
    if(downButton.pushed())
    { displayValue(WeldItemNr, menuItems[WeldItemNr].upDownValueTable, 0, editValueMode); // un-focus old item
      displayValue(WeldItemNr, menuItems[WeldItemNr.up()].upDownValueTable, 1, editValueMode); // focus
      return;
    }
    if(selectButton.pushed())
    { displayValue(WeldItemNr, menuItems[WeldItemNr].upDownValueTable, 1, editValueMode=1); // add backgound
      return;
    }
  }

  if(editValueMode)
  { if(upButton.pushed())
    { displayValue(WeldItemNr, menuItems[WeldItemNr].upDownValueTable.up(), 1, editValueMode);
      return;
    }
    if(downButton.pushed())
    { displayValue(WeldItemNr, menuItems[WeldItemNr].upDownValueTable.down(), 1, editValueMode);
      return;
    }
    if(selectButton.pushed())
    { displayValue(WeldItemNr, menuItems[WeldItemNr].upDownValueTable, 1, editValueMode=0); // delete backgound
      eeprom.write();
      return;
    }
  }
}

void Menu::displayIntrotext()
{ tft.fillScreen(TFT_BLACK);
  drawColorTextLine(0, textLeft, version, TFT_YELLOW);
  drawColorTextLine(2, textLeft, F("continuously mode:"), TFT_YELLOW);
  drawColorTextLine(3, textLeft, F("down & select"), TFT_YELLOW);
  drawColorTextLine(5, textLeft, F("change TFT orientation:"), TFT_YELLOW);
  drawColorTextLine(6, textLeft, F("up & down"), TFT_YELLOW);
}

void Menu::displayItems()
{ tft.fillScreen(TFT_BLACK);
  for(int i=0; i<3; i++)
  { WeldItemNr.value=i;
    displayName(WeldItemNr, menuItems[WeldItemNr].name);
    displayValue(WeldItemNr, menuItems[WeldItemNr].upDownValueTable, 0, 0);
  }
  WeldItemNr.value = 0;
  displayValue(WeldItemNr, menuItems[WeldItemNr].upDownValueTable, 1, 0); // item 0 has focus
  displayDot(0);
  drawColorTextLine(8, 0, F("    down            up               sel                    "), TFT_YELLOW, TFT_BLUE); // to long text is ok
}

void Menu::displayContinuously()
{ tft.fillScreen(TFT_RED);
  drawColorTextLine(2, 0, F("                 Continuously"), TFT_WHITE, TFT_RED);
  drawColorTextLine(3, 0, F("                         mode"), TFT_WHITE, TFT_RED);
  drawColorTextLine(4, 0, F("                    Take care!"), TFT_WHITE, TFT_RED);
  displayDot(0);
}

void Menu::displayDot(bool on)
{ tft.fillCircle(158, 180, 20, on? TFT_WHITE : 0x64A7/*green*/); // https://ee-programming-notepad.blogspot.nl/2016/10/16-bit-color-generator-picker.html
}

void Menu::displayName(int WeldItemNr, String &name)
{ drawColorTextLine(2*WeldItemNr, textLeft, name, TFT_YELLOW);
}

void Menu::displayValue(int WeldItemNr, int value, bool focus, bool edit)
{ drawColorTextLine(2*WeldItemNr+1, textLeft, F("                  "), TFT_WHITE); // clear line, can't be BLACK (bug?)
  drawColorTextLine(2*WeldItemNr+1, 0, ">", focus? TFT_WHITE : TFT_BLACK); // BLACK on BLACK = BLACK
  drawColorTextLine(2*WeldItemNr+1, textLeft, String(value), edit? TFT_BLACK : TFT_WHITE, edit? TFT_CYAN : TFT_BLACK);
}

void Menu::displayNoZeroCross()
{ tft.fillScreen(TFT_RED);
  drawColorTextLine(3, 0, "      No zero cross detected!", TFT_WHITE, TFT_RED);
  while(1);
} 

// ---------------------------------------------------------------------------

UpDownValueTable::UpDownValueTable(unsigned valuesPtr, int *values, unsigned size):
valuesPtr(valuesPtr), values(values), size(size)
{
}

int UpDownValueTable::up()
{ if(valuesPtr == size-1) valuesPtr = 0;
  else valuesPtr++;
  return values[valuesPtr];
}

int UpDownValueTable::down()
{ if(valuesPtr == 0) valuesPtr = size-1;
  else valuesPtr--;
  return values[valuesPtr];
}

UpDownValueTable::operator int() // conversion operator, object returns value
{ return values[valuesPtr];
}

// ---------------------------------------------------------------------------

UpDownValueStep::UpDownValueStep(int value, int step, int minValue, int maxValue):
value(value), step(step), minValue(minValue), maxValue(maxValue)
{
}

int UpDownValueStep::up()
{ value += step;
  return value = (value > maxValue) ?  minValue : value;
}

int UpDownValueStep::down()
{ value -= step;
  return value = (value < minValue ) ?  maxValue : value;
}

UpDownValueStep::operator int() // conversion operator, object returns value
{ return value;
}

// ---------------------------------------------------------------------------

MenuItem::MenuItem(String name, UpDownValueTable upDownValueTable):
name(name), upDownValueTable(upDownValueTable)
{
}
