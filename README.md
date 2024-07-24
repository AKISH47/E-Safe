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

# How it works - Web app
![Screenshot from 2024-07-24 14-50-42](https://github.com/user-attachments/assets/e7adf33e-bec4-403e-a3ad-9b35e89f491e)
![Screenshot from 2024-07-24 14-51-41](https://github.com/user-attachments/assets/94a81152-6510-4302-8612-a6f85d9f7b2a)

1. The e- safe app  first asks the ESP32 for the value from the temperature and voltage sensors.
2. Based on these inputs the ESP decides the state of the relay -  if it is on or off. If it is on, its charging else, its not.
3. The app displays the temperature and based on the state of the relay, it displays whether it is currently charging or stopped
4. The green button tells the ESP32 to change the state of the relay turning the relay on or off. Once pressed, the button turns red and has different text. 

# Presentation and Poster Links:
https://docs.google.com/presentation/d/1ag3dtNzHqOU7Nol9aGwX6iRKKu9hUqkFr-nJTckO5vc/edit#slide=id.g2703fdad717_0_181
https://docs.google.com/presentation/d/1rj1jq7bTPCQjz--uucjNxwSHfUO89c8W/edit#slide=id.p1










