because of the multi-paradigm nature of the project, I will begin labling
functions, macros, and certain labels according to these terms

SUBROUTINE : a small function or a macro function that has no side-effects
	many subroutines take no arguments,
	but not everything that has no arguments is a subroutine

PROGRAM : a function with side-effects.
	anything ambiguously mislabled "function" probably means this

CONTINUATION : a label that acts as a state in a finite-state automata

AUTOMATA : a multiple-entry function that holds continuations

anything labled "HERE BE DRAGONS" is a portion of code that
is likely to twist the mind. "AUTOMATA" automatically implies it.
