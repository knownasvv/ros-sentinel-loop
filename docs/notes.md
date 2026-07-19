# Available Components
## Software
- Arduino IDE
- ROS 2 Jazzy

## Hardware
- Arduino Uno R3
- USB Cable
- LCD 1602 with IIC
- Rc522 Module
- White Card
- Key Chain
- Joystick Module
- Keyboard
- RTC Module
- Water Level Sensor
- Humidity Sensor
- HW-479 RGB Module (common-cathode)
- Motor Driver Module
- Motor
- 1 Channel Module
- MB-102 Breadboard
- 65x Jumper Wires
- 10x F-M Cables
- Sound Sensor Module
- Remote
- 10k Potentiometer
- 1 Digital Tube
- 4 Digital Tube
- Matrix Tube
- 9G Servo
- Buzzer
- 2x Ball Switches
- 3x Photoresistance
- 5x Switches with Caps
- 9V Battery with DC
- 15x LEDs
- 30x Resistances
- Flame Sensor
- IR Receive Sensor
- 74HC595
- LM35DZ

# Timeline

## Hardware and serial foundation

### Task 1: Repository and Arduino verification
- Create the ros-sentinel-loop repository.
- Upload the Arduino Blink example.
- Inventory the available hardware.
- Start the README.
- Photograph the setup.

**Deliverable:** Arduino and repository are working. [Notes](./timeline/task1.md)
<img src="../images/initial_setup.jpg" alt="Arduino Blink example" width="400"/>

### Task 2: State-output prototype
- Connect the RGB module.
- Implement green, yellow, and red states.
- Test each state using temporary hardcoded commands.
- Use separate LEDs temporarily if necessary.
<img src="../images/rgb_module_setup.jpg" alt="RGB module setup" width="400"/>

**Deliverable:** Arduino can display all three states. [Notes](./timeline/task2.md)

### Task 3: Buzzer and manual fallback
- Connect the buzzer.
- Connect one push switch.
- Configure the switch using INPUT_PULLUP.
- Trigger red output and buzzer when the button is pressed.

**Deliverable:** Manual fallback works locally.
<img src="../images/manual_fallback_setup.jpg" alt="Manual fallback setup" width="400"/>

### Task 4: Potentiometer input
- Connect the 10k potentiometer to an analog input.
- Print raw values to the Serial Monitor.
- Convert the value to a percentage.
- Record the observed minimum and maximum.

**Deliverable:** Arduino produces stable simulated sensor readings.

### Task 5: Arduino-only classification
- Implement the initial state thresholds on Arduino.
- Display the state through the RGB module and buzzer.
- Confirm all three ranges.

**Deliverable:** A temporary Arduino-only controller works.

This logic is temporary and is later moved into ROS 2.

### Task 6: LCD and servo enhancement
- Connect the IIC LCD.
- Display sensor value and state.
- Connect the servo if the power setup is stable.
- Test safe-position movement.

**Deliverable:** At least one enhanced output works.

### Task 7: Failure testing and documentation
- Test threshold boundaries.
- Test rapid potentiometer changes.
- Test button override.
- Record wiring and results.
- Update README and test notes.

**Deliverable:** Week-one prototype is documented.

## ROS 2 integration

### Task 8: ROS 2 workspace
- Install or verify ROS 2.
- Complete a basic Python publisher/subscriber exercise.
- Create the sentinel_loop package.

**Deliverable:** The ROS 2 Python package builds and runs.

### Task 9: Standalone Python serial reader
- Install pyserial.
- Identify the Arduino serial device.
- Read Arduino messages using a normal Python script.
- Handle malformed lines without crashing.

**Deliverable:** Python receives potentiometer and button messages.

### Task 10: Serial bridge node

- Convert the serial script into a ROS 2 node.
- Publish readings to /sensor_input.
- Publish button events to /manual_fallback.

**Deliverable:** Arduino data appears on ROS 2 topics.

### Task 11: Decision node

- Subscribe to both input topics.
- Implement state thresholds.
- Implement manual-fallback priority.
- Publish /system_state.

**Deliverable:** ROS 2 produces all three states.

### Task 12: Complete round trip
- Subscribe to /system_state in the serial bridge.
- Send the resulting state back to Arduino.
- Parse the state command on Arduino.
- Control the RGB module and buzzer using ROS 2 decisions.

**Deliverable:** The full Arduino → ROS 2 → Arduino loop works.

### Task 13: Timeout and stability handling
- Track the time of the latest valid sensor message.
- Publish FALLBACK when messages stop.
- Add a moving average or hysteresis.
- Run the complete test suite.
- Record screenshots and a short demo.

**Deliverable:** Failure handling and evidence are complete.

### Task 14: Final presentation
- Clean the repository.
- Add architecture and wiring diagrams.
- Finish setup instructions.
- Add limitations and reflection.
- Prepare the DAAD and interview explanation.

**Deliverable:** The project is ready to share.