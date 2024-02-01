# Vortex Shedding Flowmeter Firmware

## Overview

This repository contains the firmware for the Vortex Shedding Flowmeter, a senior design project by Team 7 ('FlowTec'). The flowmeter is designed to measure the flow rate of liquids, primarily water, through a pipe using the vortex shedding principle. A bluff body placed in the flow path induces vortices, which are detected by a piezoelectric sensor. The sensor's oscillations, corresponding to the fluid's flow rate, are converted into an electrical signal, processed by an STM32 microcontroller, and displayed on an LCD.

### Purpose

The Vortex Shedding Flowmeter aims to provide an easy-to-install flow measurement solution for homeowners with pools, enhancing water management and monitoring efficiency.

### Functionality

- **Flow Measurement**: Utilizes vortex shedding to measure water flow rate.
- **Signal Processing**: Converts piezoelectric sensor oscillations into flow rate readings.
- **User Interface**: Displays the flow rate on an LCD screen for easy monitoring.

## Hardware Components

- **STM32 Microcontroller**: Manages data processing and device operations.
- **Piezoelectric Sensor**: Detects the vortices caused by the bluff body.
- **RS-485 Interface**: Facilitates communication for remote monitoring.
- **Bluff Body**: Induces vortices in the flowing liquid.
- **LCD Display**: Provides a user-friendly interface for data display.

## Software Features

- **ADC Sampling**: Digitizes the analog signal from the piezoelectric sensor.
- **Digital Filtering**: Enhances the signal quality for accurate flow rate calculation.
- **Display Management**: Controls the LCD to present real-time flow measurements.

## Installation

Detailed steps on how to install the firmware onto the STM32 microcontroller and integrate the flowmeter into a pipe system.

## Usage

Instructions on how to use the flowmeter, including how to read the measurements on the LCD display and troubleshoot common issues.

## Development Environment

Guidelines for setting up the development environment, including required software, libraries, and tools to modify and compile the firmware.

## Testing

Description of testing procedures to verify the accuracy, display scale range, and durability of the flowmeter, ensuring it meets specified requirements.

## Contributing

Instructions for contributing to the firmware development, including coding conventions, pull request process, and how to report bugs or suggest enhancements.

## License

Specify the license under which the firmware is released, detailing what others can and cannot do with the source code.

## Contact

Information on how to reach Team 7 ('FlowTec') for support, collaboration, or inquiries about the Vortex Shedding Flowmeter project.

