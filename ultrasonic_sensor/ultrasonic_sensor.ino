int ultra_trig[]={35,28,34};//35
int ultra_echo[]={31,24,40};//31
float distance[]={0,0,0};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0;i<3;i++){
    pinMode(ultra_trig[i],OUTPUT);
    pinMode(ultra_echo[i],INPUT);  
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<(sizeof(distance)/sizeof(float));i++){
    digitalWrite(ultra_trig[i],LOW);
    delayMicroseconds(2);
    digitalWrite(ultra_trig[i],HIGH);
    delayMicroseconds(10);
    digitalWrite(ultra_trig[i],LOW);
    float a=pulseIn(ultra_echo[i],HIGH);
    distance[i]=a/(2*29.1);
    Serial.print(distance[i]);
    Serial.print(" ");  
  }
  delay(500);
  Serial.println();
  
}
