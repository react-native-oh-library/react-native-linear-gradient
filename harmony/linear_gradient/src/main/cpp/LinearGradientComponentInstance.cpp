//
// Created on 4/3/2024.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "LinearGradientComponentInstance.h"
#include <glog/logging.h>

namespace rnoh {
    LinearGradientComponentInstance::LinearGradientComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {}

    void LinearGradientComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance,
                                                      std::size_t index) {
        CppComponentInstance::insertChild(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void LinearGradientComponentInstance::removeChild(ComponentInstance::Shared childComponentInstance) {
        CppComponentInstance::removeChild(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    LinearGradientStackNode &LinearGradientComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    void LinearGradientComponentInstance::setProps(facebook::react::Props::Shared props) {
        CppComponentInstance::setProps(props);
        auto linearGradientProps = std::dynamic_pointer_cast<const facebook::react::RNLinearGradientProps>(props);
        if (linearGradientProps == nullptr) {
            return;
        }
        this->colors = linearGradientProps->colors;
        this->angle = linearGradientProps->angle;
        this->useAngle = linearGradientProps->useAngle;
        this->locations = linearGradientProps->locations;
        this->startPoint = linearGradientProps->startPoint;
        this->endPoint = linearGradientProps->endPoint;
        this->angleCenter = linearGradientProps->angleCenter;
        this->getLinearGradient();
        for (auto location : linearGradientProps->locations) {
            LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> location: " << location;
        }
        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> angle: " << linearGradientProps->angle;

        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> useAngle: " << linearGradientProps->useAngle;
        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> startPoint: "
                  << linearGradientProps->startPoint.x << ", " << linearGradientProps->startPoint.y;
        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> endPoint: " << linearGradientProps->endPoint.x
                  << ", " << linearGradientProps->endPoint.y;
        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> angleCenter: "
                  << linearGradientProps->angleCenter.x << ", " << linearGradientProps->angleCenter.y;
        this->getLocalRootArkUINode().setLinearGradient(this->colors, this->stops, static_cast<float>(this->angle),
                                                        ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT, false);
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