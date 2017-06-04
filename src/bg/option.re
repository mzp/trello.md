let then_ f x => {
  switch (x) {
    | Some y => f y
    | None => None
  }
};

let bind x f => then_ f x;

let (>>=) = bind;
