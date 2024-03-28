/*
 * MIT License
 *
 * Copyright (C) 2021 Huawei Device Co., Ltd.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANT KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTPACKAGE_H
#define HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTPACKAGE_H

#include "RNOH/Package.h"
#include "RNOHCorePackage/ComponentInstances/ViewComponentInstance.h"
#include "ComponentDescriptors.h"
#include "LinearGradientJSIBinder.h"
#include "LinearGradientNapiBinder.h"
#include "LinearGradientComponentInstance.h"

namespace rnoh {

    class LinearGradientPackageComponentInstanceFactoryDelegate : public ComponentInstanceFactoryDelegate {
    public:
        using ComponentInstanceFactoryDelegate::ComponentInstanceFactoryDelegate;

        ComponentInstance::Shared create(ComponentInstance::Context ctx) override {
            if (ctx.componentName == "RNLinearGradient") {
                return std::make_shared<LinearGradientComponentInstance>(std::move(ctx));
            }
            return nullptr;
        }
    };

    class LinearGradientPackage : public Package {
    public:
        LinearGradientPackage(Package::Context ctx) : Package(ctx) {}
    
        ComponentInstanceFactoryDelegate::Shared createComponentInstanceFactoryDelegate() override {
            return std::make_shared<LinearGradientPackageComponentInstanceFactoryDelegate>(m_ctx);
        }

        std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() override {
            return {facebook::react::concreteComponentDescriptorProvider<
                facebook::react::RNLinearGradientComponentDescriptor>()};
        }

        ComponentJSIBinderByString createComponentJSIBinderByName() override {
            return {
                {"RNLinearGradient", std::make_shared<LinearGradientJSIBinder>()},

            };
        }

        ComponentNapiBinderByString createComponentNapiBinderByName() override {
            return {
                {"RNLinearGradient", std::make_shared<LinearGradientNapiBinder>()},
            };
        }
    };
} // namespace rnoh
#endif