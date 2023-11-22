/*
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
