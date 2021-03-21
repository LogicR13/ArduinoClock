//-------------------------------------------//
//               Электронные часы
// ver. 0.2
// Первый запуск
//-------------------------------------------//

//подключение библиотек
#include <iarduino_RTC.h>

//опередение пинов
byte PIN_CLK = 6;
byte PIN_DAT = 7;
byte PIN_RST = 8;

//определение объектов
iarduino_RTC time(RTC_DS1302, PIN_RST,PIN_CLK,PIN_DAT);

//определение системного времени
const char* strMonth = "JanFebMarAprMayJunJulAugSepOctNovDec";
const char* sysT = __TIME__; // системное время
const char* sysD = __DATE__; // системная дата
// преобразование в массив всех данных
const int sysDateTime[6] {
              (sysT[6]-48)*10+(sysT[7]-48),
              (sysT[3]-48)*10+(sysT[4]-48),
              (sysT[0]-48)*10+(sysT[1]-48),
              (sysD[4]-48)*10+(sysD[5]-48),
              ((int)memmem(strMonth,36,sysD,3)+3-(int)&strMonth[0])/3,
              (sysD[9]-48)*10+(sysD[10]-48)
             };
              

void setup() {  
  delay(300); // задержка перед запуском
  Serial.begin(9600); // установка скорости обмена с портом
  Serial.println("Start");
  time.begin(); // запуск часов реального времени
  // установка согластно системному времени
  // [сек, мин, час, день, месяц, год, день недели);
  time.settime(sysDateTime[0],sysDateTime[1],sysDateTime[2],sysDateTime[3],sysDateTime[4],sysDateTime[5]);  
  
}

void loop() {
  if (millis() % 1000 == 0) {
    Serial.println(time.gettime("d-m-Y,H:i:s, D"));  
    
  }
}
