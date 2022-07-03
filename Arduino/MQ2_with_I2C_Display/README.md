<h1 align="center">MQ2 Smoke Sensor with LCD, LED, and Buzzer</h1>
<p align="center">
 A simple MQ2 Sensor showcase which senses smoke in its vicinity and depending on its value displayed in an I2C LCD, a buzzer and an LED will go HIGH.
</p>

## ❓ How to use

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software).

2. Include LiquidCrystal_I2C library.

3. Modify smoke value to trigger the buzzer/ LED to your liking.
   <br>

   `if(value > N) : Line 27`

4. Before uploading the code, make sure that you have selected the correct BOARD and PORT of your Arduino by going to **Tools->Board** and **Tools->Port**.
   <br>

   `Verify and Upload`
