#ifndef SCREEN_H
#define SCREEN_H
#ifndef ARDUINO_H
#define ARDUINO_H

#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

// PINAGEM
// https://blog.baudaeletronica.com.br/display-lcd-tft-no-arduino-mega/
#define YP A1 // Y+ is on Analog1 (use A3 para o 9341)
#define XM A2 // X- is on Analog2 (use A2 para o 9341)
// A3, A2, A1, A0, A4
#define XP 6 // X+ is on Digital2 (use 8 para o 9341)
#define YM 7 // Y- is on Digital3 (use 9 para o 9341)

#define LCD_CS A3
#define LCD_RS A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RST 1


// CONFIGURAÇÃO TFT
#define TS_LEFT_PORT 917
#define TS_RIGHT_PORT 171
#define TS_TOP_PORT 154
#define TS_BOT_PORT 906

#define TS_LEFT_LAND 168 // NÃO MEXA
#define TS_RIGHT_LAND 916 // NÃO MEXA
#define TS_TOP_LAND 171
#define TS_BOT_LAND 917

#define PORTRAIT  0
#define LANDSCAPE 1
#define TOUCH_ORIENTATION LANDSCAPE

// Cores TFT
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F

// ESTADOS DO TFT
#define MAIN_STATE_TFT 0
#define DHT_STATE_TFT 1
#define LOX_STATE_TFT 2
#define INIT_STATE MAIN_STATE_TFT

// SETUP BOTÕES TFT

// global
#define BTN_DELAY 250

// back button
#define BACK_BTN_SIZE 1
#define BACK_BTN_X 16
#define BACK_BTN_Y 13
#define BACK_BTN_COLOR WHITE
#define BACK_BTN_COLOR_PUSHED RED
#define BACK_BTN_TEXT "VOLTAR"
#define BACK_BTN_ICON "<"
#define BACK_BTN_X1 3
#define BACK_BTN_X2 60
#define BACK_BTN_Y1 6
#define BACK_BTN_Y2 24

// LOX button
#define LOX_BTN_SIZE 2
#define LOX_BTN_Y 70
#define LOX_BTN_COLOR WHITE
#define LOX_BTN_COLOR_PUSHED BLACK
#define LOX_BTN_TEXT "SENSORES DE DISTANCIA"
#define LOX_BTN_X1 20
#define LOX_BTN_X2 300
#define LOX_BTN_Y1 55
#define LOX_BTN_Y2 95

// DHT button
#define DHT_BTN_SIZE 2
#define DHT_BTN_Y 120
#define DHT_BTN_COLOR WHITE
#define DHT_BTN_COLOR_PUSHED BLACK
#define DHT_BTN_TEXT "TEMPERATURA E UMIDADE"
#define DHT_BTN_X1 20
#define DHT_BTN_X2 300
#define DHT_BTN_Y1 105
#define DHT_BTN_Y2 145

// cooler button
#define COOLER_BTN_SIZE 2
#define COOLER_BTN_Y 170
#define COOLER_BTN_COLOR WHITE
#define COOLER_BTN_COLOR_PUSHED BLACK
#define COOLER_BTN_TEXT_ON  "DESLIGAR COOLER"
#define COOLER_BTN_TEXT_OFF " LIGAR  COOLER "
#define COOLER_BTN_X1 52
#define COOLER_BTN_X2 260
#define COOLER_BTN_Y1 155
#define COOLER_BTN_Y2 195

// Infos TFT

// GLOBAIS
#define TEXT_COLOR WHITE
#define TEXT_SIZE 2
#define LINE_COLOR WHITE

// temperatura e humidade
#define TEMP_SIZE 4
#define TEMP_TEXT_Y 40
#define TEMP_Y 75

#define HUM_SIZE 4
#define HUM_TEXT_Y 140
#define HUM_Y 175
// linha separadora DHT
#define DHT_LINE_Y 130
#define DHT_LINE_X 60

// LOX
#define LOX_SIZE 4
#define LOX_TEXT_Y1 40
#define LOX_TEXT_Y2 140
#define LOX_Y1 75
#define LOX_Y2 175
// linhas separadoras LOX
#define LOX_HLINE_X 4
#define LOX_HLINE_Y 130
#define LOX_VLINE_YS 35 // start
#define LOX_VLINE_YF 11 // finish


class Screen
{
private:
  MCUFRIEND_kbv *tft;
  TouchScreen *ts;
  TSPoint tp;

  float px, py;
  int dispx, dispy, text_y_center;
  bool state_change_TFT;
  bool Cooler_State;
  bool oldCooler_State;
  int state_TFT;

  uint16_t Measure_Pri_now;
  uint16_t Measure_Cam_now;
  uint16_t Measure_LCi_now;
  uint16_t Measure_LCo_now;
  float TempC_DHT;
  float Hum_DHT;

public:
  Screen(bool Cooler_State);
  void setup();
  void flow();
  // https://forum.arduino.cc/index.php?topic=83211.0
  void touchFlow(void (*)(), void (*)(byte option));
  void drawFlow();

  void setCoolerState(bool state);

  void readResistiveTouch();
  bool ISPRESSED();
  void print_TFT(const char *s, int size, int x, int y, uint16_t color);
  void button_TFT(const char *s, int size, int x, int y, uint16_t color, uint16_t colorBk);
  void iconbutton_TFT(const char *s, const char *i, int x, int y, int size, uint16_t color, uint16_t colorBk);
  void buttonfill_TFT(const char *s, int x, int y, int size, uint16_t colorb, uint16_t colort);
  void iconbuttonfill_TFT(const char *s, const char *i, int x, int y, int size, uint16_t colorb, uint16_t colort);
  void centerprint(const char *s, int y, int size, uint16_t color);
  void centerprint(const char *s, int y, int size, uint16_t color, int disp);
  void centerprint(const char *s, int y, int size, uint16_t color, int disp, int mapValue);
  void centerbutton(const char *s, int y, int size, uint16_t color, uint16_t colorBk);
  void centerbuttonfill(const char *s, int y, int size, uint16_t colorb, uint16_t colort);
  void backButton(boolean pushed);
  void DHTbutton(boolean pushed);
  void LOXbutton(boolean pushed);
  void coolerButton(boolean pushed);
  void printfooter();
  void printHeader();
  void presentationScreen_TFT();
  void changeState_TFT(int state);
  void LOXprintHeaders();
  void LOXprintValues(uint16_t Measure_Pri_now, uint16_t Measure_Cam_now, uint16_t Measure_LCi_now, uint16_t Measure_LCo_now);
  void DHTprintHeaders();
  void DHTprintValues(float TempC_DHT, float Hum_DHT);

  void setMeasure_Pri_now(uint16_t Measure_Pri_now);
  void setMeasure_Cam_now(uint16_t Measure_Cam_now);
  void setMeasure_LCi_now(uint16_t Measure_LCi_now);
  void setMeasure_LCo_now(uint16_t Measure_LCo_now);
  void setTempC_DHT(float TempC_DHT);
  void setHum_DHT(float Measure_Pri_now);

};


#endif
#endif
