# Simple grammar of bitty language

program> -> "program" "begin" <statement>* "end"

<statement> -> <label> = <expression> ";"
               or <expression> ";"

<expression> -> <expression> <binop_low_pres> <expression>
                or <expression> <binop_high_pres> <expression>
                or <unop> <expression>
                or "(" <expression> ")"
                or <label>
                or LITERAL

<binop_low_pres> -> "+"
                    or "-"

<binop_high_pres> -> "*"
                     or "/"

<unop> -> "+"
          or "-"

<label> -> // Sequance of alpha-numeric chars not starting with digit
