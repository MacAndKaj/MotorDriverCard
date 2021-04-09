/**
  ******************************************************************************
  * @file           : motor.h
  * @brief          : Header for main.c file.
  *                   This file contains the motor struct definition.
  ******************************************************************************
  */
#ifndef MOTORDRIVER_MOTOR_INFO_H
#define MOTORDRIVER_MOTOR_INFO_H

#include <gpio.h>

#include <stdint.h>


/// Struct for read informations about motor.
typedef struct MotorInfo
{
    uint8_t updateFlag;                 /// Flag used to signalize update of speed internal event.
    double speed;                       /// Speed of motor in radians per second.
    int32_t pulses;                     /// Actual number of pulses read from encoder.
	uint8_t direction;                  /// Actual direction of motor.
    GPIO_PinState lastPinAEncoderState; /// Last state of encoder A pin
} MotorInfoHandle;

/**
  ******************************************************************************
  *
  * Global variables externs.
  *
  *******************************************************************************
  */
extern GPIO_PinState leftMotorEncoderA_PinLastState;
extern GPIO_PinState rightMotorEncoderA_PinLastState;
extern MotorInfoHandle leftMotorHandle;
extern MotorInfoHandle rightMotorHandle;

/**
  **************************rightMotorHandle****************************************************
  *
  * Global variables externs end.
  *
  *******************************************************************************
  */

/// Function sets forward direction in struct Motor handle.
/// \param handle: [struct Motor ptr]
void setForward(MotorInfoHandle* handle);

/// Function used to check direction of working motor.
/// \param handle: [struct Motor ptr]
/// \return [int] 1 if forward, 0 othewrwise
int isForward(const MotorInfoHandle* handle);

/// Function sets backward direction in struct Motor handle.
/// \param handle: [struct Motor ptr]
void setBackward(MotorInfoHandle* handle);

/// Function sets number of encoder pulses in struct Motor handle.
/// \param handle: [struct Motor ptr]
/// \param newPulses: [int32_t] new number of pulses
void setPulses(MotorInfoHandle* handle, int32_t newPulses);

/// Function to read number of pulses on encoder for motor
/// \param handle: [struct Motor ptr]
/// \return [int32_t] number of pulses on encoder
int32_t getPulses(const MotorInfoHandle* handle);

/// Function sets speed of motor in struct Motor handle.
/// \param handle: [struct Motor ptr]
/// \param newSpeed: [double] new speed in rounds/second
void setSpeed(MotorInfoHandle* handle, double newSpeed);

/// Returns angular speed of motor in radians per second
/// \param handle [struct Motor ptr]
/// \return [double] angular speed of motor
double getSpeed(const MotorInfoHandle *handle);

/// Disables flag that signals needed update of motor speed.
/// \param handle [struct Motor ptr]
void enableSpeedUpdateFlag(MotorInfoHandle *handle);

/// Disables flag that signals needed update of motor speed.
/// \param handle [struct Motor ptr]
void disableSpeedUpdateFlag(MotorInfoHandle *handle);

/// Function for checking if speed update flag is set
/// \param handle [struct Motor ptr]
/// \return [uint8_t] update flag: 1-set, 0-not set
uint8_t isSpeedUpdateFlagSet(MotorInfoHandle *handle);

/// Function used to update speed value in MotorHandle structure.
/// \param handle [struct Motor ptr]
/// \param time [double] time in seconds
void updateSpeed(MotorInfoHandle *handle, double time);

/// Initialize struct Motor handle. Sets all parameters to 0.
/// \param handle: [struct Motor ptr]
void Motor_Init(MotorInfoHandle* handle);

/**
  ******************************************************************************
  *
  * Specialized functions begin.
  *
  *******************************************************************************
  */


void initializeLeftMotor();
void initializeRightMotor();

void updateLeftMotorParameters();
void updateRightMotorParameters();
/**
  ******************************************************************************
  *
  * Specialized functions begin.
  *
  *******************************************************************************
  */

#endif //MOTORDRIVER_MOTOR_INFO_H