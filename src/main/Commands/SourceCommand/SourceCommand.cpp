// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "SourceCommand.h"
#include "Commands/ArmMotion/ArmMotion.h"

frc2::CommandPtr SourceCommand(Arm *arm, Elevator *elevator, Intake *intake, SuperStructure *superStructure) {
    return frc2::cmd::Select < SuperStructureStates
            > ([superStructure] {
                return superStructure->getState();
            },
            std::pair {SuperStructureStates::HoldCoral,
                    frc2::cmd::Parallel(elevator->setElevatorCommand(ElevatorConstants::CoralStationPosition),
                            ArmMotion(elevator, arm, ArmConstants::ArmCoralStation, ArmConstants::WristCoralStation,
                                    ElevatorConstants::CoralStationPosition).ToPtr(),
                            intake->setIntakeCommand(IntakeConstants::CoralGrab, IntakeConstants::JawCoralOpen),
                            superStructure->setState(SuperStructureStates::EnterCoralStation).FinallyDo(
                                    [=]() {
                                        intake->setIntakeCommand(IntakeConstants::StopIntake,
                                                IntakeConstants::JawCoralClose), superStructure->setState(
                                                SuperStructureStates::HoldCoral);
                                    })

                    )}, std::pair {SuperStructureStates::EnterCoralGround,
                    frc2::cmd::Parallel(elevator->setElevatorCommand(ElevatorConstants::CoralStationPosition),
                            ArmMotion(elevator, arm, ArmConstants::ArmCoralStation, ArmConstants::WristCoralStation,
                                    ElevatorConstants::CoralStationPosition).ToPtr(),
                            intake->setIntakeCommand(IntakeConstants::CoralGrab, IntakeConstants::JawCoralOpen),
                            superStructure->setState(SuperStructureStates::EnterCoralStation).FinallyDo(
                                    [=]() {
                                        intake->setIntakeCommand(IntakeConstants::StopIntake,
                                                IntakeConstants::JawCoralClose), superStructure->setState(
                                                SuperStructureStates::HoldCoral);
                                    })

                    )}, std::pair {SuperStructureStates::EnterAlgaeGround,
                    frc2::cmd::Parallel(elevator->setElevatorCommand(ElevatorConstants::CoralStationPosition),
                            ArmMotion(elevator, arm, ArmConstants::ArmCoralStation, ArmConstants::WristCoralStation,
                                    ElevatorConstants::CoralStationPosition).ToPtr(),
                            intake->setIntakeCommand(IntakeConstants::CoralGrab, IntakeConstants::JawCoralOpen),
                            superStructure->setState(SuperStructureStates::EnterCoralStation).FinallyDo(
                                    [=]() {
                                        intake->setIntakeCommand(IntakeConstants::StopIntake,
                                                IntakeConstants::JawCoralClose), superStructure->setState(
                                                SuperStructureStates::HoldCoral);
                                    })

                    )}

            );

}
