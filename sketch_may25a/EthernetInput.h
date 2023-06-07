#include "HardwareSerial.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <NTPClient.h>
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
unsigned int localPort = 8888;  // local port to listen for UDP packets
char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
byte packetBuffer[NTP_PACKET_SIZE];  //buffer to hold incoming and outgoing packets
// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(Udp, "ru.pool.ntp.org", 10800, 60000);
String formattedDate;

class Time {
public:
  bool Ethernetinit() {
    // You can use Ethernet.init(pin) to configure the CS pin
    Ethernet.init(10);  // Most Arduino shields
    // start Ethernet and UDP
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      // Check for Ethernet hardware present
      if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      } else if (Ethernet.linkStatus() == LinkOFF) {
        Serial.println("Ethernet cable is not connected.");
      }
      // no point in carrying on, so do nothing forevermore:
      return 1;
    }
    Udp.begin(localPort);
    timeClient.begin();
    return 0;
  }
  String getDate() {
    String dayStamp;
    timeClient.update();
    formattedDate = timeClient.getFormattedDate();
    int splitT = formattedDate.indexOf("T");
    dayStamp = formattedDate.substring(0, splitT);
    return dayStamp;
  }
  String getTime() {
    String timeStamp;
    timeClient.update();
    formattedDate = timeClient.getFormattedDate();
    int splitT = formattedDate.indexOf("T");
    timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
    return timeStamp;
  }
  char getWeek() {
    timeClient.update();
    return daysOfTheWeek[timeClient.getDay()];
  }
private:
};