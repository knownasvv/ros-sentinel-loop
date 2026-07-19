| ID | Input condition | Expected state | Expected Arduino response |
|----|-----------------|----------------|---------------------------|
| T01 | Potentiometer at 20% | NORMAL | Green, buzzer off, servo normal |
| T02 | Potentiometer at 70% | CAUTION | Yellow, optional brief warning |
| T03 | Potentiometer at 95% | FALLBACK | Red, buzzer on, servo safe |
| T04 | Button pressed at 20% | FALLBACK | Red, buzzer on, servo safe |
| T05 | Reading exactly at lower caution threshold | CAUTION | Yellow |
| T06 | Reading exactly at fallback threshold | FALLBACK | Red and buzzer |
| T07 | Invalid serial message | FALLBACK | Red and buzzer |
| T08 | Arduino messages stop | FALLBACK | Red and buzzer |
| T09 | Values fluctuate around caution threshold | Stable state | No rapid state switching |
| T10 | Valid readings resume after timeout | Classified from current input | Correct output restored |
| T11 | Unknown command sent to Arduino | Previous safe state or fallback | No uncontrolled response
| T12 | ROS 2 process terminates | Defined local behaviour | Arduino enters or retains safe state |