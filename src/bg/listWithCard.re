type s = {
  card : Card.t,
  members: list Member.t
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

let make_card card_table member_table card => {
  let c = Hashtbl.find card_table card##id;
  let members =
    card##idMembers
    |> Array.to_list
    |> List.map (Hashtbl.find member_table);
  { card : c, members : members };
};

let make_list card_table member_table list => {
  let cards =
    list##cards
    |> Array.to_list
    |> List.map (make_card card_table member_table);
  { list: list, cards : cards }
};

let make lists::lists cards::cards members::members => {
  let card_table = tablize (fun x => x##id) cards;
  let member_table = tablize (fun x => x##id) members;
  ListLabels.map (make_list card_table member_table) lists;
}
