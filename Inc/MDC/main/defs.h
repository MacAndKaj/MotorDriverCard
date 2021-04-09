/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : defs.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MOTORDRIVER_PLATFORM_DEFS_H
#define MOTORDRIVER_PLATFORM_DEFS_H

// Max value of counters for timers used in PWM generation.
#define PWM_PERIOD 10000-1

// Value for backward direction.
#define BACKWARD 0

// Value for forward direction.
#define FORWARD 1

// Amount of encoder pulses per round.
#define PULSES_PER_ROUND 1920.

// Radius of wheels[m].
#define R 0.033

// Value of computed PWM that should drop PWM value to 0
#define STOP_THRESHOLD 1500

#endif //MOTORDRIVER_PLATFORM_DEFS_H
