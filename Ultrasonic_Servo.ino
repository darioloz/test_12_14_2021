//define Pins
#include <Servo.h>

Servo servo;

unsigned long heartbeat_timer;
unsigned long check_distance_timer;

int trigPin = 7;
int echoPin = 6;

// defines variables
long duration;
int distance;

//function prototypes
void timers(void);
void heartbeat_control(void);
void check_distance_control(void);

void setup()
{
  servo.attach(9);
  servo.write(0);
  delay(2000);

  // Sets the trigPin as an Output
  pinMode(trigPin, OUTPUT);
  // Sets the echoPin as an Input
  pinMode(echoPin, INPUT);
  // Starts the serial communication
  Serial.begin(9600);
}
void loop()
{

  timers();
  heartbeat_control();
  check_distance_control();

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if ( distance <= 25   ) // Change Distance according to Ultrasonic Sensor Placement
  {

    servo.write(0);
   // delay(3000);
  }
  else
  {
    servo.write(90);

  }

}

void check_distance_control(void)
{
	//if(check_distance_timer > 1) // 0-1-0-1-0-1.... every 200 ms OR 5 times per second
	//if(check_distance_timer > 4) // 0-1-2-3-4-0.... every 500 ms OR 2 times per second
	if(check_distance_timer > 4) //
	{  
		// Clears the trigPin
		  digitalWrite(trigPin, LOW);
		  delayMicroseconds(2);
		  // Sets the trigPin on HIGH state for 10 micro seconds
		  digitalWrite(trigPin, HIGH);
		  delayMicroseconds(10);
		  digitalWrite(trigPin, LOW);
		  // Reads the echoPin, returns the sound wave travel time in microseconds
		  duration = pulseIn(echoPin, HIGH);
		  // Calculating the distance
		  distance = duration * 0.034 / 2;
	}

}

void heartbeat_timer(void)
{
	if(heartbeat_timer < 10)
		digitalWrite(13,HIGH);
	else if(heartbeat_timer < 20)
		digitalWrite(13,LOW);
	else
		heartbeat_timer = 0;
}

void timers(void)
{
	static unsigned long ms_runtime;
	static int one_ms_timer;
	if(millis() > (ms_runtime + 1))
	{
		ms_runtime = ms_runtime + 1;
		one_ms_timer++;  
	}
	else if( ms_runtime > millis())
	{ // ELSE PART IS NOT NEEDED unless you 
	  // are running your code for more than _40___ days
		ms_runtime = millis();
	}
	if(one_ms_timer > 99)
	{ // our choice for 99 gives us increments of 100 ms
		one_ms_timer = 0;
		heartbeat_timer++;
		check_distance_timer++;
		
	}
}
