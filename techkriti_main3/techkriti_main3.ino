int default_1=1; //priority 1:right 2:left
int max_speed=200;
int speed_turn=160;
int speed_turn_rear=100; //curved turn velocity
int t=0; //time delay for serial moniter
const int threshold_ir[8]={350,350,350,350,350,350,350,350}; //specify threshold first of all 4 4-pi array sensors and then of single ones with right first
int color_threshold=950;

const int ir_sens_inp[4]={A7,A10,A3,A2}; //ir sensor pins start from right and use middle 4 ir sensors
const int ir_sen_single[2]={A8,A0}; //0:right backward 1:left forward 2:right forward 3:left forward
const int motor_driver[4]={4,2,9,7}; //motor_driver 0:A1 1:A2 2:B1 3:B2 and pwm pins
const int display_1[7]={};
const int display_2[7]={};
const float difference_speed=4.3;
const int leds[]={}; //for pins of led; 0:phase 4 led.

int sensor_current_val[4]={0,0,0,0};

//both ultrasonic must be digital
//first value must be for right side
const int ultrasonic_trig[3]={35,28,34};
const int ultrasonic_echo[3]={31,24,40};
float distance[]={0,0,0};
float distance_ultra[3]={0,0,0};
int color_sens_pin[5]={28,29,48,49,A7}; //color sens pins to be placed in order (S0,S1,S2,S3,OUTPUT FREQUENCY)
int numbers_led[9][7]={{1,0,0,1,1,1,1},{0,0,1,0,0,1,0},{0,0,0,0,1,1,0},{1,0,0,1,1,0,0},{0,1,0,0,1,0,0},{0,1,0,0,0,0,0},{0,0,0,1,1,1,1},{0,0,0,0,0,0,0},{0,0,0,0,1,0,0}};
int b;
int x;
int flag=1;
int flag_2=1;
int flag_3=0;
int flag_4=0;
int flag_5=0;
int boxes_count=0;
int color=2;
int color_2;

void move_straight();
void turn_opposite();
void turn_right();
void turn_left();
void turn_different_right();
void turn_different_left();
void ultrasonic_sens_val();
int color_sens();
void const_right_turn();
void const_left_turn();

void setup() {
  for(int i=0;i<(sizeof(motor_driver)/sizeof(int));i++){
    pinMode(motor_driver[i],OUTPUT);
  }
  for(int i=0;i<(sizeof(ultrasonic_trig)/sizeof(int));i++){
    pinMode(ultrasonic_trig[i],OUTPUT);
    pinMode(ultrasonic_echo[i],INPUT);
  }
  pinMode(color_sens_pin[0],OUTPUT);
  pinMode(color_sens_pin[1],OUTPUT);
  pinMode(color_sens_pin[2],OUTPUT);
  pinMode(color_sens_pin[3],OUTPUT);
  
  digitalWrite(color_sens_pin[0],HIGH);
  digitalWrite(color_sens_pin[1],LOW);
  for(int i=0;i<7;i++){
    pinMode(display_1[i],OUTPUT);
  }
  for(int i=0;i<7;i++){
    pinMode(display_2[i],OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  b=0;//for getting number of element of lower_threshold
  int lower_threshold[4]={0,0,0,0};
  for(int i=0;i<(sizeof(ir_sens_inp)/sizeof(int));i++){
    int ir_sen_val=analogRead(ir_sens_inp[i]);
    if(ir_sen_val<threshold_ir[i]){
      lower_threshold[i]=(i+1);
      b++;
    }
  }
  x=0;
  int lower_threshold_single[2]={0,0};
  for(int i=0;i<(sizeof(ir_sen_single)/sizeof(int));i++){
    int ir_sen_val=analogRead(ir_sen_single[i]);
    if(ir_sen_val<threshold_ir[i+4]){
      lower_threshold_single[i]=1;
      x++;
    }
  }
  
  if((b+x)==8){
    if(flag_3<5){
      while((b+x)==8){
        move_straight();
        
        b=0;//for getting number of element of lower_threshold
        int lower_threshold[]={0,0,0,0};
        for(int i=0;i<(sizeof(ir_sens_inp)/sizeof(int));i++){
          int ir_sen_val=analogRead(ir_sens_inp[i]);
          if(ir_sen_val<threshold_ir[i]){
            lower_threshold[i]=(i+1);
            b++;
          }
        }
        
        x=0;
        int lower_threshold_single[]={0,0,0,0};
        for(int i=0;i<(sizeof(ir_sen_single)/sizeof(int));i++){
          int ir_sen_val=analogRead(ir_sen_single[i]);
          if(ir_sen_val<threshold_ir[i+4]){
            lower_threshold_single[i]=1;
            x++;
          }
        }
        Serial.println("moving straight");
      }
      flag_3+=1;
      if(flag_3==4){
        while(flag_5!=1){
          b=0;//for getting number of element of lower_threshold
          int lower_threshold[]={0,0,0,0};
          for(int i=0;i<(sizeof(ir_sens_inp)/sizeof(int));i++){
            int ir_sen_val=analogRead(ir_sens_inp[i]);
            if(ir_sen_val<threshold_ir[i]){
              lower_threshold[i]=(i+1);
              b++;
            }
          }
          
          x=0;
          int lower_threshold_single[]={0,0,0,0};
          for(int i=0;i<(sizeof(ir_sen_single)/sizeof(int));i++){
            int ir_sen_val=analogRead(ir_sen_single[i]);
            if(ir_sen_val<threshold_ir[i+4]){
              lower_threshold_single[i]=1;
              x++;
            }
          }

          if(b==0){
            do{
              turn_left();
              for(int j=0;j<4;j++){
                int x1=analogRead(ir_sens_inp[j]);
                sensor_current_val[j]=0;
                Serial.println("moving left constantly");
                if(x1<threshold_ir[j]){
                  sensor_current_val[j]=1;
                }
              }
            } while(sensor_current_val[0]!=0 && sensor_current_val[1]!=0 && sensor_current_val[2]!=1 && sensor_current_val[3]!=1);
          }
          else if(b==1){
            turn_left();
          }
          else if(b==2){
            move_straight();
          }
          else if(b==4){
            const_right_turn();
            flag_5==1;
          }
        }
      }
    }
    else if(flag_3==5){
      analogWrite(motor_driver[0],0);
      analogWrite(motor_driver[1],0);
      analogWrite(motor_driver[2],0);
      analogWrite(motor_driver[3],0);
    }
  }
  
  //PHASE 1:
  if(flag_3==1){*/
    if(b==0){
      Serial.println("b==0");
      delay(t);
      do{
        turn_opposite();
        for(int j=0;j<4;j++){
          int x1=analogRead(ir_sens_inp[j]);
          sensor_current_val[j]=0;
          Serial.println("moving right constantly");
          if(x1<threshold_ir[j]){
            sensor_current_val[j]=1;
          }
        }
      } while(sensor_current_val[0]!=0 || sensor_current_val[1]!=1 || sensor_current_val[2]!=1 || sensor_current_val[3]!=0);
    }
    else if(b==1){
      Serial.println("b==1");
      delay(t);
      if(lower_threshold[0]==1){
        const_right_turn();
      }
      else if(lower_threshold[1]==2){
        const_right_turn();
      }
      else if(lower_threshold[2]==3){
        const_left_turn();
      }
      else if(lower_threshold[3]==4){
        const_left_turn();
      }
    }
    else if(b==2){
      Serial.println("b==2");
      delay(t);
      if(lower_threshold[1]==2 && lower_threshold[2]==3){
        Serial.println("front right and front left");
        delay(t);
        move_straight();
        Serial.println("moving straight");
      }
      else if(lower_threshold[1]==2 && lower_threshold[0]==1){
        Serial.println("right and front right");
        delay(t);
        const_left_turn();
      }
      else if(lower_threshold[2]==3 && lower_threshold[3]==4){
        Serial.println("front left and left");
        delay(t);
        const_right_turn();
      }
      else if(lower_threshold[0]==1 && lower_threshold[3]==4){
        Serial.println("right and left");
        delay(t);
        if(default_1==1){
          const_right_turn();
        }
        else if(default_1==2){
          const_left_turn();
        }
      }
    }
    else if(b==3){
      Serial.println("b==3");
      delay(t);
      if(lower_threshold[0]==1 && lower_threshold[1]==2 && lower_threshold[2]==3){
        Serial.println("right and front both");
        delay(t);
        if(default_1==1){
          const_right_turn(); 
        }
        else if(default_1==2){
          if(x==0){
            const_right_turn();
          }
          else if(x==2){
            Serial.println("moving straight");
            move_straight();
          }
        }
      }
      else if(lower_threshold[1]==2 && lower_threshold[2]==3 && lower_threshold[3]==4){
        Serial.println("front both and left");
        delay(t);
        if(default_1==2){
          const_left_turn(); 
        }
        else if(default_1==1){
          if(x==0){
            const_left_turn();
          }
          else{
            Serial.println("moving straight");
            move_straight();
          }
        }
      }
    }
    else if(b==4){
      Serial.println("b==4");
      delay(t);
      if(default_1==1){
        const_right_turn();
      }
      else if(default_1==2){
          const_left_turn();
      } 
    }    
  }
  
  //PHASE 2:
  else if(flag_3==2 || flag_3==3){
    if(flag_4==0){
      ultrasonic_sens_val();
      if(distance[0]<20){
        distance_ultra[0]=1;
      }
      else if(distance[2]<20){
        distance_ultra[0]=2;
      }
      distance_ultra[1]=14.8;
      distance_ultra[2]=15.2;
      flag_4+=1;
    }
    else if(flag_4==1){
      ultrasonic_sens_val();
      if(distance_ultra[0]==1){
        if(distance[2]<20){
          flag_4=0;
        }
      }
      else if(distance_ultra[0]==2){
        if(distance[0]<20){
          flag_4=0;
        }
      }
      
      if((distance[0]<20 && distance[1]>5 && distance[2]>20)||(distance[2]<20 && distance[1]>5 && distance[0]>20)){
                
        if(distance_ultra[0]==1 && distance[0]>distance_ultra[1] && distance[0]<distance_ultra[2]){
          move_straight(); 
          Serial.println("moving straight");
        }
        else if(distance_ultra[0]==1 && distance[0]>distance_ultra[2]){
          turn_different_right();
          Serial.println("turning right");
        }
        else if(distance_ultra[0]==1 && distance[0]<distance_ultra[1]){
          turn_different_left();
          Serial.println("turning left");
        }
        else if(distance_ultra[0]==2 && distance[2]>distance_ultra[1] && distance[2]<distance_ultra[2]){
          move_straight(); 
          Serial.println("moving straight");
        }
        else if(distance_ultra[0]==2 && distance[2]>distance_ultra[2]){
          turn_different_left();
          Serial.println("turning left");
        }
        else if(distance_ultra[0]==2 && distance[2]<distance_ultra[1]){
          turn_different_right();
          Serial.println("turning right");
        }
      }
      else if(distance[0]<20 && distance[1]<=5 && distance[2]>20){
        Serial.println("turn left");
        do{
          float t=distance[0];
          Serial.println("turning left constantly");
          analogWrite(motor_driver[0],max_speed);
          analogWrite(motor_driver[1],0);
          analogWrite(motor_driver[2],0);
          analogWrite(motor_driver[3],max_speed);  
          ultrasonic_sens_val();
        }while(distance[0]>t);
        do{
          float t=distance[0];
          Serial.println("turning left constantly");
          analogWrite(motor_driver[0],max_speed);
          analogWrite(motor_driver[1],0);
          analogWrite(motor_driver[2],0);
          analogWrite(motor_driver[3],max_speed);  
          ultrasonic_sens_val();
        }while(distance[0]<t);
        analogWrite(motor_driver[1],max_speed);
        analogWrite(motor_driver[0],0);
        analogWrite(motor_driver[3],0);
        analogWrite(motor_driver[2],max_speed);
      }
      else if(distance[2]<20 && distance[1]<=5 && distance[0]>20){
        Serial.println("turn right");
        do{
          float t=distance[2];
          Serial.println("turning right constantly");
          analogWrite(motor_driver[2],max_speed);
          analogWrite(motor_driver[3],0);
          analogWrite(motor_driver[0],0);
          analogWrite(motor_driver[1],max_speed);  
          ultrasonic_sens_val();
        }while(distance[2]>t);
        do{
          float t=distance[2];
          Serial.println("turning right constantly");
          analogWrite(motor_driver[2],max_speed);
          analogWrite(motor_driver[3],0);
          analogWrite(motor_driver[0],0);
          analogWrite(motor_driver[1],max_speed);  
          ultrasonic_sens_val();
        }while(distance[2]<t);
        analogWrite(motor_driver[3],max_speed);
        analogWrite(motor_driver[2],0);
        analogWrite(motor_driver[1],0);
        analogWrite(motor_driver[0],max_speed);
      }
      else if(distance[2]>20 && distance[1]>5 && distance[0]>20){
        if(distance_ultra[0]==1){
          Serial.println("turn right and forward");
          do{
            ultrasonic_sens_val();
            turn_different_right();
            Serial.println("turning right and forward constantly");
          } while(distance[0]>15);
        }
        else if(distance_ultra[0]==2){
          Serial.println("turn left and forward");
          do{
            ultrasonic_sens_val();
            turn_different_left(); 
            Serial.println("turning left and forward constantly");
          }while(distance[2]>15);
      }
      else if(distance[2]<40 && distance[0]<40 && distance[1]>40){
        Serial.println("moving straight");
        move_straight();
      }
    }  
  }
  }
    
  //PHASE 3:
  else if(flag_3==4){
    if(b==0){
      Serial.println("b==0");
      Serial.println("moving straight");
      move_straight();
    }
    else if(b==1){
      Serial.println("b==1");
      delay(t);
      if(lower_threshold[0]==1){
        const_right_turn();
      }
      else if(lower_threshold[1]==2){
        const_right_turn();
      }
      else if(lower_threshold[2]==3){
        const_left_turn();
      }
      else if(lower_threshold[3]==4){
        const_left_turn();
      }
    }
    else if(b==2){
      Serial.println("b==2");
      if(x==4){
        if(flag_2==1){
          Serial.println("color sensing");
          //color: 0:RED 1:BLUE
          color_sens();
          int color=color_2;
          boxes_count+=1;
          flag_2+=1; 
        }
        else if(flag_2==2){
          if(color==0){
            Serial.println("red color");
            const_right_turn();
            Serial.println("const right turn");
          }
          else if(color==1){
            Serial.println("blue color");
            const_left_turn();
            Serial.println("const left turn");
          }
          flag_2=1;
        }
      }
      else{
        if(lower_threshold[1]==2 && lower_threshold[2]==3){
            Serial.println("move straight");
            move_straight();
        }
        else if(lower_threshold[0]==1 && lower_threshold[1]==2){
          const_right_turn();
        }
        else if(lower_threshold[2]==3 && lower_threshold[3]==4){
          const_left_turn();
        }
      }
    }
    else if(b==3){
      Serial.println("b==3");
      if(lower_threshold[0]==1 && lower_threshold[1]==2 && lower_threshold[2]==3){
        const_right_turn();
        Serial.println("const right turn");
      }
      else if(lower_threshold[3]==4 && lower_threshold[1]==2 && lower_threshold[2]==3){
          const_left_turn();
          Serial.println("const left turn");
      } 
    }
    else if(b==4){
      ultrasonic_sens_val();
      if(distance[1]<=5){
        if(flag_2==1){
          Serial.println("color sensing");
          //color: 0:RED 1:BLUE
          color_sens();
          int color=color_2;
          boxes_count+=1;
          flag_2+=1; 
        }
        else if(flag_2==2){
          if(color==0){
            Serial.println("red color");
            const_right_turn();
            Serial.println("const right turn");
          }
          else if(color==1){
            Serial.println("blue color");
            const_left_turn();
            Serial.println("const left turn");
          }
          flag_2=1;
        }
      }
      else if(distance[1]<20){
        while(distance[1]>5){
          ultrasonic_sens_val();
          move_straight();
        }
        while(flag_2!=3){
          if(flag_2==1){
            Serial.println("color sensing");
            //color: 0:RED 1:BLUE
            color_sens();
            int color=color_2;
            boxes_count+=1;
            flag_2+=1; 
          }
          else if(flag_2==2){
            if(color==0){
              Serial.println("red color");
              const_right_turn();
              Serial.println("const right turn");
            }
            else if(color==1){
              Serial.println("blue color");
              const_left_turn();
              Serial.println("const left turn");
            }
            flag_2=3;
          }
        }
      }
    }
  }
  //PHASE 4:
  else if(flag_3==5){
    digitalWrite(leds[0],HIGH);
    display_number_boxes();
  }
}
void move_straight(){
  Serial.println(flag);
  analogWrite(motor_driver[0],max_speed);
  analogWrite(motor_driver[1],0);
  analogWrite(motor_driver[2],max_speed+difference_speed);
  analogWrite(motor_driver[3],0);
  Serial.println("right and left tyres moving forward");
}

void turn_opposite(){
  Serial.println(flag);
  if(default_1==1){
    analogWrite(motor_driver[2],max_speed+difference_speed);
    analogWrite(motor_driver[3],0);
    analogWrite(motor_driver[0],0);
    analogWrite(motor_driver[1],max_speed);  
  }
  if(default_1==2){
    analogWrite(motor_driver[0],max_speed);
    analogWrite(motor_driver[1],0);
    analogWrite(motor_driver[2],0);
    analogWrite(motor_driver[3],max_speed+difference_speed);  
  }
}
void turn_left(){
  analogWrite(motor_driver[0],speed_turn);
  analogWrite(motor_driver[1],0);
  analogWrite(motor_driver[2],0);
  analogWrite(motor_driver[3],0);
}

void turn_right(){
  analogWrite(motor_driver[2],speed_turn+difference_speed);
  analogWrite(motor_driver[3],0);
  analogWrite(motor_driver[0],0);
  analogWrite(motor_driver[1],0);
}

void turn_different_left(){
  analogWrite(motor_driver[0],speed_turn);
  analogWrite(motor_driver[1],0);
  analogWrite(motor_driver[2],speed_turn_rear+difference_speed);
  analogWrite(motor_driver[3],0);
}

void turn_different_right(){
  analogWrite(motor_driver[2],speed_turn);
  analogWrite(motor_driver[3],0);
  analogWrite(motor_driver[0],speed_turn_rear+difference_speed);
  analogWrite(motor_driver[1],0);
}

void ultrasonic_sens_val(){
  for(int i=0;i<3;i++){
    digitalWrite(ultrasonic_trig[i],LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonic_trig[i],HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonic_trig[i],LOW);
    float time_interval=pulseIn(ultrasonic_echo[i],HIGH);
    distance[i]=time_interval/(2*29.1);
    if(distance[i]==0){
      distance[i]=4000;
    }
    Serial.print(distance[i]);
    Serial.print("  ");
  }
  delay(t);
  Serial.println();
}

int color_sens(){
 //RED COLOR DETECTION
 digitalWrite(color_sens_pin[2],LOW);  
 digitalWrite(color_sens_pin[3],LOW);
 unsigned int a=pulseIn(color_sens_pin[4],LOW);
 Serial.println("red check");
 if(a<color_threshold){
  color_2=0;
 }
 else{
  color_2=1;
 }
}

void const_left_turn(){
  do{
    turn_left();
    Serial.println("moving left constantly");
    for(int j=0;j<4;j++){
      int x1=analogRead(ir_sens_inp[j]);
      sensor_current_val[j]=0;      
      if(x1<threshold_ir[j]){
        sensor_current_val[j]=1;
      }
    }
  }while(sensor_current_val[0]!=0 || sensor_current_val[1]!=1 || sensor_current_val[2]!=1 || sensor_current_val[3]!=0);
}

void const_right_turn(){
  do{
    turn_right();
    Serial.println("moving right constantly");
    for(int j=0;j<4;j++){
      int x1=analogRead(ir_sens_inp[j]);
      sensor_current_val[j]=0;
      if(x1<threshold_ir[j]){
        sensor_current_val[j]=1;
      }
    }
  }while(sensor_current_val[0]!=0 || sensor_current_val[1]!=1 || sensor_current_val[2]!=1 || sensor_current_val[3]!=0);
}

void display_number_boxes(){
  for(int i;i<7;i++){
    digitalWrite(display_1[i],numbers_led[boxes_count-1][i]);
  }
  for(int i;i<7;i++){
    digitalWrite(display_2[i],numbers_led[boxes_count-1][i]);
  }
}
