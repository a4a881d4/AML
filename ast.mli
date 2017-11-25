type identifier = string
                
and ttype = string
                 
and identifiers = identifier list
                 
and leftvalue =
  | Identifier of identifier                

and builtintype =
  | Builtintype of ttype
                
and expr =
  | Bool of bool
  | Int of int
  | Float of float
  | String of string
  | Leftvalue of leftvalue
  | Vec of expr * expr
  | Binop of string * expr * expr

and stmt = 
  | Assign of (leftvalue * expr)
  | Declaration of (builtintype * leftvalue * expr)
            
and block =
  | Stmt of stmt
  | Expr of expr
  | Call of (identifier * identifiers)
  | If of (expr * block_list)
  | IfElse of (expr * block_list * block_list)
  | For of (stmt * expr * stmt * block_list)
            
and block_list = block list

and toplevel = 
  | Agent of block_list * block_list
  | Function of (identifier * identifiers * block_list)

and t = toplevel list             
