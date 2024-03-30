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
 
import {
    Descriptor,
    ComponentBuilderContext,
    RNComponentFactory,
    RNViewBase,
    RNOHContext,
    ViewBaseProps,
    ColorSegments,
    convertColorSegmentsToString,
    Tag,
} from 'rnoh'

export const LINEAR_GRADIENT_TYPE: string = "RNLinearGradient"

interface ColorItem {
    color: ColorSegments
}

interface LocationItem {
    location: number
}

interface Point {
    x: number
    y: number
}

interface LinearGradientArgs{
    angle?: number | string;
    direction?: GradientDirection;
    colors: Array<[ResourceColor,number]>;
    repeating?: boolean;
}

export  interface LinearGradientProps extends ViewBaseProps {
    colors: ColorItem[]
    angle?: number
    useAngle?: boolean
    locations?: LocationItem[]
    startPoint?: Point
    endPoint?: Point
    angleCenter?: Point
}

export type LinearGradientDescriptor = Descriptor<"RNLinearGradient",LinearGradientProps>

@Component
export struct RNLinearGradient {
    ctx!: RNOHContext
    tag: number = 0
    @BuilderParam buildCustomComponent: (ComponentBuilderContext: ComponentBuilderContext) => void
    @State descriptor: LinearGradientDescriptor = {} as LinearGradientDescriptor
    private unregisterDescriptorChangesListener?: () => void = undefined

    aboutToAppear(){
      this.descriptor = this.ctx.descriptorRegistry.getDescriptor<LinearGradientDescriptor>(this.tag)
      this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
        (newDescriptor) => {
            this.descriptor = (newDescriptor as LinearGradientDescriptor)
        }
      )
      console.info(`RNOH in LinearGradient props, ${JSON.stringify(this.descriptor.props)}`);
    }
    
    aboutToDisappear(){
        this.unregisterDescriptorChangesListener?.()
    }

    getLinearGradient(): LinearGradientArgs {
        let colorArr: ResourceColor[] = [];
        let locationArr: number[] =[];
        for (let i = 0; i < this.descriptor.props.colors.length; i ++) {
            colorArr.push(convertColorSegmentsToString(this.descriptor.props.colors[i].color) as ResourceColor)
        }
        if (this.descriptor.props.locations) {
            for (let i = 0; i < this.descriptor.props.locations.length; i ++) {
                locationArr.push(this.descriptor.props.locations[i].location)
            }
        }

        let colorsRes: Array<[ResourceColor, number]> = []
        let startPoint = this.descriptor.props.startPoint ? [this.descriptor.props.startPoint.x, this.descriptor.props.startPoint.y]: [0,0]
        let endPoint = this.descriptor.props.endPoint ? [this.descriptor.props.endPoint.x, this.descriptor.props.endPoint.y]: [0,0]
        let angleCenter: [number,number] | null = null;
        if (this.descriptor.props.angleCenter) {
            angleCenter = this.descriptor.props.angleCenter.x == 0 && this.descriptor.props.angleCenter.y ==0 ? null
                : [this.descriptor.props.angleCenter.x, this.descriptor.props.angleCenter.y]
        }
        let angle = this.descriptor.props.angle ?? this.descriptor.props.angle
        let useAngle = this.descriptor.props.useAngle ?? this.descriptor.props.useAngle
        if(this.descriptor.props.colors.length == 0 || this.descriptor.props.locations && (this.descriptor.props.locations.length != 0 && colorArr.length != locationArr.length)) {
            return {
                colors: colorsRes,
                angle: 0,
            };  
        }
        if (useAngle && angleCenter != null) {
            //TODO: OH dose not support angleCenter
        } else {
            if (!useAngle) {
                angle  = this.computeAngle(startPoint, endPoint);
            }
        }
        if (this.descriptor.props.locations && this.descriptor.props.locations.length !=0){
            for (let index = 0; index < colorArr.length; index++) {
                colorsRes[index] = [colorArr[index], locationArr[index]];
            }
        }else {
            for(let index = 0; index < colorArr.length; index++) {
                colorsRes[index] = [colorArr[index], colorArr.length == 1 ? 0: index * 1.0 / (colorArr.length -1)];
            }
        }
        return {
            colors: colorsRes,
            angle: angle,
        };
    }

    computeAngle(start:Array<number>, end:Array<number>):number{
        let angle = 0
       if (start[0] == end[0]) {
        if (start[1] == end[1]) {
            angle = 0
        } else if (start[1] < end[1]) {
          angle = 180
        } else {
          angle = 0;
        }
    } else if (start[1] == end[1]) {
        if (start[0] == end[0]) {
            angle = 90
        } else if (start[0] < end[0]) {
            angle = 90;
        } else {
            angle = -90;
        }
    } else{
        let tan = (end[0] - start[0]) / (end[1] - start[1])
        angle = 180 - Math.atan(tan) * 180 / Math.PI
    }
    return angle
 }

  build() {
      RNViewBase({ ctx: this.ctx, tag: this.tag}) {
          Stack() {
              ForEach(this.descriptor.childrenTags, (tag: Tag) =>{
                  RNComponentFactory({ ctx: this.ctx, tag: tag, buildCustomComponent: this.buildCustomComponent })
              }, (tag: Tag) => tag.toString())
          }
          .width("100%")
          .height("100%")
          .linearGradient(this.getLinearGradient())
          .clip(true)
      }
  }
}
