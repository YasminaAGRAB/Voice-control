#include <Servo.h>

#define WIFI_NAME "jessy"
#define WIFI_PASSWORD "esisba2017"
#define DEVICE_ID 1
#define DEVICE_NAME "ESP"
#define TOKEN "~619330_bfxe7dwOY8SC"


#include <RemoteMe.h>
#include <RemoteMeSocketConnector.h>
#include <ESP8266WiFi.h>
#define relay D5
#define servo D1
#define buzzer D3

//uint8_t LEDpin = D5;//ADDED
Servo myservo; //ADDED

RemoteMe& remoteMe = RemoteMe::getInstance(TOKEN, DEVICE_ID);

//*************** CODE FOR COMFORTABLE VARIABLE SET *********************

inline void setRELAY_01(boolean b) {remoteMe.getVariables()->setBoolean("RELAY_01", b); }
inline void setSERVO(int32_t i) {remoteMe.getVariables()->setInteger("SERVO", i); }

//*************** IMPLEMENT FUNCTIONS BELOW *********************

void onRELAY_01Change(boolean b) {
    digitalWrite(relay,b?HIGH:LOW);
}
void onSERVOChange(int32_t i) {
     myservo.write(i);
}




void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.print("connected");
  
  myservo.write(120);
  Serial.print("hey");
  pinMode(relay,OUTPUT);
  pinMode(servo,OUTPUT);
  pinMode(buzzer,OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  remoteMe.getVariables()->observeBoolean("RELAY_01" ,onRELAY_01Change);
  remoteMe.getVariables()->observeInteger("servo" ,onSERVOChange);

  remoteMe.setConnector(new RemoteMeSocketConnector());
  remoteMe.sendRegisterDeviceMessage(DEVICE_NAME);

  myservo.attach(servo);//ADDED
  pinMode(relay, OUTPUT);//ADDED
  digitalWrite(relay, LOW);//ADDED
}


void loop() {
  remoteMe.loop();
}

