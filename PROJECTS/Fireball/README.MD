# LED Visualizer/Controller

Arduino Circuit Diagram
![Arduino Circuit Diagram](Arduino/TrashFolder/image.png)

## How it Works

Inputs
I used a rotary encoder (PinCLK/PinDT) to change the animation speed via the EnIndex1 array. There are three buttons: one to start the system, one to flip the LED direction, and one to trigger the "Fireshow" mode. I also added a potentiometer on A5 to handle the brightness.

Animations
The "Fireball" effect moves a light across 6 LEDs. I used millis() instead of delay() so the app doesn't freeze and can still read the buttons. The "Fireshow" mode is a quicker, flashing sequence based on the current index.

The Technical Side
I wrote a custom BtnIsPressed function to handle debouncing, which stops the buttons from triggering multiple times by accident.
