# ESPHome ePaper Calendar
<p align="center">
	<img src="https://github.com/paviro/ESPHome-ePaper-Calendar/assets/992826/4516fc09-13db-48a0-9bb4-6b77c75827b0">
</p>
<p align="center">A ePaper calendar using <a href=“https://esphome.io/“>ESPHome</a> designed for the <a href=“https://soldered.com/product/soldered-inkplate-6-6-e-paper-board/“> Inkplate 6</a>.</p>

The device automatically displays as many entries as will fit on the screen. Events on the same day are grouped together. The firmware tries to optimise for low power consumption, so the device does not need to be recharged often.

## Architecture
<p align="center">
	<img src="https://github.com/paviro/ESPHome-ePaper-Calendar/assets/992826/70344da3-d793-4516-8b8c-cae3b836d326">
</p>
The ePaper calendar retrieves calendar data from a template sensor within [Home Assistant](https://www.home-assistant.io). A Python script converts the calendar data into the format required by the ESPHome firmware.  

A random quote from [api.quotable.io](https://api.quotable.io) can be fetched directly by the device.  

More information on how to setup everything can be found in the `home-assistant` directory.

## Hardware
The case and code is designed to use an [Inkplate 6](https://soldered.com/product/soldered-inkplate-6-6-e-paper-board/) from [Soldered Electronics](https://soldered.com/about-us/). I highly recommend their products as they offer excellent support and I just love their boards.  

I used a 3.7V 4200mAh battery with dimensions of 90.5x60x6mm. The case is designed for these dimensions, but could easily be adapted for a smaller battery using a CAD tool. You will need to attach a JST-PH 2.0 2-pin connector to the battery to connect it to the Inkplate board.  

The case itself can be 3D printed without the need for supports.