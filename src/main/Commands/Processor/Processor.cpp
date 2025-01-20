// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Processor.h"
#include "Subsystems/Arm/Constants.h"
#include "Subsystems/Elevator/Constants.h"

frc2::CommandPtr Processor(Arm *arm, Elevator *elevator) {
    return frc2::cmd::Sequence(elevator->setElevatorCommand(ElevatorConstants::ProcessorPosition),
            frc2::cmd::WaitUntil([elevator] {
                return elevator->isElevatorAtPosition(ElevatorConstants::ProcessorPosition);
            }),
            arm->setArmCommand(Constants::ArmProcessor, Constants::WristProcessor), frc2::cmd::WaitUntil([arm] {
                return arm->isArmAtPosition(Constants::ArmProcessor, Constants::WristProcessor);

            })

    );
}
