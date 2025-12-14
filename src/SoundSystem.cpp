#include "SoundSystem.h"
#include <sstream>

SoundSystem::SoundSystem(const std::string& brand, const std::string& model)
    : Device(brand, model), volume(50), isMuted(false), currentSource("Bluetooth") {
}

SoundSystem::~SoundSystem() {}

void SoundSystem::doPowerOn() {
    std::cout << "  -> Sound System " << name << " ready. Source: " << currentSource 
              << ", Volume: " << volume << "%" << std::endl;
}

void SoundSystem::doPowerOff() {
    std::cout << "  -> Sound System " << name << " turned off." << std::endl;
}

std::string SoundSystem::getDeviceType() const {
    return "Sound System";
}

std::string SoundSystem::getStatus() const {
    std::ostringstream oss;
    oss << Device::getStatus() << " | Volume: " << volume << "%";
    oss << ", Muted: " << (isMuted ? "Yes" : "No");
    oss << ", Source: " << currentSource;
    return oss.str();
}

void SoundSystem::copyConfigurationFrom(const Device* other) {
    Device::copyConfigurationFrom(other);
    const SoundSystem* otherSS = dynamic_cast<const SoundSystem*>(other);
    if (otherSS) {
        this->volume = otherSS->volume;
        this->currentSource = otherSS->currentSource;
    }
}

void SoundSystem::setVolume(int vol) {
    if (vol < 0) vol = 0;
    if (vol > 100) vol = 100;
    volume = vol;
    std::cout << "[INFO] " << name << " volume set to: " << volume << "%" << std::endl;
}

void SoundSystem::mute() {
    isMuted = true;
    std::cout << "[INFO] " << name << " muted." << std::endl;
}

void SoundSystem::unmute() {
    isMuted = false;
    std::cout << "[INFO] " << name << " unmuted." << std::endl;
}

void SoundSystem::setSource(const std::string& source) {
    currentSource = source;
    std::cout << "[INFO] " << name << " source changed to: " << currentSource << std::endl;
}

int SoundSystem::getVolume() const {
    return volume;
}

bool SoundSystem::getIsMuted() const {
    return isMuted;
}

std::string SoundSystem::getCurrentSource() const {
    return currentSource;
}

void SoundSystem::playMusic() {
    if (powerState) {
        std::cout << "[INFO] " << name << " playing music from " << currentSource << "..." << std::endl;
    }
}

void SoundSystem::stopMusic() {
    std::cout << "[INFO] " << name << " music stopped." << std::endl;
}

// Sonos Sound System
SonosSoundSystem::SonosSoundSystem()
    : SoundSystem("Sonos", "Arc Soundbar") {
    volume = 40;
}

SonosSoundSystem::~SonosSoundSystem() {}

Device* SonosSoundSystem::clone() const {
    SonosSoundSystem* newSS = new SonosSoundSystem();
    newSS->copyConfigurationFrom(this);
    return newSS;
}

// Bose Sound System
BoseSoundSystem::BoseSoundSystem()
    : SoundSystem("Bose", "Smart Soundbar 900") {
    volume = 35;
}

BoseSoundSystem::~BoseSoundSystem() {}

Device* BoseSoundSystem::clone() const {
    BoseSoundSystem* newSS = new BoseSoundSystem();
    newSS->copyConfigurationFrom(this);
    return newSS;
}
