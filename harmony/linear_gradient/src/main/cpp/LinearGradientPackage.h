#ifndef HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTPACKAGE_H
#define HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTPACKAGE_H

#include "RNOH/Package.h"
#include "ComponentDescriptors.h"
#include "LinearGradientJSIBinder.h"
#include "LinearGradientNapiBinder.h"

namespace rnoh {

class LinearGradientPackage : public Package {
  public:
      LinearGradientPackage(Package::Context ctx) : Package(ctx) {}

      std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() override 
      {
          return {
              facebook::react::concreteComponentDescriptorProvider<
                  facebook::react::RNLinearGradientComponentDescriptor>()
            //   facebook::react::concreteComponentDescriptorProvider<
            //       facebook::react::RNCAnyHeaderComponentDescriptor>(),
            //   facebook::react::concreteComponentDescriptorProvider<
            //       facebook::react::RNCDefaultHeaderComponentDescriptor>(),
//              facebook::react::concreteComponentDescriptorProvider<
//                  facebook::react::RNCMaterialHeaderComponentDescriptor>(),
//              facebook::react::concreteComponentDescriptorProvider<
//                  facebook::react::RNCStoreHouseHeaderComponentDescriptor>(),
//              facebook::react::concreteComponentDescriptorProvider<
//                  facebook::react::RNCClassicsHeaderComponentDescriptor>(),
        
        
          };
    }
    
    ComponentJSIBinderByString createComponentJSIBinderByName() override
    {
        return {{"RNLinearGradient",std::make_shared<LinearGradientJSIBinder>()},
        // {"RNCAnyHeader",std::make_shared<RNCAnyHeaderJSIBinder>()},
        // {"RNCDefaultHeader",std::make_shared<RNCDefaultHeaderJSIBinder>()},
//        {"RTNCenteredText",std::make_shared<RNCDefaultHeaderJSIBinder>()},
//        {"RNCClassicsHeader",std::make_shared<RNCDefaultHeaderJSIBinder>()},
//        {"RNCMaterialHeader",std::make_shared<RNCDefaultHeaderJSIBinder>()},
//        {"RNCStoreHouseHeader",std::make_shared<RNCDefaultHeaderJSIBinder>()},
        };
    }
    
    ComponentNapiBinderByString createComponentNapiBinderByName() override{
        return {
        {"RNLinearGradient", std::make_shared<LinearGradientNapiBinder>()},
        // {"RNCAnyHeader", std::make_shared<RNCAnyHeaderNapiBinder>()},
        // {"RNCDefaultHeader", std::make_shared<RNCDefaultHeaderNapiBinder>()},
//        {"RTNCenteredText", std::make_shared<RNCDefaultHeaderNapiBinder>()},
//        {"RNCClassicsHeader", std::make_shared<RNCDefaultHeaderNapiBinder>()},
//        {"RNCMaterialHeader", std::make_shared<RNCDefaultHeaderNapiBinder>()},
//        {"RNCStoreHouseHeader", std::make_shared<RNCDefaultHeaderNapiBinder>()},
        };
    }
    
    // EventEmitRequestHandlers createEventEmitRequestHandlers() override {
    //     return {std::make_shared<SmartRefreshLayoutEmitRequestHandler>()};
    // }
};
} // namespace rnoh
#endif