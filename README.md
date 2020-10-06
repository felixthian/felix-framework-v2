# Felix Framework
This is a framework for Makeblock mbot. It contains EVERYTHING you need!
## Setup
To setup the project, you need visual studio code with platformio extension
Then, add the folder into visual studio code.
![setup](https://github.com/felixthian/felix-framework-v2/blob/master/pic/001.png)
## Development
The framework is not completed yet but the basic sensor is supported!
Feature:
### Hardware
- [X] MeRGBLineFollower Support
- [X] onboard RGBLED Support
- [X] onboard Buzzer Support
- [X] onboard Button Support
- [X] onboard LightSensor Support
- [X] MeUltrasonic Support
- [X] MeDCMotor Support
- [X] MeLineFollower Support
- [ ] BlueTooth Module Controller Support
### Software
- [X] Wired Serial
- [X] Felixmeter (a piece of code that make linefollower into motor encoder)
- [ ] EEPROM
- [ ] Line Following Algorithm
- [ ] AI (removed temporary due to unstable code)
- [X] ESP8266-01s Wireless Serial
# Documentation
This framework is written in C++, so you MUST have C++ basic before starting
### MeRGBLineFollower
rgblinefollower(port number, address) - initialize the sensor
setRGBColour(colour code) - change the colour of the rgb led, colour code can found in 4dotlinefollower.h
getPositionState() - get the sensor scanned dot data
### onboard button
button() - initialize button
is_pressed() - check if the button pressed
waitForWait() - wait until the button is pressed
### onboard buzzer
buzzer - initialize buzzer
tone(frequency, duration in ms) - call buzzer to play tone
### onboard light sensor
light_sensor() - initialize light sensor
read() - get the light intensity - the bigger value for brighter environment
### MeLineFollower
linefollower(port number) - initialize the line follower
readSensor() - get the sensor value
readSensor1() - get sensor 1 value
readSensor2() - get sensor 2 value 
### MeDCMotor
motor() - initialize motor
run(motor_1, motor_2) - set motor speed
### onboard RGBLED
rgbled() - initialize rgbled
setColor(red, green, blue);
setColor(side, red, green, blue);
### MeUltrasonic
ultrasonic() - initialize ultrasonic sensor
distanceCm() - get the distance
### Wired Serial
Serial(baudrate) - intialize the serial
log(msg) - send the msg in log form
log_no_newline(msg) - send the msg in log form without newline
write(msg) - send the msg normally
### felixmeter
felixmeter(port number of line follower) - initialize the felixmeter
run(sector, m1, m2) - run at m1 m2 until reach targeted sector
## remind
If you want to make the code into release mode which make the code run faster, please disable the debug mode by commnect the code at hw/config/h line 11 to 14
If the code is too big or the RAM is not enough, release mode also can be enable to release some compute resource.
release mode MAY cause some bug