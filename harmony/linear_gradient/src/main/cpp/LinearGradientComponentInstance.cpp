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

    void LinearGradientComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }
    void LinearGradientComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    LinearGradientStackNode &LinearGradientComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

     void LinearGradientComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        CppComponentInstance::onPropsChanged(props);
        auto linearGradientProps = std::dynamic_pointer_cast<const facebook::react::RNLinearGradientProps>(props);
        if (linearGradientProps == nullptr) {
            return;
        }
        this->colors = props->colors;
        this->angle = props->angle;
        this->useAngle = props->useAngle;
        this->locations = props->locations;
        this->startPoint = props->startPoint;
        this->endPoint = props->endPoint;
        this->angleCenter = props->angleCenter;
        this->getLinearGradient();
        for (auto location : props->locations) {
            LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> location: " << location;
        }
        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> angle: " << props->angle;

        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> useAngle: " << props->useAngle;
        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> startPoint: "
                  << props->startPoint.x << ", " << props->startPoint.y;
        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> endPoint: " << props->endPoint.x
                  << ", " << props->endPoint.y;
        LOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> angleCenter: "
                  << props->angleCenter.x << ", " << props->angleCenter.y;
		this->getLocalRootArkUINode().setLinearGradient(this->colors, this->stops, static_cast<float>(this->angle),
													ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM, false);
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