type t = Js.t {.
  name: string,
  cards: array (Js.t {.
    id: string,
    idMembers: array string
  })
};

let fetch: Trello.t => string => Js.Promise.t (list t);
