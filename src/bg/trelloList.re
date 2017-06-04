type t = Js.t {.
  name: string,
  cards: array (Js.t {.
    id: string,
    idMembers: array string
  })
};

external coerce : Js.Json.t => t = "%identity";

let fetch client id => {
  let url = Printf.sprintf "/1/boards/%s/lists?cards=open" id;
  Trello.get client url
  |> Js.Promise.then_ (fun response => Js.Promise.resolve (Json.decodeList coerce response))
};
