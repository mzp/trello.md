module Tabs = {
  type tab = Js.t { .
    url : Js.Null.t string,
    id : int
  };

  module OnUpdated = {
    external add_listener: (int => unit => tab => unit) => unit = "addListener" [@@bs.val] [@@bs.scope ("chrome", "tabs", "onUpdated")];
  }
};

module PageAction = {
  external show: int => unit = "show" [@@bs.val] [@@bs.scope ("chrome", "pageAction")];
  external set_icon: Js.t {. tabId: int, path : string } => unit = "setIcon" [@@bs.val] [@@bs.scope ("chrome", "pageAction")];

  module OnClicked = {
    external add_listener: (Tabs.tab => unit) => unit = "addListener" [@@bs.val] [@@bs.scope ("chrome", "pageAction", "onClicked")];
  };
};
