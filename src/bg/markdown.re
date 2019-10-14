open Printf;

let h1 buffer title => Buffer.add_string buffer ("# " ^ title ^ "\n\n");
let h2 buffer title => Buffer.add_string buffer ("## " ^ title ^ "\n\n");
let quote buffer text => {
  let s = Js.String.replaceByRe (Js.Re.fromStringWithFlags "\n" flags::"g") "\n> " text;
  Buffer.add_string buffer ("> " ^ s ^ "\n\n")
};

let avatarUrl hash =>
  sprintf "https://trello-avatars.s3.amazonaws.com/%s/30.png" hash;

let avatar member => {
  let hash = Js.Null.to_opt member##avatarHash;
  switch(hash) {
    | Some hash => sprintf "![%s](%s)" member##username (avatarUrl hash)
    | None => member##username
  };
};

let attachment obj => {
  let url =
    Js.Undefined.to_opt obj##url
    |> Option.get "";
  sprintf "![%s](%s)" obj##name url;
};

let format xs => {
  let buffer = Buffer.create 0;
  ListLabels.iter xs f::(fun { ListWithCard.list, cards } => {
    h1 buffer list##name;
    ListLabels.iter cards f::(fun { ListWithCard.card, members, actions } => {
      let card_members =
        members
        |> List.map avatar
        |> String.concat " ";

      h2 buffer (sprintf "[:link:](%s) %s %s" card##url card##name card_members);
      quote buffer card##desc;
      ListLabels.iter actions f::(fun (action, member) => {
        quote buffer "----";
        Option.iter (fun m =>
                     quote buffer (sprintf "%s %s" (avatar m) action##date)) member;
        Js.Undefined.iter action##data##text
          ((fun text => quote buffer text) [@bs]);
        Js.Undefined.iter action##data##attachment
          ((fun obj => quote buffer (attachment obj)) [@bs]);
      })
    })
  });
  Buffer.contents buffer;
}
