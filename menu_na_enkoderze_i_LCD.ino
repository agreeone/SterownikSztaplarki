//16x2 LCD
#include <LiquidCrystal_I2C.h> //SDA = A4, SCL = A5
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int Pin1 = 8;
const int PinOut1 = 9;
//Defining pins for rotary encoder
const int RotaryCLK = 2; //CLK pin on the rotary encoder
const int RotaryDT = 3; //DT pin on the rotary encoder
const int RotarySW = 4; //SW pin on the rotary encoder (Button function)
#define PIN_ROTARY_5V 5
#define PIN_ROTARY_GND 6

//Defining variables for rotary encoder and button
int ButtonCounter = 0; //counts the button clicks
int RotateCounter = 0; //counts the rotation clicks
bool rotated = true; //info of the rotation
bool ButtonPressed = false; //info of the button

//Statuses
int CLKNow;
int CLKPrevious;
int DTNow;
int DTPrevious;
int zadana1=0;
int zadana2;
int a=0;
int b=0;
int c=0;
int d=0;

// Timers
float TimeNow1;
float TimeNow2;

//LED things
//digital pins
const int whiteLED = 8;
const int blueLED = 9;
const int greenLED = 10;
const int yellowLED = 11;
const int redLED = 12;
//statuses (1/true: ON, 0/false: OFF)
bool whiteLEDStatus = false;
bool blueLEDStatus = false;
bool greenLEDStatus = false;
bool yellowLEDStatus = false;
bool redLEDStatus = false;
//------------------------------

//Drawing of the LCD layout
//W  B  G  Y  R   CLK
//0  0  0  0  0    1
int impuls;
int lastImpuls;
int licznik = 0;
int aaa=1;
int bbb;
  int RotateCounter2;
void setup()
{
Serial.begin(9600);

pinMode(Pin1, INPUT);
pinMode(PinOut1, OUTPUT);
pinMode(PIN_ROTARY_5V, OUTPUT);
pinMode(PIN_ROTARY_GND, OUTPUT);


digitalWrite(PIN_ROTARY_GND, LOW);
digitalWrite(PIN_ROTARY_5V, HIGH);


digitalWrite(PinOut1, HIGH);
    //Serial.begin(9600); //we don't use the serial in this example
  
  //------------------------------------------------------
  lcd.begin();                      // initialize the lcd   
  lcd.backlight();
  //------------------------------------------------------
  lcd.setCursor(0,0); //Defining position to write from first row, first column .
  lcd.print("A   B      CLK");
  lcd.setCursor(0,1); //second line, 1st block
  lcd.print("0   0       0"); //You can write 16 Characters per line .
  delay(3000); //wait 3 sec
  //------------------------------------------------------
   //setting up pins  
   pinMode(2, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);
   pinMode(4, INPUT_PULLUP);

   pinMode(whiteLED, OUTPUT); //white LED
   pinMode(blueLED, OUTPUT); //blue LED
   pinMode(greenLED, OUTPUT); //green LED
   pinMode(yellowLED, OUTPUT); //yellow LED
   pinMode(redLED, OUTPUT); //red LED
  
  //LOW pins = LEDs are off. (LED + is connected to the digital pin)
   digitalWrite(whiteLED, LOW);
   digitalWrite(blueLED, LOW);
   digitalWrite(greenLED, LOW);
   digitalWrite(yellowLED, LOW);
   digitalWrite(redLED, LOW);
   
digitalWrite(PinOut1, HIGH);
  //Store states
  CLKPrevious = digitalRead(RotaryCLK);
  DTPrevious = digitalRead(RotaryDT);
    
  attachInterrupt(digitalPinToInterrupt(RotaryCLK), rotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RotarySW), buttonPressed, FALLING); //either falling or rising but never "change".
  attachInterrupt(digitalPinToInterrupt(Pin1), impuls, FALLING);
  TimeNow1 = millis(); //Start timer 1  
}


void loop()
{
  printLCD();
  ButtonChecker();
   
impuls = digitalRead(Pin1);
if(impuls != lastImpuls)
{
licznik++;
}
if(licznik>20)licznik=0;   //zabieg konwertujacy licznik aby były uwzglednione podwujne impulsy z czujnika
lastImpuls = impuls;
Serial.println(licznik);



if ((a == licznik) && (aaa == 1))
{
  digitalWrite(PinOut1, LOW);
  delay(300);
  digitalWrite(PinOut1, HIGH);
  aaa=0;
  bbb=1;
  licznik = 0;

}

if ((b == licznik) && (bbb == 1))
{
  digitalWrite(PinOut1, LOW);
  delay(300);
  digitalWrite(PinOut1, HIGH);
  aaa=1;
  bbb=0;
  licznik = 0;

}

  if(Pin1 == HIGH)
  {
    impuls++;
  }
}

void buttonPressed()
{  
  //This timer is a "software debounce". It is not the most effective solution, but it works
  TimeNow2 = millis();
  if(TimeNow2 - TimeNow1 > 500)
  {    
    ButtonPressed = true;

  }
  TimeNow1 = millis();  //"reset" timer; the next 500 ms is counted from this moment
zadana1++;

}

void rotate()
{
  CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin

  // If last and current state of CLK are different, then a pulse occurred  
    if (CLKNow != CLKPrevious  && CLKNow == 1)
    {
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so increase
      if (digitalRead(RotaryDT) != CLKNow) 
      {        
      RotateCounter++; 

      if(RotateCounter > 10)
      {
       RotateCounter = 1;
      }

      }
      else
      {        
      RotateCounter--;
            
      if(RotateCounter < 1)
      {
        RotateCounter = 10;  
      }   
        
      }       
    }   

  CLKPrevious = CLKNow;  // Store last CLK state
  rotated = true;
}


void printLCD()
{

    if(rotated == true) //refresh the CLK
    {
      lcd.print("                ");
      lcd.setCursor(12,1); 
      RotateCounter2=RotateCounter*2;//zabieg konwertujacy licznik aby były uwzglednione podwujne impulsy z czujnika
    
      lcd.print(RotateCounter);

      rotated = false;
    }
    
}


void ButtonChecker() //this is basically the menu part. keep track of the buttonpressed and rotatecounter for navigation
{
  if(digitalRead(RotarySW) == LOW)
  {
    switch(zadana1)
    {
      case 0:      

  a=RotateCounter2;    //zabieg konwertujacy licznik aby były uwzglednione podwujne impulsy z czujnika
  lcd.setCursor(0,1);
c=a*0.5;   //zabieg konwertujacy licznik aby były uwzglednione podwujne impulsy z czujnika
  lcd.print(c);   
  zadana1++;  
  
      break;
      
      case 1:

  b=RotateCounter2;  //zabieg konwertujacy licznik aby były uwzglednione podwujne impulsy z czujnika
d=b*0.5;   //zabieg konwertujacy licznik aby były uwzglednione podwujne impulsy z czujnika
  lcd.setCursor(4,1); 

  lcd.print(d);


      break;
      
//      case 2:
//      if(greenLEDStatus == false)
//      {
 //       greenLEDStatus = true;
  //      digitalWrite(greenLED, HIGH);  
   //     
    //  }
   //   else
   //   {
   //     greenLEDStatus = false;
   //     digitalWrite(greenLED, LOW);          
  //    }
//
//      lcd.setCursor(4,1); // Defining positon to write from second row, first column .
 //     lcd.print(greenLEDStatus);
  //    break;
      
  //    case 3:
  //    if(yellowLEDStatus == false)
  //    {
  //      yellowLEDStatus = true;
   //     digitalWrite(yellowLED, HIGH);          
    //  }
    //  else
    //  {
    //    yellowLEDStatus = false;
    //    digitalWrite(yellowLED, LOW);          
   //   }
   //   lcd.setCursor(6,1); // Defining positon to write from second row, first column .
   //   lcd.print(yellowLEDStatus);
   //   
   //   break;
    //  
  //    case 4:
  //    if(redLEDStatus == false)
   //   {
   //    redLEDStatus = true;
   //    digitalWrite(redLED, HIGH);  
 //       
 //     }
  //    else
  //    {
   //     redLEDStatus = false;
    //    digitalWrite(redLED, LOW);          
  //    }
//
 //     lcd.setCursor(8,1); // Defining positon to write from second row, first column .
  //    lcd.print(redLEDStatus);
   //   break;
}    
}  
  ButtonPressed = false; //reset this variable
}
