# The Air Quality Index (IAQ, IQA) with a DSM501 on ESP32 or ESP8266 or Arduino
The "Soaring hunt the PM 2.5" project has implemented Calculate the Air Quality Index (IAQ, IQA) with a DSM501 on Arduino or ESP8266, a project that assigned Nong Um to measure PM in air with a drone.

# Introduction
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/The%20Air%20Quality%20Index%20(IAQ%2C%20IQA)%20with%20a%20DSM501%20on%20ESP32%20or%20ESP8266%20or%20Arduino/20210203_162737.jpg" width="350">
The Air Quality Index (IAQ) is fairly easy to determine using an ESP32 (or ESP8266/Arduino) and a DSM501 sensor. The DSM501A is a detector capable of measuring the presence of fine particles in suspension in the atmosphere according to PM2.5 and PM10 standards. The DSM501A is a very economical sensor which can be used as a base to build an air quality measurement station connected with an ESP32. The DSM501A is able to carry out measurements to the PM2.5 and PM10 standards. That is, it is capable of detecting particles whose diameter is less than 2.5 μm for PM2.5 and less than 1 μm for PM1.0.

# Principle of the sensor
The DSM501 is a Led optical detector that is more economical to manufacture than Laser models. The operating principle is similar to the smoke detectors used in fire detectors. The led illuminates the particles in a dark room. A photo-detector collects light. The measured signal is then proportional to the size and the quantity of particles in suspension.
<br>
Attention. Do not use this sensor to detect fumes from a fire.
<br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/The%20Air%20Quality%20Index%20(IAQ,%20IQA)%20with%20a%20DSM501%20on%20ESP32%20or%20ESP8266%20or%20Arduino/principe-dsm501-dust-detector.png" width="450">
<br>
source : http://doc.lijun.li/misc-dust-detector-with-arduino-serial-comm.html

The DSM501 is capable of classifying and measuring airborne particles less than 1 micron (PM1.0) and 2.5 micrometres (PM2.5) in size.

# Principle of communication with the ESP32 / Arduino / ESP8266

The DSM501 does not send its measurement directly. It uses the PWM system. It will therefore be necessary to measure the ratio between the time spent in the high state (+ 4.5V) and the time spent in the low state (0V). Then, thanks to this curve, it is possible to determine the quantity of particles in the air.
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/The%20Air%20Quality%20Index%20(IAQ,%20IQA)%20with%20a%20DSM501%20on%20ESP32%20or%20ESP8266%20or%20Arduino/dsm501-pwm-communication.png" width="450">

# Can I use the DSM501 on an ESP32?
Some of you will certainly yell at the 4.5V outputs of the sensors plugged into the ESP32. Theoretically, the inputs of the ESP8266 must not exceed 3.3V. This is perfectly correct, but the ESP32 seems to tolerate a voltage overrun if the intensity remains low according to this study published by Digital Me. One risks especially to deteriorate its ESP by directly plug the + 5V on terminal 3, 3V or a GPIO output by mistake.

# Determination of particle concentration
Fortunately, Makers have done the job for us! Here is the function that retrieves the PWM signal and determine the ratio. Knowing the ratio, it is possible to deduce the concentration of particles in suspension in the air in mg/m3.

```
long getPM(int DUST_SENSOR_DIGITAL_PIN) {
  starttime = millis();
  while (1) {
    duration = pulseIn(DUST_SENSOR_DIGITAL_PIN, LOW);
    lowpulseoccupancy += duration;
    endtime = millis();
    if ((endtime-starttime) >= sampletime_ms) {
      ratio = lowpulseoccupancy / (sampletime_ms*10.0);
      //ratio = (lowpulseoccupancy-endtime+starttime)/(sampletime_ms*10.0);  // Integer percentage 0=>100 -> Not working
      long concentration = 1.1 * pow( ratio, 3) - 3.8 *pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
      Serial.println(ratio);
      lowpulseoccupancy = 0;
      return(concentration);    
    }
  }  
}
```

Sources : https://github.com/mysensors/MySensors/blob/master/examples/DustSensorDSM/DustSensorDSM.ino

# Calculate the Air Quality Index (AQI)
The French Air Quality Index (AQI) or Air Quality Index (AIQ) in English is an indicator for determining an air quality level. Several pollutants are taken into account. (NO2), oxides of nitrogen (NOx), sulfur dioxide (SO2), lead (Pb), fine particles less than 10μm (PM10), less than 2.5μm Carbon (CO), Benzene (C6H6) and ozone (O3).

The big problem is that there is no international standard. In France, for example, the ATMO. The air quality is determined by an index ranging from 1 (very good) to 10 (dangerous). The ATMO is derived from the European system. In Europe, the Common Air Quality Index (CAQI) ranges from 0 to 100 (5 levels). In the USA and China, the AQI index has 6 levels ranging from 0 to 500 (or more).

To find the thresholds that correspond to your country, go to this Wikipedia page.

# How to calculate the French ATMO index
In France, two indices have been developed to make air quality more visible. Everything is explained in detail on this page Wikipedia:

The ATMO index for agglomerations with populations exceeding 100,000. It is the maximum threshold of four pollutants. The index varies from 1 to 10.
The IQA index for agglomerations of less than 100,000 inhabitants. It is a simplified index, which can be based on the measurement of a smaller number of pollutants (from 1 to 3). According to Article 4 of the French decree JORF No 274 of 25 November 2004, the simplified air quality index (IQA / AQI) is equal to the largest of the sub-indices of the polluting substances actually measured in the Geographical area. The index includes 6 levels (very good, good, average, mediocre, bad, dangerous).
To determine the AQI, we need only have at least one measure. If we have several sensors at our disposal, it will be the worst sub-index that will be used as an IQA index. The thresholds are imposed by Directive 2008/50/EC of 21 May 2008.

This summary table (taken from the Wikipedia article) makes it possible to determine the ATMO index. In the absence of thresholds for PM2.5, I used those of England, very close to European levels.

For example, if a PM10 = 15.5 is found, the simplified ATMO (AQI) will be 3. If there are several measures, the worst index (the highest score) becomes the ATMO.

<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/The%20Air%20Quality%20Index%20(IAQ,%20IQA)%20with%20a%20DSM501%20on%20ESP32%20or%20ESP8266%20or%20Arduino/Opera%20Snapshot_2021-02-06_175359_diyprojects.io.png" width="750">

# How to determine the European CAQI index (also called Citeair)
The calculation is similar to the French ATMO. It is obtained using the following grid published on the website airqualitynow.eu. At a minimum, the measurement should last 1 hour (PM10 or PM2.5).
<br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/The%20Air%20Quality%20Index%20(IAQ,%20IQA)%20with%20a%20DSM501%20on%20ESP32%20or%20ESP8266%20or%20Arduino/caqi-europe-common-air-quality-index-grid.png" width="450">
<br>
Source : https://www.airqualitynow.eu/about_indices_definition.php
# How to calculate AQI in China and the USA
China and the US have the same calculation system. The level of air quality has 6 levels (good, moderate, mediocre, bad for health, very bad for health, dangerous). The threshold therefore ranges from 0 to 500 (or more) instead of going from 1 to 10 in Europe (ATMO). It is very often the method of calculation that one finds in the examples of codes Arduino. There is also an online calculator here.
<br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/The%20Air%20Quality%20Index%20(IAQ,%20IQA)%20with%20a%20DSM501%20on%20ESP32%20or%20ESP8266%20or%20Arduino/Opera%20Snapshot_2021-02-06_175426_diyprojects.io.png" width="650">
<br>
To calculate the threshold, use this formula.
<br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/The%20Air%20Quality%20Index%20(IAQ,%20IQA)%20with%20a%20DSM501%20on%20ESP32%20or%20ESP8266%20or%20Arduino/Opera%20Snapshot_2021-02-06_175444_diyprojects.io.png" width="750">

# Circuit
Connect the DSM501 to an ESP32 or Arduino or ESP8266 using the following marking
<br>
<img src="https://github.com/chatchai-khuntichot/IoT/blob/main/The%20Air%20Quality%20Index%20(IAQ,%20IQA)%20with%20a%20DSM501%20on%20ESP32%20or%20ESP8266%20or%20Arduino/Opera%20Snapshot_2021-02-06_205212_github.com.png" width="450">
<br>
Source : http://www.samyoungsnc.com/products/3-1%20Specification%20DSM501.pdf

# Refereance
"Calculate the Air Quality Index (IAQ, IQA) with a DSM501 on Arduino or ESP8266", diyprojects, 15 Dec. 2020, diyprojects.io/calculate-air-quality-index-iaq-iqa-dsm501-arduino-esp8266/#.YB5rBulR1Pb
