#include "DEV_Config.h"
#include "LCD_1in69.h"

// The color format is RGB565. bbbb bxxx xxxx xxxx
#define WHITE       0xFFFF
#define RED         0x07E0
#define GREEN       0x001F
#define BLUE        0xF800

#define BUTTON1_PIN 14
UWORD gStaging[LCD_1IN69_WIDTH * LCD_1IN69_HEIGHT ];
const int ballDiam = 50;
int ballX = 50;
int ballY = 50;
int ballVX = 5;
int ballVY = 5;
int ballColorIndex = 0;

void InitializeButton(uint gpio)
{
  // The buttons use pull-up resistors
  gpio_init(gpio);
  gpio_set_dir(gpio, GPIO_IN);
  gpio_pull_up(gpio);
}

void setup() 
{
  DEV_ModuleInit();
  LCD_1IN69_Init();

  InitializeButton(BUTTON1_PIN);
}

static const UWORD colors[] = {RED, GREEN, BLUE };
void IncrementBallColor()
{
  ballColorIndex = (ballColorIndex + 1) % count_of(colors);
}

UWORD GetBallColor()
{
  return colors[ballColorIndex];
}

void MoveBall()
{
  // Horizontal
  ballX += ballVX;
  if (ballX <= 0)
  {
    ballX = 0;
    ballVX = -ballVX;
    IncrementBallColor();
  }
  if (ballX > LCD_1IN69_WIDTH-ballDiam-1)
  {
    ballX = LCD_1IN69_WIDTH-ballDiam-1;
    ballVX = -ballVX;
    IncrementBallColor();
  }
  
  // Vertical
  ballY += ballVY;
  if (ballY <= 0)
  {
    ballY = 0;
    ballVY = -ballVY;
    IncrementBallColor();
  }
  if (ballY > LCD_1IN69_HEIGHT-ballDiam-1)
  {
    ballY = LCD_1IN69_HEIGHT-ballDiam-1;
    ballVY = -ballVY;
    IncrementBallColor();
  }  
}

void DrawToStaging()
{
  // Clear the background to white
  for (int i=0; i<LCD_1IN69_WIDTH * LCD_1IN69_HEIGHT; ++i )
  {
    gStaging[i] = WHITE;
  }

  // Draw a colored ball
  UWORD ballColor = GetBallColor();

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
        gStaging[screenY*LCD_1IN69_WIDTH + screenX] = ballColor;
      }
    }
  }
}

void CopyStagingToScreen()
{
  LCD_1IN69_SetWindows(0, 0, LCD_1IN69_WIDTH, LCD_1IN69_HEIGHT);
  DEV_Digital_Write(LCD_DC,1);
  DEV_SPI_Write_nByte((uint8_t*)&gStaging, LCD_1IN69_WIDTH * LCD_1IN69_HEIGHT * 2);
}

// the loop function runs over and over again forever
void loop()
{
  MoveBall();
  DrawToStaging();
  CopyStagingToScreen();

  if (!gpio_get(BUTTON1_PIN)) 
  {
      IncrementBallColor();
  }
  
  delay(50); // Wait this number of ms
}
