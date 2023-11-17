#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>
#include "Props.h"

namespace facebook {
namespace react {

RNLinearGradientProps::RNLinearGradientProps(
    const PropsParserContext &context,
    const RNLinearGradientProps &sourceProps,
    const RawProps &rawProps)
    : ViewProps(context, sourceProps, rawProps),

        angle(convertRawProp(context, rawProps, "angle", sourceProps.angle, {0.0})),
        useAngle(convertRawProp(context, rawProps, "useAngle", sourceProps.useAngle, {false})),
        startPoint(convertRawProp(context, rawProps, "startPoint", sourceProps.startPoint, {.x = 0.5, .y = 0})),
        endPoint(convertRawProp(context, rawProps, "endPoint", sourceProps.endPoint, {.x = 0.5, .y = 1})),
        colors(convertRawProp(context, rawProps, "colors", sourceProps.colors, {})),
        locations(convertRawProp(context, rawProps, "locations", sourceProps.locations, {})),
        angleCenter(convertRawProp(context, rawProps, "angleCenter", sourceProps.angleCenter, {})){}

} // namespace react
} // namespace facebook
