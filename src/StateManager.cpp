#include "StateManager.h"
#include "Device.h"
#include <iostream>
#include <ctime>
#include <sstream>

// HomeMemento Implementation
HomeMemento::HomeMemento(const std::string& state, const std::string& mode)
    : stateName(state), modeName(mode) {
    // Generate timestamp
    time_t now = time(0);
    char* dt = ctime(&now);
    timestamp = std::string(dt);
    // Remove newline
    if (!timestamp.empty() && timestamp[timestamp.length()-1] == '\n') {
        timestamp.erase(timestamp.length()-1);
    }
}

void HomeMemento::addDeviceState(const std::string& deviceName, bool powerState) {
    devicePowerStates[deviceName] = powerState;
}

std::string HomeMemento::getStateName() const {
    return stateName;
}

std::string HomeMemento::getModeName() const {
    return modeName;
}

std::map<std::string, bool> HomeMemento::getDevicePowerStates() const {
    return devicePowerStates;
}

std::string HomeMemento::getTimestamp() const {
    return timestamp;
}

void HomeMemento::display() const {
    std::cout << "  State: " << stateName << ", Mode: " << modeName 
              << ", Time: " << timestamp << std::endl;
}

// SystemState Implementation
SystemState::SystemState(const std::string& name, const std::string& desc)
    : stateName(name), description(desc) {
}

SystemState::~SystemState() {}

std::string SystemState::getName() const {
    return stateName;
}

std::string SystemState::getDescription() const {
    return description;
}

void SystemState::display() const {
    std::cout << "=== System State: " << stateName << " ===" << std::endl;
    std::cout << "  " << description << std::endl;
}

// Normal State
NormalState::NormalState() 
    : SystemState("Normal", "Standard operation mode - all features available") {
}

void NormalState::apply() {
    std::cout << "[STATE] System running in Normal mode." << std::endl;
    std::cout << "  - All devices operating normally" << std::endl;
    std::cout << "  - Full functionality available" << std::endl;
}

// High Performance State
HighPerformanceState::HighPerformanceState() 
    : SystemState("High Performance", "Maximum performance - increased resource usage") {
}

void HighPerformanceState::apply() {
    std::cout << "[STATE] System running in High Performance mode." << std::endl;
    std::cout << "  - Faster response times" << std::endl;
    std::cout << "  - Higher energy consumption" << std::endl;
}

// Low Power State
LowPowerState::LowPowerState() 
    : SystemState("Low Power", "Energy saving mode - reduced functionality") {
}

void LowPowerState::apply() {
    std::cout << "[STATE] System running in Low Power mode." << std::endl;
    std::cout << "  - Reduced energy consumption" << std::endl;
    std::cout << "  - Non-essential devices may be limited" << std::endl;
}

// Sleep State
SleepState::SleepState() 
    : SystemState("Sleep", "Minimal operation - only critical systems active") {
}

void SleepState::apply() {
    std::cout << "[STATE] System running in Sleep mode." << std::endl;
    std::cout << "  - Only security and detection systems active" << std::endl;
    std::cout << "  - Minimal energy consumption" << std::endl;
}

// StateManager Implementation
StateManager::StateManager() : currentHistoryIndex(-1) {
    normalState = new NormalState();
    highPerfState = new HighPerformanceState();
    lowPowerState = new LowPowerState();
    sleepState = new SleepState();
    
    // Default state is Normal
    currentState = normalState;
}

StateManager::~StateManager() {
    delete normalState;
    delete highPerfState;
    delete lowPowerState;
    delete sleepState;
    
    for (size_t i = 0; i < stateHistory.size(); ++i) {
        delete stateHistory[i];
    }
    stateHistory.clear();
}

void StateManager::setState(char stateChar) {
    switch (stateChar) {
        case 'N':
        case 'n':
            currentState = normalState;
            std::cout << "[INFO] System state changed to Normal." << std::endl;
            break;
        case 'H':
        case 'h':
            currentState = highPerfState;
            std::cout << "[INFO] System state changed to High Performance." << std::endl;
            break;
        case 'L':
        case 'l':
            currentState = lowPowerState;
            std::cout << "[INFO] System state changed to Low Power." << std::endl;
            break;
        case 'S':
        case 's':
            currentState = sleepState;
            std::cout << "[INFO] System state changed to Sleep." << std::endl;
            break;
        case 'P':
        case 'p':
            restorePreviousState();
            return;
        default:
            std::cout << "[ERROR] Invalid state selection." << std::endl;
            return;
    }
    applyState();
}

void StateManager::applyState() {
    if (currentState) {
        currentState->apply();
    }
}

SystemState* StateManager::getCurrentState() const {
    return currentState;
}

std::string StateManager::getCurrentStateName() const {
    return currentState ? currentState->getName() : "Unknown";
}

void StateManager::saveState(const std::string& modeName, const std::vector<Device*>& allDevices) {
    // Remove any future states if we're not at the end
    while (currentHistoryIndex < (int)stateHistory.size() - 1) {
        delete stateHistory.back();
        stateHistory.pop_back();
    }
    
    // Create new memento
    HomeMemento* memento = new HomeMemento(getCurrentStateName(), modeName);
    
    // Save all device states
    for (size_t i = 0; i < allDevices.size(); ++i) {
        memento->addDeviceState(allDevices[i]->getName(), allDevices[i]->isPoweredOn());
    }
    
    // Limit history size
    if (stateHistory.size() >= MAX_HISTORY) {
        delete stateHistory[0];
        stateHistory.erase(stateHistory.begin());
    }
    
    stateHistory.push_back(memento);
    currentHistoryIndex = stateHistory.size() - 1;
    
    std::cout << "[INFO] State saved to history. Total states: " << stateHistory.size() << std::endl;
}

bool StateManager::restorePreviousState() {
    if (currentHistoryIndex > 0) {
        currentHistoryIndex--;
        HomeMemento* memento = stateHistory[currentHistoryIndex];
        std::cout << "[INFO] Restoring previous state..." << std::endl;
        memento->display();
        return true;
    } else {
        std::cout << "[WARNING] No previous state available." << std::endl;
        return false;
    }
}

bool StateManager::restoreNextState() {
    if (currentHistoryIndex < (int)stateHistory.size() - 1) {
        currentHistoryIndex++;
        HomeMemento* memento = stateHistory[currentHistoryIndex];
        std::cout << "[INFO] Restoring next state..." << std::endl;
        memento->display();
        return true;
    } else {
        std::cout << "[WARNING] No next state available." << std::endl;
        return false;
    }
}

void StateManager::displayHistory() const {
    std::cout << "=== State History ===" << std::endl;
    for (size_t i = 0; i < stateHistory.size(); ++i) {
        std::cout << (i == (size_t)currentHistoryIndex ? " -> " : "    ");
        std::cout << "[" << i + 1 << "] ";
        stateHistory[i]->display();
    }
    std::cout << "Total: " << stateHistory.size() << " states" << std::endl;
}

int StateManager::getHistorySize() const {
    return stateHistory.size();
}

void StateManager::displayCurrentState() const {
    if (currentState) {
        currentState->display();
    }
}
