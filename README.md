# ledController

For now this is just a small arduino project aiming, to build an arduino leonardo based led controller, with lots of additional features.

## Features
- Still color
    - Color is controlled bd a knob on the cotroller
    - Brightness can be easly changed with a knob
- Breathing mode
    - Brightness changes over time
    - Color is controlled bd a knob on the cotroller
    - Speed of the efect can be controlled with a knob
- Random color mode
    - Displays random color for set amount of time
    - Fluent color transitions
    - Speed of the efect can be controlled with a knob

## Plans

* 3 rotary encoders for controlling led strips color, brightness, and sound volume.
* 3 push buttons for controlling led mode, turning on pc, and controlling currently active color, for encoder #1
* 2 double pole single throw switches - 1 for turning on and off the controller, and led's, and 1 for controlling lights
* I am aiming to fit whole controller (with arduino, but without the power supply) into a small 20cm X 20cm x 4cm wooden box, and use concrete knobs for encoders, so space will be really limited.
* Hardware for the project has to be cheaper than $25 (including led strip and arduino, but not including old pc power supply that will power the project, as I had it laying around)

## Schematic
![Schematic for the controller](http://i.imgur.com/Ak2lQeI.png, "Generated with easyEDA")

### Buttons
As you can see I decided to use separate pushbuttons, insted of using encoder buttons. This is just because I'll be using big concrete knobs, and I suspect that buttins will be pushed permanently.
### Indicator led
As I am using only 1 knob to controll displayed color, I need a button to cycle through colors that knob is currently controlling. Led is used to show currently selected color.
### Minimum brightness
This is honestly the biggest flow of this design, as I can't set led strip to be 100% off. This is due voltage leak on mosfets, and I don't know and easy ways to change that. Solid state realy or simple on/off switch on +12V rail of led strip is a one way of solving this.
### Practical design
I opted to build this circuit on 2 perf-boards, as I wasn't able to fit it on one 4x5cm board. One board is used for power delivery of encoders, and the other one is for rest of the components.
