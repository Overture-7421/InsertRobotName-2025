// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/DigitalInput.h>
#include "OvertureLib/Gamepads/OverXboxController/OverXboxController.h"
#include <frc2/command/Commands.h>
#include "Subsystems/Arm/Arm.h"
#include "Subsystems/Elevator/Elevator.h"

frc2::CommandPtr LowAlgae(Arm *arm, Elevator *elevator, OverXboxController *overxboxController);
