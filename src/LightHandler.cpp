/**
 * @file LightHandler.cpp
 * @brief Implementation of Light Handler
 * @version 5.0
 * @date 03/12/2025
 * 
 * @authors
 * - 220201981: Security System - Chain of Responsibility (Handler)
 * 
 * @patterns Chain of Responsibility
 */

#include "LightHandler.h"
#include <iostream>
#include <unistd.h> // For sleep/usleep

LightHandler::LightHandler(std::vector<Light*>* lights) : lights(lights) {}

void LightHandler::handleRequest() {
    std::cout << "[SECURITY] Flashing lights..." << std::endl;
    
    if (lights && !lights->empty()) {
        for (int i = 0; i < 3; ++i) {
            for (size_t j = 0; j < lights->size(); ++j) {
                (*lights)[j]->powerOn();
            }
            // Simple sleep for simulation (would use timer in real embedded)
            // Using a loop to simulate short delay
            std::cout << "  -> Blink ON" << std::endl;
            
            for (size_t j = 0; j < lights->size(); ++j) {
                (*lights)[j]->powerOff();
            }
            std::cout << "  -> Blink OFF" << std::endl;
        }
        
        // Restore lights to ON for security visibility
        for (size_t j = 0; j < lights->size(); ++j) {
            (*lights)[j]->powerOn();
        }
    }
    
    SecurityHandler::handleRequest();
}
