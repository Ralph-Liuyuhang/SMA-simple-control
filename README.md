The drive module adopts Irf520 Mosfet Module 140c07

Ranging signal line————A3

pwm1————P2

pwm2————P3

File "5mm_control" is a simple open-loop test. The pins are slightly different from the final closed-loop pins. Readers are asked to distinguish simple questions by themselves. It mainly tests whether the two SMAs are usable and whether the SMA can be shrunk by the thermal effect of current.

If you need to add new degrees of freedom and new SMA for control later, you can continue to add PWM later.

Enter the setpoint, and after burning, the system will automatically approach the setpoint, and use the PID algorithm to close the loop to stabilize near the setpoint and continue to do so.
