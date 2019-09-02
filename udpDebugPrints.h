#ifndef UdpDebugPrints_h
#define UdpDebugPrints_h


class UdpDebugPrints 
{
  public:
    UdpDebugPrints(); 
    ~UdpDebugPrints();

    void begin(const char *addr, int port);
    void end();
    void print(const char * format, ... );
  private:
    char remoteIP[50];
    int remotePort;
};
#endif
