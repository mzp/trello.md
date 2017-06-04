type t = Js.t {.
  avatarHash: string,
  username: string
};

external coerce : Js.Json.t => t = "%identity";

let fetch client id => {
  let url = Printf.sprintf "/1/boards/%s/members?fields=all" id;
  Trello.get client url
  |> Js.Promise.then_ (fun response => Js.Promise.resolve (Json.decodeList coerce response))
}
