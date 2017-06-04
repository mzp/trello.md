type t = Js.t {.
  id : string,
  name : string,
  desc : string,
  url : string,
  idMembers: array string,
  actions : array (Js.t {.
    idMemberCreator : string,
    data: (Js.t {.
      text : Js.Null.t string,
      attachment : Js.Null.t (Js.t {.
        name : string,
        url : string
      })
    })
  })
};

external coerce : Js.Json.t => t = "%identity";

let fetch : Trello.t => string => Js.Promise.t (list t);
