import React, { useEffect } from 'react';
import { useSize } from 'react-use';
import { DistPlotD3 } from './distPlotD3';

/**
 * @param min
 * @param max
 * @returns {number}
 */
function getRandomInt(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

/**
 * @param props
 * @returns {*}
 * @constructor
 */
function DistPlotReact(props) {
  const containerRef = React.createRef();
  const key = "cdf-chart-react-" + getRandomInt(0, 1000);
  const style = !!props.width ? { width: props.width + "px" } : {};

  const [sized, { width }] = useSize(() => {
    return React.createElement("div", {
      key: "resizable-div",
    });
  }, {
    width: props.width,
  });

  useEffect(() => {
    try {
      new DistPlotD3()
        .set('svgWidth', width)
        .set('svgHeight', props.height)
        .set('maxX', props.maxX)
        .set('minX', props.minX)
        .set('onHover', props.onHover)
        .set('marginBottom', props.marginBottom || 15)
        .set('marginLeft', 30)
        .set('marginRight', 30)
        .set('marginTop', 5)
        .set('showDistributionLines', props.showDistributionLines)
        .set('showDistributionYAxis', props.showDistributionYAxis)
        .set('verticalLine', props.verticalLine || 110)
        .set('showVerticalLine', props.showVerticalLine)
        .set('container', containerRef.current)
        .set('xScaleType', props.xScale || 'linear')
        .set('yScaleType', props.yScale || 'linear')
        .set('xScaleTimeOptions', props.timeScale)
        .set('yMaxContinuousDomainFactor', props.yMaxContinuousDomainFactor || 1)
        .set('yMaxDiscreteDomainFactor', props.yMaxDiscreteDomainFactor || 1)
        .data({
          continuous: props.continuous,
          discrete: props.discrete,
        })
        .render();
    } catch (e) {
      console.error("distPlotD3 Error: ", e)
    }
  });

  return React.createElement("div", {
    style: {
      paddingLeft: "10px",
      paddingRight: "10px",
    },
  }, [
    sized,
    React.createElement("div", {
      key,
      style,
      ref: containerRef,
    }),
  ]);
}

export default DistPlotReact;
