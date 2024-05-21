//
// Created on 2024/5/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_NATIVENODEAPI_H
#define HARMONY_NATIVENODEAPI_H
#pragma once
#include <arkui/native_interface.h>
#include <arkui/native_node.h>

namespace rnoh {

class NativeNodeApi {
public:
    static ArkUI_NativeNodeAPI_1 *getInstance();

private:
    NativeNodeApi() {}

    static ArkUI_NativeNodeAPI_1 *api;
};

} // namespace rnoh
#endif // HARMONY_NATIVENODEAPI_H