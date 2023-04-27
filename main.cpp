#include "Social.h"
#include <iostream>

int main()
{
	Social s;

	s.addUser("Oleg");
	s.addUser("Petr");
	s.addUser("Ivan");
	s.addUser("Olya");
	s.addUser("Sergey");
	s.addUser("Nastya");
	s.addUser("Nikita");

	s.addConnection("Oleg", "Petr");
	s.addConnection("Oleg", "Ivan");
	s.addConnection("Oleg", "Nastya");
	s.addConnection("Petr", "Nikita");
	s.addConnection("Petr", "Ivan");
	s.addConnection("Nastya", "Sergey");
	s.addConnection("Nastya", "Ivan");
	s.addConnection("Nastya", "Olya");
	s.addConnection("Nastya", "Nikita");
	s.addConnection("Nastya", "Petr");

	s.show();

	std::cout << std::endl;
	
	const int handshakeMax = 3;
	s.searchSocialConnections(handshakeMax);
	
	return 0;
}