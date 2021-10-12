//
// Created by f.wimmer on 12.10.2021.
//

#include <Arduino.h>
#include "ArduinoButton.h"

ArduinoButton::ArduinoButton(uint32_t shortPressDuration, uint32_t longPressDuration)
        : _shortPressDuration{shortPressDuration}, _longPressDuration{longPressDuration}{

}

ArduinoButton::ArduinoButton(uint8_t pin, PinMode mode,
                             ArduinoButton::TriggerType trigger,
                             uint32_t shortPressDuration,
                             uint32_t longPressDuration)
        : ArduinoButton{shortPressDuration, longPressDuration}{
    configure(pin, mode, trigger);
}

void ArduinoButton::loop() {
    _button.update();
    // long press or short press
    // and report the one if registered
    uint32_t currentMillis = millis();

    if (((currentMillis - _buttonDownTimestamp) > _longPressDuration)
        && _currentButtonState == ButtonState::Down){

        _currentButtonState = ButtonState::Long;
        if(_buttonCb != nullptr){
            _buttonCb(this,TriggerType::LongPress);
        }
    }

    if(_button.fallingEdge()){
        // check if event on falling edge is registered
        if (((_trigger & TriggerType::Falling) == static_cast<TriggerTypeIntEqual>(TriggerType::Falling)) &&
            _buttonCb != nullptr){
            _buttonCb(this,TriggerType::Falling);
        }

        // remember the timestamp to determine long press or short press later
        _buttonDownTimestamp = currentMillis;
        _currentButtonState = ButtonState::Down;
    }else if(_button.risingEdge()){
        // check if the raising edge should reported
        if (((_trigger & TriggerType::Rising) == static_cast<TriggerTypeIntEqual>(TriggerType::Rising)) &&
            _buttonCb != nullptr){
            _buttonCb(this,TriggerType::Rising);
        }

        if(((currentMillis - _buttonDownTimestamp) > _shortPressDuration)
           && _currentButtonState == ButtonState::Down){
            if(_buttonCb != nullptr){
                _buttonCb(this,TriggerType::Press);
            }
        }

        _currentButtonState = ButtonState::Up;
    }
}

void ArduinoButton::setButtonCallback(ArduinoButton::ButtonCallback buttonCb) {
    _buttonCb = buttonCb;
}

uint8_t ArduinoButton::getPin() const {
    return _pin;
}

void ArduinoButton::configure(uint8_t pin, ArduinoButton::PinMode mode, ArduinoButton::TriggerType trigger) {
    _trigger = static_cast<TriggerTypeIntEqual>(trigger);
    _pin = pin;


    // get requested pin pull mode
    uint8_t inputType = INPUT;
    if(mode == PinMode::PullDown){
        _button.setPressedState(HIGH);
    }else if(mode == PinMode::PullUp){
        inputType = INPUT_PULLUP;
        _button.setPressedState(LOW);
    }

    // configure pin and debouncing
    _button.attach(static_cast<int>(pin), static_cast<int>(inputType));
    _button.interval(sDebounceIntervall);
}

void ArduinoButton::setShortPressDuration(uint32_t value) {
    _shortPressDuration = value;
}

void ArduinoButton::setLongPressDuration(uint32_t value) {
    _longPressDuration = value;
}


ArduinoButton::TriggerTypeIntEqual operator&(ArduinoButton::TriggerType first, ArduinoButton::TriggerType second){
    return static_cast<ArduinoButton::TriggerTypeIntEqual>(first) &
           static_cast<ArduinoButton::TriggerTypeIntEqual>(second);
}

ArduinoButton::TriggerTypeIntEqual operator&(ArduinoButton::TriggerTypeIntEqual first, ArduinoButton::TriggerType second){
    return first & static_cast<ArduinoButton::TriggerTypeIntEqual>(second);
}

ArduinoButton::TriggerTypeIntEqual operator|(ArduinoButton::TriggerType first, ArduinoButton::TriggerType second){
    return static_cast<ArduinoButton::TriggerTypeIntEqual>(first) |
           static_cast<ArduinoButton::TriggerTypeIntEqual>(second);
}

ArduinoButton::TriggerType operator+(ArduinoButton::TriggerType first, ArduinoButton::TriggerType second){
    return static_cast<ArduinoButton::TriggerType>(static_cast<ArduinoButton::TriggerTypeIntEqual>(first) |
                                                   static_cast<ArduinoButton::TriggerTypeIntEqual>(second));
}