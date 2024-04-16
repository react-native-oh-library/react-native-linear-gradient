/**
 * MIT License
 *
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef HARMONY_LINEARGRADIENTCOMPONENTINSTANCE_H
#define HARMONY_LINEARGRADIENTCOMPONENTINSTANCE_H

#include "RNOH/CppComponentInstance.h"
#include "LinearGradientStackNode.h"
#include "Props.h"
#include "ShadowNodes.h"

namespace rnoh {
    class LinearGradientComponentInstance : public CppComponentInstance<facebook::react::RNLinearGradientShadowNode> {
    private:
        LinearGradientStackNode m_stackNode;
        std::vector<facebook::react::SharedColor> colors;
        facebook::react::Float angle;
        bool useAngle;
        std::vector<facebook::react::Float> locations;
        facebook::react::Point startPoint;
        facebook::react::Point endPoint;
        facebook::react::Point angleCenter;
        std::vector<float> stops;
        

    public:
        LinearGradientComponentInstance(Context context);
        void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;
    
        void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;

        LinearGradientStackNode &getLocalRootArkUINode() override;
    
        void onPropsChanged(SharedConcreteProps const &props) override;
        void getNapiProps(facebook::react::Props::Shared props);
        void getLinearGradient();
        facebook::react::Float computeAngle(facebook::react::Point const &start, facebook::react::Point const &end);
    };
} // namespace rnoh

#endif //HARMONY_LINEARGRADIENTCOMPONENTINSTANCE_H
