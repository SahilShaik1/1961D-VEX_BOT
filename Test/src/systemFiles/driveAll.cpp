#include "main.h"

void driveAll(bool direction, int speedPct){
    if(direction){
        backLeftDrive.move_velocity(6 * speedPct);
        frontLeftDrive.move_velocity(6 * speedPct);
        backRightDrive.move_velocity(6 * speedPct);
        frontRightDrive.move_velocity(6 * speedPct);
    }else{
        backLeftDrive.move_velocity(-6 * speedPct);
        frontLeftDrive.move_velocity(-6 * speedPct);
        backRightDrive.move_velocity(-6 * speedPct);
        frontRightDrive.move_velocity(-6 * speedPct);
    } 
}

void driveStop(){
    backLeftDrive.move_velocity(0);
    frontLeftDrive.move_velocity(0);
    backRightDrive.move_velocity(0);
    frontRightDrive.move_velocity(0);
} 
