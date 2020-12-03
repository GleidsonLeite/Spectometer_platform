#include <Arduino.h>
#include "Screen.h"

Screen::Screen(bool Cooler_State)
{
  this->state_change_TFT = true;
  this->state_TFT = INIT_STATE;

  this->ts = new TouchScreen(XP, YP, XM, YM, 300);
  this->tft = new MCUFRIEND_kbv(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RST);

  this->Cooler_State = Cooler_State;
  this->oldCooler_State = Cooler_State;
}

void Screen::setCoolerState(bool state, bool old_state){
  this->Cooler_State = state;
  this->oldCooler_State = old_state;
}

void Screen::readResistiveTouch()
{
  this->tp = this->ts->getPoint();
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);
  digitalWrite(XM, HIGH);
}

bool Screen::ISPRESSED()
{
  int count = 0;
  bool state, oldState;

  while (count < 10)
  {
    this->readResistiveTouch();
    state = this->tp.z > 20;
    count = state == oldState ? count + 1 : 0;
    oldState = state;
    delay(5);
  }

  return oldState;
}

void Screen::print_TFT(const char *s, int size, int x, int y, uint16_t color)
{
  this->tft->setTextSize(size);
  this->tft->setCursor(x, y);
  this->tft->setTextColor(color);
  this->tft->print(s);
}

void Screen::button_TFT(const char *s, int size, int x, int y, uint16_t color, uint16_t colorBk)
{
  int len = strlen(s) * 6 * size;
  int xr = x - 13, yr = y - (7 * size), lenr = len + 26, sizer = 20 * size;
  this->tft->fillRoundRect(xr, yr, lenr, sizer, 5, colorBk);
  this->tft->drawRoundRect(xr, yr, lenr, sizer, 5, color);
  print_TFT(s, size, x, y, color);
}

void Screen::iconbutton_TFT(const char *s, const char *i, int x, int y, int size, uint16_t color, uint16_t colorBk)
{
  int len = strlen(s) * 6 * size;
  int xr = x - 13, yr = y - (7 * size), lenr = len + 26, sizer = 20 * size;
  this->tft->fillRoundRect(xr, yr, lenr, sizer, 5, colorBk);
  this->tft->drawRoundRect(xr, yr, lenr, sizer, 5, color);
  print_TFT(s, size, x, y, color);
  print_TFT(i, size + 1, x - (12 * size), y - (4 * size), color);
}

void Screen::buttonfill_TFT(const char *s, int x, int y, int size, uint16_t colorb, uint16_t colort)
{
  int len = strlen(s) * 6 * size;
  int xr = x - 13, yr = y - (7 * size), lenr = len + 26, sizer = 20 * size;
  this->tft->fillRoundRect(xr, yr, lenr, sizer, 5, colorb);
  print_TFT(s, size, x, y, colort);
}

void Screen::iconbuttonfill_TFT(const char *s, const char *i, int x, int y, int size, uint16_t colorb, uint16_t colort)
{
  int len = strlen(s) * 6 * size;
  int xr = x - 13, yr = y - (7 * size), lenr = len + 26, sizer = 20 * size;
  this->tft->fillRoundRect(xr, yr, lenr, sizer, 5, colorb);
  print_TFT(s, size, x, y, colort);
  print_TFT(i, size + 1, x - (12 * size), y - (4 * size), colort);
}

void Screen::centerprint(const char *s, int y, int size, uint16_t color) {
  int len = strlen(s) * 6 * size;
  print_TFT(s, size, (dispx - len) / 2, y, color);
}

void Screen::centerprint(const char *s, int y, int size, uint16_t color, int disp) {
  int len = strlen(s) * 6 * size;
  print_TFT(s, size, (disp - len) / 2, y, color);
}

void Screen::centerprint(const char *s, int y, int size, uint16_t color, int disp, int mapValue) {
  int len = strlen(s) * 6 * size;
  print_TFT(s, size, map((disp - len) / 2, 0, disp, disp, mapValue), y, color);
}

void Screen::centerbutton(const char *s, int y, int size, uint16_t color, uint16_t colorBk) {
  int len = strlen(s) * 6 * size;
  int x = (dispx - len) / 2;
  int xr = x - 13, yr = y - (7 * size), lenr = len + 26, sizer = 20 * size;
  this->tft->fillRoundRect(xr, yr, lenr, sizer, 5, colorBk);
  this->tft->drawRoundRect(xr, yr, lenr, sizer, 5, color);
  print_TFT(s, size, x, y, color);
}

void Screen::centerbuttonfill(const char *s, int y, int size, uint16_t colorb, uint16_t colort) {
  int len = strlen(s) * 6 * size;
  int x = (dispx - len) / 2;
  int xr = x - 13, yr = y - (7 * size), lenr = len + 26, sizer = 20 * size;
  this->tft->fillRoundRect(xr, yr, lenr, sizer, 5, colorb);
  print_TFT(s, size, x, y, colort);
}

void Screen::backButton(boolean pushed) {
  if (pushed) {
    iconbuttonfill_TFT(BACK_BTN_TEXT, BACK_BTN_ICON, BACK_BTN_X, BACK_BTN_Y,  BACK_BTN_SIZE, BACK_BTN_COLOR, BACK_BTN_COLOR_PUSHED);
  } else {
    iconbutton_TFT(BACK_BTN_TEXT, BACK_BTN_ICON, BACK_BTN_X, BACK_BTN_Y, BACK_BTN_SIZE, BACK_BTN_COLOR, BACK_BTN_COLOR_PUSHED);
  }
}

void Screen::DHTbutton(boolean pushed) {
  if (pushed) {
    centerbutton(DHT_BTN_TEXT, DHT_BTN_Y, DHT_BTN_SIZE, DHT_BTN_COLOR, DHT_BTN_COLOR_PUSHED);
  } else {
    centerbuttonfill(DHT_BTN_TEXT, DHT_BTN_Y, DHT_BTN_SIZE, DHT_BTN_COLOR, DHT_BTN_COLOR_PUSHED);
  }
}

void Screen::LOXbutton(boolean pushed) {
  if (pushed) {
    centerbutton(LOX_BTN_TEXT, LOX_BTN_Y, LOX_BTN_SIZE, LOX_BTN_COLOR, LOX_BTN_COLOR_PUSHED);
  } else {
    centerbuttonfill(LOX_BTN_TEXT, LOX_BTN_Y, LOX_BTN_SIZE, LOX_BTN_COLOR, LOX_BTN_COLOR_PUSHED);
  }
}

void Screen::coolerButton(boolean pushed) {
  if (pushed) {
    centerbutton(Cooler_State ? COOLER_BTN_TEXT_ON : COOLER_BTN_TEXT_OFF, COOLER_BTN_Y, COOLER_BTN_SIZE, COOLER_BTN_COLOR, COOLER_BTN_COLOR_PUSHED);
  } else {
    centerbuttonfill(Cooler_State ? COOLER_BTN_TEXT_ON : COOLER_BTN_TEXT_OFF, COOLER_BTN_Y, COOLER_BTN_SIZE, COOLER_BTN_COLOR, COOLER_BTN_COLOR_PUSHED);
  }
}

void Screen::printfooter() {
  centerprint("MOSSORO 2020", 232, 1, WHITE);
}

void Screen::printHeader() {
  this->tft->fillRect(0, 0, dispx, 32, RED);
  centerprint("PLATAFORMA", 6, 3, WHITE);
}

void Screen::presentationScreen_TFT() {

  // IMPRIMI LOGO DA UFERSA
  this->tft->fillRect(0, 0, dispx, 10, GREEN);
  centerprint("UNIVERSIDADE FEDERAL", 1, 1, WHITE);
  this->tft->fillRect(0, 11, dispx, 40, WHITE);
  centerprint("UFERSA", 17, 4, BLUE);
  this->tft->fillRect(0, 52, dispx, 10, GREEN);
  centerprint("RURAL DO SEMI-ARIDO", 53, 1, WHITE);
  // FIM LOGO DA UFERSA 62 Y

  // TÍTULO DO TRABALHO
  centerprint("PLATAFORMA AUTOMATIZADA", 70, 2, WHITE);
  centerprint("PARA SENSOR BASEADO NA", 88, 2, WHITE);
  centerprint("RESSONANCIA DE PLASMONS", 106, 2, WHITE);
  centerprint("DE SUPERFICIE", 124, 2, WHITE);
  // FIM TÍTULO DO TRABALHO 150

  print_TFT("DISCENTE: FRANCISCO JOSIRAN", 1, 2, 180, WHITE);
  print_TFT("ORIENTADOR: LEIVA CASEMIRO", 1, 2, 190, WHITE);

  printfooter();
}

void Screen::changeState_TFT(int state) {
  state_change_TFT = true;
  state_TFT = state;
}

void Screen::LOXprintHeaders() {
  int disp = dispx / 2;
  // Linhas separadoras
  this->tft->drawFastHLine(LOX_HLINE_X, LOX_HLINE_Y, dispx - (LOX_HLINE_X * 2), LINE_COLOR);
  this->tft->drawFastVLine(disp, LOX_VLINE_YS, dispy - (LOX_VLINE_YS + LOX_VLINE_YF), LINE_COLOR);

  // Cabeçalhos
  centerprint("L. Prisma", LOX_TEXT_Y1, TEXT_SIZE, TEXT_COLOR, disp);
  centerprint("L. Camera", LOX_TEXT_Y1, TEXT_SIZE, TEXT_COLOR, disp, dispx);
  centerprint("L. Cilind", LOX_TEXT_Y2, TEXT_SIZE, TEXT_COLOR, disp);
  centerprint("L. Colima", LOX_TEXT_Y2, TEXT_SIZE, TEXT_COLOR, disp, dispx);
}

void Screen::LOXprintValues(uint16_t Measure_Pri_now, uint16_t Measure_Cam_now, uint16_t Measure_LCi_now, uint16_t Measure_LCo_now) {
  int disp = dispx / 2;

  String value = "";
  value = value + Measure_Pri_now + "mm";
  centerprint(value.c_str(), LOX_Y1, LOX_SIZE, TEXT_COLOR, disp);

  value = "";
  value = value + Measure_Cam_now + "mm";
  centerprint(value.c_str(), LOX_Y1, LOX_SIZE, TEXT_COLOR, disp, dispx);

  value = "";
  value = value + Measure_LCi_now + "mm";
  centerprint(value.c_str(), LOX_Y2, LOX_SIZE, TEXT_COLOR, disp);

  value = "";
  value = value + Measure_LCo_now + "mm";
  centerprint(value.c_str(), LOX_Y2, LOX_SIZE, TEXT_COLOR, disp, dispx);
}

void Screen::DHTprintHeaders(){
  // Linha separadora
  this->tft->drawFastHLine(DHT_LINE_X, DHT_LINE_Y, dispx - (DHT_LINE_X * 2), LINE_COLOR);

  // Cabeçalhos
  centerprint("TEMPERATURA", TEMP_TEXT_Y, TEXT_SIZE, TEXT_COLOR);
  centerprint("HUMIDADE", HUM_TEXT_Y, TEXT_SIZE, TEXT_COLOR);
}

void Screen::DHTprintValues(float TempC_DHT, float Hum_DHT) {
  String value = "";
  value = value + TempC_DHT + " C";
  centerprint(value.c_str(), TEMP_Y, TEMP_SIZE, TEXT_COLOR);
  value = "";
  value = value + Hum_DHT;
  centerprint(value.c_str(), HUM_Y, HUM_SIZE, TEXT_COLOR);
}

void Screen::setup() {

  setMeasure_Pri_now(0);
  setMeasure_Cam_now(0);
  setMeasure_LCi_now(0);
  setMeasure_LCo_now(0);
  setTempC_DHT(0);
  setHum_DHT(0);

  this->tft->reset();
  delay(500);
  Serial.print("TFT ID: Ox");
  uint16_t ID = this->tft->readID();
  Serial.println(ID,  HEX);
  this->tft->begin(ID);
  this->tft->fillScreen(BLACK);
  this->tft->setRotation(TOUCH_ORIENTATION);

  dispx = this->tft->width();
  dispy = this->tft->height();
  text_y_center = (dispy / 2) - 6;

  presentationScreen_TFT();
  delay(3000);
}

void Screen::touchFlow(void (*switch_CoolerState)(), void (*requestInfo)(byte option)) {
  if (ISPRESSED()) // touch confirmado
  {
    // Tratamento do ponto
    if (TOUCH_ORIENTATION == LANDSCAPE) {
      uint16_t tempx = tp.x;
      tp.x = this->tft->width() - (map(tp.y, TS_LEFT_LAND, TS_RIGHT_LAND, this->tft->width(), 0));
      tp.y = this->tft->height() - (map(tempx, TS_TOP_LAND, TS_BOT_LAND, this->tft->height(),0));
    } else {
      tp.x = this->tft->width() - (map(tp.x, TS_LEFT_PORT, TS_RIGHT_PORT, this->tft->width(), 0));
      tp.y = this->tft->height() - (map(tp.y, TS_TOP_PORT, TS_BOT_PORT, this->tft->height(),0));
    }

    // for debug
    Serial.print("px: ");
    Serial.print(tp.x);
    Serial.print("  py: ");
    Serial.println(tp.y);

    if (state_TFT != MAIN_STATE_TFT) {
      if ((tp.y >= BACK_BTN_Y1 && tp.y <= BACK_BTN_Y2) && (tp.x >= BACK_BTN_X1 && tp.x <= BACK_BTN_X2)) {
        // back button foi pressionado
        changeState_TFT(MAIN_STATE_TFT);
        backButton(true);
        delay(BTN_DELAY);
      }
    } else {
      if ((tp.y >= DHT_BTN_Y1 && tp.y <= DHT_BTN_Y2) && (tp.x >= DHT_BTN_X1 && tp.x <= DHT_BTN_X2)) {
        // dht button foi pressionado
        changeState_TFT(DHT_STATE_TFT);
        DHTbutton(true);
        delay(BTN_DELAY);
        (*requestInfo)(2);
      } else if ((tp.y >= LOX_BTN_Y1 && tp.y <= LOX_BTN_Y2) && (tp.x >= LOX_BTN_X1 && tp.x <= LOX_BTN_X2)) {
        // lox button foi pressionado
        changeState_TFT(LOX_STATE_TFT);
        LOXbutton(true);
        delay(BTN_DELAY);
        (*requestInfo)(1);
      } else if ((tp.y >= COOLER_BTN_Y1 && tp.y <= COOLER_BTN_Y2) && (tp.x >= COOLER_BTN_X1 && tp.x <= COOLER_BTN_X2)) {
        // COOLER button foi pressionado
        coolerButton(true);
        delay(BTN_DELAY);
        while(ISPRESSED()) {} // esperar soltar
        (*switch_CoolerState)();
        (*requestInfo)(3);
      }
    }
  }
}

void Screen::drawFlow() {
  if (state_change_TFT) {
    state_change_TFT = false;
    this->tft->fillScreen(BLACK);
    printHeader();
    printfooter();
    if (state_TFT != MAIN_STATE_TFT) {
      backButton(false);
      switch (state_TFT)
      {
        case LOX_STATE_TFT:
          LOXprintHeaders();
          break;
        case DHT_STATE_TFT:
          DHTprintHeaders();
          break;
      }

    } else {
      LOXbutton(false);
      DHTbutton(false);
      if ((oldCooler_State != Cooler_State)) oldCooler_State = Cooler_State;
      coolerButton(false);
    }
  }
  if ((state_TFT == MAIN_STATE_TFT && (oldCooler_State != Cooler_State))) {
    oldCooler_State = Cooler_State;
    coolerButton(false);
  }

  switch (state_TFT)
  {
    case LOX_STATE_TFT:
      LOXprintValues(this->Measure_Pri_now, this->Measure_Cam_now, this->Measure_LCi_now, this->Measure_LCo_now);
      break;
    case DHT_STATE_TFT:
      DHTprintValues(this->TempC_DHT, this->Hum_DHT);
      break;
  }
}

void Screen::setMeasure_Pri_now(uint16_t Measure_Pri_now){this->Measure_Pri_now = Measure_Pri_now;}
void Screen::setMeasure_Cam_now(uint16_t Measure_Cam_now){this->Measure_Cam_now = Measure_Cam_now;}
void Screen::setMeasure_LCi_now(uint16_t Measure_LCi_now){this->Measure_LCi_now = Measure_LCi_now;}
void Screen::setMeasure_LCo_now(uint16_t Measure_LCo_now){this->Measure_LCo_now = Measure_LCo_now;}
void Screen::setTempC_DHT(uint16_t TempC_DHT){this->TempC_DHT = TempC_DHT;}
void Screen::setHum_DHT(uint16_t Measure_Pri_now){this->Measure_Pri_now = Measure_Pri_now;}
