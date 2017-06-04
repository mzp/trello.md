external get_item : string => Js.Null.t string = "getItem" [@@bs.val] [@@bs.scope "localStorage"];
external set_item : string => string => unit = "setItem" [@@bs.val] [@@bs.scope "localStorage"];
