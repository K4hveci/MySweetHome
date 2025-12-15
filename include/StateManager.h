/**
 * @file StateManager.h
 * @brief Caretaker for Memento Pattern - Manages state history
 * @version 5.0
 * @date 03/12/2025
 * 
 * @authors
 * - 220201981: State History - Memento Pattern Implementation
 * 
 * @patterns Memento (Caretaker)
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <string>

// Forward declaration
class HomeMemento;
class Device;

class StateManager {
private:
    std::vector<HomeMemento*> history;
    std::string currentState;

public:
    StateManager();
    ~StateManager();

    void saveState(const std::string& modeName, const std::vector<Device*>& devices);
    void restorePreviousState();
    
    void setState(char choice);
    void applyState();
    
    std::string getCurrentStateName() const;
    void displayCurrentState() const;
};

#endif // STATEMANAGER_H