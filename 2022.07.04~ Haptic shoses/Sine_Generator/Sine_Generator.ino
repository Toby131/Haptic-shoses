#include <TimerOne.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN 선언.
const byte address[6] = "00001"; //주소값을 5가지 문자열로 변경할 수 있으며, 송신기과 수신기가 동일한 주소로 해야됨.

//Seperators
char *A ="";
char *B ="";
char *C ="";

//Values
float fsampleTime;
float ffreq;
float fAmpli;

//sine
#define outPin  10
#define delayPin  11    // this pin is just used to test the compute time
const float pi = 3.14159 ;
const float T = 100 ;    // sample time in microseconds
const float Sampling = 1000000.0;
float newOmega;
float a[]={0,0,0};
float c1=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  Timer1.initialize(T);
  Timer1.pwm(outPin, 0,T);
}
//COM03
void loop() {
  // put your main code here, to run repeatedly:
  
if (radio.available())
  {
        char text[32] = "";
        radio.read(&text, sizeof(text));
        Serial.println(text);
         delay(20);
        char*d = strtok(text,"#");
        int count =0; 
      
        //seperating values
        while (d!= NULL)
          {
            if(count==0)
            {
              A=d;
            }
            else if (count==1)
            {
              B=d;
            }
            else if(count==2)
            {
              C=d;
            }
            count++;
            //Serial.println(d);
            d=strtok(NULL,"#");
          }
        //Serial.println(A);
        //Serial.println(B);
        //Serial.println(C);
      
        fsampleTime=atof(A);
        ffreq=atof(B);
        fAmpli=atof(C);
        delay(20);
        Serial.println(fsampleTime);
        Serial.println(ffreq);
        Serial.println(fAmpli);
      
        newOmega=(float)(2*pi*ffreq) ;
        a[1]=fAmpli*sin(newOmega*T/Sampling);
        a[0]=0.0;
        a[2]=0.0;
        c1 = (8.0 - 2.0*pow(newOmega*T/Sampling,2))/(4.0+pow(newOmega*T/Sampling,2));
        delay(20);
        makeSineWave();
        pinMode(delayPin, OUTPUT);
        Timer1.setPwmDuty(outPin, LOW); //사인 없애기
  }
    
 
}

void makeSineWave()
{
   for(uint32_t tStart = millis();  (millis()-tStart) < fsampleTime;)
  {
    compute();
  }
}

void compute() 
{
    digitalWrite(delayPin, HIGH);
    a[2] = c1*a[1] - a[0] ;  // recursion equation
    a[0] = a[1] ;
    a[1] = a[2] ;
    Timer1.setPwmDuty(outPin, int(a[2])+512); ////1024 //it's giving a voltage
    digitalWrite(delayPin, LOW);
} 
