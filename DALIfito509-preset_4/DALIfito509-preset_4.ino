#include <Dali.h>

const int DALI_TX = 13;
const int DALI_RX_A = 0;

unsigned long timing;
//имя, адрес, поток

uint8_t adressFlux[33][2] = { // по факту адреса на единицу меньше, но в digidim такие стоят, поэтому не совсем корректно
// Боксы 1,2,3, Порядок цветов Белый, синий, красный, дальний красный(w,b,r,fr) 1 - у стены, 2 - ближний, 3 - центральный
// Кодовая запись бокс 1 белый у стены 1w1,

//Первый бокс
  // Светильник у стены
  {27, 222}, // 0 1fr1
  {30, 145}, // 1 1r1
  {26, 155},  // 2 1b1
  {14, 236},  // 3 1w1
  // Светильник по центру
  {3, 145}, // 4 1r3
  {7, 155},  // 5 1b3
  {4, 236}, // 6 1w3
  // Светильник ближний
  {15, 222},  // 7 1fr2 
  {8, 145},  // 8 1r2
  {11, 155},  // 9 1b2
  {29, 236},  // 10 1w2

// Второй бокс
  // Светильник у стены
  {13, 212}, // 11 2fr1
  {5, 174},  // 12 2r1
  {1, 148},  // 13 2b1
  {6, 235},  // 14 2w1
  // Светильник по центру
  {10, 174}, // 17 2r3
  {9, 148},  // 16 2b3
  {18, 235},  // 15 2w3
  // Светильник ближний
  {17, 212}, // 18 2fr2
  {2, 174},  // 19 2r2
  {12, 148}, // 20 2b2
  {16, 235}, // 21 2w2

// Третий бокс
  // Светильник у стены
  {32, 222}, // 22 3fr1
  {28, 0}, // 23 3r1
  {33, 148}, // 24 3b1
  {20, 228}, // 25 3w1
  // Светильник по центру
  {25, 0}, // 26 3r3
  {21, 148},  // 27 3b3
  {22, 228},  // 28 3w3
  // Светильник ближний
  {24, 222},  // 29 3fr2
  {31, 0},  // 30 3r2
  {19, 148},  // 31 3b2
  {23, 228},  // 32 3w2
};

/*

  uint8_t adress1 = 1;    uint8_t flux1 = 103; //бокс2 синий у стены
  uint8_t adress2 = 2;    uint8_t flux2 = 100; //бокс2 красный ближний
  uint8_t adress3 = 3;    uint8_t flux3 = 300; //бокс1 синий ближний
  uint8_t adress4 = 4;    uint8_t flux4 = 100; //бокс1 дальний красный ближний
  uint8_t adress5 = 5;    uint8_t flux5 = 200; //бокс2 красный у стены
  uint8_t adress6 = 6;    uint8_t flux6 = 205; //бокс2 белый у стены
  uint8_t adress7 = 7;    uint8_t flux7 = 202; //бокс1 синий у стены
  uint8_t adress8 = 8;    uint8_t flux8 = 205; //бокс1 красный у стены
  uint8_t adress9 = 13;    uint8_t flux9 = 201; //бокс1 красный ближний
  uint8_t adress10 = 10;  uint8_t flux10 = 200; //бокс1 белый у стены
  uint8_t adress11 = 11;  uint8_t flux11 = 205; //бокс2 синий ближний
  uint8_t adress12 = 12;  uint8_t flux12 = 200; //бокс1 белый ближний
*/

#define BROADCAST_C 0b11111111
#define BROADCAST_F 0b11111110
#define ON_C 0b00000101
#define MIN_C 0b00000110

void setup() {
  Serial.begin(9600); //74880
  Serial.println("start");
  //устанавливаем цифровой выход для передачи сообщений
  Serial.println(" dali.setupTransmit(DALI_TX);");
  dali.setupTransmit(DALI_TX);
  //устанавливаем аналоговый вход для приема сообщений
  Serial.println("dali.setupAnalogReceive(DALI_RX_A);");
  dali.setupAnalogReceive(DALI_RX_A);
  //тестируем шину
  // Serial.println("dali.busTest();");
  //dali.busTest();
  //режим сообщений
  Serial.println(" dali.msgMode = true;");
  dali.msgMode = true;
  // Serial.println(" sinus();");
  // initLum(); //
  //  sinus();


  for (byte i = 0; i < 33; i++) {
    dali.transmit((adressFlux[i][0] - 1) << 1, adressFlux[i][1]); delay(200);
  }
  /*dali.transmit(adress2 << 1, flux2); delay(200);
    dali.transmit(adress3 << 1, flux3); delay(200);
    dali.transmit(adress4 << 1, flux4); delay(200);
    dali.transmit(adress5 << 1, flux5); delay(200);
    dali.transmit(adress6 << 1, flux6); delay(200);
    dali.transmit(adress7 << 1, flux7); delay(200);
    dali.transmit(adress8 << 1, flux8); delay(200);
    dali.transmit(adress9 << 1, flux9); delay(200);
    dali.transmit(adress10 << 1, flux10); delay(200);
    dali.transmit(adress11 << 1, flux11); delay(200);
    dali.transmit(adress12 << 1, flux12); delay(200);

  */

  /* for (byte i = 0; i < 64; i++) {
     dali.transmit(i << 1, 0);
     delay(200);
    }
  */
}

void loop() {

  if (millis() - timing > 600000){
    timing = millis(); 
    dali.transmit((20 - 1) << 1, 228);
    delay(50);
    dali.transmit((22 - 1) << 1, 228);
    delay(50);
    dali.transmit((23 - 1) << 1, 228);
    delay(50);
    dali.transmit((28 - 1) << 1, 0);
    delay(50);
    dali.transmit((25 - 1) << 1, 0);
    delay(50);
    dali.transmit((31 - 1) << 1, 0);
    delay(50);
    dali.transmit((33 - 1) << 1, 148);
    delay(50);
    dali.transmit((21 - 1) << 1, 148);
    delay(50);
    dali.transmit((19 - 1) << 1, 148);
    delay(50);
    dali.transmit((32 - 1) << 1, 222);
    delay(50);
    dali.transmit((24 - 1) << 1, 222);
  }
  if (Serial.available()) {
    uint8_t adress = Serial.parseInt();
    uint8_t flux = Serial.parseInt();
    if (adress < 34) {
      Serial.println("Адрес: " + String(adress) + ". Поток: " + String(flux));
      dali.transmit((adress - 1) << 1, flux);
    }
    switch (adress) {
      //Красный канал в первом боксе
    case 34:
        Serial.println("Красный канал 1 бокс. Поток: " + String(flux));
        dali.transmit((30 - 1) << 1, flux);
        delay(50);
        dali.transmit((3 - 1) << 1, flux);
        delay(50);
        dali.transmit((8 - 1) << 1, flux);
        break;        
      //Синий канал в первом боксе  
    case 35:
        Serial.println("Синий канал 1 бокс. Поток: " + String(flux));
        dali.transmit((26 - 1) << 1, flux);
        delay(50);
        dali.transmit((7 - 1) << 1, flux);
        delay(50);
        dali.transmit((11 - 1) << 1, flux);
        break;  
      //Белый канал в первом боксе  
    case 36:
        Serial.println("Белый канал 1 бокс. Поток: " + String(flux));
        dali.transmit((14 - 1) << 1, flux);
        delay(50);
        dali.transmit((4 - 1) << 1, flux);
        delay(50);
        dali.transmit((29 - 1) << 1, flux);
        break; 
      //Дальний красный канал в первом боксе  
    case 37:
        Serial.println("Дальний красный канал 1 бокс. Поток: " + String(flux));
        dali.transmit((27 - 1) << 1, flux);
        delay(50);
        dali.transmit((15 - 1) << 1, flux);
        break;
      //Красный канал во втором боксе
    case 38:
        Serial.println("Красный канал 2 бокс. Поток: " + String(flux));
        dali.transmit((5 - 1) << 1, flux);
        delay(50);
        dali.transmit((10 - 1) << 1, flux);
        delay(50);
        dali.transmit((2 - 1) << 1, flux);
        break;        
      //Синий канал во втором боксе  
    case 39:
        Serial.println("Синий канал 2 бокс. Поток: " + String(flux));
        dali.transmit((1 - 1) << 1, flux);
        delay(50);
        dali.transmit((9 - 1) << 1, flux);
        delay(50);
        dali.transmit((12 - 1) << 1, flux);
        break;  
      //Белый канал во втором боксе  
    case 40:
        Serial.println("Белый канал 2 бокс. Поток: " + String(flux));
        dali.transmit((6 - 1) << 1, flux);
        delay(50);
        dali.transmit((18 - 1) << 1, flux);
        delay(50);
        dali.transmit((16 - 1) << 1, flux);
        break; 
      //Дальний красный канал во втором боксе  
    case 41:
        Serial.println("Дальний красный канал 2 бокс. Поток: " + String(flux));
        dali.transmit((13 - 1) << 1, flux);
        delay(50);
        dali.transmit((17 - 1) << 1, flux);
        break;
    case 42:
      //Красный канал в третьем боксе    
        Serial.println("Красный канал 3 бокс. Поток: " + String(flux));
        dali.transmit((28 - 1) << 1, flux);
        delay(50);
        dali.transmit((25 - 1) << 1, flux);
        delay(50);
        dali.transmit((31 - 1) << 1, flux);
        break;        
      //Синий канал в третьем боксе  
    case 43:
        Serial.println("Синий канал 3 бокс. Поток: " + String(flux));
        dali.transmit((33 - 1) << 1, flux);
        delay(50);
        dali.transmit((21 - 1) << 1, flux);
        delay(50);
        dali.transmit((19 - 1) << 1, flux);
        break;  
      //Белый канал в третьем боксе  
    case 44:
        Serial.println("Белый канал 3 бокс. Поток: " + String(flux));
        dali.transmit((20 - 1) << 1, flux);
        delay(50);
        dali.transmit((22 - 1) << 1, flux);
        delay(50);
        dali.transmit((23 - 1) << 1, flux);
        break; 
      //Дальний красный канал в третьем боксе  
    case 45:
        Serial.println("Дальний красный канал 3 бокс. Поток: " + String(flux));
        dali.transmit((32 - 1) << 1, flux);
        delay(50);
        dali.transmit((24 - 1) << 1, flux);
        break;
    }


    
    
    //dali.transmit(BROADCAST_F, flux);
    
  }
  //     dali.transmit(BROADCAST_C, ON_C);
  //     Serial.println("  dali.transmit(BROADCAST_C, ON_C);");
  //delay(5000);

  //     dali.transmit(BROADCAST_C, MIN_C);
  //      Serial.println("  dali.transmit(BROADCAST_C, MIN_C);");
  delay(50);
}
