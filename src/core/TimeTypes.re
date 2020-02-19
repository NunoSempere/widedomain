type timeUnit = [
  | `days
  | `hours
  | `milliseconds
  | `minutes
  | `months
  | `quarters
  | `seconds
  | `weeks
  | `years
];

type timeVector = {
  zero: MomentRe.Moment.t,
  length: MomentRe.Moment.t,
  step: timeUnit,
};

type timePoint = {
  timeVector,
  value: float,
};

module TimeUnit = {
  let toString = (timeUnit: timeUnit) =>
    switch (timeUnit) {
    | `days => "days"
    | `hours => "hours"
    | `milliseconds => "milliseconds"
    | `minutes => "minutes"
    | `months => "months"
    | `quarters => "quarters"
    | `seconds => "seconds"
    | `weeks => "weeks"
    | `years => "years"
    };
};

module TimePoint = {
  let fromTimeVector = (timeVector, value): timePoint => {timeVector, value};

  let toMoment = (timePoint: timePoint) => {
    timePoint.timeVector.zero
    |> MomentRe.Moment.add(
         ~duration=
           MomentRe.duration(timePoint.value, timePoint.timeVector.step),
       );
  };

  let fromMoment = (timeVector: timeVector, moment: MomentRe.Moment.t) =>
    MomentRe.diff(timeVector.zero, moment, timeVector.step);
};

module RelativeTimePoint = {
  type timeInVector =
    | Time(MomentRe.Moment.t)
    | XValue(float);

  let toTime = (timeVector: timeVector, timeInVector: timeInVector) =>
    switch (timeInVector) {
    | Time(r) => r
    | XValue(r) =>
      timeVector.zero
      |> MomentRe.Moment.add(~duration=MomentRe.duration(r, timeVector.step))
    };

  let _timeToX = (time, timeStart, timeUnit) =>
    MomentRe.diff(timeStart, time, timeUnit);

  let toXValue = (timeVector: timeVector, timeInVector: timeInVector) =>
    switch (timeInVector) {
    | Time(r) => _timeToX(r, timeVector.zero, timeVector.step)
    | XValue(r) => r
    };
};