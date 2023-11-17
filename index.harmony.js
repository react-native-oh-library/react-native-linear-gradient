

import React, { Component, ctreateRef } from 'react';
import { processColor, StyleSheet, View } from 'react-native';
import NativeLinearGradient, { type Props } from './src';

const convertPoint = (name,point) => {
    if (Array.isArray(point)) {
        console.warn(
            `LinearGradient '${name}' property should be an object with fields 'x' and 'y',` +
            `Array type is deprecated.`
        );

        return{
            x: point[0],
            y: point[1]
        };
    }
    return point;
};

export default class LinearGradient extends Component<Props> {
    props: Props;
    gradientRef = createRef<NativeLinearGradient>();

    static defaultProps = {
       start: { x: 0.5, y: 0.0},
       end: { x: 0.5, y: 1.0},
    };
    setNativeProps(props: Props) {
        this.gradientRef.current.setNativeProps(props);
    }

    render() {
        const {
            children,
            style,
            start,
            end,
            colors,
            locations,
            useAngle,
            angleCenter,
            angle,
            ...otherProps
        } = this.props;
        if ((colors && locations) && (colors.length !== location.length)) {
            console.warn('LinearGradient colors and location props should be array of the same length');
        }
        return (
            <View ref={this.gradientRef} {...otherProps} style={[this.style.LinearGradientContainer, style]}>
              <NativeLinearGradient
                style={{position: 'absolute', top: 0, left: 0, bottom: 0, right: 0}}
                colors={colors.map(processColor)}
                startPoint={convertPoint('start',start)}
                endPoint={convertPoint('end',end)}
                locations={locations ? location.slice(0, colors.length) : null}
                useAngle={useAngle}
                angleCenter={convertPoint('angleCenter',angleCenter)}
                angle={angle}
              />
              {children}
            </View>
        );
    }
    styles = StyleSheet.create({
        LinearGradientContainer: {
            overflow: 'hidden'
        }
    })
    
    
}