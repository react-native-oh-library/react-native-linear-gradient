/**
 * MIT License
 *
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANT KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTNAPIBINDER_H
#define HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTNAPIBINDER_H
#include "RNOHCorePackage/ComponentBinders/ViewComponentNapiBinder.h"
#include "Props.h"

namespace rnoh {

class LinearGradientNapiBinder : public ViewComponentNapiBinder {
  public:
    napi_value createProps(napi_env env, facebook::react::ShadowView const shadowView) override 
    {
        napi_value napiViewProps = ViewComponentNapiBinder::createProps(env, shadowView);
        auto propsObjBuilder =  ArkJS(env).getObjectBuilder(napiViewProps);
        
        if (auto props = std::dynamic_pointer_cast<const facebook::react::RNLinearGradientProps>(shadowView.props)) {
            auto colors = std::vector<napi_value>();
            auto colorsRaw = props ->colors;
            for (auto color : colorsRaw){
                auto colorObjBuilder = ArkJS(env).createObjectBuilder();
                colorObjBuilder.addProperty("color",color);
                colors.push_back(colorObjBuilder.build());
            }
            auto colorsArray = ArkJS(env).createArray(colors);

            auto locations = std::vector<napi_value>();
            auto locationsRaw = props->locations;
            for (auto location : locationsRaw) {
                auto locationObjBuilder = ArkJS(env).createObjectBuilder();
                locationObjBuilder.addProperty("location",location);
                locations.push_back(locationObjBuilder.build());    
            }
            auto locationsArray = ArkJS(env).createArray(locations);

            auto startPointObj = ArkJS(env).createObjectBuilder()
                .addProperty("x",props->startPoint.x)
                .addProperty("y",props->startPoint.y)
                .build();
            auto endPointObj = ArkJS(env).createObjectBuilder()
                .addProperty("x",props->endPoint.x)
                .addProperty("y",props->endPoint.y)
                .build();
            auto angleCenterObj = ArkJS(env).createObjectBuilder()
                .addProperty("x",props->angleCenter.x)
                .addProperty("y",props->angleCenter.y)
                .build();
            propsObjBuilder.addProperty("angle",props->angle)
                .addProperty("useAngle",props->useAngle)
                .addProperty("colors",colorsArray)
                .addProperty("locations",locationsArray)
                .addProperty("startPoint",startPointObj)
                .addProperty("endPoint",endPointObj)
                .addProperty("angleCenter",angleCenterObj);

            return propsObjBuilder.build();
        }
        return napiViewProps;
    };
};

} // namespace rnoh
#endif
