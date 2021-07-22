int latchPin = 9;  // Latch pin (STCP腳位)
int clockPin = 10; // Clock pin (SHCP腳位)
int dataPin = 11;  // Data pin (DS腳位) 
const int LED_PIN =  12; 
byte leds = 0;    // 亮燈的LED數量

void updateShiftRegister() //由左至右副程式 MSBFIRST
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
void updateright() //由右至左副程式 LSBFIRST
{
   digitalWrite(latchPin, HIGH);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, LOW);
}

void setup() 
{
  Serial.begin(9600);
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() 
{
  leds = 0; // 一開始燈全滅，所以設為0
  updateShiftRegister();  //進行送資料的副程式
  delay(500);
  for (int i = 0; i < 8; i++) //依序亮燈
  {
    bitSet(leds, i);    // 經由多少燈要亮的i，換算成10進位，並把結果交給leds
    updateShiftRegister(); //進行送資料的副程式
    delay(200);
    Serial.println("Test");
  }
  leds = 0;
  updateright(); //進行送資料的副程式
   for (int k = 0; k < 9; k++) //依序亮燈
  {
    bitSet(leds, k);    // 經由多少燈要亮的k，換算成10進位，並把結果交給leds
    updateright(); //進行送資料的副程式
    delay(200);
    Serial.println("Test2");
  }
}
