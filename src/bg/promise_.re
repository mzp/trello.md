type t 'a = Js.Promise.t 'a;

external all3 : (t 'a0, t 'a1, t 'a2) => t ('a0 , 'a1, 'a2 ) = "Promise.all" [@@bs.val];

let map f x =>
  Js.Promise.then_ (fun y => Js.Promise.resolve (f y)) x;

