#ifndef SHADOWNODES_H
#define SHADOWNODES_H

#pragma once

#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <react/renderer/components/view/ViewShadowNode.h>
#include <jsi/jsi.h>
#include "Props.h"

namespace facebook {
namespace react {

JSI_EXPORT extern const char RNLinearGradientComponentName[];

/*
 * `ShadowNode` for <RTNCenteredText> component.
 */
using RNLinearGradientShadowNode = ConcreteViewShadowNode<
    RNLinearGradientComponentName,
    RNLinearGradientProps,
    ViewEventEmitter
>;

} // namespace react
} // namespace facebook
#endif
