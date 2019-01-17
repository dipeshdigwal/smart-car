int motor_driver[]={4,2,7,9};
float speed_m1=100;
float speed_m2=160;
void setup() {
  // put your setup code here, to run once:
  for(int j=0;j<(sizeof(motor_driver)/sizeof(int));j++){
    pinMode(motor_driver[j],OUTPUT);
  }
  //pinMode(2,OUTPUT);
  //pinMode(12,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly
 analogWrite(motor_driver[0],speed_m1);
 analogWrite(motor_driver[1],0);
 analogWrite(motor_driver[2],speed_m2);
 analogWrite(motor_driver[3],0);
 Serial.println("Forward");
}

