/*
  HMC5883L Triple Axis Digital Compass. Compass Example.
  Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-magnetometr-hmc5883l.html
  GIT: https://github.com/jarzebski/Arduino-HMC5883L
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;

void setup()
{
  Serial.begin(9600);

  // Initialize Initialize HMC5883L
  Serial.println("Initialize HMC5883L");
  while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
  }

  // Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_30HZ);

  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(0, 0, 0);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // For Bytom / Poland declination angle is 4'26E (positive)
  compass.setDeclination(4,26,'E');

  // Set if compass is flipped upside down. This is normally true for drone GPS/Magnetometers
  compass.compassFlip = false;

  // Set the compass offset rotation in degrees. This is normally 90 degrees for drone GPS/Magnetometers
  compass.offsetDegrees = 0;
}

void loop()
{
  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = compass.getAzimuth();

  // Output
  Serial.print(" Heading = ");
  Serial.print(heading);
  Serial.println();

  delay(100);
}

