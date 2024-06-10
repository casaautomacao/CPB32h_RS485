#include <ModbusMaster.h>

#define MAX485_DE      15 // CPBh 

// instantiate ModbusMaster object
ModbusMaster node;

void preTransmission()
{
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_DE, 0);
}

void setup()
{

  pinMode(MAX485_DE, OUTPUT);
  // Init in receive mode
  digitalWrite(MAX485_DE, 0);

  // Modbus communication runs at 115200 baud
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1);
  // Modbus slave ID 1
  node.begin(1, Serial2);
  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

bool state = true;

void loop()
{
  uint8_t result;
  uint16_t data[6];

  result = node.readHoldingRegisters(0x0000, 6);
  if (result == node.ku8MBSuccess)
  {
    for (int i = 0; i < 3; i++)
    {
      //  Serial.println("passo 1");
      Serial.print(nomeVar(i));
      Serial.print(": ");
      Serial.print(node.getResponseBuffer(i) / 10.0);
      Serial.print(",");
    }

    Serial.println();
    // Serial.println();

  }

  delay(100);
}
