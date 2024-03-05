#pragma once

#include "RNOH/arkui/ArkUINode.h"
#include "RNOH/arkui/StackNode.h"
#include <react/renderer/graphics/Color.h>

namespace rnoh {

    class LinearGradientStackNode : public ArkUINode {
    public:
        LinearGradientStackNode();

        void insertChild(ArkUINode &child, std::size_t index);
        void removeChild(ArkUINode &child);
    
        LinearGradientStackNode &setLinearGradient(std::vector<facebook::react::SharedColor> const &,
                                                   std::vector<float> const &, float const &,
                                                   ArkUI_LinearGradientDirection const &, bool const &);
    };

} // namespace rnoh