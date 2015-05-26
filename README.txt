# Particle Photon/Spark WiFi Garden Controller

## Primary Functions

- control two main water valves for sprinklers
- simple "programming" via IFTTT
- monitor soil moisture
- notifications on important events (low moisture, pressure drops, weather changes, etc)

## Extra Functions

- log data to google docs (through IFTTT)
- measure temperature
- weather alerts or adjustments via IFTTT
- measure incoming pressure (to make sure no roommate turned off the hose)

## Parts

- $9.95 flow sensor http://www.adafruit.com/products/828
- $6.95 12V solenoid http://www.adafruit.com/products/997
- $39.95 Particle Core (or $19.95 Particle Photon if available)
- $6-12 2+ relay board http://www.amazon.com/s/ref=nb_sb_noss?url=search-alias%3Daps&field-keywords=arduino+relay+baord
- free random 12V power supply
- weatherproof box of some fashion
- wire

### Soil Moisture Sensors (Hygrometers)
- $1.50 ebay china http://www.ebay.com/sch/i.html?_odkw=veggietronix&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR3.TRC2.A0.H0.Xsoil+moisture+sensor.TRS0&_nkw=soil+moisture+sensor&_sacat=0
- $4.95 Soil Moisture Sensor http://www.seeedstudio.com/depot/grove-moisture-sensor-p-955.html?cPath=144_147
- $43 Vegetronics waterproof moisture sensor with 5 meter cord http://vegetronix.com/Products/VH400/

## Firmware

- cloud variables
	- moisture
	- water flow
- cloud functions
	- valve (on/off, time each)
	- rain delay (time)

## Web Interface

- 
	
	
## Stub
- write main high level logic
- stub out smaller functions
- give them good names, determing what arguments they need
- make them return fake placeholder data as you would expect
- test your main high level loop
- write your lover level stub functions
- write unit tests for lower level stub functions
- iterate!