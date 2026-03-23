#ifndef IIC_TIMEOUT_US
    #define IIC_TIMEOUT_US 1000
#endif

/*
While waiting for acknowledgement, if the process lasts for over 1000 microseconds, stop the process
Please change it if needed
*/

#define IIC_ACK_RECEIVED 0
#define IIC_ERROR_TIMEOUT 1

#ifndef SCL
    #define SCL 9
#endif

#ifndef SDA
    #define SDA 10
#endif
/*
The default pins of SCL and SDA are respectively 9 and 10.
*/

/*
==========Basic IIC Functions==========
*/


void IIC_delay(uint8_t time);
void IIC_start();
void IIC_stop();
uint8_t IIC_waitACK();
void IIC_ACK();
void IIC_NACK();
void IIC_sendByte(uint8_t data);

void IIC_delay(uint8_t time)
{
    delayMicroseconds(time);
}

void IIC_start()
{
    pinMode(SCL, OUTPUT);
    pinMode(SDA, OUTPUT);
    digitalWrite(SDA, HIGH);
    digitalWrite(SCL, HIGH);
    IIC_delay(1);
    digitalWrite(SDA, LOW);
    IIC_delay(1);
    digitalWrite(SCL, LOW);
    digitalWrite(SDA, HIGH);
}

void IIC_stop()
{
    pinMode(SCL, OUTPUT);
    pinMode(SDA, OUTPUT);
    digitalWrite(SDA, LOW);
    digitalWrite(SCL, HIGH);
    IIC_delay(1);
    digitalWrite(SDA, HIGH);
    IIC_delay(1);
    digitalWrite(SCL, LOW);
}

uint8_t IIC_waitACK()
{
    uint32_t startTime;
    pinMode(SDA, INPUT);
    pinMode(SCL, OUTPUT);
    digitalWrite(SCL, HIGH);
    startTime = micros();

    while(digitalRead(SDA))
    {
        if(micros() - startTime > IIC_TIMEOUT_US)
        {
            digitalWrite(SCL, LOW);
            return IIC_ERROR_TIMEOUT;
        }
    }
    digitalWrite(SCL, LOW);
    digitalWrite(SDA, HIGH);
    return IIC_ACK_RECEIVED;
}

void IIC_ACK()
{
    pinMode(SCL, OUTPUT);
    pinMode(SDA, OUTPUT);
    digitalWrite(SDA, LOW);
    digitalWrite(SCL, HIGH);
    IIC_delay(1);
    digitalWrite(SCL, LOW);
    digitalWrite(SDA, HIGH);
}

void IIC_NACK()
{
    pinMode(SCL, OUTPUT);
    pinMode(SDA, OUTPUT);
    digitalWrite(SDA, HIGH);
    digitalWrite(SCL, HIGH);
    IIC_delay(1);
    digitalWrite(SCL, LOW);
    digitalWrite(SDA, HIGH);
}

void IIC_sendByte(uint8_t data)
{
    pinMode(SCL, OUTPUT);
    pinMode(SDA, OUTPUT);
    for(int i = 0; i < 8; i ++)
    {
        digitalWrite(SDA, data & 0x80);
        digitalWrite(SCL, HIGH);
        IIC_delay(1);
        digitalWrite(SCL, LOW);
        data <<= 1;
    }
    digitalWrite(SDA, HIGH);
}