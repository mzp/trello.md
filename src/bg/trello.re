type t;

external create : string => t = "trello-browser" [@@bs.new] [@@bs.module];

external set_token : t => string => unit = "setToken" [@@bs.send];
external token : t => string = "token" [@@bs.get];

external get : t => string => Js.Promise.t Js.Json.t = "get" [@@bs.send];

external auth : t => Js.t { .
  name : string,
  expiration : string,
  scope : Js.t { . read : bool, write : bool, account : bool }
} => Js.Promise.t unit = "auth" [@@bs.send]
