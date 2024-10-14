//
// Created on 4/3/2024.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "LinearGradientComponentInstance.h"

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
            DLOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> location: " << location;
        }
        DLOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> angle: " << props->angle;

        DLOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> useAngle: " << props->useAngle;
        DLOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> startPoint: "
                  << props->startPoint.x << ", " << props->startPoint.y;
        DLOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> endPoint: " << props->endPoint.x
                  << ", " << props->endPoint.y;
        DLOG(INFO) << "[clx] <LinearGradientComponentInstance::setProps> angleCenter: "
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
                DLOG(INFO) << "[clx] <RNLinearGradient::getLinearGradient> stops:" << std::to_string(stops[index]);
            }
        } else {
            this->computeStops();
        }
        DLOG(INFO) << "[clx] <RNLinearGradient::getLinearGradient> angle:" << std::to_string(this->angle);
        return;
    }

    void LinearGradientComponentInstance::computeStops() {
        float startPointX = this->startPoint.x > 0 ? this->startPoint.x : 0.0;
        float startPointY = this->startPoint.y > 0 ? this->startPoint.y : 0.0;
        float endPointX = this->endPoint.x > 0 ? this->endPoint.x : 0.0;
        float endPointY = this->endPoint.y > 0 ? this->endPoint.y : 0.0;
        float pointMax = 0.0;
        float pointMin = 0.0;
        if (startPointX == endPointX) {
            pointMin = startPointY < endPointY ? startPointY : endPointY;
            pointMin = pointMin > 1.0 ? 1.0 : pointMin;
            pointMax = startPointY > endPointY ? startPointY : endPointY;
            pointMax = pointMax > 1.0 ? 1.0 : pointMax;
        } else if (startPointY == endPointY) {
            pointMin = startPointX < endPointX ? startPointX : endPointX;
            pointMin = pointMin > 1.0 ? 1.0 : pointMin;
            pointMax = startPointX > endPointX ? startPointX : endPointX;
            pointMax = pointMax > 1.0 ? 1.0 : pointMax;
        } else {
            float pointMinY = startPointY < endPointY ? startPointY : endPointY;
            pointMinY = pointMinY > 1.0 ? 1.0 : pointMinY;
            float pointMaxY = startPointY > endPointY ? startPointY : endPointY;
            pointMaxY = pointMaxY > 1.0 ? 1.0 : pointMaxY;
            float pointMinX = startPointX < endPointX ? startPointX : endPointX;
            pointMinX = pointMinX > 1.0 ? 1.0 : pointMinX;
            float pointMaxX = startPointX > endPointX ? startPointX : endPointX;
            pointMaxX = pointMaxX > 1.0 ? 1.0 : pointMaxX;
            if ((pointMaxY - pointMinY) < (pointMaxX - pointMinX)) {
                pointMin = pointMinX;
                pointMax = pointMaxX;
            } else {
                pointMin = pointMinY;
                pointMax = pointMaxY;
            }
        }
        for (int index = 1; index <= this->colors.size(); index++) {
            if (this->colors.size() == 1) {
                this->stops.push_back(1);
            } else {
                if (index == 1) {
                    this->stops.push_back(pointMin);
                }
                if (index == this->colors.size()) {
                    this->stops.push_back(pointMax);
                }
                if (index > 1 && index < this->colors.size()) {
                    this->stops.push_back(pointMin +
                                          (index - 1) * 1.0 / (this->colors.size() - 1) * (pointMax - pointMin));
                }
            }
        }
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