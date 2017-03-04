#
main: main.o PhoneBookEntry.o PhoneBook.o PhoneBookNode.o
	g++ -o main main.o PhoneBookEntry.o PhoneBook.o PhoneBookNode.o
#
main.o: main.cxx PhoneBookEntry.h PhoneBook.h PhoneBookNode.h
	g++ -g -c -Wall main.cxx
#
PhoneBook.o: PhoneBook.cxx PhoneBook.h
	g++ -g -c -Wall PhoneBook.cxx
#
PhoneBookEntry.o: PhoneBookEntry.cxx PhoneBookEntry.h
	g++ -g -c -Wall PhoneBookEntry.cxx
#
PhoneBookNode.o: PhoneBookNode.cxx PhoneBookNode.h
	g++ -g -c -Wall PhoneBookNode.cxx
#
run: main
	./main
