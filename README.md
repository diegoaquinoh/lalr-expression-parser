# lalr-expression-parser

Academic project for implementing a **bottom-up LALR(1) parser** for arithmetic expressions.

The objective is to construct a parser from the provided grammar and parsing table, then evaluate expressions involving values, addition, multiplication, and parentheses. The parsing strategy follows a **shift-reduce approach**, with conflicts resolved through **operator precedence** and **left associativity**.

## Grammar

```
1) E' -> E
2) E  -> E + E
3) E  -> E * E
4) E  -> ( E )
5) E  -> val
```

## Architecture

The parser uses the **State design pattern** as described in the course:

- **`Automate`** — owns a state stack and a symbol stack, coordinates shifts, gotos, and reductions
- **`Etat0`–`Etat9`** — each state class implements one row of the LALR(1) parse table
- **`Lexer`** — tokenizes the input string into `Symbole*` objects
- **`Expr` hierarchy** — expression tree built during reductions and evaluated polymorphically

### Conflict resolution

- `+` is left-associative (state 7: `d4/r2` resolved to `r2`)
- `*` is left-associative (state 8: `d5/r3` resolved to `r3`)
- `*` has higher precedence than `+` (state 7: `d5/r2` resolved to `d5`; state 8: `d4/r3` resolved to `r3`)

## Build

```
make
```

## Usage

```
echo "2+3*4" | ./parser
```

Output: `14`

## Examples

| Input | Output |
|---|---|
| `(1+34)*123` | `4305` |
| `2+3*4` | `14` |
| `2*3+4` | `10` |
| `1+2+3` | `6` |
| `42` | `42` |
| `(((5)))` | `5` |
