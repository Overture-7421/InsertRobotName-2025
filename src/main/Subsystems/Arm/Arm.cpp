// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Arm/Arm.h"
#include <iostream>

Arm::Arm() {
    armRightMotor.setFollow(ArmConstants::ArmLeftMotorId, true);

    armLeftMotor.setRotorToSensorRatio(ArmConstants::ArmRotorToSensor);
    wristMotor.setRotorToSensorRatio(ArmConstants::WristRotorToSensor);

    armLeftMotor.setFusedCANCoder(ArmConstants::ArmCANCoderId);
    wristMotor.setFusedCANCoder(ArmConstants::WristCANCoderId);

    armLeftMotor.configureMotionMagic(ArmConstants::ArmCruiseVelocity, ArmConstants::ArmCruiseAcceleration,
            0.0_tr_per_s_cu);
    wristMotor.configureMotionMagic(ArmConstants::WristCruiseVelocity, ArmConstants::WristCruiseAcceleration,
            0.0_tr_per_s_cu);
}

void Arm::setToAngle(units::degree_t armAngle, units::degree_t wristAngle) {
    frc::SmartDashboard::PutNumber("ArmTarget/ArmTargetPosition", armAngle.value());
    frc::SmartDashboard::PutNumber("ArmTarget/WristTargetPosition", wristAngle.value());

    armLeftMotor.SetControl(armVoltage.WithPosition(armAngle).WithEnableFOC(true));
    wristMotor.SetControl(wristVoltage.WithPosition(wristAngle).WithEnableFOC(true));

}

void Arm::blockedWrist(units::degree_t armAngle, units::degree_t wristAngle) {

    bool blockingNegative = armLeftMotor.GetPosition().GetValueAsDouble() * 360 < -20;
    bool blockingPositive = armLeftMotor.GetPosition().GetValueAsDouble() * 360 > 20;

    frc::SmartDashboard::PutBoolean("BlockWrist/blockingNegative", blockingNegative);
    frc::SmartDashboard::PutBoolean("BlockWrist/blockingPositive", blockingPositive);

    if (blockingNegative && blockingPositive) {
        setToAngle(armAngle, 0_deg);
    } else {
        setToAngle(armAngle, wristAngle);
    }
}

bool Arm::isArmAtPosition(units::degree_t armAngle, units::degree_t wristAngle) {
    units::degree_t armError = armAngle - armLeftMotor.GetPosition().GetValue();
    units::degree_t wristError = wristAngle - wristMotor.GetPosition().GetValue();

    return ((units::math::abs(armError) < ArmConstants::ArmAngleRange)
            && (units::math::abs(wristError) < ArmConstants::WristAngleRange));
}

frc2::CommandPtr Arm::setArmCommand(units::degree_t armAngle, units::degree_t wristAngle) {

    return frc2::FunctionalCommand([this, armAngle, wristAngle]() {
        setToAngle(armAngle, wristAngle);
    }, []() {
    }, [](bool interupted) {
    }, [this, armAngle, wristAngle]() {
        return isArmAtPosition(armAngle, wristAngle);
    },
    {this}).ToPtr();
}

frc2::CommandPtr Arm::SysIdQuasistatic(frc2::sysid::Direction direction) {
    return m_sysIdRoutine.Quasistatic(direction);
}

frc2::CommandPtr Arm::SysIdDynamic(frc2::sysid::Direction direction) {
    return m_sysIdRoutine.Dynamic(direction);
}

void Arm::Periodic() {
    double armCurrentAngle = armLeftMotor.GetPosition().GetValueAsDouble() * 360;
    double wristCurrentAngle = wristMotor.GetPosition().GetValueAsDouble() * 360;
    frc::SmartDashboard::PutNumber("ArmCurrent/CurrentArmAngle", armCurrentAngle);
    frc::SmartDashboard::PutNumber("ArmCurrent/CurrentWristAngle", wristCurrentAngle);
}
