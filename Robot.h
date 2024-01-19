// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "rev/CANSparkMax.h"
#include <frc/Joystick.h>
#include <frc/GenericHID.h>
#include <frc/DigitalInput.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;
  //FUNÇÕES MECACHRONICAS
  void tankControl();//Controle de movimentação do Robô
  void shooterControl();//Controle do lançador de notas
  void climberControl();//Controle do escalador

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  
  //Testar se a função teleoperada está rodando
  bool teleopPeriodicStarted = false;

  //Controle do robô - Joystick 1
  frc::Joystick joy1{0};
    //Movimentação
    double tankVerDirection = 0.0;
    double tankHorDirection = 0.0;
    double tankLeftMotorSpeed=0.0;
    double tankRigthMotorSpeed=0.0;
    double tankGear = 1.0;//Inicia sempre com a marcha de velocidade mais alta
    bool tankGearUpButton = false;
    bool tankGearDownButton = false;
    //Comandos SHOOTER
    bool shooterButtonA = false;
    //Comandos CLIMBER
    bool climberButtonY = false;
    bool climberButtonB = false;
    bool climberUperSwitch = false;
    bool climberLowerSwitch = false;
    //Comandos INTAKE


  //===================TANQUE================================================
  //Motores do tanque
  rev::CANSparkMax tankLeftMotorFront {1, rev::CANSparkMax::MotorType::kBrushed};
  rev::CANSparkMax tankLeftMotorRear  {2, rev::CANSparkMax::MotorType::kBrushed};
  rev::CANSparkMax tankRightMotorFront{4, rev::CANSparkMax::MotorType::kBrushed};
  rev::CANSparkMax tankRightMotorRear {3, rev::CANSparkMax::MotorType::kBrushed};

  //===================SHOOTER================================================
  //Motores do lançador
  rev::CANSparkMax shooterLeftMotor {5, rev::CANSparkMax::MotorType::kBrushed};
  rev::CANSparkMax shooterRightMotor  {6, rev::CANSparkMax::MotorType::kBrushed};

  //===================CLIMBER================================================
  //Motores do Climber
  rev::CANSparkMax climberLeftMotor {7, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax climberRightMotor  {8, rev::CANSparkMax::MotorType::kBrushless};
  //Fins de curso do escalador
  frc::DigitalInput	climberUpLimSwitch{1};
  frc::DigitalInput	climberDownLimSwitch{2};
};
