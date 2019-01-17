const int inp_pin[] = {A7,A3,A0,A12,A8,A0,A10,A12};
//right : a7,middle : a3,left : a2,top : a12
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<(sizeof(inp_pin)/sizeof(int));i++){
    int a=analogRead(inp_pin[i]);
    Serial.print(a);
    Serial.print(" ");
  }
  Serial.println();
  delay(500);
}
