let decodeList coerce xs =>
  switch (Js.Json.decodeArray xs) {
    | None => []
    | Some xs => List.map coerce (Array.to_list xs)
  }
