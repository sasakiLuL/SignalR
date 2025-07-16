# Syntax Parser

This project is a **syntax parser** for a simplified programming language based on a signal grammar.


- Constructs a **parse tree** to represent the syntactic structure of the input program
- Builds detailed **tables of identifiers and constants**, which are essential for subsequent stages such as semantic analysis or code generation
- Produces a **listing** of the original program, annotated with any **lexical or syntactic error messages**

This tool is designed for educational purposes to demonstrate key principles of compiler construction, particularly the implementation of a parser as the second phase of a typical compilation pipeline.

---

## Grammar Rules

The syntax parser is built upon the following grammar:

```ebnf
1.  <signal-program> → <program>
2.  <program> → PROGRAM <procedure-identifier> ; <block>.
3.  <block> → <declarations> BEGIN <statements-list> END
4.  <statements-list> → <empty>
5.  <declarations> → <math-function-declarations>
6.  <math-function-declarations> → DEFFUNC <function-list> | <empty>
7.  <function-list> → <function> <function-list> | <empty>
8.  <function> → <function-identifier> = <constant> <function-characteristic> ;
9.  <function-characteristic> → \ <unsigned-integer> , <unsigned-integer>
10. <constant> → <unsigned-integer>
11. <procedure-identifier> → <identifier>
12. <function-identifier> → <identifier>
13. <identifier> → <letter> <string>
14. <string> → <letter> <string> | <digit> <string> | <empty>
15. <unsigned-integer> → <digit> <digits-string>
16. <digits-string> → <digit> <digits-string> | <empty>
17. <digit> → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
18. <letter> → A | B | C | D | ... | Z
