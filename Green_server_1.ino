#include <VirtualWire.h>

const int receive_pin = 2;
const int led_pin = 13;

void setup()
{
  // Init serial port
  Serial.begin(9600);
  while (!Serial) {}

  // Init onboard LED
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);

  // Init receiver
  vw_set_rx_pin(receive_pin);
  vw_setup(1024);
  vw_rx_start();
}

byte count = 1;
void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    digitalWrite(led_pin, HIGH);
    int i;
    Serial.print("Got: ");
    for (i = 0; i < buflen; i++)
    {
      //Serial.print(buf[i], HEX);
      Serial.print((char)buf[i]);
      //Serial.print(' ');
    }
    Serial.println();
    digitalWrite(led_pin, LOW);
  }
}
