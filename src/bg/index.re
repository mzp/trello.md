let domain = Js.Re.fromString "trello[.]com/b/";
let app_key = "d79e101f262c8b20de7993cdc98cd5b2";

let show_if_trello tab_id _ tab => {
  switch (Js.Null.to_opt tab##url) {
    | Some url when Js.Re.test url domain =>
      Chrome.PageAction.show tab_id
    | Some _ | None =>
      ()
  }
};

let create_trello () => {
  let t = Trello.create app_key;
  switch (Js.Null.to_opt @@ LocalStorage.get_item "token") {
    | Some token =>
      Trello.set_token t token;
      Js.Promise.resolve t;
    | None =>
      Trello.auth t {
        "name": "Trello.md",
        "expiration": "never",
        "scope": { "read": true, "write": false, "account": false }
      }
      |> Js.Promise.then_ (fun () => {
        LocalStorage.set_item "token" (Trello.token t);
        Js.Promise.resolve t
      })
  }
};

let copy_to_clipboard tab => {
  Chrome.PageAction.set_icon {
    "tabId": tab##id,
    "path": "../icons/executing.png"
  };
  create_trello ()
  |> Js.Promise.then_ (fun client =>
    Js.Null.to_opt tab##url
    |> Option.then_ Board.parse_url
    |> Option.map (fun id =>
      Promise_.all3
        (TrelloList.fetch client id,
         Card.fetch client id,
         Member.fetch client id))
    |> Option.get (Js.Promise.resolve ([], [], [])))
  |> Js.Promise.then_ (fun (lists, cards, members) => {
    Js.Promise.resolve (ListWithCard.make lists::lists cards::cards members::members)
  })
  |> Js.Promise.then_ (fun x => Js.Promise.resolve (Markdown.format x))
  |> Promise_.map Clipboard.write
  |> Promise_.map (fun () =>
    Chrome.PageAction.set_icon {
      "tabId": tab##id,
      "path": "../icons/icon19.png"
    })
  |> ignore;
  ()
};

Chrome.Tabs.OnUpdated.add_listener show_if_trello;
Chrome.PageAction.OnClicked.add_listener copy_to_clipboard;
