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

## Controls

- Button 2 cycles through modes
- Still color

  - Knob 1 - sets brightness of currently selected color
  - Knob 2 - sets brightness of led strip
  - Button 1 - cycles through selected colors (red, green, blue)

- Breathing mode

  - Knob 1 - sets brightness of currently selected color
  - Knob 2 - controlls speed of breathing
  - Button 1 - cycles through selected colors (red, green, blue)

- Rainbow mode

  - Knob 1 - controlls how often color changes
  - Knob 2 - controlls speed of the transitions
  - Button 1 - forces color to change instantly

## Schematic

![Schematic for the controller](http://i.imgur.com/Ak2lQeI.png, "Generated with easyEDA")

## Serial api

Everything can be set by serial via usb, so you can connect your controller to pc or RPI and controll it remotely. By default serial baud rate is set to 9600

### Get information

To get json representation of current settings you can call `json`. Object returned:

```json
{
      "mode": 0,
      "brightnes": 1.00,
      "brightnesStep": -0.01,
      "colors": {
          "red": 255,
          "green": 255,
          "blue": 255
      },
      "rainbow": {
          "lastUpdate": 0,
          "changeEvery": 5000,
          "transitionSteps": 500
      },
      "alarm": {
          "hour": 20,
          "minute": 15,
          "alarmMode": 0,
          "colors": {},
          "red": 9,
          "green": 9,
          "blue": 7
      }
    }
```

- modes number representation

  - 0 - color mode
  - 1 - breathing mode
  - 2 - random mode

- If alarm isn't set `alarm` object has value of `false`

### Set values

You can also set variables via this api

- To change mode use `mode [color|breathing|random]` comand

  - For example to set random mode use `mode random`

- To change color use `color [red] [green] [blue]`

  - For example to set blue use `color 0 0 255`

- To change brightnes use `brightnes [value(0-1)]`

  - For example to set brightnes of 50% use `brightnes 0.5`

- To set an alarm use `alarm [on|off] [hour] [minute] [mode] [red] [green] [blue]`

  - modes number representation

    - 0 - color mode
    - 1 - breathing mode
    - 2 - random mode

    - If Time wasn't yet set after using `alarm` comand conotrller will respond with `time`. After that you have to send current time in posix format

      - For example `1476981420`

  - For example to set alarm at 16:20 using breathing mode with color blue use `alarm on 16 20 1 0 255 0`

## Design

### Buttons

As you can see I decided to use separate pushbuttons, insted of using encoder buttons. This is just because I'll be using big concrete knobs, and I suspect that buttins will be pushed permanently.

### Indicator led

As I am using only 1 knob to controll displayed color, I need a button to cycle through colors that knob is currently controlling. Led is used to show currently selected color.

### Minimum brightness

This is honestly the biggest flow of this design, as I can't set led strip to be 100% off. This is due voltage leak on mosfets, and I don't know and easy ways to change that. Solid state realy or simple on/off switch on +12V rail of led strip is a one way of solving this.

### Board design

I opted to build this circuit on 2 perf-boards, as I wasn't able to fit it on one 4x5cm board. One board is used for power delivery of encoders, and the other one is for rest of the components.

## Plans

- 3 rotary encoders for controlling led strips color, brightness, and sound volume.
- 3 push buttons for controlling led mode, turning on pc, and controlling currently active color, for encoder #1
- 2 double pole single throw switches - 1 for turning on and off the controller, and led's, and 1 for controlling lights
- I am aiming to fit whole controller (with arduino, but without the power supply) into a small 20cm X 20cm x 4cm wooden box, and use concrete knobs for encoders, so space will be really limited.
- Hardware for the project has to be cheaper than $25 (including led strip and arduino, but not including old pc power supply that will power the project, as I had it laying around)
