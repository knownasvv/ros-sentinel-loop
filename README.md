# Sentinel Loop: ROS 2 + Arduino Fallback Behaviour Demo

Sentinel Loop is a small introductory robotics decision-loop project connecting Arduino-based physical input with ROS 2 decision logic. A potentiometer simulates a changing sensor signal, while a push button provides a manual fallback trigger.

Arduino sends the input readings to a ROS 2 system through serial communication. ROS 2 classifies the readings into NORMAL, CAUTION, or FALLBACK, then sends the selected state back to Arduino.

#### Arduino presents the result through:
- an RGB status indicator,
- an LCD status display,
- an audible buzzer warning,
- an servo safe-position response.

## Minimum success
The project is complete when:
1. Arduino reads the potentiometer.
2. Arduino detects the manual fallback button.
3. Arduino sends input messages to the laptop.
4. A ROS 2 node parses those messages.
5. The decision node publishes NORMAL, CAUTION, or FALLBACK.
6. ROS 2 sends the decision back to Arduino.
7. The RGB module displays the selected state.
8. The buzzer activates during fallback.
9. The README documents setup, behaviour, testing, and limitations.

## Strong success
A stronger version adds:
1. LCD display for sensor value and state.
2. Servo safe-position response.
3. Serial timeout detection.
4. Invalid-message handling.
5. Moving-average filtering.
6. Hysteresis near thresholds.
7. Manual fallback priority.
8. Automated tests for the decision logic.
9. Architecture diagram.
10. Short demonstration video.

## System overview
```
Physical input
    ↓
Arduino Uno
    ↓ Serial sensor message
ROS 2 sensor node
    ↓
ROS 2 decision node
    ↓ Serial state command
Arduino Uno
    ↓
RGB light + LCD + buzzer + servo
```

### Serial Protocol
1. Arduino sends sensor readings to ROS 2 in the format:
    ```
    SENSOR:<value>
    BUTTON:<fallback>
    ERROR:<error_message>
    ```

2. ROS 2 sends state commands back to Arduino in the format:
    ```
    STATE:<NORMAL|CAUTION|FALLBACK>
    ```

3. Arduino interprets the state command and updates the output devices accordingly.

## States
### Inputs
1. **Potentiometer:** Produces an analog value between 0 and 1023, simulating a sensor reading. The value is sent to ROS 2 for classification.

   | Potentiometer value | Risk level | State | Meaning |
   |---------------------|------------|-------|---------|
   | 0–599    | Below 60%     | NORMAL   | Input is within the expected operating range |
   | 600–849  | 60%–84%       | CAUTION  | Input is approaching an unsafe range |
   | 850–1023 | 85% or higher | FALLBACK | Input has crossed the unsafe threshold |

   Risk level formula: `risk_percent = raw_value × 100 / 1023`

2. **Manual Fallback Switch:** Act as an emergency trigger. When pressed: `BUTTON:FALLBACK` is sent to ROS 2, which will classify the state as FALLBACK regardless of the potentiometer value.

### Outputs   
| State | RGB | LCD | Buzzer | Servo |
|-------|-----|-----|--------|-------|
| NORMAL | Green | "NORMAL" | Off | 90° |
| CAUTION | Yellow | "CAUTION" | Beep | 45° |
| FALLBACK | Red | "FALLBACK" | Continuous beep | 0° |

1. **RGB Module:** Displays the current state with color coding.
2. **LCD 1602 with IIC:** Displays the current state and the simulated input value.
3. **Buzzer:** Emits a warning sound when in CAUTION or FALLBACK state.
4. **Servo:** Moves to a safe position when in FALLBACK state.