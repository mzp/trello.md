type t = Js.t {.
  id : string,
  avatarHash: string,
  username: string
};
let fetch: Trello.t => string => Js.Promise.t (list t);
