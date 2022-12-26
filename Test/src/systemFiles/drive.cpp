#include "main.h"

//MOTORS
pros::Motor backLeftDrive(17, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor frontLeftDrive(18, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor backRightDrive(11, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor frontRightDrive(12, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);

/*
int num = 0;
int sum = 0;
int drive_a[4];
void slewControl(){
  sum = 0;
  drive_a[num] = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  for(int i = 0; i < 4; i++){
    sum += drive_a[i];
  }
  num++;
  num = num % 4;
  backLeftDrive.move_voltage(sum/4);
  frontLeftDrive.move_voltage(sum/4);
  backRightDrive.move_voltage(sum/4);
  frontRightDrive.move_voltage(sum/4); 
}
*/

//STATUS BOOLS
bool DrivetrainLeftNeedsToBeStopped = true;
bool DrivetrainRightNeedsToBeStopped = true;

//JOYSTICK MAPPING
void doubleArcade() {  
  int drivetrainLeftSideSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  int drivetrainRightSideSpeed = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  if (abs(drivetrainLeftSideSpeed) < 5) {
    if (DrivetrainLeftNeedsToBeStopped == true) {
      backRightDrive.move_velocity(0);
      frontRightDrive.move_velocity(0);
      DrivetrainLeftNeedsToBeStopped = false;
    }
  } else {
      DrivetrainLeftNeedsToBeStopped = true;
    }

  if (abs(drivetrainRightSideSpeed) < 5) {
    if (DrivetrainRightNeedsToBeStopped) {
      backLeftDrive.move_velocity(0);
      frontLeftDrive.move_velocity(0);
      DrivetrainRightNeedsToBeStopped = false;
    }
  } else {
      DrivetrainRightNeedsToBeStopped = true;
  }

  if(drivetrainLeftSideSpeed > 100){
    drivetrainLeftSideSpeed  = 100;
  }else if (drivetrainLeftSideSpeed < -100){
    drivetrainLeftSideSpeed  = -100;
  }
  if(drivetrainRightSideSpeed > 100){
    drivetrainRightSideSpeed  = 100;
  }else if (drivetrainRightSideSpeed < -100){
    drivetrainRightSideSpeed  = -100;
  }

  if (DrivetrainLeftNeedsToBeStopped) {
      backLeftDrive.move_velocity(drivetrainLeftSideSpeed * 6);
      frontLeftDrive.move_velocity(drivetrainLeftSideSpeed * 6);
  }

  if (DrivetrainRightNeedsToBeStopped) {
      backRightDrive.move_velocity(drivetrainRightSideSpeed * 6);
      frontRightDrive.move_velocity(drivetrainRightSideSpeed * 6);
  }
}


