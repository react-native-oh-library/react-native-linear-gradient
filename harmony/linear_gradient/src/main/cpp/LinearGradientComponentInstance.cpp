//
// Created on 4/3/2024.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "LinearGradientComponentInstance.h"
#include <glog/logging.h>

namespace rnoh {
    LinearGradientComponentInstance::LinearGradientComponentInstance(Context context, facebook::react::Tag tag)
        : ComponentInstance(std::move(context), tag) {}

    void LinearGradientComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance,
                                                      std::size_t index) {
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    LinearGradientStackNode &LinearGradientComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    void LinearGradientComponentInstance::setProps(facebook::react::Props::Shared props) {
        if (auto p = std::dynamic_pointer_cast<const facebook::react::RNLinearGradientProps>(props)) {
            this->getNapiProps(props);
            this->getLinearGradient();
            for (auto color : p->colors) {
                auto colorComponents = colorComponentsFromColor(color);
                uint32_t red = static_cast<uint32_t>(colorComponents.red * 255) & 0xFF;
                uint32_t green = static_cast<uint32_t>(colorComponents.green * 255) & 0xFF;
                uint32_t blue = static_cast<uint32_t>(colorComponents.blue * 255) & 0xFF;
                uint32_t alpha = 0xFF; // static_cast<uint32_t>(colorComponents.alpha * 255) & 0xFF; something is off
                                       // with the alpha by default. We may need to get color from rawProps.
                auto colorValue = (alpha << 24) | (red << 16) | (green << 8) | blue;
                LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> color: " << std::to_string(colorValue);
            }
            for (auto location : p->locations) {
                LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> location: " << location;
            }
            LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> angle: " << p->angle;

            LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> useAngle: " << p->useAngle;
            LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> startPoint: " << p->startPoint.x << ", "
                      << p->startPoint.y;
            LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> endPoint: " << p->endPoint.x << ", "
                      << p->endPoint.y;
            LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> angleCenter: " << p->angleCenter.x << ", "
                      << p->angleCenter.y;
            this->getLocalRootArkUINode().setLinearGradient(this->colors, this->stops, static_cast<float>(this->angle),
                                                            ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT, false);
        }
    }

    void LinearGradientComponentInstance::getNapiProps(facebook::react::Props::Shared props) {
        auto p = std::dynamic_pointer_cast<const facebook::react::RNLinearGradientProps>(props);
        this->colors = p->colors;
        this->angle = p->angle;
        this->useAngle = p->useAngle;
        this->locations = p->locations;
        this->startPoint = p->startPoint;
        this->endPoint = p->endPoint;
        this->angleCenter = p->angleCenter;
    }

    void LinearGradientComponentInstance::getLinearGradient() {
        if (this->colors.size() == 0 ||
            locations.size() != 0 && (this->locations.size() != 0 && this->colors.size() != this->locations.size())) {
            this->angle = 0;
            return;
        }
        if (this->useAngle && this->angleCenter == facebook::react::Point{0, 0}) {
            // TODO:OH dose not support angleCenter
        } else {
            if (!this->useAngle) {
                this->angle = this->computeAngle(this->startPoint, this->endPoint);
            }
        }
        if (this->locations.size() != 0) {
            for (int index = 0; index < this->colors.size(); index++) {
                this->stops.push_back(static_cast<float>(this->locations[index]));
                LOG(INFO) << "[clx] <RNLinearGradient::getLinearGradient> stops:" << std::to_string(stops[index]);
            }
        } else {
            for (int index = 0; index < this->colors.size(); index++) {
                if (this->colors.size() == 1)
                    this->stops.push_back(0);
                this->stops.push_back(index * 1.0 / (this->colors.size() - 1));
                LOG(INFO) << "[clx] <RNLinearGradient::getLinearGradient> stops:" << std::to_string(stops[index]);
            }
        }
        LOG(INFO) << "[clx] <RNLinearGradient::getLinearGradient> angle:" << std::to_string(this->angle);
        return;
    }

    facebook::react::Float LinearGradientComponentInstance::computeAngle(facebook::react::Point const &start,
                                                                         facebook::react::Point const &end) {
        float angle = 0;
        if (start.x == end.x) {
            if (start.y == end.y) {
                angle = 0;
            } else if (start.y < end.y) {
                angle = 180.0;
            } else {
                angle = 0;
            }
        } else if (start.y == end.y) {
            if (start.x == end.x) {
                angle = 90.0;
            } else if (start.x < end.x) {
                angle = 90.0;
            } else {
                angle = -90.0;
            }
        } else {
            float tan = (end.x - start.x) / (end.y - start.y);
            angle = 180.0 - atan(tan) * 180.0 / M_PI;
        }
        return angle;
    }
} // namespace rnoh