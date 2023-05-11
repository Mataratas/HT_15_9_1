#include "Chat.h"
//==================================================================================
#define MAXPWDLENGTH 21
//----------------------------------------------------------------------------------
void init_users(Chat& ch) {
		ch.reg((char*)"user1", (char*)"pwd1", 4);
		ch.reg((char*)"user2", (char*)"pwd2", 4);
		ch.reg((char*)"user3", (char*)"pwd3", 4);
		ch.reg((char*)"user4", (char*)"pwd4", 4);
		ch.reg((char*)"user5", (char*)"pwd5", 4);
		ch.reg((char*)"user6", (char*)"pwd6", 4);
}
//----------------------------------------------------------------------------------
int main() {

	Chat session;
	init_users(session);
	session.show();

	char login[NAMELENGTH]{ '\0' };
	char pwd[MAXPWDLENGTH]{ '\0' };

	while (true) {
		char choice{ '\0' };
		std::cout << "Choose action:(l - login r - remove account s - squize users * - exit):\n";
		std::cin >> choice;
		if (choice=='*') break;

		switch (choice) {
			case 'l': {
				std::cout << "Type login:\n";
				std::cin >> login;
				std::cout << "Type password:\n";
				std::cin >> pwd;
				if (!session.login(login, pwd, strlen(pwd)))
					std::cout << "Login failed\n";
				else
					std::cout << "Login successfull\n";
				break;
			}
			case 'r': {
				std::cout << "Type login:\n";
				std::cin >> login;
				session.remove_account(login);
				session.show();
				break;
			}
			case 's': {
				session.squize();
				session.show();
				break;
			}
		}
	}
	return 0;

}