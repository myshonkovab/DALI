/*
маленькая плата первый вариант
чтоб можно было вставить просто в ардуино уно используем пины аналоговые в режимах:
А0 - не надо ипользовать
А1 - передача команд
А2 - Чтение команд
А3 - Земля
*/

#include <Dali.h>

#define BROADCAST_C 0b11111111
#define BROADCAST_F 0b11111110
#define ON_C 0b00000101
#define MIN_C 0b00000110

const int DALI_VCC = 14;   //A0
const int DALI_TX = 15;    //A1
const int DALI_RX_A = 16;  //A2
const int DALI_G = 17;     //A3

void setup() {
  Serial.begin(9600);  //74880
  pinMode(DALI_VCC, OUTPUT);
  pinMode(DALI_TX, OUTPUT);
  pinMode(DALI_G, OUTPUT);
  digitalWrite(DALI_VCC, HIGH);
  digitalWrite(DALI_G, LOW);


  Serial.println("start DALI control");
  dali.setupTransmit(DALI_TX);         //устанавливаем цифровой выход для передачи сообщений
  dali.setupAnalogReceive(DALI_RX_A);  //устанавливаем аналоговый вход для приема сообщений
  dali.msgMode = true;

  //режим сообщений

  dali.busTest();//тестируем шину
  //dali.initialisation(); // Запустить инициализацию.

  // dali.scanShortAdd();
}

void loop() {
  if (Serial.available()) {
    uint8_t adress = Serial.parseInt();
    uint8_t flux = Serial.parseInt();
    if (adress < 64) {
      dali.transmit((adress) << 1, flux);
      Serial.println("Адрес: " + String(adress) + ". Поток: " + String(flux));
    }
    if (adress == 64) {
      dali.transmit((adress-65) << 1, flux);
      Serial.println("Адрес: " + String(adress) + ". Поток: " + String(flux));
    }
  }
  delay(50);
}
