// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Processor.h"
#include "Commands/ArmMotion/ArmMotion.h"

frc2::CommandPtr Processor(Arm *arm, Elevator *elevator, Intake *intake) {
    return frc2::cmd::Select < IntakeStates
            > ([intake] {
                return intake->getState();
            },
            std::pair {IntakeStates::HoldAlgae, frc2::cmd::Parallel(
                    elevator->setElevatorCommand(ElevatorConstants::ProcessorPosition),
                    ArmMotion(elevator, arm, ArmConstants::ArmProcessor, ArmConstants::WristProcessor,
                            ElevatorConstants::ProcessorPosition).ToPtr())}

            );

}
