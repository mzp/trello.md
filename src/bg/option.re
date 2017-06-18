let then_ f x => {
  switch (x) {
    | Some y => f y
    | None => None
  }
};

let iter f x => {
  switch x {
    | Some y => f y
    | None => ()
  }
};

let map f x => {
  switch (x) {
    | Some y => Some (f y)
    | None => None
  }
};

let get or_else x => {
  switch (x) {
    | Some y => y
    | None => or_else
  }
};

let to_list x => {
  switch x {
    | Some y => [y]
    | None => []
  }
};

let bind x f => then_ f x;

let (>>=) = bind;
