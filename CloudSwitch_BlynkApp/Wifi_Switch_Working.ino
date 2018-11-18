//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//// your authentication token received from Blynk (eg:54rfgtacab7b74f8981153fc753b4frth )
char auth[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

//WiFi credentials.
char ssid[] = "yourwifissid";
char pass[] = "yourwifipassword";

const int btnPin = D2;             // pin for physical push button switch.
const int btnPin1 = D3;             // pin for physical push button switch.
const int RelayPin = D4;         // pin for relay output.
const int RelayPin1 = D5;         // pin for relay output.

BlynkTimer timer;
void checkPhysicalButton();
int btnPinState = LOW;           // ON
int btnPinState1 = LOW;           // ON

int RelayPinState = HIGH;        // OFF
int RelayPinState1 = HIGH;        // OFF

//*******Sets Relays to Off Position*****************
#define TURN_ON 0                 // TURN_ON and TURN_OFF are defined to account for Active High relays
#define TURN_OFF 1                // Used to switch relay states

void setup()
{
  Serial.begin (9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(RelayPin, OUTPUT);            //  initialize your pin as output.
  pinMode(RelayPin1, OUTPUT);            //  initialize your pin as output.
  pinMode(btnPin, INPUT_PULLUP);        //  initialize your pin as input with enable internal pull-up resistor "input_pullup"
  pinMode(btnPin1, INPUT_PULLUP);        //  initialize your pin as input with enable internal pull-up resistor "input_pullup"
  digitalWrite(RelayPin, RelayPinState);
  digitalWrite(RelayPin1, RelayPinState1);
  digitalWrite(RelayPin, TURN_OFF);     // remain off till command is receive
  digitalWrite(RelayPin1, TURN_OFF);     // remain off till command is receive

  // Setup a function to be called every 100 ms
  timer.setInterval(100L, checkPhysicalButton);
}

// Every time we connect to the cloud...
BLYNK_CONNECTED()
{
  // Request the latest state from the server
  Blynk.syncVirtual(V1);
    Blynk.syncVirtual(V2);

}

// When App button is pushed - switch the state
// Map this Virtual Pin to your Mobile Blynk apps widget.
BLYNK_WRITE(V1)
{                           
  RelayPinState = param.asInt();
  digitalWrite(RelayPin, RelayPinState);
}
BLYNK_WRITE(V2)
{                           
  RelayPinState1 = param.asInt();
  digitalWrite(RelayPin1, RelayPinState1);
}

void checkPhysicalButton()
{
  if (digitalRead(btnPin) == LOW)
  {
    // btnPinState is used to avoid sequential toggles
    if (btnPinState != LOW)
    {
      // Toggle relay state
      RelayPinState = !RelayPinState;
      digitalWrite(RelayPin, RelayPinState);
      Blynk.virtualWrite(V1, RelayPinState);  //Update button widget
    }

    btnPinState = LOW; 
  }
  else
  {
    btnPinState = HIGH;
  }


if (digitalRead(btnPin1) == LOW)
  {
    // btnPinState is used to avoid sequential toggles
    if (btnPinState1 != LOW)
    {
      // Toggle relay state
      RelayPinState1 = !RelayPinState1;
      digitalWrite(RelayPin1, RelayPinState1);
      Blynk.virtualWrite(V2, RelayPinState1);  //Update button widget
    }

    btnPinState1 = LOW; 
  }
  else
  {
    btnPinState1 = HIGH;
  }
  
}

void loop()
{
  Blynk.run();                               // Run Blynk
  timer.run();                               // Run SimpleTimer
}
