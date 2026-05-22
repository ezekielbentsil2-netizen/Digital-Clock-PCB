
# Digital Clock — KiCad PCB Project ⏰

A microcontroller-based digital clock designed and built using 
KiCad. Features a 4-digit 7-segment display, buzzer alert system, 
and button controls.

## Features
- 4-digit 7-segment display (CA56-12CGKWA)
- Two push buttons for time setting/control
- Buzzer alert via NPN transistor switch (B550)
- 12MHz crystal oscillator for accurate timekeeping
- Dual diode reverse polarity protection
- Battery + DC power input
- Real-time display of time

## Hardware Components
- STC12C4052 Microcontroller
- 12MHz Crystal (T1) with 10pF and 30pF load capacitors
- 4-digit 7-segment display
- NPN Transistor B550 (buzzer driver)
- 1N4007 Diodes (power protection)
- Push buttons x2 (SW1, SW2)
- Buzzer (BZ1)
- Resistor network for segment control

## Tools Used
- KiCad (schematic design & PCB layout)
- C++ / Arduino (firmware)

## Project Files
- Schematic (.kicad_sch)
- PCB Layout (.kicad_pcb)

## Designer
Ezekiel Ekwam-Bentsil Dadze
Electrical Engineering Student | KNUST, Ghana
Date: January 2026
