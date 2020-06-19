/*
 * Copyright (C) 2018 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_HARDWARE_LIGHT_V2_0_LIGHT_H
#define ANDROID_HARDWARE_LIGHT_V2_0_LIGHT_H

#include <android/hardware/light/2.0/ILight.h>
#include <hidl/Status.h>
#include <fstream>
#include <mutex>
#include <unordered_map>

namespace android {
namespace hardware {
namespace light {
namespace V2_0 {
namespace implementation {

using ::android::hardware::Return;
using ::android::hardware::light::V2_0::ILight;
using ::android::hardware::light::V2_0::LightState;
using ::android::hardware::light::V2_0::Status;
using ::android::hardware::light::V2_0::Type;

class Light : public ILight {
  public:
    Light();
    // Methods from ::android::hardware::light::V2_0::ILight follow.
    Return<Status> setLight(Type type, const LightState& state) override;
    Return<void> getSupportedTypes(getSupportedTypes_cb _hidl_cb) override;

  private:
    void setBatteryLight(const LightState& state);
    void setNotificationLight(const LightState& state);
    void setLcdBacklight(const LightState& state);
    void setSpeakerBatteryLightLocked();
    void setSpeakerLightLocked(const LightState& state);
    void setSpeakerNotificationLightLocked();
    void setSpeakerNLightLocked(const LightState& state);
    void handleWhiteLed(const LightState& state, size_t index);

    std::pair<std::ofstream, uint32_t> mLcdBacklight;
    std::ofstream mChargingLed;
    std::ofstream mNotificationLed;

    LightState mBatteryState;
    LightState mNotificationState;

    std::mutex mLock;
    std::unordered_map<Type, std::function<void(const LightState&)>> mLights;
    std::array<LightState, 2> mLightStates;

};

}  // namespace implementation
}  // namespace V2_0
}  // namespace light
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_LIGHT_V2_0_LIGHT_H
