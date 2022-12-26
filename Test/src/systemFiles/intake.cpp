#include "main.h"

pros::Motor intakeMotorA(9, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeMotorB(10, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor_Group intake ({intakeMotorA, intakeMotorB});

bool Controller1RightShoulderControlMotorsStopped = true; 


//R1 and R2 intake Mapping
void intakeControl(){
  double intakeScale = 1;
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    intake.move_velocity(600 * intakeScale);
    Controller1RightShoulderControlMotorsStopped = false;
  } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    intake.move_velocity(-600 * intakeScale);
    Controller1RightShoulderControlMotorsStopped = false;
  } else if(!Controller1RightShoulderControlMotorsStopped) { 
    intake.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    intake.brake();
    Controller1RightShoulderControlMotorsStopped = true;
  }
}
