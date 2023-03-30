# Multitasking-using-mutexes

This repository contains an example project for counting button presses and displaying the count on an LED array. The project is implemented on an LPC1768 board using the CMSIS-RTOS2 operating system.

<b><h2>Installation and Usage</b></h2>

- Clone the repository to your local machine.
- Open the project in an IDE that supports the LPC1768 board and CMSIS-RTOS2, such as Keil or LPCXpresso.
- Build the project.
- Flash the compiled binary onto the LPC1768 board.
- Connect a button to pin P2.10 and connect LEDs to pins P1.28, P1.29, P1.31, P2.2, P2.3, P2.4, P2.5, and P2.6.
- Press the button and observe the LEDs to see the count increase.

<b><h2>Code Explanation</b></h2>

The project contains two threads: adder and LED. The adder thread continuously polls the state of the button connected to P2.10 and increments a count variable whenever the button is pressed. The LED thread continuously updates the state of the LEDs connected to the LPC1768 board's pins based on the count variable.

The threads are synchronized using a mutex. The adder thread acquires the mutex before updating the count variable to prevent data corruption, and the LED thread acquires the mutex before accessing the count variable to prevent data races.
