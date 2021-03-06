type route =
  | Model(string)
  | DistBuilder
  | DistBuilder2
  | DistBuilder3
  | Home
  | NotFound;

let routeToPath = route =>
  switch (route) {
  | Model(modelId) => "/m/" ++ modelId
  | DistBuilder => "/dist-builder"
  | DistBuilder2 => "/dist-builder2"
  | DistBuilder3 => "/dist-builder3"
  | Home => "/"
  | _ => "/"
  };

module Models = {
  let all = [|
    EAFunds.Interface.model,
    GlobalCatastrophe.Interface.model,
    Human.Interface.model,
  |];
  let getById = id => E.A.getBy(all, r => r.id == id);
};

module Menu = {
  module Styles = {
    open Css;
    let menu =
      style([
        position(`relative),
        marginTop(em(0.25)),
        marginBottom(em(0.25)),
        selector(
          "a",
          [
            borderRadius(em(0.25)),
            display(`inlineBlock),
            backgroundColor(`hex("eee")),
            padding(em(1.)),
            cursor(`pointer),
          ],
        ),
        selector("a:hover", [backgroundColor(`hex("bfcad4"))]),
        selector("a:hover", [backgroundColor(`hex("bfcad4"))]),
        selector(
          "a:not(:first-child):not(:last-child)",
          [marginRight(em(0.25)), marginLeft(em(0.25))],
        ),
      ]);
  };

  module Item = {
    [@react.component]
    let make = (~href, ~children) => {
      <a
        href
        onClick={e => {
          e->ReactEvent.Synthetic.preventDefault;
          ReasonReactRouter.push(href);
        }}>
        children
      </a>;
    };
  };

  [@react.component]
  let make = () => {
    <div className=Styles.menu>
      <Item href={routeToPath(Home)} key="home"> {"Home" |> E.ste} </Item>
      <Item href={routeToPath(DistBuilder)} key="dist-builder">
        {"Dist Builder" |> E.ste}
      </Item>
      <Item href={routeToPath(DistBuilder2)} key="dist-builder-2">
        {"Dist Builder 2" |> E.ste}
      </Item>
      <Item href={routeToPath(DistBuilder3)} key="dist-builder-3">
        {"Dist Builder 3" |> E.ste}
      </Item>
    </div>;
  };
};

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let routing =
    switch (url.path) {
    | ["m", modelId] => Model(modelId)
    | ["dist-builder"] => DistBuilder
    | ["dist-builder2"] => DistBuilder2
    | ["dist-builder3"] => DistBuilder3
    | [] => Home
    | _ => NotFound
    };

  <div className="w-full max-w-screen-xl mx-auto px-6">
    <Menu />
    {switch (routing) {
     | Model(id) =>
       switch (Models.getById(id)) {
       | Some(model) => <FormBuilder.ModelForm model key=id />
       | None => <div> {"Page is not found" |> E.ste} </div>
       }
     | DistBuilder => <DistBuilder />
     | DistBuilder2 => <DistBuilder2 />
     | DistBuilder3 => <DistBuilder3 />
     | Home => <Home />
     | _ => <div> {"Page is not found" |> E.ste} </div>
     }}
  </div>;
};