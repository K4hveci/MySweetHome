/**
 * @file PoliceHandler.h
 * @brief Final handler in the security chain
 * @version 5.0
 * @date 03/12/2025
 * 
 * @authors
 * - 220201981: Security System - Chain of Responsibility (Handler)
 * 
 * @patterns Chain of Responsibility
 */

#ifndef POLICEHANDLER_H
#define POLICEHANDLER_H

#include "SecurityHandler.h"

class PoliceHandler : public SecurityHandler {
public:
    virtual void handleRequest();
};

#endif // POLICEHANDLER_H
