const unsigned maxWrites = 100;
const unsigned initValue = 12
; // take another value for default EEPROM settings

void Eeprom::init()
{ setMemPool(0, EEPROMSizeATmega328);
  setMaxAllowedWrites(maxWrites);
  storedInitValue_addr = getAddress(sizeof(unsigned));
  preweld_ms_addr = getAddress(sizeof(unsigned));
  pause_ms_addr = getAddress(sizeof(unsigned));
  weld_ms_addr = getAddress(sizeof(unsigned));
  orientation_addr = getAddress(sizeof(unsigned));
  if(!initialized()) write(); // fill an empty EEPROM with factory default settings
}

void Eeprom::read()
{ menuItems[0].upDownValueTable.valuesPtr = readInt(preweld_ms_addr);
  menuItems[1].upDownValueTable.valuesPtr = readInt(pause_ms_addr);
  menuItems[2].upDownValueTable.valuesPtr = readInt(weld_ms_addr);
  orientation = readInt(orientation_addr);
}

void Eeprom::write()
{ writeInt(storedInitValue_addr, initValue);
  writeInt(preweld_ms_addr, menuItems[0].upDownValueTable.valuesPtr);
  writeInt(pause_ms_addr, menuItems[1].upDownValueTable.valuesPtr);
  writeInt(weld_ms_addr, menuItems[2].upDownValueTable.valuesPtr);
  writeInt(orientation_addr, orientation);
}

bool Eeprom::initialized()
{ return readInt(storedInitValue_addr) == initValue;
}

