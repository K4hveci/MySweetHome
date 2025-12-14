#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "Device.h"
#include <string>

// Base Sound System class
class SoundSystem : public Device {
protected:
    int volume;      // 0-100
    bool isMuted;
    std::string currentSource;  // Bluetooth, AUX, etc.

public:
    SoundSystem(const std::string& brand, const std::string& model);
    virtual ~SoundSystem();

    virtual void doPowerOn();
    virtual void doPowerOff();
    virtual std::string getDeviceType() const;
    virtual std::string getStatus() const;
    virtual Device* clone() const = 0;
    virtual void copyConfigurationFrom(const Device* other);

    // Sound system methods
    void setVolume(int vol);
    void mute();
    void unmute();
    void setSource(const std::string& source);
    int getVolume() const;
    bool getIsMuted() const;
    std::string getCurrentSource() const;
    
    void playMusic();
    void stopMusic();
};

// Concrete Sound System - Sonos
class SonosSoundSystem : public SoundSystem {
public:
    SonosSoundSystem();
    virtual ~SonosSoundSystem();
    virtual Device* clone() const;
};

// Concrete Sound System - Bose
class BoseSoundSystem : public SoundSystem {
public:
    BoseSoundSystem();
    virtual ~BoseSoundSystem();
    virtual Device* clone() const;
};

#endif // SOUNDSYSTEM_H
