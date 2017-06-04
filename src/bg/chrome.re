module Tabs = {
  module OnUpdated = {
    type tab = Js.t { . url : Js.Null.t string };
    external add_listener: (int => unit => tab => unit) => unit = "addListener" [@@bs.val] [@@bs.scope ("chrome", "tabs", "onUpdated")];
  }
};

module PageAction = {
  external show: int => unit = "show" [@@bs.val] [@@bs.scope ("chrome", "pageAction")]
};
