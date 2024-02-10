#define LED1 23
#define BT 15
hw_timer_t *My_timer = NULL;

int D = 500000/1175;
int A = 500000/1760;
int B = 500000/1976;
int G = 500000/1568;
int F = 500000/1480;
int E = 500000/1319;
int Note[] = {D,D,A,A,B,B,A,G,G,F,F,E,E,D,A,A,G,G,F,F,E,A,A,G,G,F,F,E,D,D,A,A,B,B,A,G,G,F,F,E,E,D};
int j=0;

float lv[]={7,6,4,2,0.5};
bool doingWork = false;

void IRAM_ATTR button(){
  j++;
  if(j==5) j=0;
}
void IRAM_ATTR onTimer(){
  digitalWrite(LED1, !digitalRead(LED1));
}


void setup() {
  Serial.begin(115200);
  Serial.println("Starting");
  pinMode(LED1, OUTPUT);
  pinMode(BT, INPUT);
  My_timer = timerBegin(0, 80, true);  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  attachInterrupt(BT,button,FALLING);
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  timerAlarmEnable(My_timer);  // enable the alarm
}

void loop() {
  for(int i=0;i<42;i++){
     timerAlarmWrite(My_timer, Note[i], true);
     timerAlarmEnable(My_timer);
     delay(2*Note[i]);
     timerAlarmDisable(My_timer);
     delay(lv[j]*Note[i]);
     Serial.println("Lv"+(j+1));
  }
}
  