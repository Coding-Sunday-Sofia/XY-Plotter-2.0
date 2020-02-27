# RubyRemote: GCode remote control in Ruby

This is a first draft attempt to output GCode from Ruby.

## Requirements

* Ruby 2.0.x or greater

## Installation

    bundle install

## Usage

Before running this, you will probably want to load the GRemote tool
to set the XYZ steps per mm. It always seemed too small for me.

Check in the Arduino IDE what the serial port is called. On mine it was:

    /dev/tty.usbmodem1421

If yours is different you should change it in the `send.rb` file.

Then run it:

    ruby send.rb

This will output one of the working samples to the plotter.

### Caveats

This is really early days. If you `ctrl-c` the execution it will leave
the serial port open, and you'll need to power-cycle the plotter.

### Author

[David Parry](https://github.com/suranyami)
