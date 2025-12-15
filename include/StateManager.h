#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <string>
#include <vector>
#include <map>

// Forward declarations
class Device;

// Memento Pattern - State snapshot
class HomeMemento {
private:
    std::string stateName;
    std::map<std::string, bool> devicePowerStates;
    std::string modeName;
    std::string timestamp;

public:
    HomeMemento(const std::string& state, const std::string& mode);
    
    void addDeviceState(const std::string& deviceName, bool powerState);
    std::string getStateName() const;
    std::string getModeName() const;
    std::map<std::string, bool> getDevicePowerStates() const;
    std::string getTimestamp() const;
    void display() const;
};

// System State - Different operating conditions
class SystemState {
protected:
    std::string stateName;
    std::string description;

public:
    SystemState(const std::string& name, const std::string& desc);
    virtual ~SystemState();
    
    virtual void apply() = 0;
    std::string getName() const;
    std::string getDescription() const;
    virtual void display() const;
};

// Concrete System States
class NormalState : public SystemState {
public:
    NormalState();
    virtual void apply();
};

class HighPerformanceState : public SystemState {
public:
    HighPerformanceState();
    virtual void apply();
};

class LowPowerState : public SystemState {
public:
    LowPowerState();
    virtual void apply();
};

class SleepState : public SystemState {
public:
    SleepState();
    virtual void apply();
};

// Caretaker - Manages state history (Memento Pattern)
class StateManager {
private:
    SystemState* currentState;
    std::vector<HomeMemento*> stateHistory;
    int currentHistoryIndex;
    
    // System states
    NormalState* normalState;
    HighPerformanceState* highPerfState;
    LowPowerState* lowPowerState;
    SleepState* sleepState;
    
    static const int MAX_HISTORY = 50;

public:
    StateManager();
    ~StateManager();

    // State management
    void setState(char stateChar);
    void applyState();
    SystemState* getCurrentState() const;
    std::string getCurrentStateName() const;
    
    // Memento operations
    void saveState(const std::string& modeName, const std::vector<Device*>& allDevices);
    bool restorePreviousState();
    bool restoreNextState();
    void displayHistory() const;
    int getHistorySize() const;
    
    void displayCurrentState() const;
};

#endif // STATEMANAGER_H
