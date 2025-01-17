// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Servo/Servo.h"

Servo::Servo() = default;

// This method will be called once per scheduler run
void Servo::setServoAngle(units::degree_t angle) { //Conditional that allows us to invert the right servo if needed.
    double angleToServo = angle.value() * (slope) + 0.5;
    servo.Set(angleToServo);
}

frc2::CommandPtr Servo::servoAngleCommand(units::degree_t angle) {
    return this->RunOnce([this, angle] {
        this->setServoAngle(angle);
    });
}

double Servo::getServoAngle() {
    return servo.GetAngle();
}

void Servo::Periodic() {
}
