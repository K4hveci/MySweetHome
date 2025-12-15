/**
 * @file ModeManager.cpp
 * @authors
 * - 220201023: Mode System - State Pattern Implementation
 * 
 * @patterns State (Context)
 */

#include "ModeManager.h"
#include "Device.h"
#include "Light.h"
#include "Television.h"
#include "SoundSystem.h"
#include <iostream>

// ModeState Implementation
ModeState::ModeState(const std::string& name, bool light, bool tv, bool music)
    : modeName(name), lightOn(light), tvOn(tv), musicOn(music) {
}

ModeState::~ModeState() {}

std::string ModeState::getName() const {
    return modeName;
}

bool ModeState::isLightOn() const {
    return lightOn;
}

bool ModeState::isTVOn() const {
    return tvOn;
}

bool ModeState::isMusicOn() const {
    return musicOn;
}

void ModeState::display() const {
    std::cout << "=== Mode: " << modeName << " ===" << std::endl;
    std::cout << "  Light: " << (lightOn ? "ON" : "OFF") << std::endl;
    std::cout << "  TV: " << (tvOn ? "ON" : "OFF") << std::endl;
    std::cout << "  Music: " << (musicOn ? "ON" : "OFF") << std::endl;
}

// Normal Mode: light on, TV off, music off
NormalMode::NormalMode() : ModeState("Normal", true, false, false) {}

void NormalMode::apply(std::vector<Device*>& lights, 
                       std::vector<Device*>& tvs,
                       std::vector<Device*>& soundSystems) {
    std::cout << "[MODE] Applying Normal Mode..." << std::endl;
    
    for (size_t i = 0; i < lights.size(); ++i) {
        lights[i]->powerOn();
    }
    for (size_t i = 0; i < tvs.size(); ++i) {
        tvs[i]->powerOff();
    }
    for (size_t i = 0; i < soundSystems.size(); ++i) {
        soundSystems[i]->powerOff();
    }
    
    display();
}

// Evening Mode: light off, TV off, music off
EveningMode::EveningMode() : ModeState("Evening", false, false, false) {}

void EveningMode::apply(std::vector<Device*>& lights, 
                        std::vector<Device*>& tvs,
                        std::vector<Device*>& soundSystems) {
    std::cout << "[MODE] Applying Evening Mode..." << std::endl;
    
    for (size_t i = 0; i < lights.size(); ++i) {
        lights[i]->powerOff();
    }
    for (size_t i = 0; i < tvs.size(); ++i) {
        tvs[i]->powerOff();
    }
    for (size_t i = 0; i < soundSystems.size(); ++i) {
        soundSystems[i]->powerOff();
    }
    
    display();
}

// Party Mode: light on, TV off, music on
PartyMode::PartyMode() : ModeState("Party", true, false, true) {}

void PartyMode::apply(std::vector<Device*>& lights, 
                      std::vector<Device*>& tvs,
                      std::vector<Device*>& soundSystems) {
    std::cout << "[MODE] Applying Party Mode..." << std::endl;
    
    for (size_t i = 0; i < lights.size(); ++i) {
        lights[i]->powerOn();
        Light* light = dynamic_cast<Light*>(lights[i]);
        if (light) {
            light->setColor("multicolor");
        }
    }
    for (size_t i = 0; i < tvs.size(); ++i) {
        tvs[i]->powerOff();
    }
    for (size_t i = 0; i < soundSystems.size(); ++i) {
        soundSystems[i]->powerOn();
        SoundSystem* ss = dynamic_cast<SoundSystem*>(soundSystems[i]);
        if (ss) {
            ss->playMusic();
        }
    }
    
    display();
}

// Cinema Mode: light off, TV on, music off
CinemaMode::CinemaMode() : ModeState("Cinema", false, true, false) {}

void CinemaMode::apply(std::vector<Device*>& lights, 
                       std::vector<Device*>& tvs,
                       std::vector<Device*>& soundSystems) {
    std::cout << "[MODE] Applying Cinema Mode..." << std::endl;
    
    for (size_t i = 0; i < lights.size(); ++i) {
        lights[i]->powerOff();
    }
    for (size_t i = 0; i < tvs.size(); ++i) {
        tvs[i]->powerOn();
    }
    for (size_t i = 0; i < soundSystems.size(); ++i) {
        soundSystems[i]->powerOff();
    }
    
    display();
}

// ModeManager Implementation
ModeManager::ModeManager() {
    normalMode = new NormalMode();
    eveningMode = new EveningMode();
    partyMode = new PartyMode();
    cinemaMode = new CinemaMode();
    
    // Default mode is Normal
    currentMode = normalMode;
}

ModeManager::~ModeManager() {
    delete normalMode;
    delete eveningMode;
    delete partyMode;
    delete cinemaMode;
}

void ModeManager::setMode(char modeChar) {
    switch (modeChar) {
        case 'N':
        case 'n':
            currentMode = normalMode;
            std::cout << "[INFO] Mode changed to Normal." << std::endl;
            break;
        case 'E':
        case 'e':
            currentMode = eveningMode;
            std::cout << "[INFO] Mode changed to Evening." << std::endl;
            break;
        case 'P':
        case 'p':
            currentMode = partyMode;
            std::cout << "[INFO] Mode changed to Party." << std::endl;
            break;
        case 'C':
        case 'c':
            currentMode = cinemaMode;
            std::cout << "[INFO] Mode changed to Cinema." << std::endl;
            break;
        default:
            std::cout << "[ERROR] Invalid mode selection." << std::endl;
    }
}

void ModeManager::applyMode(std::vector<Device*>& lights, 
                            std::vector<Device*>& tvs,
                            std::vector<Device*>& soundSystems) {
    if (currentMode) {
        currentMode->apply(lights, tvs, soundSystems);
    }
}

ModeState* ModeManager::getCurrentMode() const {
    return currentMode;
}

std::string ModeManager::getCurrentModeName() const {
    return currentMode ? currentMode->getName() : "Unknown";
}

void ModeManager::displayCurrentMode() const {
    if (currentMode) {
        currentMode->display();
    }
}