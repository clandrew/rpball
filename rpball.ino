#include "DEV_Config.h"
#include "LCD_1in69.h"

#define WHITE       0xFFFF
#define BLUE        0xF800
#define GREEN       0x001F
#define RED         0x07E0

UWORD gStaging[LCD_1IN69_WIDTH * LCD_1IN69_HEIGHT ];
const int ballDiam = 50;
int ballX = 50;
int ballY = 50;
int ballVX = 5;
int ballVY = 5;

void setup() 
{
  DEV_ModuleInit();
  LCD_1IN69_Init(VERTICAL);
}

void MoveBall()
{
  ballX += ballVX;
  if (ballX <= 0)
  {
    ballX = 0;
    ballVX = -ballVX;
  }
  if (ballX > LCD_1IN69_WIDTH-ballDiam-1)
  {
    ballX = LCD_1IN69_WIDTH-ballDiam-1;
    ballVX = -ballVX;
  }
  
  ballY += ballVY;
  if (ballY <= 0)
  {
    ballY = 0;
    ballVY = -ballVY;
  }
  if (ballY > LCD_1IN69_HEIGHT-ballDiam-1)
  {
    ballY = LCD_1IN69_HEIGHT-ballDiam-1;
    ballVY = -ballVY;
  }  
}

void DrawToStaging()
{
  // Clear the background to white
  for (int i=0; i<LCD_1IN69_WIDTH * LCD_1IN69_HEIGHT; ++i )
  {
    gStaging[i] = WHITE;
  }

  // Draw a red ball
  int centerX = (ballDiam / 2);
  int centerY = (ballDiam / 2);
  int ballRad = ballDiam / 2;
  int ballRadSq = ballRad * ballRad;
  for (int y=0; y<ballDiam; ++y)
  {
    for (int x=0; x<ballDiam; ++x)
    {
      int distFromCenterX = abs(x - centerX);
      int distFromCenterY = abs(y - centerY);
      int distSq = (distFromCenterX*distFromCenterX) + (distFromCenterY*distFromCenterY);
      if (distSq < ballRadSq)
      {
        int screenX = ballX + x;
        int screenY = ballY + y;
        gStaging[screenY*LCD_1IN69_WIDTH + screenX] = RED;
      }
    }
  }
}

void CopyStagingToScreen()
{
  uint8_t* rowStart = (uint8_t*)&gStaging;
  int pitch = LCD_1IN69_WIDTH * 2;

  LCD_1IN69_SetWindows(0, 0, LCD_1IN69.WIDTH, LCD_1IN69.HEIGHT);
  LCD_1IN69_DC_1;
  for (int j=0; j<LCD_1IN69.HEIGHT; j++) 
  {
    DEV_SPI_Write_nByte(rowStart, LCD_1IN69.WIDTH * 2);
    rowStart += pitch;
  }
}

// the loop function runs over and over again forever
void loop()
{
  MoveBall();
  DrawToStaging();
  CopyStagingToScreen();
  delay(50); // Wait this number of ms
}
