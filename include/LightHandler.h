/**
 * @file LightHandler.h
 * @brief Handler that flashes lights in the security chain
 * @version 5.0
 * @date 03/12/2025
 * 
 * @authors
 * - 220201981: Security System - Chain of Responsibility (Handler)
 * 
 * @patterns Chain of Responsibility
 */

#ifndef LIGHTHANDLER_H
#define LIGHTHANDLER_H

#include "SecurityHandler.h"
#include "Light.h"
#include <vector>

class LightHandler : public SecurityHandler {
private:
    std::vector<Light*>* lights;
    
public:
    LightHandler(std::vector<Light*>* lights);
    virtual void handleRequest();
};

#endif // LIGHTHANDLER_H
