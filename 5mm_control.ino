char A[10]; 
int pwm1_out=3;
int pwm2_out=5;
int analogPin = 3;     
double val = 0.0000;           // variable to store the value read
double distance0=0.0000;
double distance=0.0000;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(pwm1_out,OUTPUT);
  pinMode(pwm2_out,OUTPUT);
} 

/*
函数名称：计算距离值                              传感器量程  --> 输出电压 --> 采集到的数值
函数功能：读取一次当前激光传感器数值，并进行转换   65.00-135.00 -->  0-5v   -->   0-1023
输入：无     输出：要得到的距离值
*/
double val_test=0.0000; 
double distance_calculate(){
    val_test = analogRead(analogPin);    // read the input pin
    double distance_test=(70.0000/1024.0000)*val_test+65.0000;

    return distance_test;
} 
 

void loop() {
  int j=Serial.available();

  if(j!=0){
    for(int i=0;i<j;i++){
      A[i]=Serial.read();
    }
  }
  if(A[0]=='0'){//按下0记录此刻读数
    distance0=distance_calculate();
    Serial.print("now the distance=");//打印出来
    Serial.println(distance0);
  }
  if(A[0]=='1'){//按下1向前运行5mm
    distance0=distance_calculate();//记录此刻读数
    Serial.print("you send:  ");
    Serial.print(A);
    Serial.print("  ,now pwm1 out begin!,Move  forward, start  distance=   ");//开始移动提示
    Serial.println(distance0);

    analogWrite(pwm1_out,200);//pwm占空比为200/255

    while(1){
      distance=distance_calculate();
      
      if((distance-distance0)>5.00 || distance<=65.00 || distance>=135.00){//判断是否移动5mm
      Serial.print("move +5mm over,now the distance = ");
      Serial.println(distance);
      analogWrite(pwm1_out,0);//大于5mm，停止移动
      break;//跳出循环
      }

    }    
  }

  else if(A[0]=='3'){//按下3向后运行5mm
    distance0=distance_calculate();//记录此刻读数
    Serial.print("you send:  ");
    Serial.print(A);
    Serial.print("  ,now pwm2 out begin!,Move backward, start  distance=   ");//开始移动提示
    Serial.println(distance0);

    analogWrite(pwm2_out,200);//pwm占空比为200/255

    while(1){
      distance=distance_calculate();
      if((distance-distance0)<-6.00 || distance<=65.00 || distance>=135.00){//判断是否移动5mm
      Serial.print("move -6mm over,now the distance = ");
      Serial.println(distance);
      analogWrite(pwm2_out,0);//大于6mm，停止移动
      break;//跳出循环
      }
    } 
  }
  
  else if(A[0]=='2'){//按下2停止输出pwm1
    analogWrite(pwm1_out,0);//停止移动
    delay(10);
    Serial.print("you send:  ");
    Serial.print(A);
    Serial.println("  ,pwm1 out stop!");
  }
  else if(A[0]=='4'){//按下4停止输出pwm2
    analogWrite(pwm2_out,0);//停止移动
    Serial.print("you send:  ");
    Serial.print(A);
    Serial.println("  ,pwm2 out stop!");
  }
  if(j!=0){//清空串口数据
    for(int i=0;i<j;i++){
      A[i]=0;
    }
  }
  delay(10);
}