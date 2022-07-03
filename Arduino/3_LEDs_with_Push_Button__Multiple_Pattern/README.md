<h1 align="center">Multi Patterned LED (3x) with Push Button</h1>
<p align="center">
 A simple 3 LED pattern with a push button for changing patterns.
</p>

## ❓ How to use

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software).

2. Connect multiple LED's and a push button to the Arduino. Store them in a variable for easy access.
   <br>

   `const int redLED = 10;`
   <br>
   `const int yellowLED = 11;`
   <br>
   `const int greenLED = 12;`
   <br>
   `const int pinButton = 8;`

3. Initialize them in void setup().
   <br>

   `pinMode(greenLED, OUTPUT);`
   <br>
   `pinMode(yellowLED, OUTPUT);`
   <br>
   `pinMode(redLED, OUTPUT);`
   <br>
   `pinMode(buzzerPin, OUTPUT);`

4. Modify or Add Patterns to your liking.
   <br>

   ```
   void PatternN(){
       Insert new pattern here
   }
   ```

5. Before uploading the code, make sure that you have selected the correct BOARD and PORT of your Arduino by going to **Tools->Board** and **Tools->Port**.
   <br>

   `Verify and Upload`
