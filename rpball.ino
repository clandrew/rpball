#include "DEV_Config.h"
#include "LCD_1in69.h"

#define WHITE       0xFFFF
#define BLUE        0xF800
#define GREEN       0x001F
#define RED         0x07E0

void setup() {
  DEV_ModuleInit();
  LCD_1IN69_Init(VERTICAL);
  LCD_1IN69_Clear(WHITE);
}

// the loop function runs over and over again forever
void loop()
{
  LCD_1IN69_Clear(WHITE);
  delay(500);   // wait half a second
}
