# Arduino Smart Elderly Alert System

## Overview
This project is a smart alert system prototype designed to support elderly users during emergencies or periods of inactivity. It uses an ultrasonic sensor to monitor movement, a push button for manual emergency activation/reset, and a staged alert system using an LED, buzzer, and servo motor.

The system was designed as a simple embedded prototype that combines sensor input, actuator output, timing logic, and user-centred design for elderly safety.

## Problem Statement
Elderly individuals may face difficulty calling for help during emergencies, especially if they fall unconscious or become unable to move. This project explores a simple embedded system that can detect extended inactivity and trigger graduated alerts to attract attention.

## Solution
The prototype provides two alert methods:

1. **Automatic Detection**
   - Uses an ultrasonic sensor to monitor distance/movement.
   - If no meaningful movement is detected for a set time, the system escalates through alert stages.

2. **Manual Emergency Button**
   - A button allows the user to trigger emergency mode manually.
   - During emergency mode, the button can also reset the system.

## Alert Stages
The automatic alert sequence uses three stages:

| Stage | Time Without Movement | System Response |
|---|---:|---|
| Stage 1 | 5 seconds | Blinking LED warning |
| Stage 2 | 10 seconds | Blinking LED + servo nudge |
| Stage 3 | 15 seconds | Continuous buzzer, solid LED, servo movement |

The demo timings are intentionally short for testing. In a real system, these thresholds should be longer and validated with users.

## Hardware Used
- Arduino-compatible microcontroller
- Ultrasonic distance sensor
- Push button
- Buzzer
- LED
- Servo motor
- Jumper wires / breadboard or prototype board

## Software Features
- Distance measurement using ultrasonic sensor timing
- Movement detection using distance threshold comparison
- Multi-stage alert logic using `millis()`
- Servo motor control
- Buzzer and LED emergency output
- Manual emergency trigger and reset logic
- Serial monitor debugging output

## Repository Structure
```text
arduino-smart-elderly-alert-system/
├── README.md
├── src/
│   └── smart_elderly_alert_system.ino
├── screenshots/
│   ├── 01-block-diagram.png
│   ├── 02-tinkercad-diagram.png
│   ├── 03-wiring-schematic.png
│   └── 04-prototype-photo.png
├── docs/
│   ├── design_notes.md
│   └── testing_notes.md
└── report/
    └── smart-elderly-alert-system-case-study.pdf
```

## Limitations
This is an early prototype, not a medical device. The ultrasonic sensor detects distance changes, not actual medical conditions. A real deployment would require better sensing, longer validation, emergency contact integration, enclosure design, and reliability testing.

## What I Learned
This project strengthened my understanding of embedded systems, sensor integration, staged alert logic, and user-centred design. It also showed the importance of reducing false alarms when building assistive technology for elderly users.
