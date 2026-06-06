# Testing Notes

## Tested Behaviours
- Ultrasonic sensor distance readings through Serial Monitor
- LED warning after inactivity threshold
- Servo nudge after longer inactivity
- Full emergency mode after final threshold
- Manual emergency button activation
- Reset during emergency mode

## Key Testing Considerations
- Distance readings can fluctuate, so the movement threshold helps reduce false triggers.
- Demo timing values are short for presentation/testing purposes.
- Mechanical button input may require better debounce handling in future versions.
- Ultrasonic sensor placement affects reliability.

## Potential Improvements
- Use a pull-down or pull-up resistor for more reliable button input.
- Add proper button debouncing.
- Replace demo timing with realistic inactivity thresholds.
- Add wireless alert notification, SMS, or IoT integration.
- Use better fall detection sensors such as IMU/accelerometer.
- Add battery backup and enclosure design.
