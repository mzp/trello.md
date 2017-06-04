let domain = Js.Re.fromString "trello[.]com";

let show_if_trello tab_id _ tab => {
  switch (Js.Null.to_opt tab##url) {
    | Some url when Js.Re.test url domain =>
      Chrome.PageAction.show tab_id
    | Some _ | None =>
      ()
  }
};

let copy_to_clipboard tab => {
  Js.log tab##url;
};

Chrome.Tabs.OnUpdated.add_listener show_if_trello;
Chrome.PageAction.OnClicked.add_listener copy_to_clipboard;
