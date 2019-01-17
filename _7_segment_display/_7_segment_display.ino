int pins[]={22,23,24,25};
void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<(sizeof(pins)/sizeof(int));i++){
    pinMode(pins[i],OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<(sizeof(pins)/sizeof(int));i++){
    digitalWrite(pins[i],LOW);
  }
}
