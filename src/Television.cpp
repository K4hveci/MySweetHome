#include "Television.h"
#include <sstream>

// Base Television implementation
Television::Television(const std::string& brand, const std::string& model)
    : Device(brand, model), screenSize(55), resolution("4K"), volume(30), channel(1), smartTV(true) {
}

Television::~Television() {}

void Television::doPowerOn() {
    std::cout << "  -> TV " << name << " displaying on channel " << channel 
              << " at volume " << volume << std::endl;
}

void Television::doPowerOff() {
    std::cout << "  -> TV " << name << " display off." << std::endl;
}

std::string Television::getDeviceType() const {
    return "Television";
}

std::string Television::getStatus() const {
    std::ostringstream oss;
    oss << Device::getStatus() << " | Size: " << screenSize << "\", Resolution: " << resolution;
    oss << ", Volume: " << volume << ", Channel: " << channel;
    oss << ", Smart TV: " << (smartTV ? "Yes" : "No");
    return oss.str();
}

void Television::copyConfigurationFrom(const Device* other) {
    Device::copyConfigurationFrom(other);
    const Television* otherTV = dynamic_cast<const Television*>(other);
    if (otherTV) {
        this->volume = otherTV->volume;
        this->channel = otherTV->channel;
    }
}

void Television::setVolume(int vol) {
    if (vol < 0) vol = 0;
    if (vol > 100) vol = 100;
    volume = vol;
    std::cout << "[INFO] " << name << " volume set to: " << volume << std::endl;
}

void Television::setChannel(int ch) {
    if (ch < 1) ch = 1;
    channel = ch;
    std::cout << "[INFO] " << name << " channel set to: " << channel << std::endl;
}

int Television::getVolume() const {
    return volume;
}

int Television::getChannel() const {
    return channel;
}

int Television::getScreenSize() const {
    return screenSize;
}

std::string Television::getResolution() const {
    return resolution;
}

bool Television::isSmartTV() const {
    return smartTV;
}

// Samsung TV
SamsungTV::SamsungTV()
    : Television("Samsung", "QLED Q80B") {
    screenSize = 65;
    resolution = "4K";
    smartTV = true;
}

SamsungTV::~SamsungTV() {}

Device* SamsungTV::clone() const {
    SamsungTV* newTV = new SamsungTV();
    newTV->copyConfigurationFrom(this);
    return newTV;
}

// LG TV
LGTV::LGTV()
    : Television("LG", "OLED C3") {
    screenSize = 55;
    resolution = "4K";
    smartTV = true;
}

LGTV::~LGTV() {}

Device* LGTV::clone() const {
    LGTV* newTV = new LGTV();
    newTV->copyConfigurationFrom(this);
    return newTV;
}
