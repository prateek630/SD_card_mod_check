#include <SPI.h>
#include <SD.h>

#define SD_CS 13

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println("SD TEST START");

  SPI.begin(18, 19, 23, 13);   // SCK, MISO, MOSI, CS

  if (!SD.begin(SD_CS))
  {
    Serial.println("SD INIT FAILED");
    return;
  }

  Serial.println("SD INIT OK");

  uint64_t sizeMB = SD.cardSize() / (1024 * 1024);
  Serial.print("CARD SIZE: ");
  Serial.print(sizeMB);
  Serial.println(" MB");

  File file = SD.open("/test.txt", FILE_WRITE);

  if (!file)
  {
    Serial.println("FILE OPEN FAILED");
    return;
  }

  file.println("ESP32 SD CARD TEST SUCCESS");
  file.close();

  Serial.println("WRITE OK");

  file = SD.open("/test.txt");

  while (file.available())
    Serial.write(file.read());

  file.close();

  Serial.println("\nREAD OK");
}

void loop()
{
}