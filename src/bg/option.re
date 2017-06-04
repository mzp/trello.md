let then_ f x => {
  switch (x) {
    | Some y => f y
    | None => None
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

let bind x f => then_ f x;

let (>>=) = bind;
