/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Javier/UCB/Proyecto/Particle/HelloWorld/HelloWorld/src/HelloWorld.ino"
#include "MQTT.h"

void setup();
void loop();
#line 3 "d:/Javier/UCB/Proyecto/Particle/HelloWorld/HelloWorld/src/HelloWorld.ino"
void callback(char* topic, byte* payload, unsigned int length);

/**
 * if want to use IP address,
 * byte server[] = { XXX,XXX,XXX,XXX };
 * MQTT client(server, 1883, callback);
 * want to use domain name,
 * exp) iot.eclipse.org is Eclipse Open MQTT Broker: https://iot.eclipse.org/getting-started
 * MQTT client("mqtt.eclipse.org", 1883, callback);
 **/
byte broker[] = {165, 227, 185, 78};
MQTT client(broker, 1883, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;

    if (!strcmp(p, "RED"))
        RGB.color(255, 0, 0);
    else if (!strcmp(p, "GREEN"))
        RGB.color(0, 255, 0);
    else if (!strcmp(p, "BLUE"))
        RGB.color(0, 0, 255);
    else
        RGB.color(255, 255, 255);
    delay(1000);
}


void setup() {
    RGB.control(true);

    // connect to the server
    client.connect("sparkclient", "603fe7e6085a4950dc3d1903", "203ebd274c20215d4b9f1bb10d1db62f5b6fc0423034b490355a4cadd1ebd28d");

    // publish/subscribe
    if (client.isConnected()) {
        client.publish("outTopic/message","hello world");
        client.subscribe("inTopic/message");
    }
}

void loop() {
    if (client.isConnected())
        client.loop();
}
