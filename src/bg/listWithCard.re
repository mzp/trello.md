type s = {
  card : Card.t,
  members : list Member.t,
  actions : list (Card.action, option Member.t)
};
type t = {
  list : TrelloList.t,
  cards : list s
};

let tablize : ('a => string) => list 'a => Hashtbl.t string 'a = fun f xs => {
  let tbl = Hashtbl.create 0;
  ListLabels.iter xs f::(fun x => Hashtbl.add tbl (f x) x);
  tbl
};

let filter_map f xs =>
  List.concat (List.map (fun x => Option.to_list (f x)) xs);

let find tbl x => {
  try (Some (Hashtbl.find tbl x)) {
  | Not_found => None
  }
};

let make_card card_table member_table card => {
  let c = Hashtbl.find card_table card##id;
  let members =
    card##idMembers
    |> Array.to_list
    |> filter_map (find member_table);
  let actions =
    c##actions
    |> Array.to_list
    |> List.map (fun action =>
      (action, find member_table action##idMemberCreator));
  { card : c, members, actions };
};

let make_list card_table member_table list => {
  let cards =
    list##cards
    |> Array.to_list
    |> List.map (make_card card_table member_table);
  { list, cards }
};

let make lists::lists cards::cards members::members => {
  let card_table = tablize (fun x => x##id) cards;
  let member_table = tablize (fun x => x##id) members;
  List.map (make_list card_table member_table) lists;
}
