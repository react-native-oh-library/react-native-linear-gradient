//
// Created on 4/3/2024.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_LINEARGRADIENTCOMPONENTINSTANCE_H
#define HARMONY_LINEARGRADIENTCOMPONENTINSTANCE_H

#include "RNOH/CppComponentInstance.h"
#include "LinearGradientStackNode.h"
#include "Props.h"

namespace rnoh {
    class LinearGradientComponentInstance : public CppComponentInstance {
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
        LinearGradientComponentInstance(Context context, facebook::react::Tag tag);

        void insertChild(ComponentInstance::Shared childComponentInstance, std::size_t index) override;

        void removeChild(ComponentInstance::Shared childComponentInstance) override;

        LinearGradientStackNode &getLocalRootArkUINode() override;

        void setProps(facebook::react::Props::Shared props) override;
        void getNapiProps(facebook::react::Props::Shared props);
        void getLinearGradient();
        facebook::react::Float computeAngle(facebook::react::Point const &start, facebook::react::Point const &end);
    };
} // namespace rnoh

#endif //HARMONY_LINEARGRADIENTCOMPONENTINSTANCE_H
