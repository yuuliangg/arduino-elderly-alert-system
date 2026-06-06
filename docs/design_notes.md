# Design Notes

## Main Design Goal
The system was designed to be simple enough for elderly users while still providing both automatic and manual alert options.

## Automatic Inactivity Detection
The ultrasonic sensor measures distance repeatedly. If the measured distance does not change beyond a threshold for a set period, the system assumes inactivity and begins the alert sequence.

## Manual Emergency Activation
A push button allows the user to trigger emergency mode immediately. This provides a backup option in case the user is conscious but needs urgent help.

## Graduated Alert Logic
Instead of instantly triggering a loud emergency alarm, the system escalates in stages:
1. LED warning
2. LED warning + servo nudge
3. Full emergency alarm

This design helps reduce unnecessary panic and gives the user a chance to respond before the full alert triggers.

## User-Centred Considerations
The system was designed with elderly users in mind:
- simple interaction
- clear visual/audio alerts
- automatic backup if the user cannot press a button
- reduced false alarm risk through staged escalation
