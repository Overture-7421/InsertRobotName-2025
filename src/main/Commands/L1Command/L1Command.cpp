// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "L1Command.h"
#include "Commands/ArmMotion/ArmMotion.h"

frc2::CommandPtr L1Command(Arm *arm, Elevator *elevator, SuperStructure *superStructure) {
    return frc2::cmd::Select < SuperStructureStates
            > ([superStructure] {
                return superStructure->getState();
            },
            std::pair {SuperStructureStates::HoldCoral, frc2::cmd::Sequence(
                    frc2::cmd::Sequence(elevator->setElevatorCommand(ElevatorConstants::L1Position),
                            ArmMotion(elevator, arm, ArmConstants::ArmL1Reef, ArmConstants::WristClosed,
                                    ElevatorConstants::L1Position).ToPtr(),
                            ArmMotion(elevator, arm, ArmConstants::ArmL1Reef, ArmConstants::WristL1Reef,
                                    ElevatorConstants::L1Position).ToPtr()

                            ))}

            );

}
