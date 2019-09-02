#include "udpDebugPrints.h"
#if defined(ESP8266) || defined(ESP32)
    #include <WiFi.h>
    #include <WiFiUdp.h>
    WiFiUDP udp;
#elif defined(SPARK)
    #include "Particle.h"
    UDP Udp;
#else
    #include <Ethernet.h>
    #include <EthernetUdp.h>
    EthernetUDP Udp;
#endif

UdpDebugPrints::UdpDebugPrints(){
    remotePort = -1;
}

UdpDebugPrints::~UdpDebugPrints(){
        
}

void UdpDebugPrints::begin(const char *addr, int port){
    remotePort = port;
    strcpy(remoteIP, addr);    
}

void UdpDebugPrints::end(){
    remotePort = -1;
}

void UdpDebugPrints::print(const char * format, ... ){
    if(remotePort<0) return;
    
    static uint8_t buffer[500];
    va_list args;
    va_start (args, format);
    int size = vsprintf ((char*)buffer,format, args);
    
    Udp.beginPacket(remoteIP, remotePort);
    Udp.write(buffer, strlen((char*)buffer)+1);
    Udp.flush();
    Udp.endPacket();
    
    va_end(args);
}
