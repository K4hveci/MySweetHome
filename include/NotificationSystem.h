/**
 * @file NotificationSystem.h
 * @authors
 * - 220201013: Notification System & Integration
 * 
 * @patterns Strategy, Observer (Observer impl)
 */

#ifndef NOTIFICATIONSYSTEM_H
#define NOTIFICATIONSYSTEM_H

#include "Device.h" // For IDeviceObserver
#include <string>

class NotificationSystem : public IDeviceObserver {
public:
    NotificationSystem();
    virtual ~NotificationSystem();
    
    void notify(const std::string& message);
    
    // Observer update method
    virtual void onDeviceFailure(const std::string& deviceName, const std::string& message);
    
    void displayStatus() const;
};

#endif // NOTIFICATIONSYSTEM_H