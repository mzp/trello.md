let regexp = Js.Re.fromString "trello[.]com/b/([^/]+)";

let board_id url =>
  Js.Re.exec url regexp
  |> Option.then_ (fun result => {
    let xs = Js.Re.matches result;
    if (Array.length xs >= 2) {
      Some xs.(1)
    } else {
      None
    }
  });

let cards client url => {
  switch (board_id url) {
    | None => Js.Promise.resolve Js.Json.null
    | Some id => {
      let url = Printf.sprintf "/1/boards/%s/lists?cards=open" id;
      Trello.get client url
    }
  }
};

let members client url => {
  switch (board_id url) {
    | None => Js.Promise.resolve Js.Json.null
    | Some id => {
      let url = Printf.sprintf "/1/boards/%s/members?fields=all" id;
      Trello.get client url
    }
  }
}
