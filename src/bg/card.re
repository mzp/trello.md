type action = Js.t {.
  idMemberCreator : string,
  date : string,
  data: (Js.t {.
    text : Js.Undefined.t string,
    attachment : Js.Undefined.t (Js.t {.
      name : string,
      url : Js.Undefined.t string
    })
  })
};

type t = Js.t {.
  id : string,
  name : string,
  desc : string,
  url : string,
  idMembers: array string,
  actions : array action
};

external coerce : Js.Json.t => t = "%identity";

let fetch client id => {
  let url = Printf.sprintf "/1/boards/%s/cards?actions=commentCard,addAttachmentToCard" id;
  Trello.get client url
  |> Js.Promise.then_ (fun response => Js.Promise.resolve (Json.decodeList coerce response))
};
