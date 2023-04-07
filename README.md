# Smart_Study_Buddy

SMART STUDY BUDDY PROJECT REPORT

Introduction: 
The Smart Study Buddy is a project aimed at enhancing students' study experience by providing three different modes to choose from: Work, Chill, and Danger mode.
The project utilizes an Arduino board, three push buttons, an RGB LCD, and a distance sensor to detect when the door is opened.

NOTE:
This project is tailored to be used on MY linux mint laptop, and to connect to MY amazon echo dot using bluetooth. Make changes in the codes to change bluetooth, or the txt files to add your study materials and music.

Workings:

arduino_sketch:
1. The code defines the pins to be used for the green, blue, and red LED lights, and for the button, as well as the pins for the ultrasonic sensor.
2. The setup() function initializes the serial communication and sets the pin modes.
3. The loop() function checks the button state and sets the LED lights and danger mode based on the button state.
4. If the danger mode is on, the ultrasonic sensor is used to detect if an object is within 88 centimeters. If an object is detected, the danger mode is set and the red LED light is turned on.
5. If an object is no longer detected and danger mode is still on, the danger mode is turned off and the red LED light is turned off.

studyBuddy:
1. Reads the serial monitor and watches for texts 'chill_mode' 'work_mode' 'DANGER'.
2. Depending on the text it reads, it opens the program.

work_mode:
1. Opens the first link from a pre-determined study material text file 'study_materials.txt'.
2. Opens a random link from the text file 'study_music.txt'.
3. Opens a pomodoro timer website from a link in the text file 'pomodoro.txt'.
3. Connects to 'Echo Dot-V1R' using the device address.
4. Changes the volume level to 100%.

chill_mode:
1. Asks the user to choose a link from 'chill_mode.txt' by giving the option to choose a whole number. The numbers shown depends on the number of links in the text file.
2. Depending on the user response, a link is opened.
3. Connects to 'Echo Dot-V1R' using the device address.
4. Changes the volume level to 100%.

danger_mode:
1. Changes the volume level to 0%.
2. Opens the first link from a pre-determined study material text file 'study_materials.txt'.

Conclusion:
The Smart Study Buddy project provides students with a unique study experience, enabling them to choose between different study modes based on their mood and preferences. The project's flexibility and functionality make it an ideal study companion for students who want to optimize their study sessions.
