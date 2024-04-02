#include "LinearGradientStackNode.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include <memory>
#include "glog/logging.h"

namespace rnoh {
    LinearGradientStackNode::LinearGradientStackNode()
        : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_STACK)) {}

    void LinearGradientStackNode::insertChild(ArkUINode &child, std::size_t index) {
        maybeThrow(NativeNodeApi::getInstance()->insertChildAt(m_nodeHandle, child.getArkUINodeHandle(), index));
    }

    void LinearGradientStackNode::removeChild(ArkUINode &child) {
        maybeThrow(NativeNodeApi::getInstance()->removeChild(m_nodeHandle, child.getArkUINodeHandle()));
    }
    LinearGradientStackNode &
    LinearGradientStackNode::setLinearGradient(const std::vector<facebook::react::SharedColor> &colors,
                                               std::vector<float> const &stops, const float &angle,
                                               const ArkUI_LinearGradientDirection &direction, const bool &repeating) {
        std::vector<uint32_t> colorsInput;
        std::vector<float> stopsInput = stops;
        for (auto color : colors) {
            uint32_t colorValue = *color;
//             auto colorComponents = colorComponentsFromColor(color);
//             uint32_t red = static_cast<uint32_t>(colorComponents.red * 255) & 0xFF;
//             uint32_t green = static_cast<uint32_t>(colorComponents.green * 255) & 0xFF;
//             uint32_t blue = static_cast<uint32_t>(colorComponents.blue * 255) & 0xFF;
//             uint32_t alpha = 0xFF; // static_cast<uint32_t>(colorComponents.alpha * 255) & 0xFF; something is off with
//                                    // the alpha by default. We may need to get color from rawProps.
//             auto colorValue = (alpha << 24) | (red << 16) | (green << 8) | blue;
            colorsInput.push_back(colorValue);
        }
        ArkUI_ColorStop colorStop = {colorsInput.data(), stopsInput.data(), static_cast<int>(colorsInput.size())};
        ArkUI_NumberValue linearGradientValue[] = {angle, {.u32 = direction}, static_cast<float>(repeating)};
        ArkUI_AttributeItem linearGradientItem = {linearGradientValue,
                                                  sizeof(linearGradientValue) / sizeof(ArkUI_NumberValue),
                                                  .object = reinterpret_cast<void *>(&colorStop)};
        maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_LINEAR_GRADIENT, &linearGradientItem));
        return *this;
    }

} // namespace rnoh
