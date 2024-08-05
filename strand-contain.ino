#include <PID_v1.h>

// 定义结构体来存储PID控制器的状态和参数
struct PIDController {
  double Setpoint;
  double Input;
  double Output;
  double Kp;
  double Ki;
  double Kd;
  int pwm_out_pin;
  PID* pid;
};

// 初始化PID控制器
void initializePID(PIDController &controller, double setpoint, double kp, double ki, double kd, int pwm_out_pin) {
  controller.Setpoint = setpoint;
  controller.Kp = kp;
  controller.Ki = ki;
  controller.Kd = kd;
  controller.Input = 0;
  controller.Output = 0;
  controller.pwm_out_pin = pwm_out_pin;
  controller.pid = new PID(&controller.Input, &controller.Output, &controller.Setpoint, kp, ki, kd, DIRECT);
  controller.pid->SetMode(AUTOMATIC);
  controller.pid->SetOutputLimits(0, 255); // PWM输出限制
  controller.pid->SetSampleTime(100);
  pinMode(pwm_out_pin, OUTPUT);
}

// 更新PID控制器
void updatePID(PIDController &controller, double input) {
  controller.Input = input;
  controller.pid->Compute();
  analogWrite(controller.pwm_out_pin, controller.Output);
}

// 清理PID控制器
void cleanupPID(PIDController &controller) {
  delete controller.pid;
}

PIDController pid1, pid2;

// 计算距离的函数
double distance_calculate(int analogPin) {
  double val = analogRead(analogPin); // 读取输入引脚
  return (70.0 / 1024.0) * val + 65.0;
}

void setup() {
  Serial.begin(9600);
  
  // 初始化两个PID控制器
  initializePID(pid1, 105, 60.0, 1, 5, 2);
  initializePID(pid2, -105, 60.0, 1, 5, 3);
}

void loop() {
  char A[10];
  int j = Serial.available();
  if (j != 0) {
    for (int i = 0; i < j; i++) {
      A[i] = Serial.read();
    }
  }

  double input1 = distance_calculate(3); // 更新输入值
  double input2 = -input1;
  updatePID(pid1, input1);
  updatePID(pid2, input2);

  Serial.println(input1);
  Serial.println(pid1.Output);
  Serial.println(pid2.Output);
  
  if (j != 0) { // 清空串口数据
    for (int i = 0; i < j; i++) {
      A[i] = 0;
    }
  }
  delay(1);
}
