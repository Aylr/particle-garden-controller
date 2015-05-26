// ************************* DEFINITIONS *************************
#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)

// ************************* VARIABLES *************************
unsigned long last_cloud_time_sync = millis();


// ************************* SETUP *************************
void setup() {
	// set time zone to MST (daylight -6, std -7) on each boot
	set_time_zone(-6);
	publish_event("Booted", NULL);
}


// ************************* MAIN LOOP *************************
void loop() {
	if (check_sync_timer()) { 
		sync_time_with_cloud();
	}
}


// ************************* MISC FUNCTIONS *************************

// int API(String command){
// 	// parse commands coming in via the particle cloud

// 	return true; // or something
// }

// void set_rain_delay(int delay_time){
// 	// set rain delay for delay_time number of hours
// }


// ************************* ZONE FUNCTIONS *************************

void run_zone_for_duration(char zone_number, int duration){
	// turn on zone for duration

	// set timer and run
	change_zone_valve(zone_number, 1);
}

bool change_zone_valve(char zone_number, bool on_or_off){
	// turn the specified zone on or off

	return on_or_off;
}

void zones_all_off(){
	// turn all zones off
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
	Spark.syncTime();
	last_cloud_time_sync = millis();
	publish_event("time synced", NULL);
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