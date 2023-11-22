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

#ifndef HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_PROPS_H
#define HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_PROPS_H

#include <jsi/jsi.h>
#include <react/renderer/components/view/ViewProps.h>
#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>
#include <vector>
#include <boost/json.hpp>

namespace facebook {
namespace react {

class JSI_EXPORT RNLinearGradientProps final : public ViewProps {
 public:
  RNLinearGradientProps() = default;
  RNLinearGradientProps(const PropsParserContext& context, const RNLinearGradientProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props

  Point startPoint{};
  Point endPoint{};
  std::vector<SharedColor> colors{};
  std::vector<Float> locations{};
  bool useAngle{false};
  Point angleCenter{};
  Float angle{0.0};
};

} // namespace react
} // namespace facebook
#endif
