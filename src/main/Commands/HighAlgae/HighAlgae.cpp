// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "HighAlgae.h"
#include "Commands/ArmMotion/ArmMotion.h"

frc2::CommandPtr HighAlgae(Arm *arm, Elevator *elevator, Intake *intake, SuperStructure *superStructure) {
    return frc2::cmd::Select < SuperStructureStates
            > ([superStructure] {
                return superStructure->getState();
            },
            std::pair {SuperStructureStates::HoldCoral,
                    frc2::cmd::Sequence(

                            frc2::cmd::Parallel(elevator->setElevatorCommand(ElevatorConstants::HighAlgae),
                                    ArmMotion(elevator, arm, ArmConstants::ArmAlgaeInter, ArmConstants::WristHighAlgae,
                                            ElevatorConstants::HighAlgae).ToPtr()),
                            frc2::cmd::Parallel(superStructure->setState(SuperStructureStates::EnterHighAlgae),
                                    elevator->setElevatorCommand(ElevatorConstants::HighAlgae),
                                    ArmMotion(elevator, arm, ArmConstants::ArmHighAlgae, ArmConstants::WristHighAlgae,
                                            ElevatorConstants::HighAlgae).ToPtr(),
                                    intake->setIntakeCommand(IntakeConstants::AlgaeGrab, IntakeConstants::JawAlgae))).Until(
                            [intake] {
                                return intake->isAlgaeIn(IntakeConstants::JawAlgae);
                            }).FinallyDo(
                            [=]() {
                                intake->setIntakeCommand(IntakeConstants::StopIntake, IntakeConstants::JawAlgae), superStructure->setState(
                                        SuperStructureStates::HoldAlgae);
                            })

            }, std::pair {SuperStructureStates::EnterLowAlgae,
                    frc2::cmd::Sequence(

                            frc2::cmd::Parallel(elevator->setElevatorCommand(ElevatorConstants::HighAlgae),
                                    ArmMotion(elevator, arm, ArmConstants::ArmAlgaeInter, ArmConstants::WristHighAlgae,
                                            ElevatorConstants::HighAlgae).ToPtr()),

                            frc2::cmd::Parallel(
                                    // intake->setJawCommand(IntakeConstants::JawAlgae),
                                    superStructure->setState(SuperStructureStates::EnterHighAlgae),
                                    elevator->setElevatorCommand(ElevatorConstants::HighAlgae),
                                    ArmMotion(elevator, arm, ArmConstants::ArmHighAlgae, ArmConstants::WristHighAlgae,
                                            ElevatorConstants::HighAlgae).ToPtr(),
                                    intake->setIntakeCommand(IntakeConstants::AlgaeGrab, IntakeConstants::JawAlgae))).Until(
                            [intake] {
                                return intake->isAlgaeIn(IntakeConstants::JawAlgae);
                            }).FinallyDo(
                            [=]() {
                                intake->setIntakeCommand(IntakeConstants::StopIntake, IntakeConstants::JawAlgae), superStructure->setState(
                                        SuperStructureStates::HoldAlgae);
                            })

            }

            );

}

