# Sentinel Loop: ROS 2 + Arduino Fallback Behaviour Demo

Sentinel Loop is a small introductory robotics decision-loop project connecting Arduino-based physical input with ROS 2 decision logic.

The initial version uses a potentiometer as a simulated sensor input and a push button as a manual fallback trigger. Arduino sends these inputs to ROS 2, where the system classifies the situation as NORMAL, CAUTION, or FALLBACK. The decision is then sent back to Arduino and represented through hardware outputs such as an RGB indicator, buzzer, LCD, and servo.

## Scope
This project is not an autonomous robot or a safety-certified control system. It is a small educational demonstration of sensor input, software-based state classification, fallback behaviour, communication monitoring, and hardware response.

## System overview
```
Physical input
    ↓
Arduino Uno
    ↓ Serial communication
ROS 2 decision logic
    ↓ Serial communication
Arduino hardware response
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


### Documentation
- [docs/notes.md](./docs/notes.md): daily progress notes.
- [docs/test_cases.md](./docs/test_cases.md): planned and completed tests.
- [docs/reflection.md](./docs/reflection.md): learning notes.