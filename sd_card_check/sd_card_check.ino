#include <SPI.h>
#include <SD.h>

#define SD_CS 10

void setup()
{
    Serial.begin(9600);

    delay(2000);

    Serial.println("===== SD CARD FULL TEST =====");

    // Initialize SD
    if (!SD.begin(SD_CS))
    {
        Serial.println("SD INIT FAILED");
        return;
    }

    Serial.println("SD INIT SUCCESS");

    // Remove old file if exists
    if (SD.exists("test.txt"))
    {
        SD.remove("test.txt");
        Serial.println("Old file deleted");
    }

    // Create and write file
    File file = SD.open("test.txt", FILE_WRITE);

    if (!file)
    {
        Serial.println("FILE CREATE FAILED");
        return;
    }

    Serial.println("Writing data...");

    file.println("Line 1");
    file.println("Line 2");
    file.println("Line 3");

    file.close();

    Serial.println("WRITE SUCCESS");

    // Read file
    file = SD.open("test.txt");

    if (!file)
    {
        Serial.println("READ FAILED");
        return;
    }

    Serial.println("Reading file:");

    while (file.available())
    {
        Serial.write(file.read());
    }

    file.close();

    Serial.println();
    Serial.println("READ SUCCESS");

    // Append test
    file = SD.open("test.txt", FILE_WRITE);

    if (!file)
    {
        Serial.println("APPEND FAILED");
        return;
    }

    file.println("New appended line");

    file.close();

    Serial.println("APPEND SUCCESS");

    // Final read
    file = SD.open("test.txt");

    Serial.println();
    Serial.println("FINAL FILE CONTENT:");

    while (file.available())
    {
        Serial.write(file.read());
    }

    file.close();

    Serial.println();
    Serial.println("===== SD TEST COMPLETE =====");
}

void loop()
{
}