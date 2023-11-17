#ifndef HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTJSIBINDER_H
#define HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTJSIBINDER_H
#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace  rnoh {
class LinearGradientJSIBinder : public ViewComponentJSIBinder {
    facebook::jsi::Object createNativeProps(facebook::jsi::Runtime &rt) override
    {
        auto object = ViewComponentJSIBinder::createNativeProps(rt);
        object.setProperty(rt,"colors","array");
        object.setProperty(rt,"location","array");
        object.setProperty(rt,"angle","float");
        object.setProperty(rt,"startPoint","object");
        object.setProperty(rt,"endPoint","object");
        object.setProperty(rt,"angleCenter","object");
        object.setProperty(rt,"useAngle","boolean");
        return object;
    }
};    
} // namespace  rnoh 
#endif
