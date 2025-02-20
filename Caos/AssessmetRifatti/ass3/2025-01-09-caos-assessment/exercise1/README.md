# Exercise 1 — Linux kernel module

An embedded platform running embedded Linux is equipped with a custom memory-mapped hardware component consisting of a matrix of 16x16 LEDs that can be used to display digits.

The component is mapped in memory through the following registers:

* `0x00080000` — Control register. This register is used to control and configure the component. It is a 32bit word where bits have the following meanings:
	* bit 0: enable bit (1: enabled, 0: disabled)
	* bit 1-2: colour bits. It allows to configure the colour of the LEDs (00: white, 01:yellow, 10: green, 11:red)
	* bit 3: blinking bit (1: blinking, 1: not-blinking)
	* bit 5-8: blinking rate (it enables to set the blinking rate among 16 possible levels)
	* bit 9-12: intensity (it enables to set the LED intensity among 16 possible levels)

	
Write a LINUX device driver (to be tested on a standard LINUX distribution) that can control this specific device. 

* You can decide how to organise your device driver based on functionalities.  
* Add short comments in your code to explain your choices. 
* Pay attention to the user/kernel mode memory management
* Low-level memory operations must be present in your code. However, to test your code, please place them in a comment and substitute them with equivalent log messages.
* The folder you deliver must be a working project ready to be tested on a Linux machine, including the related Makefile.


You are allowed to consult the Linux Kernel Module Programming Guide to develop this code [https://sysprog21.github.io/lkmpg/#introductio](https://sysprog21.github.io/lkmpg/#introductio)
