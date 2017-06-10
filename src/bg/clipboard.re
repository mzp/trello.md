type document;

type element = Js.t {.
  value [@bs.set] : string,
  select [@bs.meth] : unit => unit
};

external document :  document = "document" [@@bs.val];
external get_element_by_id : document => string => element = "getElementById" [@@bs.send];
external exec_command : document => string => bool = "execCommand" [@@bs.send];

let write value => {
    let textarea = get_element_by_id document "ta";
    textarea##value #= value;
    textarea##select ();
    if (not (exec_command document "copy")) {
      failwith "fail to write clipboard";
    }
}
