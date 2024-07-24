# E-Safe - automatic cut-off circuit for e-bike charging --> For National Engineering Design Challenge - https://nedc.mesausa.org/

# Problem -- Ebike fires happen all over the United States due to overcharing electric vehicles
![Screenshot from 2024-07-24 12-00-40](https://github.com/user-attachments/assets/12ed4b0a-d624-42b0-adb9-f0bf418dfadf)

# Proposed Solution 
Use a relay to automatically turn on and off the charging process controlled by an ESP32 microcontroller
![Screenshot from 2024-07-24 12-23-25](https://github.com/user-attachments/assets/66a2159d-fcd4-45ce-bdf1-cf8128ce2fa2)

# Parts Used
1. ESP32  (micro-controller) - $3
2. 1 Channel AC 250V/ DC 30V Relay (to turn charging on or off ) - $2
3. AC/DC 5V Converter (to power ESP32 from Relay load ) - $1
4. DHT11 Digital Temperature And Humidity Sensor (to measure temperature of the battery) - $4
5. Resistors (measures voltage output) - $0.20
6. Extension Cord ( for charger to plug into) - $2
7. Filament ( for enclosure of parts ) - $0.30
8. Miscellaneous ( wires, screws, connectors ) - $0.50
Total: 13 dollars(approximate)

# How it works
![Screenshot from 2024-07-24 11-46-06](https://github.com/user-attachments/assets/b6f24d2d-bcd3-4872-a48b-c902c6c23dd9)

1. First, a male plug connects to the wall outlet whose extension cord is attached to E-Safe.
2. Second, the extension cord goes to the relay where the voltage will be controlled.
3. Third, the ESP32 gets inputs from the voltage (through a “jig”) and temperature sensor.
4. Next, the 5V AC/DC converter takes the 220V and converts it to 5V DC for the ESP32.
5. Then, based on the inputs, the ESP32 turns the relay on or off.
6. Finally, the output of the relay goes to the female connector of the extension cord where the battery charger can be plugged in.









