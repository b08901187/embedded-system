/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __BLE_STUDENTID_SERVICE_H__
#define __BLE_STUDENTID_SERVICE_H__

#include <string>
class StudentIDService {
public:
    const static uint16_t STUDENTID_SERVICE_UUID   = 0xA002;
    const static uint16_t BUTTON_STATE_CHARACTERISTIC_UUID = 0xA001;

    StudentIDService(BLE &_ble, char* buttonPressedInitial) :
        ble(_ble), studentID(BUTTON_STATE_CHARACTERISTIC_UUID, buttonPressedInitial, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY)
    {
        GattCharacteristic *charTable[] = {&studentID};
        GattService         studentIDService(StudentIDService::STUDENTID_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
        ble.gattServer().addService(studentIDService);
    }

    void updateButtonState(char* newState) {
        ble.gattServer().write(studentID.getValueHandle(), (uint8_t *)newState, 9);
        
    }

private:
    BLE                              &ble;
    ReadOnlyArrayGattCharacteristic<char,9>  studentID;
    
    
    
};

#endif /* #ifndef __BLE_BUTTON_SERVICE_H__ */