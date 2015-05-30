// This #include statement was automatically added by the Spark IDE.
#include "TimeAlarms/TimeAlarms.h"

// ************************* DEFINITIONS *************************
#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
#define ZONE0 0
#define ZONE1 1
#define ZONE2 2
#define ZONE3 3

// ************************* VARIABLES *************************
unsigned long last_cloud_time_sync = millis();
byte zone_state_array[4] = {0,0,0,0};
byte zones[4] = {ZONE0, ZONE1, ZONE2, ZONE3};
byte test_timer = 20;	// seconds for "relay test heartbeat timer"

int API_test(String command);

// ************************* SETUP *************************
void setup() {
	// set time zone to MST (daylight -6, std -7) on each boot
	set_time_zone(-6);

	// pin setup and initialization
	for (int i = 0; i < 4; i++){
		pinMode(zones[i], OUTPUT);
		digitalWrite(zones[i], LOW);
	}


	publish_event("GardenPhoton Booted", NULL);

	// Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
	// Alarm.alarmRepeat(17,45,10,EveningAlarm);  // 5:45pm every day 
	// Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 

    Alarm.timerRepeat(test_timer, Repeats);     // timer for every 15 seconds    

	Spark.function("test", API_test);
}

int API_test(String command) {
	toggle_zone_state(ZONE0);
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
	Alarm.delay(0); // required for all alarms (the point where it can check)
	if (check_sync_timer()) { 
		sync_time_with_cloud();
	}


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