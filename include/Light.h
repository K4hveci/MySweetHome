#ifndef LIGHT_H
#define LIGHT_H

#include "Device.h"
#include <string>

// Base Light class
class Light : public Device {
protected:
    std::string color;
    int brightness;  // 0-100

public:
    Light(const std::string& brand, const std::string& model);
    virtual ~Light();

    virtual void doPowerOn();
    virtual void doPowerOff();
    virtual std::string getDeviceType() const;
    virtual std::string getStatus() const;
    virtual Device* clone() const = 0;
    virtual void copyConfigurationFrom(const Device* other);

    // Light-specific methods
    void setColor(const std::string& color);
    void setBrightness(int level);
    std::string getColor() const;
    int getBrightness() const;
    
    // For security/detection system
    void blinkLight();
};

// Concrete Light classes - Philips Hue
class PhilipsHueLight : public Light {
public:
    PhilipsHueLight();
    virtual ~PhilipsHueLight();
    virtual Device* clone() const;
};

// Concrete Light classes - IKEA Tradfri
class IKEATradfriLight : public Light {
public:
    IKEATradfriLight();
    virtual ~IKEATradfriLight();
    virtual Device* clone() const;
};

#endif // LIGHT_H
