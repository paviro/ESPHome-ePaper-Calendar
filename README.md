# ESPHome ePaper Calendar

<p align="center">
	<img src="https://github.com/paviro/ESPHome-ePaper-Calendar/assets/992826/4516fc09-13db-48a0-9bb4-6b77c75827b0">
</p>
<p align="center">
	An ePaper calendar using <a href="https://esphome.io/">ESPHome</a>, specifically designed for <a href="https://soldered.com/product/soldered-inkplate-6-6-e-paper-board/">Inkplate 6</a>.
</p>


This sleek and minimalist ePaper calendar dynamically displays as many appointments as can fit on the available screen real estate. It groups events that occur on the same day, while multi-day events show either the remaining days or the total days if they occur in the future. Designed with energy efficiency in mind, the firmware tries to optimise power consumption to extend battery life between charges.

## Architecture Overview

<p align="center">
	<img src="https://github.com/paviro/ESPHome-ePaper-Calendar/assets/992826/70344da3-d793-4516-8b8c-cae3b836d326">
</p>

The calendar sources its data from a template sensor in [Home Assistant](https://www.home-assistant.io), processed through a Python script to match the firmware's required format. Additionally, the device can directly retrieve random quotes from [api.quotable.io](https://api.quotable.io).

Detailed setup instructions are available in the `home-assistant` directory of this repository.

## Hardware Recommendations

The case and firmware is designed to use an [Inkplate 6](https://soldered.com/product/soldered-inkplate-6-6-e-paper-board/) from [Soldered Electronics](https://soldered.com/about-us/). I highly recommend their products as they offer excellent support and I just love their boards.

I recommend using a 3.7V 4200mAh battery (dimensions: 90.5x60x6mm) for an optimal fit within the custom 3D-printable case, though modifications for other sizes can be made using CAD software. The battery should be equipped with a JST-PH 2.0 2-pin connector for easy connection to the Inkplate board. 

The 3D case designed for this project requires no support structures while printing, simplifying the process.
