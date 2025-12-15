/**
/**
 * @file ModeManager.h
 * @authors
 * - 220201023: Mode System - State Pattern Implementation
 * 
 * @patterns State (Context)
 */


#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include <string>
#include <vector>

// Forward declarations
class Device;
class Light;
class Television;
class SoundSystem;

// State Pattern - Mode States
class ModeState {
protected:
    std::string modeName;
    bool lightOn;
    bool tvOn;
    bool musicOn;

public:
    ModeState(const std::string& name, bool light, bool tv, bool music);
    virtual ~ModeState();
    
    virtual void apply(std::vector<Device*>& lights, 
                      std::vector<Device*>& tvs,
                      std::vector<Device*>& soundSystems) = 0;
    
    std::string getName() const;
    bool isLightOn() const;
    bool isTVOn() const;
    bool isMusicOn() const;
    
    virtual void display() const;
};

// Concrete Mode States
class NormalMode : public ModeState {
public:
    NormalMode();
    virtual void apply(std::vector<Device*>& lights, 
                      std::vector<Device*>& tvs,
                      std::vector<Device*>& soundSystems);
};

class EveningMode : public ModeState {
public:
    EveningMode();
    virtual void apply(std::vector<Device*>& lights, 
                      std::vector<Device*>& tvs,
                      std::vector<Device*>& soundSystems);
};

class PartyMode : public ModeState {
public:
    PartyMode();
    virtual void apply(std::vector<Device*>& lights, 
                      std::vector<Device*>& tvs,
                      std::vector<Device*>& soundSystems);
};

class CinemaMode : public ModeState {
public:
    CinemaMode();
    virtual void apply(std::vector<Device*>& lights, 
                      std::vector<Device*>& tvs,
                      std::vector<Device*>& soundSystems);
};

// Mode Manager - Context class for State Pattern
class ModeManager {
private:
    ModeState* currentMode;
    NormalMode* normalMode;
    EveningMode* eveningMode;
    PartyMode* partyMode;
    CinemaMode* cinemaMode;

public:
    ModeManager();
    ~ModeManager();

    void setMode(char modeChar);
    void applyMode(std::vector<Device*>& lights, 
                   std::vector<Device*>& tvs,
                   std::vector<Device*>& soundSystems);
    
    ModeState* getCurrentMode() const;
    std::string getCurrentModeName() const;
    void displayCurrentMode() const;
};

#endif // MODEMANAGER_H