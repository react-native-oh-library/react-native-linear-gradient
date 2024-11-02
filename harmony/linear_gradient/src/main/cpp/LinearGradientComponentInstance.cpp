/**
 * MIT License
 *
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "LinearGradientComponentInstance.h"

namespace rnoh {
LinearGradientComponentInstance::LinearGradientComponentInstance(Context context)
    : BaseRNLinearGradientComponentInstance(std::move(context)) {}

void LinearGradientComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                      std::size_t index) {
    super::onChildInserted(childComponentInstance, index);
    m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
}

void LinearGradientComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
    super::onChildRemoved(childComponentInstance);
    m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
};

LinearGradientStackNode &LinearGradientComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

void LinearGradientComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
    super::onPropsChanged(props);
    m_colors = props->colors;
    m_angle = props->angle;
    m_useAngle = props->useAngle;
    m_locations = props->locations;
    m_startPoint = props->startPoint;
    m_endPoint = props->endPoint;
    m_angleCenter = props->angleCenter;
    this->getLinearGradient();
    this->getLocalRootArkUINode().setLinearGradient(m_colors, m_stops, static_cast<float>(m_angle),
                                                    ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM, false);
}

void LinearGradientComponentInstance::getLinearGradient() {
    if (m_colors.size() == 0 ||
        m_locations.size() != 0 && (m_locations.size() != 0 && m_colors.size() != m_locations.size())) {
        m_angle = 0;
        return;
    }
    if (m_useAngle && m_angleCenter == facebook::react::Point{0, 0}) {
        // TODO:OH dose not support angleCenter
    } else {
        if (!m_useAngle) {
            m_angle = this->computeAngle(m_startPoint, m_endPoint);
        }
    }
    if (m_locations.size() != 0) {
        for (int index = 0; index < m_colors.size(); index++) {
            m_stops.push_back(static_cast<float>(m_locations[index]));
        }
    } else {
        this->computeStops();
    }
    return;
}

void LinearGradientComponentInstance::computeStops() {
    float startPointX = m_startPoint.x > 0 ? m_startPoint.x : 0.0;
    float startPointY = m_startPoint.y > 0 ? m_startPoint.y : 0.0;
    float endPointX = m_endPoint.x > 0 ? m_endPoint.x : 0.0;
    float endPointY = m_endPoint.y > 0 ? m_endPoint.y : 0.0;
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
    for (int index = 1; index <= m_colors.size(); index++) {
        if (m_colors.size() == 1) {
            m_stops.push_back(1);
        } else {
            if (index == 1) {
                m_stops.push_back(pointMin);
            }
            if (index == m_colors.size()) {
                m_stops.push_back(pointMax);
            }
            if (index > 1 && index < m_colors.size()) {
                m_stops.push_back(pointMin + (index - 1) * 1.0 / (m_colors.size() - 1) * (pointMax - pointMin));
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