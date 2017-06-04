let fetch client id => {
  let url = Printf.sprintf "/1/boards/%s/lists?cards=open" id;
  Trello.get client url
};
