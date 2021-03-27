#include "MQTT.h"

void callback(char *topic, byte *payload, unsigned int length);

int x = 0;
int y = 0;

class Robot {
    private: 
    int m1F;
    int m1B;
    int m2F;
    int m2B;

    public:
    Robot(int m1F, int m1B, int m2F, int m2B) {
        this->m1F = m1F;
        this->m1B = m1B;
        this->m2F = m2F;
        this->m2B = m2B;
        pinMode(m1F, OUTPUT);
        pinMode(m1B, OUTPUT);
        pinMode(m2F, OUTPUT);
        pinMode(m2B, OUTPUT);

        digitalWrite(m1F, LOW);
        digitalWrite(m1B, LOW);
        digitalWrite(m2F, LOW);
        digitalWrite(m2B, LOW);
    }

    void stop() {
        digitalWrite(m1F, LOW);
        digitalWrite(m1B, LOW);
        digitalWrite(m2F, LOW);
        digitalWrite(m2B, LOW);
    }

    void moveForeward() {
        digitalWrite(m1F, HIGH);
        digitalWrite(m1B, LOW);
        digitalWrite(m2F, HIGH);
        digitalWrite(m2B, LOW);
    }

    void moveBackward() {
        digitalWrite(m1F, LOW);
        digitalWrite(m1B, HIGH);
        digitalWrite(m2F, LOW);
        digitalWrite(m2B, HIGH);
    }

    void moveLeft() {
        digitalWrite(m1B, LOW);
        digitalWrite(m2B, LOW);

        analogWrite(m1F, 180);
        digitalWrite(m2F, HIGH);
    }

    void turnLeft() {
        digitalWrite(m1F, LOW);
        digitalWrite(m1B, HIGH);
        digitalWrite(m2F, HIGH);
        digitalWrite(m2B, LOW);
    }

    void moveRight() {
        digitalWrite(m1B, LOW);
        digitalWrite(m2B, LOW);

        digitalWrite(m1F, HIGH);
        analogWrite(m2F, 180);
    }

    void turnRight() {
        digitalWrite(m1B, LOW);
        digitalWrite(m1F, HIGH);
        digitalWrite(m2B, HIGH);
        digitalWrite(m2F, LOW);
    }

    void moveBackRight() {
        digitalWrite(m1F, LOW);
        digitalWrite(m2F, LOW);

        digitalWrite(m1B, HIGH);
        analogWrite(m2B, 180);
    }

    void moveBackLeft() {
        digitalWrite(m1F, LOW);
        digitalWrite(m2F, LOW);

        digitalWrite(m2B, HIGH);
        analogWrite(m1B, 180);
    }
};

Robot robot(D0, D3, D5, D8);

MQTT iotlabs("192.168.0.10", 1883, callback);

// recieve message
void callback(char *topic, byte *payload, unsigned int length)
{
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;

    if (!strcmp(topic, "iotlabs/lab1/joystick_X"))
    {
        if (!strcmp(p, "0"))
        {
            x = 0;
        }
        else if (!strcmp(p, "1"))
        {
            x = 1;
        }
        else if (!strcmp(p, "-1"))
        {
            x = -1;
        }
    }
    else if (!strcmp(topic, "iotlabs/lab1/joystick_Y"))
    {
        if (!strcmp(p, "0"))
        {
            y = 0;
        }
        else if (!strcmp(p, "1"))
        {
            y = 1;
        }
        else if (!strcmp(p, "-1"))
        {
            y = -1;
        }
    }
}

void setup() {
    Particle.syncTime();
    waitUntil(Particle.syncTimeDone);

    // connect to the server
    iotlabs.connect("ParticleArgon", "603fe7e6085a4950dc3d1903", "203ebd274c20215d4b9f1bb10d1db62f5b6fc0423034b490355a4cadd1ebd28d");

    iotlabs.publish("iotlabs/lab1/new/device", "Particle");
    // subscribe to topics
    if (iotlabs.isConnected()) {
        iotlabs.subscribe("iotlabs/lab1/joystick_X");
        iotlabs.subscribe("iotlabs/lab1/joystick_Y");
    }

    // led.setOnTime(23, 20, 0);
    // led.setOffTime(23, 25, 0);
    // led.setProgramState(true);
}

void loop() {
    delay(1000);
    if (iotlabs.isConnected()) {
        iotlabs.loop();
        if (x == 0 && y == 0) {
            // stop
            robot.stop();
        } else if (x == 0 && y == 1) {
            // foreward
            robot.moveForeward();
        } else if (x == 0 && y == -1) {
            // backward
            robot.moveBackward();
        } else if (x == 1 && y == 0) {
            // right
            robot.turnRight();
        } else if (x == -1 && y == 0) {
            // left
            robot.turnLeft();
        } else if (x == 1 && y == 1) {
            // top right
            robot.moveRight();
        } else if (x == -1 && y == 1) {
            // top left
            robot.moveLeft();
        } else if (x == 1 && y == -1) {
            // back right
            robot.moveBackRight();
        } else if (x == -1 && y == -1) {
            // back left
            robot.moveBackLeft();
        }
    }
}
