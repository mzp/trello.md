type s = {
  card : Card.t,
  members : list Member.t,
  actions : list (Card.action, option Member.t)
};
type t = {
  list : TrelloList.t,
  cards : list s
};

let make: lists::list TrelloList.t => cards::list Card.t => members::list Member.t => list t;
