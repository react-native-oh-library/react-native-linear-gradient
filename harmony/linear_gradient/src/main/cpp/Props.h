#ifndef HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_PROPS_H
#define HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_PROPS_H

#include <jsi/jsi.h>
#include <react/renderer/components/view/ViewProps.h>
#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/PropsConversions.h>
#include <vector>
#include <boost/json.hpp>


namespace facebook{
namespace react {

class JSI_EXPORT RNLinearGradientProps final : public ViewProps {
 public:
  RNLinearGradientProps() = default;
  RNLinearGradientProps(const PropsParserContext &context, const RNLinearGradientProps &sourceProps, const RawProps &rawProps);

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


