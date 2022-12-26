#include "main.h"

using pros::E_CONTROLLER_DIGITAL_B;
using pros::E_CONTROLLER_DIGITAL_X;

pros::Motor flywheelMotorA(16, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheelMotorB(19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor_Group flywheel ({flywheelMotorA, flywheelMotorB});

int flywheelSpeed = 599;
bool flywheelState = false;
bool Controller1L1ControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;



//L1 flywheel Mapping
void flywheelControl(){
  if (controller.get_digital(E_CONTROLLER_DIGITAL_X)) {
    if(flywheelSpeed < 599){
      flywheelSpeed += 1;
    }
    Controller1XBButtonsControlMotorsStopped = false;
  } else if (controller.get_digital(E_CONTROLLER_DIGITAL_B)) {
    if(flywheelSpeed > 60){
      flywheelSpeed -= 1;
    }
    Controller1XBButtonsControlMotorsStopped = false;
  } else if (!Controller1XBButtonsControlMotorsStopped) {
    Controller1XBButtonsControlMotorsStopped = true;
  }

  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
    flywheelState = !flywheelState;
    Controller1L1ControlMotorsStopped = false; 
  }else if(!Controller1L1ControlMotorsStopped) { 
    Controller1L1ControlMotorsStopped = true;
  }

  if(flywheelState){
    flywheel.move_velocity(flywheelSpeed);
  }else{
    flywheel.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    flywheel.brake();
  }
  int flywheelPct = flywheelSpeed/6;
  controller.print(1, 0, "FlyW Pct: %d", flywheelPct);
}
