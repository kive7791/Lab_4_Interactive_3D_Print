# Lab_4_Interactive_3D_Print
A project that involves creating an interactive 3D-printed object (bunny) using Fusion 360, an ESP32, a photoresistor (LDR), and a vibration motor. The system responds to changes in light by activating different vibration patterns. When the sensor detects complete darkness, a sound effect is played on the connected computer.

## Demo Video link
Youtube link: [Lab 4 video](https://youtube.com/shorts/r5f1UFw0_mo?feature=share)

If the link is not working, please go to the folder titled "Assets" and watch it there.

## What is the interactive system
The interactive system uses a photoresistor (LDR) connected to an ESP32 to detect changes in surrounding light. The ESP32 reads the sensor's analog values and determines how the vibration motor should respond. An L293D motor driver controls the vibration motor.

- Bright light: No vibration.
- Dim light: The motor produces a heartbeat-like vibration pattern.
- Complete darkness: The motor vibrates continuously, and the computer plays a sound effect.

The sound is handled separately using Python, pygame, and serial communication between the ESP32 and the computer.


## How it runs
To run the system:
1. Connect the ESP32 to the computer using USB.
2. Upload the Arduino code to the ESP32.
3. Make sure the LDR and vibration motor are connected correctly.
4. Expose the LDR to light/dark.
5. To enable the sound effect, run the Python audio program on the computer while the ESP32 is connected.

The Arduino Serial Monitor must be closed before running the Python program because both applications cannot use the same serial port simultaneously.

## Extra things used in order to complete this lab

### Youtube video use
I used YouTube tutorials to learn the basic controls of Fusion 360 and how to combine different shapes into a single model.

[3D Modeling a Penguin in Fusion 360](https://www.youtube.com/watch?v=X77jad1NWzc)
[How to Combine in Fusion360](https://www.youtube.com/watch?v=7g_hwDebnVc)

### Sound effect 
I used Freesound to find a sound effect for the interaction when the LDR detects complete darkness.
- https://freesound.org/people/MLGProPlayer/sounds/269346/ 


## Issues encountered

### Photoresistor (LDR) Connection
Initially, my LDR constantly returned a value of 4095, even when I completely covered the sensor.

After troubleshooting the wiring, I discovered that the LDR circuit did not share a common ground with the ESP32.

Once I corrected the ground connection, the LDR was able to detect changes in light properly, allowing the vibration motor to respond.

### Computer audio 
I also encountered issues when trying to play a sound through my computer when the LDR detected complete darkness.

The Arduino code could control the motor, but playing sound required a separate Python program.

Some of the issues included:

- Installing pygame and pyserial in the correct Python environment.
- Identifying the ESP32's serial port.
- Understanding the difference between Linux and Windows serial ports.
- Receiving a permission error when Python attempted to access COM3.

Using Windows Device Manager, I identified the ESP32 as a Silicon Labs CP210x USB to UART Bridge connected to COM3.

The permission error indicated that another application, potentially Arduino IDE's Serial Monitor, was already using the port.

The audio functionality was still being tested during troubleshooting.

## AI Use Disclosure

I was having an issue where my computer would not play the sound effect when my LDR sensor reached state 2. I had a test.py that was working correctly, so I knew it wasn't a problem with my speaker or audio file. I also had a print statement that told me when the sound would play, but none would.

Input:
"The motor works with the LDR sensor. I haven't heard the sound play as of yet. I have reset it multiple times, but it does not seem to be playing."

I also provided my code, and any installation errors I got later on.

Summary of output:
ChatGPT explained that the ESP32 cannot directly play audio through the computer without another program receiving its serial messages.

It recommended installing pygame and pyserial (which I had), identifying the correct serial port, and closing the Arduino Serial Monitor(major issue) before running the Python program. I also was using wsl which caused another issue for my port use.