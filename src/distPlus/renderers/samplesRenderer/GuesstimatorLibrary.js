const _ = require("lodash");
const { Guesstimator } = require('@foretold/guesstimator/dist');

const stringToSamples = (
  text,
  sampleCount,
  inputs = [],
) => {
  const [_error, { parsedInput, parsedError }] = Guesstimator.parse({ text:"=" + text });

  const guesstimator = new Guesstimator({ parsedInput });
  const {values, errors} = guesstimator.sample(
    sampleCount,
    inputs,
  );
  if (errors.length > 0){
    return []
  } else {
    return values
  }
};

module.exports = {
  stringToSamples,
};
