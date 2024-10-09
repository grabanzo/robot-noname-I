#include <DualShock.h>
#include <RobotOmniW.h>


DualShockConfig dualshock_config{
  .pin_clk = 13,
  .pin_cmd = 8,
  .pin_att = 7,
  .pin_dat = 12
};

MotorControllerConfig motor_config{
  .pin_IN1_Front = 4,
  .pin_IN2_Front = 6,
  .pin_IN3_Front = 9,
  .pin_IN4_Front = 10,
  .pin_ENA_Front = 5,
  .pin_ENB_Front = 6,
  .pin_IN1_Rear = A1,
  .pin_IN2_Rear = A2,
  .pin_IN3_Rear = A3,
  .pin_IN4_Rear = A4,
  .pin_ENA_Rear = 3,
  .pin_ENB_Rear = 11,
};

RobotOmniW robot_omniw;
DualShock dual_sock;

void setup() {
  Serial.begin(9600);

  robot_omniw.configure(motor_config);
  dual_sock.configure(dualshock_config); // software SPI initialization

  dual_sock.setButtonEventCB(ButtonR2, [](ButtonEvent event) {
    Serial.print("Event");
    Serial.println(event);
    if(event == ButtonEventPressed) {
      robot_omniw.setEnabled();
    } else {
      robot_omniw.setDisabled();
    }
  });
  dual_sock.setStickEventCB(StickButtonRight, [](byte value_x, byte value_y) {
    robot_omniw.moveByXY(value_x, value_y);
  });
}

void loop() {
  dual_sock.poll();
  delay(50);
}
