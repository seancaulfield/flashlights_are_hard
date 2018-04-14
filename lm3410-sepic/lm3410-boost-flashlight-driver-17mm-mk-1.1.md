Mk 1.1 changes: 
* switched to PFL2512 inductor (much smaller but still in spec and hopefully other 2512 inductors as alternatives)
* relabeled PWM2 to "0" (for PB0, the pin it's attached to)
* added pan for PB4, labeled "4"
* switched OTC back to "usual" pin PB3
* vdiv switched back to "usual" pin PB2
* heavily reworked layout

Basic boost design for the LM3410X (SOT-23 package). Designed to drive a low Vf Nichia 319AT white LED as well as work with the slightly lower voltage of LiFePO4 cells (3.2V nominal, 2.5V min/dead). While Nicha 319AT's have a Vf=3.0V at If=1A, at If=2A it climbs to ~3.25V, which is just enough to make direct drive "meh" if the battery isn't near full. Ergo, time for a boost mode driver.

* U1 - ATTiny13 / ATTiny25
* U2 - LM3410X
* R1 - 0603 19.1Kohm
* R2 - 0603 4.7Kohm
* R3 - 0805 0.127ohm
* C1 - 0603 10uF 6.3V
* C2 - 0603 1uF
* C3 - 0603 4.7uF
* C4 - 0603 10uF 10V
* D1, D2 - SOD323 Schottky 1.5A+ BATJ169 (or similar)
* L1 - 1uH *Coilcraft PFL2512* (or similar)

Iout around 1.5A; gets reaalllly close to the LM3410's internal switch limit (2.8A) but should not exceed it even with 50% ripple from 2.5V.
