#include "Light.h"
#include <sstream>

// Base Light implementation
Light::Light(const std::string& brand, const std::string& model)
    : Device(brand, model), color("white"), brightness(100) {
}

Light::~Light() {}

void Light::doPowerOn() {
    std::cout << "  -> Light " << name << " illuminating with color: " << color 
              << ", brightness: " << brightness << "%" << std::endl;
}

void Light::doPowerOff() {
    std::cout << "  -> Light " << name << " turning off illumination." << std::endl;
}

std::string Light::getDeviceType() const {
    return "Light";
}

std::string Light::getStatus() const {
    std::ostringstream oss;
    oss << Device::getStatus() << " | Color: " << color << ", Brightness: " << brightness << "%";
    return oss.str();
}

void Light::copyConfigurationFrom(const Device* other) {
    Device::copyConfigurationFrom(other);
    const Light* otherLight = dynamic_cast<const Light*>(other);
    if (otherLight) {
        this->color = otherLight->color;
        this->brightness = otherLight->brightness;
    }
}

void Light::setColor(const std::string& c) {
    color = c;
    std::cout << "[INFO] " << name << " color set to: " << color << std::endl;
}

void Light::setBrightness(int level) {
    if (level < 0) level = 0;
    if (level > 100) level = 100;
    brightness = level;
    std::cout << "[INFO] " << name << " brightness set to: " << brightness << "%" << std::endl;
}

std::string Light::getColor() const {
    return color;
}

int Light::getBrightness() const {
    return brightness;
}

void Light::blinkLight() {
    std::cout << "[ALERT] " << name << " BLINKING ON/OFF!" << std::endl;
}

// Philips Hue Light
PhilipsHueLight::PhilipsHueLight()
    : Light("Philips", "Hue White A19") {
}

PhilipsHueLight::~PhilipsHueLight() {}

Device* PhilipsHueLight::clone() const {
    PhilipsHueLight* newLight = new PhilipsHueLight();
    newLight->copyConfigurationFrom(this);
    return newLight;
}

// IKEA Tradfri Light
IKEATradfriLight::IKEATradfriLight()
    : Light("IKEA", "Tradfri E27") {
}

IKEATradfriLight::~IKEATradfriLight() {}

Device* IKEATradfriLight::clone() const {
    IKEATradfriLight* newLight = new IKEATradfriLight();
    newLight->copyConfigurationFrom(this);
    return newLight;
}
