<h1 align="center">IoT-based Attendance System using RFID and Face Recognition with SMS Capability</h1>
<p align="justify">
 My Undergraduate Thesis where I used a Raspberry Pi 4B. The project is connected in a Node.js-Express.js based REST API which consumes both GET and POST HTTP Methods. To read more, <a href='https://www.jeffreybernadas.tech/thesis' target='_blank' rel='noreferrer'>click me</a>.
</p>

## 🖼️ Preview

### 🧠 What you'll learn

<ul>
   <li>You'll be able to interface the following: </li>
    <ul>
      <li>RC522 Reader with Raspberry Pi (Read & Write).</li>
      <li>SIM900A GSM Module with Raspberry Pi (Send SMS).</li>
      <li>1.3in OLED with Raspberry Pi.</li>
    </ul>
    <li>Send HTTP Requests to any REST API (GET & POST HTTP Methods) with Raspberry Pi.</li>
    <li>Python Multithread (Run Face Recognition and Attendance Recording Simultaneously).</li>
</ul>

### 🛠️ Project Components

<ul>
   <li>Raspberry Pi 4B (4GB RAM) - Main brain of the project.</li>
   <li>RC522 RFID Reader - To read RFID tags which will determine who the owner is inside the database.</li>
   <li>1.3inch OLED - To display instructions, and information on what process it is currently undergoing.</li>
   <li>SIM900 A GSM Module - To send an SMS alert to the phone number of the parents after a successful RFID Scan.</li>
   <li>Hi-Link AC-DC Step-down PSU - To supply enough power needed.</li>
   <li>An Online/ Offline REST API - Create one (GET & POST).</li>
   <li>Computer Peripherals</li>
</ul>

## ❓ How to use

1. Install Raspberry Pi OS and configure them.

2. Download and install [Thonny IDE](https://thonny.org/).

3. Create your REST API (POST & GET).

4. Install all required libraries for each external components.

5. Carefully connect all external components to the Raspberry Pi.

6. Tweak the final-script.py code to your liking. Read comments to understand them better.

### 📓 How it works

<ol>
  <li>Prompt admin if they want to register a new student ('Y') or start recognition and attendance recording ('N').</li>
  <li>If 'Y' (Register)</li>
    <ol>
      <li>The admin will be asked to input the student name to check if they are already registered, if not then Camera Starts and a Frame will open. Face the camera directly and press 'Space' key to capture images (Five images). 'ESC' key is then pressed to exit the frame.</li>
      <li>The captured images will then be trained using the encodings.pickle and save them in a directory named to them.</li>
      <li>Admin will then be asked to input the student name again and scan an RFID to embed their name to it.</li>
    </ol>
  <li>If 'N' (Start Recognition & Attendance Recording)</li>
    <ol>
      <li>Camera starts and a frame will open for the face recognition. The RC522 will also be ready for RFID scanning.</li>
      <li>To record attendance, the student's face must first be recognized via the face recognition and then scan their RFID tag. If the name displayed in the face recognition frame is not the same to the name embedded to the RFID tag, then a warning is displayed in the 1.3inch OLED.</li>
      <li>If they match, then the script communicates to the REST API (GET) to check if that user exists in the database, if they aren't then a warning again is displayed.</li>
      <li>If they exist in the database, then it will retrieve the phone number of that student and send a POST request to create the attendance in the database. Lastly, the retrieved number is passed to the SIM900A function to send an SMS to it.</li>
    </ol>
  <li>The script loops whatever option is selected.</li>
  <li>To read more, <a href='https://www.jeffreybernadas.tech/thesis' target='_blank' rel='noreferrer'>click me</a>.</li>
</ol>
