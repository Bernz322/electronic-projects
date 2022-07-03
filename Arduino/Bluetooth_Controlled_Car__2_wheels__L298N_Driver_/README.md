<h1 align="center">Bluetooth Controlled Two Wheeled Car</h1>
<p align="center">
 A hobby project. 
</p>

### 🛠️ Components

<ul>
   <li>Arduino Uno.</li>
   <li>L298 Motor Driver.</li>
   <li>HC-05 Bluetooth.</li>
   <li>Two DC Motors.</li>
   <li>Breadboard.</li>
   <li>18650 Batteries w/ enough Voltage and Current for both the Driver and Bluetooh.</li>
   <li>Playstore - <a href='https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=en&gl=US'>Bluetooth RC Controller</a></li>
</ul>

## ❓ How to use

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software).

2. Carefully configure the wirings and components. Make sure that the battery can handle the voltage and current of the project. Read the documentation of each components.

3. Before uploading the code, make sure that you have selected the correct BOARD and PORT of your Arduino by going to **Tools->Board** and **Tools->Port**.

4. Run the Bluetooth RC Controller App together with the Two-Wheeled Car. Connect to its bluetooth with the password `1234`.

5. In case if the App doesn't work although the Arduino Hardware is running, check if the battery is enough as HC-05 is very sensitive to power consumption.
