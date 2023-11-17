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
