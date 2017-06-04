let regexp = Js.Re.fromString "trello[.]com/b/([^/]+)";

let parse_url url =>
  Js.Re.exec url regexp
  |> Option.then_ (fun result => {
    let xs = Js.Re.matches result;
    if (Array.length xs >= 2) {
      Some xs.(1)
    } else {
      None
    }
  });
