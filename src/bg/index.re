let domain = Js.Re.fromString "trello[.]com";

let show_if_trello tab_id _ tab => {
  switch (Js.Null.to_opt tab##url) {
    | Some url when Js.Re.test url domain =>
      Chrome.PageAction.show tab_id
    | Some _ | None =>
      ()
  }
};

Chrome.Tabs.OnUpdated.add_listener show_if_trello;
