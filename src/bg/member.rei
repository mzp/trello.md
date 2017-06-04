type t = Js.t {.
  avatarHash: string,
  username: string
};
let fetch: Trello.t => string => Js.Promise.t (list t);
