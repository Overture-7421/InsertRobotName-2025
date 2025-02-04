// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "LowAlgae.h"
#include "Commands/ArmMotion/ArmMotion.h"

frc2::CommandPtr LowAlgae(Arm *arm, Elevator *elevator, Intake *intake) {
    return frc2::cmd::Select < IntakeStates
            > ([intake] {
                return intake->getState();
            },
            std::pair {IntakeStates::EnterCoral, frc2::cmd::Parallel(
                    intake->setJawCommand(IntakeConstants::JawAlgae, IntakeStates::EnterAlgae),
                    elevator->setElevatorCommand(ElevatorConstants::LowAlgae),
                    ArmMotion(elevator, arm, ArmConstants::ArmLowAlgae, ArmConstants::WristLowAlgae,
                            ElevatorConstants::LowAlgae).ToPtr())}, std::pair {IntakeStates::HoldCoral,
                    frc2::cmd::Parallel(intake->setJawCommand(IntakeConstants::JawAlgae, IntakeStates::EnterAlgae),
                            elevator->setElevatorCommand(ElevatorConstants::LowAlgae),
                            ArmMotion(elevator, arm, ArmConstants::ArmLowAlgae, ArmConstants::WristLowAlgae,
                                    ElevatorConstants::LowAlgae).ToPtr())}

            );

}
