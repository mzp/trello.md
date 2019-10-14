type t = Js.t {.
  id : string,
  avatarHash: Js.Null.t string,
  username: string
};
let fetch: Trello.t => string => Js.Promise.t (list t);
