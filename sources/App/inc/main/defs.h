/**
  * Copyright (c) 2020 M. Kajdak. All rights reserved.
  *
  ******************************************************************************
  * @file           : defs.h
  * @brief          : Header for <source file name> file.
  *                   This file contains <what does the file contains>
  ******************************************************************************
  */
#ifndef MDC_MAIN_DEFS_H
#define MDC_MAIN_DEFS_H

#include <cmsis_os2.h>

// Max value of counters for timers used in PWM generation.
#define PWM_PERIOD (10000-1)

// Value for backward currentDirection.
#define BACKWARD 0

// Value for forward currentDirection.
#define FORWARD 1

// Amount of encoder pulses per round.
#define PULSES_PER_ROUND 1920.

// Radius of wheels[m].
#define R 0.033

// Value of computed PWM that should drop PWM value to 0
#define STOP_THRESHOLD 1500

// Word length in bytes
#define ONE_WORD 1


/*

          ***           +-------------+      +-------------+
       + *    *   e(t)  |      T      | u(t) |             |  y(t)
r(t)--->*      *------- |  Controller |----->|  Process    |--------+--------->
         *    *         |    (PID)    |      |             |        |
          ***           +-------------+      +-------------+        |
           ^ -                                                      |
           |                                                        |
           |                 +-------------+                        |
           |                 |      T      |                        |
           +-----------------|  Feedback   |<-----------------------+
                             |             |
                             +-------------+
*/

/*

LeftEncoder
 +--------+                   y
 |        |                   ^     (Accelerometer)
 |        +--------------+    |
 |                       |    o-----> x
 |        +--------------+   z
 |        |
 +--------+
RightEncoder

 */


struct SpeedValues
{
    double leftMotorSpeed, rightMotorSpeed; // [ROUNDS/s]
};

struct InternalMessage
{
    union 
    {
        struct SpeedValues speed_values;
    };
    int msg_id;
};

// **************************************************************
// SYSCOM DEFS
// **************************************************************
#define DATA_RECEIVED_THREAD_FLAG 0x01
#define DATA_TX_BUFFERED_THREAD_FLAG 0x02
#define DATA_TX_RX_TRANSFERRED_THREAD_FLAG 0x03
// **************************************************************

// **************************************************************
// INTERNAL COMMUNICATIONS DEFS
// **************************************************************
#define UNKNOWN_MSG_ID 0x00
#define SPEED_VALUES_MSG_ID 0x01
// **************************************************************

struct message_subscription
{
    uint8_t msg_id;
    osMessageQueueId_t *subscription_queue;
};

#define ARRAY_LEN(SUBSCRIPTIONS) sizeof(SUBSCRIPTIONS)/sizeof(struct message_subscription)

struct Message;

typedef void (*send_syscom_message_func_t)(const struct Message*);

#endif //MDC_MAIN_DEFS_H
