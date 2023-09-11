# Simple grammar of bitty language

program> -> "program" "begin" <statement>* "end"

<statement> -> <label> = <expression> ";"
			   or <expression> ";"

<expression> -> <expression> <binop_low_pres> <expression>
				or <expression> <binop_high_pres> <expression>
				or <unop> <expression>
				or <label>
				or LITERAL
