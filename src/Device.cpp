#include "Device.h"

Device::Device(const std::string& brand, const std::string& model)
    : brand(brand), model(model), powerState(false), operationMode(true), observer(NULL) {
    name = brand + " " + model;
}

Device::~Device() {}

void Device::powerOn() {
    if (!operationMode) {
        std::cout << "[WARNING] " << name << " is inactive/failed and cannot be powered on." << std::endl;
        notifyFailure("Device is inactive/failed");
        return;
    }
    if (!powerState) {
        powerState = true;
        doPowerOn();
        std::cout << "[INFO] " << name << " powered ON." << std::endl;
    } else {
        std::cout << "[INFO] " << name << " is already ON." << std::endl;
    }
}

void Device::powerOff() {
    if (powerState) {
        powerState = false;
        doPowerOff();
        std::cout << "[INFO] " << name << " powered OFF." << std::endl;
    } else {
        std::cout << "[INFO] " << name << " is already OFF." << std::endl;
    }
}

std::string Device::getStatus() const {
    std::string status = name + " [" + getDeviceType() + "] - ";
    status += powerState ? "ON" : "OFF";
    status += operationMode ? " (Active)" : " (FAILED)";
    return status;
}

std::string Device::getName() const {
    return name;
}

std::string Device::getBrand() const {
    return brand;
}

std::string Device::getModel() const {
    return model;
}

bool Device::isPoweredOn() const {
    return powerState;
}

bool Device::isActive() const {
    return operationMode;
}

void Device::setOperationMode(bool active) {
    operationMode = active;
    if (!active) {
        std::cout << "[WARNING] " << name << " has been marked as FAILED/INACTIVE." << std::endl;
        notifyFailure("Device marked as failed");
    }
}

void Device::setObserver(IDeviceObserver* obs) {
    observer = obs;
}

void Device::notifyFailure(const std::string& message) {
    if (observer) {
        observer->onDeviceFailure(name, message);
    }
}

void Device::copyConfigurationFrom(const Device* other) {
    if (other) {
        // Base configuration copy - derived classes override for specific config
        this->operationMode = other->operationMode;
    }
}
