# Recursive Descent Parser
This project is a recursive descent parser which recognizes valid programs of the fictional `Progrotron-16.3` programming language. The program receives input as text and determines whether or not it is a valid program. It does not determine the meaning of the input, just its validity.

## Tokens
Programs of the `Progrotron` language are built from the following tokens:

* **Integer** Non-empty sequence of digits optionally preceded with `+` or `-`
* **Decimal** An **Integer** followed by `.` character then followed by a non-empty sequence of digits
* **String** Any non-space sequence of characters enclosed in double quotes e.g. `"string"`
* **Keyword** Specific strings or symbols `<= + - * / or and ~ ( ) lt gt eq < > ! print inc ret if fi else while elihw defprog blip blorp`
* **Identifier** Sequence of digits or letters. The first character *must* be a letter and an **Identifier** cannot be a **Keyword**

Tokens in `Progrotron` are always separated by a space.

## Grammar
The `Progrotron` language conforms to the following grammar rules:

* Routine Declaration is the start symbol
* Terminal symbols are in **bold**. Collections of terminal symbols are in *italics*
* Brackets `[` and `]` denote an optional section of a grammar rule
* Braces `{` and `}` denote repetition of a section (zero or more) 

The following rules are in Extended Backus-Naur Form:

* Relation := **lt** | **gt** | **eq** 
* AddOperator := **+** | **-** | **or** 
* MulOperator := * | **/** | **and** 
* Expression := SimpleExpression [ Relation SimpleExpression ]
* SimpleExpression := Term { AddOperator Term }
* Term := Factor { MulOperator Factor }
* Factor := *integer* | *decimal* | *string* | *identifier* | **(** Expression **)** | **~** Factor
* Assignment := *identifier* **<=** Expression **!**
* IncStatement := **inc** *identifier* **!**
* IfStatement := **if <** Expression **>** StatementSequence [ **else** StatementSequence ] **fi**
* LoopStatement := **while <** Expression **>** StatementSequence **elihw**
* PrintStatement := **print** *identifier* **!**
* Statement := [ Assignment | IfStatement | LoopStatement | PrintStatement | IncStatement ]
* StatementSequence := Statement { Statement }
* ParamSequence := *identifier* { , *identifier* }
* RoutineDeclaration := **defprog** *identifier* **<** [ ParamSequence ] **> blip** [ StatementSequence ] [ **ret** Expression ] **blorp**

## Output
If the input program is valid, the program will output `CORRECT`. Otherwise, it will output `INVALID!`.
