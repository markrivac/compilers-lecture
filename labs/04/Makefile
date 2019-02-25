all:
	lex compiler.l
	gcc lex.yy.c -o compiler -ll
	python3 code_generator.py --stress
clean:
	rm -rf compiler