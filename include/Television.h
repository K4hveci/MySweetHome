#ifndef TELEVISION_H
#define TELEVISION_H

#include "Device.h"
#include <string>

// Base Television class
class Television : public Device {
protected:
    int screenSize;      // inches
    std::string resolution;
    int volume;          // 0-100
    int channel;
    bool smartTV;

public:
    Television(const std::string& brand, const std::string& model);
    virtual ~Television();

    virtual void doPowerOn();
    virtual void doPowerOff();
    virtual std::string getDeviceType() const;
    virtual std::string getStatus() const;
    virtual Device* clone() const = 0;
    virtual void copyConfigurationFrom(const Device* other);

    // TV-specific methods
    void setVolume(int vol);
    void setChannel(int ch);
    int getVolume() const;
    int getChannel() const;
    int getScreenSize() const;
    std::string getResolution() const;
    bool isSmartTV() const;
};

// Concrete TV classes - Samsung
class SamsungTV : public Television {
public:
    SamsungTV();
    virtual ~SamsungTV();
    virtual Device* clone() const;
};

// Concrete TV classes - LG
class LGTV : public Television {
public:
    LGTV();
    virtual ~LGTV();
    virtual Device* clone() const;
};

#endif // TELEVISION_H
