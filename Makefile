FLAGS = -Wall -Werror -Wextra -std=c11

all: SmartCalc.a

SmartCalc.a:
	gcc -c $(FLAGS) Calc.c
	ar rc Calc.a *.o
	ranlib Calc.a

test: SmartCalc.a 
	gcc -c $(FLAGS) test_calc.c
	gcc -lcheck -fprofile-arcs -ftest-coverage Calc.c Calc.a test_calc.o  -o tests
	./tests
	
gcov_report:	test
	gcov -i *.gcda	
	lcov -t "calc1" -o calc1.info -c -d .
	genhtml -o report calc1.info
	cd report/ && open index.html
	# gcovr --html-details -o report.html
	# open report.html

install:
	cd SmartCalc && qmake && make && make clean
	cp -r SmartCalc/SmartCalc.app ~/Desktop

uninstall:
	rm -rf SmartCalc/SmartCalc.app 
	rm -rf ~/Desktop/SmartCalc.app
	rm -rf SmartCalc/Makefile
	
dvi:
	open dvi.html

dist: install
	mkdir archiv
	cp -r *.c *.h Makefile SmartCalc/ archiv
	tar -cvzf SmartCalc.tar.gz archiv
	rm -rf archiv

style:
	clang-format -i *.c *.h
	clang-format -n *.c *.h

leaks:
	leaks -atExit -- ./tests
clean:
	rm -rf *.o *.a *.gcno  *.gcda *.gcov *.css report *.dSYM report *.info *.gz
	rm -rf tests