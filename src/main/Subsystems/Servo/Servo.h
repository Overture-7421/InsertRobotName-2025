// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc2/command/Command.h>
#include <frc2/command/CommandPtr.h>
#include <OvertureLib/MotorControllers/OverTalonFX/OverTalonFX.h>
#include <frc/Servo.h>

class Servo: public frc2::SubsystemBase {
public:
    Servo(); //Constructor

    void Periodic() override; //Method that activates the susbystem

    void setServoAngle(units::degree_t angle);
    frc2::CommandPtr servoAngleCommand(units::degree_t angle);

    double getServoAngle();

private:
    frc::Servo servo {4};

    const double slope = 135;
};
