/**
 * @file PoliceHandler.cpp
 * @brief Implementation of Police Handler
 * @version 5.0
 * @date 03/12/2025
 * 
 * @authors
 * - 220201981: Security System - Chain of Responsibility (Handler)
 * 
 * @patterns Chain of Responsibility
 */

#include "PoliceHandler.h"
#include <iostream>

void PoliceHandler::handleRequest() {
    std::cout << "[SECURITY] Calling Police Department..." << std::endl;
    std::cout << "           (Simulating call: 155 dialed...)" << std::endl;
    
    // End of chain
    SecurityHandler::handleRequest(); 
}
