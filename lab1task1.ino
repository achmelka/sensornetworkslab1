void setup() {
  pinMode(PIN_LED_13,OUTPUT);
  digitalWrite(PIN_LED_13, HIGH);

  GCLK->GENDIV.reg = GCLK_GENDIV_ID(2) | GCLK_GENDIV_DIV(4);

  GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(2) |
  GCLK_GENCTRL_GENEN |
  GCLK_GENCTRL_SRC_OSCULP32K |
  GCLK_GENCTRL_DIVSEL;

  while(GCLK->STATUS.bit.SYNCBUSY); // Think about why this is used
  // WDT clock = clock gen 2
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID_WDT |
  GCLK_CLKCTRL_CLKEN |
  GCLK_CLKCTRL_GEN_GCLK2;

  WDT->CTRL.reg = 0; //disable watchdog
  
  uint8_t period =0x8;
  WDT->CONFIG.bit.PER = period; // Set period for chip reset from the datasheet
  WDT->INTENCLR.bit.EW = 1; // Disable early warning interrupt
  WDT->CTRL.bit.WEN = 0; // Disable window mode
 
  WDT->CTRL.bit.ENABLE = 1;//re-enable the watchdog
  WDT->CLEAR.reg = WDT_CLEAR_CLEAR_KEY;//clear the watchdog
}

void loop() {
}
