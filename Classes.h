#ifndef _Classes_H_
#define _Classes_H_

#include <Arduino.h>

class UpDownValueStep
{ public:
    UpDownValueStep(int value, int step, int minValue, int maxValue);
    int up();
    int down();
    operator int();

    int value, step, minValue, maxValue;
};

// ---------------------------------------------------------------------------

class UpDownValueTable
{ public:
    UpDownValueTable(unsigned valuesPtr, int *values, unsigned size);
    int up();
    int down();
    operator int();

    int *values;
    unsigned valuesPtr, size;
};

// ---------------------------------------------------------------------------

class MenuItem
{ public:
    MenuItem(String name, UpDownValueTable upDownValueTable);

    String name;
    UpDownValueTable upDownValueTable;
};

// ---------------------------------------------------------------------------

class Menu
{ public:
    void start();
    void control();
    void displayDot(bool on);
    void displayNoZeroCross();
    void displayItems();

  private:
    void displayName(int itemNr, String &name);
    void displayValue(int itemNr, int value, bool focus, bool edit);
    void displayContinuously();
    void displayIntrotext();

    bool editValueMode=0;
    const int textLeft = 20;
};

#endif
