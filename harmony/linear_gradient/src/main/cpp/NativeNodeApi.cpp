#include "NativeNodeApi.h"

namespace rnoh {

ArkUI_NativeNodeAPI_1 *NativeNodeApi::getInstance() {
#ifdef C_API_ARCH
    static ArkUI_NativeNodeAPI_1 *INSTANCE = nullptr;
    if (INSTANCE == nullptr) {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, INSTANCE);
    }
    return INSTANCE;
#endif
}

} // namespace rnoh