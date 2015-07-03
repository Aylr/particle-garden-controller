// ************************* DEFINITIONS *************************
#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
#define ZONE0 0
#define ZONE1 1
#define ZONE2 2
#define ZONE3 3

// ************************* VARIABLES *************************

bool disable_watering = false;
unsigned long last_cloud_time_sync = millis();
byte zone_state_array[4] = {0,0,0,0};
byte zones[4] = {ZONE0, ZONE1, ZONE2, ZONE3};
byte test_timer = 20;	// seconds for "relay test heartbeat timer"
unsigned long default_watering_interval = ONE_DAY_MILLIS;	// seconds until next watering event
unsigned long default_watering_duration = 10;				// seconds to water
unsigned long api_interval = 10*1000;


// ************************* TIMER CLASS *************************

class Timer{
		// class member variables initialized at startup
		unsigned long timer_last_millis;							// stores the last event
		unsigned long timer_interval_millis;						// stores the interval called for
		
	public:
		// constructor - creates a timer and initializes variables
		Timer(unsigned long interval){
			timer_interval_millis = interval;
		}
		bool checkTimer(){
			unsigned long timer_current_millis = millis();			// get current 'time'
			
			if((timer_current_millis - timer_last_millis) >= timer_interval_millis){
				timer_last_millis = timer_current_millis;
				return true;										// it's time!
			}else{
				return false;										// it's not time.
			}
		}
		unsigned long interval(){
			return timer_interval_millis;
		}
		unsigned long last_ran() {
			return timer_last_millis;
		}
		unsigned long next_run() {
			return timer_last_millis + timer_interval_millis;
		}
};


// ************************* SETUP *************************
Timer zone_0_timer(api_interval);
Timer zone_1_timer(20*1000);

void setup() {
	// set time zone to MST (daylight -6, std -7) on each boot
	set_time_zone(-6);

	// pin setup and initialization
	for (int i = 0; i < 4; i++){
		pinMode(zones[i], OUTPUT);
		digitalWrite(zones[i], LOW);
	}


	publish_event("GardenPhoton Booted", NULL);

	Spark.function("test", API_test);
	Spark.function("handler", handler);
}

int API_test(String command) {
	toggle_zone_state(ZONE0);
	update_interval()
	publish_event("api", NULL);
}

void Repeats(){
  toggle_zone_state(ZONE0);
  publish_event("test-timer", String(test_timer));
}

bool toggle_zone_state(byte zone) {
	if(zone_state_array[zone]) {
		digitalWrite(zone, LOW);
		zone_state_array[zone] = 0;
	} else {
		digitalWrite(zone, HIGH);
		zone_state_array[zone] = 1;
	}

	publish_event("Zone Change", "{" + String(zone) + ":" + String(zone_state_array[zone]) + "}");// + ":" + String(zone_state_array[zone])));
	return zone_state_array[zone];
}


// ************************* MAIN LOOP *************************
void loop() {
	run_every_loop();
	



}

// ************************* INTERVAL FUNCTIONS *************************
void run_every_loop() {
	if (check_sync_timer()) { 
			sync_time_with_cloud();
	}
	if ( zone_0_timer.checkTimer() ) {			// check timer on zone 0
		toggle_zone_state(0);
	}
	if ( zone_1_timer.checkTimer() ) {			// check timer on zone 1
		toggle_zone_state(1);
	}
}


// ************************* API FUNCTIONS *************************

int handler(String inputString){
	byte tempReturn;
	String trimmedInputString = inputString.substring(1);	// trim off first charcter

	switch (inputString.substring(0,1).toInt()){			// switch based on first character
		case 0:												// 0 = all off
			zones_all_off();
			publish_event("mode", "off");
			tempReturn = 0;
			break;
		case 1:												// 1 = disable automatic watering
			disable_watering = true;
			publish_event("mode", "disable watering");
			tempReturn = 1;
			break;
		case 2:												// change zone state
			// ***** make a string to array function that you can pass the dirty string in and
			// get an array (or pointer to an array) containing all the clean data
			// then pass that clean data to the given function.
			change_zone_valve(trimmedInputString);
			publish_event("mode", "gradient");
			tempReturn = 2;
			break;
		default:
			tempReturn = -1;
			break;
	}
	updateAPIStripColors32();	// set the spark variable string with strip colors
	mode = tempReturn;	// update the current spark variable mode
	return tempReturn;	// return with the mode number
}

int string_to_array_ptr(){
	return 0;
}


// ************************* MISC FUNCTIONS *************************

// int API(String command){
// 	// parse commands coming in via the particle cloud

// 	return true; // or something
// }

void set_rain_delay(int delay_time){
	// set rain delay for delay_time number of hours

	publish_event("Rain Delay", String(delay_time));
}


// ************************* ZONE FUNCTIONS *************************

void run_zone_for_duration(char zone_number, int duration){
	// turn on zone for duration

	// set timer and run
	change_zone_valve(zone_number, 1);
}

bool change_zone_valve(char zone_number, bool on_or_off){
	// turn the specified zone on or off
	String status;

	if (on_or_off){
		status = "on";
	} else {
		status = "off";
	}

	publish_event("Zone Change", String(zone_number + ":" + status));

	return on_or_off;
}

void zones_all_off(){
	// turn all zones off

	publish_event("Zones All Off", NULL);
}


// ************************* SENSOR FUNCTIONS *************************

int check_moisture(){
	// setup moisture sensor
	// take a few readings and average
	int moisture_percent_average = 76;

	return moisture_percent_average;
}

int measure_flow(){
	// do sometihng to measure the flow of water
	int flow = 10;

	return flow;
}


// ************************* TIME FUNCTIONS *************************

void set_time_zone(float offset){
	// set the current time zone
	Time.zone(offset);
}

bool check_sync_timer(){
	// check if 24 hours have passed
	if (millis() - last_cloud_time_sync > ONE_DAY_MILLIS) {
		return true;
	} else {
		return false;
	}
}

void sync_time_with_cloud(){
	// update current time on microprocessor
// 	Spark.syncTime();
	last_cloud_time_sync = millis();

	publish_event("Time synced", NULL);
}


// ************************* PUBLISH FUNCTIONS *************************

void publish_event(String event_name, String data) {
    // publish an event
	Spark.publish(event_name, data, 60, PRIVATE);
}


// ************************* LOGGING FUNCTIONS *************************

// bool update_google_doc(){
// 	// log data points to google docs

// 	return true;
// }