// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <rev/CANSparkMax.h>
#include "frc/Joystick.h"
#include <frc/GenericHID.h>
#include <frc/DigitalInput.h>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  std::cout<<"TeleopInit() Begin..."<<std::endl;//me

  std::cout<<"TeleopInit() Ended!"<<std::endl;//me
}

//TELEOPERADO PERIÓDICO
void Robot::TeleopPeriodic() {
  if(teleopPeriodicStarted==false){
  std::cout<<"TeleopPeriodic() Begin..."<<std::endl;//me
  }

  Robot::tankControl();

  Robot::shooterControl();

  Robot::climberControl();


  if(teleopPeriodicStarted==false){
  std::cout<<"TeleopPeriodic() End!"<<std::endl;//me
  teleopPeriodicStarted=true;
  }

}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}


//IMPLEMENTADO SISTEMA DE MARCHAS 11/01/2023
/*
* R1 - Gear Up    controle vibra
* L1 - Gear Down  controle vibra
* LeftStick - Forward and Backward
* RightStick - Left and Right
*/
void Robot::tankControl(){
  tankVerDirection = -joy1.GetRawAxis(1); // Eixo vertical do analogico esquerdo. ↑=-1.0 e ↓=+1.0
  tankHorDirection = joy1.GetRawAxis(4); // Eixo horizontal do analogico direito. ←=-1.0 e →=+1.0
  tankGearUpButton = joy1.GetRawButtonPressed(6);//R1 - Aumenta a marcha
  tankGearDownButton = joy1.GetRawButtonPressed(5);//L1 - Diminui a marcha
  
  tankLeftMotorSpeed = tankVerDirection;
  tankRigthMotorSpeed = tankVerDirection;

  if (tankVerDirection != 0) {
    if (tankHorDirection > 0.0) { // Se hDirection > 0, então o robô deve virar para a direita
            tankLeftMotorSpeed += tankHorDirection;
       }
      if (tankHorDirection < 0.0) { // Se hDirection < 0, então o robô deve virar para a esquerda
            tankRigthMotorSpeed -= tankHorDirection;
      }
    } else {
      if (tankHorDirection > 0.0) { // Se hDirection > 0, então o robô deve virar para a direita
        tankLeftMotorSpeed += tankHorDirection;
        tankRigthMotorSpeed = -tankLeftMotorSpeed;
      }
      if (tankHorDirection < 0.0) { // Se hDirection < 0, então o robô deve virar para a esquerda
        tankRigthMotorSpeed -= tankHorDirection;
        tankLeftMotorSpeed = -tankRigthMotorSpeed;
      }
    }

    // Controle de velocidade
    if(tankGearUpButton==true && tankGear<=0.75){
      tankGear+=0.25;
      //joy1.SetRumble(frc::Joystick::RumbleType::kRightRumble, 1);//Para joysticks com função vibra
      std::cout<<"GEAR = "<<tankGear<<std::endl;//me
      }
    if(tankGearDownButton==true && tankGear>=0.5){
      tankGear-=0.25;
      //joy1.SetRumble(frc::Joystick::RumbleType::kLeftRumble, 1);//Para joysticks com função vibra
      std::cout<<"GEAR = "<<tankGear<<std::endl;//me
    }
        tankLeftMotorSpeed *= tankGear;
        tankRigthMotorSpeed *= tankGear;

    tankLeftMotorFront.Set(-tankLeftMotorSpeed);
    tankLeftMotorRear.Set(-tankLeftMotorSpeed);
    tankRightMotorFront.Set(tankRigthMotorSpeed);
    tankRightMotorRear.Set(tankRigthMotorSpeed);

    if (tankVerDirection == 0 && tankHorDirection == 0) {
        tankLeftMotorFront.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);//Brake =1 | Coast = 0
        tankLeftMotorRear.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
        tankRightMotorFront.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
        tankRightMotorRear.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    }
    /*else if(tankHorDirection == 0 && tankVerDirection == 0) {
        tankLeftMotorFront.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);//Brake =1 | Coast = 0
        tankLeftMotorRear.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
        tankRightMotorFront.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
        tankRightMotorRear.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    }*/
}

void Robot::shooterControl(){
  shooterButtonA = joy1.GetRawButton(1);
  if(shooterButtonA==true){
    shooterLeftMotor.Set(1.0);
    shooterRightMotor.Set(-1.0);
  }else{
    shooterLeftMotor.Set(0.0);
    shooterRightMotor.Set(0.0);
  }

  //std::cout<<"X Button = "<<shooterButtonA<<std::endl;//me

}

void Robot::climberControl(){
  climberLowerSwitch = !climberUpLimSwitch.Get();
  climberUperSwitch = !climberDownLimSwitch.Get();
  climberButtonY = joy1.GetRawButton(4);
  climberButtonB = joy1.GetRawButton(2);
  //std::cout<<"Y Button = "<<climberButtonY<<std::endl;//me
  //std::cout<<"B Button = "<<climberButtonY<<std::endl;//me
  if(climberButtonY==true){
    climberLeftMotor.Set(-0.3);
    climberRightMotor.Set(-0.3);
    std::cout<<"sobe CLIMBER"<<std::endl;//me
  }
  else if(climberButtonB==true){
    climberLeftMotor.Set(0.3);
    climberRightMotor.Set(0.3);
    std::cout<<"desce CLIMBER"<<std::endl;//me
  }
  else{
    climberLeftMotor.Set(0);
    climberRightMotor.Set(0);
    std::cout<<"desliga CLIMBER"<<std::endl;//me
  }
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
