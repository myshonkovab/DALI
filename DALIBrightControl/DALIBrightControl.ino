#include <Dali.h>

const int DALI_TX = 13;
const int DALI_RX_A = A0;

void setup() {
  Serial.begin(9600);  //74880
  Serial.println("start");
  dali.setupTransmit(DALI_TX);         //устанавливаем цифровой выход для передачи сообщений
  dali.setupAnalogReceive(DALI_RX_A);  //устанавливаем аналоговый вход для приема сообщений
  dali.msgMode = true;                 //режим сообщений

  //dali.busTest();//тестируем шину
  //initLum(); // Инициализация световых приборов (присвоение коротких адресов?)
  //dali.initialisation(); // Запустить инициализацию.
}

void loop() {
  if (Serial.available()) {
    uint8_t adress = Serial.parseInt();
    uint8_t flux = Serial.parseInt();
    if (adress < 65) {
      dali.transmit((adress - 1) << 1, flux);
      Serial.println("Адрес: " + String(adress) + ". Поток: " + String(flux));
    }
  }
  delay(50);
}
