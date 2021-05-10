# Introduction
Closing-opening the door with ESP32 via Blynk application is a basic project that Nong Poo Nim has been assigned to develop this. The development consists of an ESP32 and Servo motor.
The Servo motor connection arm applied from <a href="https://www.youtube.com/watch?v=_pcEXlyhIIU" target="_blank">"DIY mini project to open and close the door with mobile phone esp8266 + Blynk (default)"</a> and Servo motor rotation via Blynk applied from <a href="https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/" target="_blank">"ESP32 Servo Motor Web Server with Arduino IDE"</a>.

<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/Close-Open%20the%20door%20with%20ESP32/images/Screenshot_20210510-113844_Blynk.jpg" width="250">

# Connecting the Servo Motor to the ESP32
Servo motors have three wires: power, ground, and signal. The power is usually red, the GND is black or brown, and the signal wire is usually yellow, orange, or white.
<br><br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/Close-Open%20the%20door%20with%20ESP32/images/servo-motor-wires.jpg" width="550">
| Wire  | Color |
| ------------- | ------------- |
| Power  | Red  |
| GND | Black, or brown |
| Signal | Yellow, orange, or white |
<br>
When using a small servo like the S0009 as shown in the figure below, you can power it directly from the ESP32.
<br><br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/Close-Open%20the%20door%20with%20ESP32/images/servo-motor-s009.jpg" width="550">
<br>
But if you’re using more than one servo or other type, you’ll probably need to power up your servos using an external power supply.
<br><br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/Close-Open%20the%20door%20with%20ESP32/images/servo-motors.jpg" width="550">
<br>
If you’re using a small servo like the S0009, you need to connect:
<ul>
<li>GND -> ESP32 GND pin;</li>
<li>Power -> ESP32 VIN pin;</li>
<li>Signal -> GPIO 13 (or any PWM pin).</li>
</ul>

# Schematic
In our examples we’ll connect the signal wire to GPIO 13. So, you can follow the next schematic diagram to wire your servo motor.
<br><br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/Close-Open%20the%20door%20with%20ESP32/images/servo-esp32-schematic.png" width="550">
<br>
<i>(This schematic uses the ESP32 DEVKIT V1 module version with 36 GPIOs – if you’re using another model, please check the pinout for the board you’re using.)</i>

# How to Control a Servo Motor?
You can position the servo’s shaft in various angles from 0 to 180º. Servos are controlled using a pulse width modulation (PWM) signal. This means that the PWM signal sent to the motor will determine the shaft’s position.
<br><br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/Close-Open%20the%20door%20with%20ESP32/images/0-180-degrees.png" width="550">
<br>
To control the motor you can simply use the PWM capabilities of the ESP32 by sending a 50Hz signal with the appropriate pulse width. Or you can use a library to make this task much simpler.
<br>

# Preparing the Arduino IDE
There’s an add-on for the Arduino IDE allows you to program the ESP32 using the Arduino IDE and its programming language. Follow one of the next tutorials to prepare your Arduino IDE to work with the ESP32, if you haven’t already.
<ul>
  <li><a href="https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/" target="_blank">Windows instructions – ESP32 Board in Arduino IDE</a></li>
  <li><a href="https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-mac-and-linux-instructions/" target="_blank">Mac and Linux instructions – ESP32 Board in Arduino IDE</a></li>
</ul>
After making sure you have the ESP32 add-on installed, you can continue this tutorial.

# Installing the ESP32_Arduino_Servo_Library
The ESP32 Arduino Servo Library makes it easier to control a servo motor with your ESP32, using the Arduino IDE. Follow the next steps to install the library in your Arduino IDE:
<br>
<ul>
  <li>Click here to download the <a href="https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/" target="_blank">ESP32_Arduino_Servo_Library</a>. You should have a .zip folder in your Downloads folder</li>
  <li>Unzip the .zip folder and you should get ESP32-Arduino-Servo-Library-Master folder</li>
  <li>Rename your folder from ESP32-Arduino-Servo-Library-Master to ESP32_Arduino_Servo_Library</li>
  <li>Move the ESP32_Arduino_Servo_Library folder to your Arduino IDE installation libraries folder</li>
  <li>Finally, re-open your Arduino IDE</li>
</ul>

# Reference
<ul>
  <li>https://www.youtube.com/watch?v=hTQslbGyv5s</li>
  <li>https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/</li>
</ul>
