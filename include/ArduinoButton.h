//
// Created by f.wimmer on 12.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_ARDUINOBUTTON_H
#define ESP32PROROTYPINGLIB_ARDUINOBUTTON_H

#include <stdint.h>
#include "Bounce2.h"
/**
 *
 * Requires: Bounce 2 (platformio library: thomasfredericks/Bounce2 @ ^2.57)
 */
class ArduinoButton  {
public:
    /**
     * Trigger typ of the button, can be combined
     */
    enum class TriggerType {
        Rising = 1,
        Falling = 2,
        Press = 4,
        LongPress = 8
    };
    typedef uint8_t TriggerTypeIntEqual;

    enum class PinMode{
        No,
        PullUp,
        PullDown,
    };

    enum class ButtonState{
        Up,
        Down,
        Long
    };

    typedef void(*ButtonCallback)(ArduinoButton *, TriggerType);

    /**
     * @param pin   Number of the pin to which the button is connected
     * @param mode  pull-up, pull-down, nothing
     * @param trigger   Which events should be forwarded to the cb
     * @param shortPressDuration    Duration of the short press in milliseconds
     * @param longPressDuration     Duration of the long press in milliseconds
     */
    ArduinoButton(uint8_t pin, PinMode mode, TriggerType trigger,
                  uint32_t shortPressDuration = 100,
                  uint32_t longPressDuration = 1000);

    /**
     *
     * @param shortPressDuration    Duration of the short press in milliseconds
     * @param longPressDuration     Duration of the long press in milliseconds
     */
    ArduinoButton(uint32_t shortPressDuration = 100,
                  uint32_t longPressDuration = 1000);

    /**
     *
     * @param pin   Number of the pin to which the button is connected
     * @param mode  pull-up, pull-down, nothing
     * @param trigger   Which events should be forwarded to the cb
     */
    void configure(uint8_t pin, PinMode mode, TriggerType trigger);

    /**
     * Set the function which is called if a button event appears
     * @param buttonCb
     */
    void setButtonCallback(ButtonCallback buttonCb);

    /**
     * Loop of the button, it is important to execute this on a continuous base
     */
    void loop();

    /**
     *
     * @return pin of this button
     */
    uint8_t getPin() const;

    /**
     * Set the duration how long the button needs to be pressed for a short press
     * @param value
     */
    void setShortPressDuration(uint32_t value);
    /**
     * Set the duration how long the button needs to be pressed for a long press
     * @param value
     */
    void setLongPressDuration(uint32_t value);


private:

    static const int sDebounceIntervall = 5;
    TriggerTypeIntEqual _trigger;
    uint8_t _pin = -1;
    Bounce2::Button _button;
    ButtonState _currentButtonState = ButtonState::Up;

    uint32_t _buttonDownTimestamp = 0;
    uint32_t _shortPressDuration = 50;
    uint32_t _longPressDuration = 1000;

    ButtonCallback _buttonCb = nullptr;
};

/**
 * Enable binary & operator for this enum
 * @param first
 * @param second
 * @return
 */
ArduinoButton::TriggerTypeIntEqual operator&(ArduinoButton::TriggerType first, ArduinoButton::TriggerType second);
/**
 * Enable binary & operator for this enum
 * @param first
 * @param second
 * @return
 */
ArduinoButton::TriggerTypeIntEqual operator&(ArduinoButton::TriggerTypeIntEqual first, ArduinoButton::TriggerType second);
/**
 * Enable binary | operator for this enum
 * @param first
 * @param second
 * @return
 */
ArduinoButton::TriggerTypeIntEqual operator|(ArduinoButton::TriggerType first, ArduinoButton::TriggerType second);
/**
 * Enable binary + operator for this enum
 * @param first
 * @param second
 * @return
 */
ArduinoButton::TriggerType operator+(ArduinoButton::TriggerType first, ArduinoButton::TriggerType second);

#endif //ESP32PROROTYPINGLIB_ARDUINOBUTTON_H
