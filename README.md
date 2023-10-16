# DALI
Настройка

void setup() {
Serial.begin(74880); 
/*
Задаем цифровой выход.
*/
dali.setupTransmit(3); 

/*
Задаем аналоговый вход. 
Применяется блок питания большой мощности (12В 2,1А) 
и светильники не могут просадить напряжение до 0В. 
В моем случае логическая единица соответствует напряжению 4,5В, 
а логический нуль соответствует напряжению 3,8В.
*/
dali.setupAnalogReceive(0); 

/* 
Тестирование шины:
- светильники должны выключиться и включиться;
- определяется среднее значение между логическим нулем  и единицей.
*/
dali.busTest();  

/* 
Режим сообщений, передаваемых по-COM порту
false - передаются только ответы от светильников;
true - предается вся информации с комментариями.
*/
dali.msgMode = true; 

} 

Основные команды

/*
Передача информации от DALI контроллера, где:
cmd1 - адресный байт;
cmd2 - байт команды.
*/
dali.transmit(cmd1, cmd2) 

/*
Получить ответ от светильника
*/
uint8_t response = dali.receive()

/*
Проверка получения ответа
*/
bool response = dali.getResponse()

/*
Сканировать короткие адреса. 
*/
dali.scanShortAdd() 

/*
Запустить инициализацию.
*/
dali.initialisation(); 

Пример использования

Ниже приводится пример использования библиотеки. Комбинируя яркости различных каналов светильника, мы получаем разные цвета.


#include <Dali.h>

const int DALI_TX = 3;
const int DALI_RX_A = 0;
#define BROADCAST_C 0b11111111
#define ON_C 0b00000101

void setup() {
  Serial.begin(74880);
  //устанавливаем цифровой выход для передачи сообщений
  dali.setupTransmit(DALI_TX);
  //устанавливаем аналоговый вход для приема сообщений
  dali.setupAnalogReceive(DALI_RX_A);
  //тестируем шину
  dali.busTest();
  //режим сообщений
  dali.msgMode = true;
  sinus();
  }

void sinus () {
  // задаем адреса светильников
  uint8_t lf_1_add = 0;
  uint8_t lf_2_add = 1;
  uint8_t lf_3_add = 2;
  // переменные для значений яркости каждого светильника
  uint8_t lf_1;
  uint8_t lf_2;
  uint8_t lf_3;
  // счетчик
  uint8_t i;

  while (Serial.available() == 0) {
    for (i = 0; i < 360; i ++) {
        //выход из цикла
        if (Serial.available() != 0) {
        dali.transmit(BROADCAST_C, ON_C);
        break;
      }
      //определяем значение яркости
      lf_1 = (int) abs(254 * sin(i * 3.14 / 180));
      lf_2 = (int) abs(254 * sin(i * 3.14 / 180 + 2 * 3.14 / 3));
      lf_3 = (int) abs(254 * sin(i * 3.14 / 180 + 1 * 3.14 / 3));
      //задаем яркость      
      dali.transmit(lf_1_add << 1, lf_1);
      delay(5);
      dali.transmit(lf_2_add << 1, lf_2);
      delay(5);
      dali.transmit(lf_3_add << 1, lf_3);
      delay(5);
      delay(20);
    }
  }
}

void loop() {

};

Источник: https://habr.com/ru/articles/321888/
