void setup() {
  // put your setup code here, to run once:
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

  double milSec = 10;
  SetWatchdog(milSec);  //set period to after 4096 clock cycles. That would mean 4 seconds with a 1024hz clock.
  WDT->INTENCLR.bit.EW = 1; // Disable early warning interrupt
  WDT->CTRL.bit.WEN = 0; // Disable window mode
 
  WDT->CTRL.bit.ENABLE = 1;//re-enable the watchdog
  //WDT->CLEAR.reg = WDT_CLEAR_CLEAR_KEY;//clear the watchdog
  pinMode(PIN_LED_13,OUTPUT);
  digitalWrite(PIN_LED_13, HIGH);

}

void loop() {
}

void SetWatchdog(double period){
    
    if(period < 15.625){ //8 clock cycles(8/1024 seconds)
    WDT->CONFIG.bit.PER = 0x0; // Set period for chip reset from the datasheet
    }
    else if(period >= 15.625 && period < 31.25){//16 clock cycles(16/1024 seconds)
    WDT->CONFIG.bit.PER = 0x1; // Set period for chip reset from the datasheet
    }
    else if(period >= 31.25 && period < 62.5){//32 clock cycles(32/1024 seconds)
    WDT->CONFIG.bit.PER = 0x2; // Set period for chip reset from the datasheet
    }
    else if(period >= 62.5 && period < 125){//64 clock cycles(64/1024 seconds)
    WDT->CONFIG.bit.PER = 0x3; // Set period for chip reset from the datasheet
    }
    else if(period >= 125 && period < 250){//128 clock cycles(128/1024 seconds)
    WDT->CONFIG.bit.PER = 0x4; // Set period for chip reset from the datasheet
    }
    else if(period >= 250 && period < 500){//256 clock cycles(256/1024 seconds)
    WDT->CONFIG.bit.PER = 0x5; // Set period for chip reset from the datasheet
    }
    else if(period >= 500 && period < 1000){//512 clock cycles(512/1024 seconds)
    WDT->CONFIG.bit.PER = 0x6; // Set period for chip reset from the datasheet
    }
    else if(period >= 1000 && period < 2000){//1024 clock cycles(1024/1024 seconds)
    WDT->CONFIG.bit.PER = 0x7; // Set period for chip reset from the datasheet
    }
    else if(period >= 2000 && period < 4000){//2048 clock cycles(2048/1024 seconds)
    WDT->CONFIG.bit.PER = 0x8; // Set period for chip reset from the datasheet
    }
    else if(period >=  4000 && period < 8000){//4096 clock cycles(4096/1024 seconds)
    WDT->CONFIG.bit.PER = 0x9; // Set period for chip reset from the datasheet
    }
    else if(period >= 8000 && period < 16000){//8192 clock cycles(8192/1024 seconds)
    WDT->CONFIG.bit.PER = 0xA; // Set period for chip reset from the datasheet
    }
    else if(period >= 16000){//16384 clock cycles(16384/1024 seconds)
    WDT->CONFIG.bit.PER = 0xB; // Set period for chip reset from the datasheet
    }
    else{}
  
  //WDT->CONFIG.bit.PER = period; // Set period for chip reset from the datasheet
//return;
  
}
