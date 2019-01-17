int pins[]={39,44,43,53,A14};
int frequency = 0;

void setup() {
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
  pinMode(pins[3], OUTPUT);
  
  
  // Setting frequency-scaling to 20%
  digitalWrite(pins[0],LOW);
  digitalWrite(pins[1],HIGH);
  
  Serial.begin(9600);
}

void loop() {
  // Setting red filtered photodiodes to be read
  digitalWrite(pins[2],LOW);
  digitalWrite(pins[3],LOW);
  // Reading the output frequency
  frequency = pulseIn(pins[4], LOW);
  Serial.print(" ");
  Serial.print(frequency);//printing RED color frequency
  
  // Printing the value on the serial monitor
  Serial.println();
  delay(0);
}
