#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <vector>
#include <cstring>

#include "messy_crackme.h"

std::unordered_map<std::string, std::string> users = {
	{"admin", "{hidden}"},
	{"guest", "GUEST"}
};

std::unordered_map<unsigned int, std::string> user_index = {
	{1, "aname"}, // aname
	{2, "admin"}, // iM_aDMiNs_pasSWord
	{3, "guest"} // GUEST
};

int always_zero = 0;
const std::vector<char> password_1 = {
	'3', '3', '3'
};

const std::vector<char> dummy_1 = {
	'1', '4', '8'
};

const std::vector<char> dummy_2 = {
	'a', 'c', 'a'
};

const std::vector<char> password_2 = {
	'8', '2', '3'
};

const std::vector<char> dummy_3 = {
	'e', 'f', '2'
};

const std::vector<char> password_3 = {
	'6', '8', 'e'
};

const std::vector<char> password_5 = {
	'4', '5', '2'
};

const std::vector<char> dummy_4 = {
	'c', 'f', 'd'
};

const std::vector<char> password_6 = {
	'b', '6', '3'
};

const std::vector<char> dummy_5 = {
	'7', '4', '0'
};

const std::vector<char> dummy_6 = {
	'9', '1', '1'
};

const std::vector<char> dummy_7 = {
	'0', '8', '0'
};

const std::vector<char> password_7 = {
	'1', '2', '2'
};

const std::vector<char> dummy_8 = {
	'2', '5', '6'
};

const std::vector<const char*> last_password = {
	"46cda556dda9a8d7f57009244",
	"0c90182b4de6d21cfca38a4ec",
	"989576b5cfaa06654217d7a1a"
};

int main(int argc) {
	if (!argc) {
		always_zero = argc;
		std::cout << "incorrect user..\n";
		return 1;
	}
	std::string userid;
	std::string userpw;

	std::cout << "type userid: ";
	std::cin >> userid;

	std::cout << "type userpw for user " + userid + ": ";
	std::cin >> userpw;

	if (login(userid, userpw, always_zero)) {
		std::cout << "hello " + userid << "\n";
		std::cout << userid + "{" + userpw + "}\n";
	}
	else
	{
		std::cout << "incorrect user!\n";
	}
	return 0;
}

void check_user_next(bool result) {
	while (!result) {
		if (main(0)) {
			std::exit(0);
		}
	}
}

bool check_user(const std::string& userid, const std::string& userpw) {
	bool result = false;
	for (const auto& v : users) {
		if (userid == v.first) {
			result = true;
			break;
		}
	}
	check_user_next(result || userid == "aname");
	return login(userid, userpw, 2);
}

void get_user_index_next(int index) {
	while (!index) {
		std::cout << "incorrect password..\n";
		std::exit(always_zero);
	}
}

bool get_user_index(const std::string& userid, const std::string& userpw) {
	int index = always_zero;
	for (const auto& v : user_index) {
		if (userid == v.second) {
			index = v.first;
			break;
		}
	}
	get_user_index_next(index);
	return login(userid, userpw, index + 4);
}

void check_password_1(int status) {
	for (int i = always_zero; i < status; ++i) {
		while (true) {
			always_zero = i;
			get_user_index_next(always_zero);
			always_zero = 1;
			break;
		}
	}
}

void check_password_2(char userpw, int user_index) {
	if (static_cast<int>(userpw) != static_cast<int>(password_2[user_index])) {
		get_user_index_next(always_zero);
		always_zero = 0;
		main(1);
	}
}

void check_password_3(char userpw, int user_index) {
	if (static_cast<int>(userpw) != static_cast<int>(password_3[user_index])) {
		get_user_index_next(always_zero);
		always_zero = 0;
		main(1);
	}
}

bool check_password_4(const std::string& userpw, int user_index) {
	const std::vector<char> password_4 = {
		'f', 'c', '9'
	};
	if (static_cast<int>(userpw[userpw[always_zero]-48]) != static_cast<int>(password_4[user_index])) {
		always_zero = 0;
		return false;
	}
	return true;
}

void check_password_5(char userpw, int user_index) {
	if (static_cast<int>(userpw) != static_cast<int>(password_5[user_index])) {
		get_user_index_next(always_zero);
	}
}

void check_password_6(char userpw, int user_index) {
	if (static_cast<int>(userpw) != static_cast<int>(password_6[user_index])) {
		get_user_index_next(always_zero);
	}
}

void check_password_7(char userpw, int user_index) {
	if (static_cast<int>(userpw) != static_cast<int>(password_7[user_index])) {
		get_user_index_next(always_zero);
	}
}

std::string get_last_part(const std::string& userpw, int process) {
	return userpw.substr(process);
}

bool login(const std::string& userid, const std::string& userpw, int process) {
	if (!process) {
		always_zero = process;
		return check_user(userid, userpw);
	}
	else if (process < 4) {
		if (process == 2) {
			return login(userid, userpw, --process);
		}
		else if (process == 1) {
			return get_user_index(userid, userpw);
		}
		else {
			main(process);
		}
	}
	else {
		auto user_index = process - 4;
		password_1[always_zero] ^ process;
		user_index ^ password_1[always_zero] + 2;
		user_index + 4;
		if (always_zero) {
			main(--process);
		}
		else {
			always_zero = 0;
			check_password_1(
				static_cast<int>(userpw[always_zero]) ^
				static_cast<int>(password_1[user_index - 1])
			);
			check_password_2(userpw[always_zero + 1], user_index - 1);
			password_1[process - 4];
			password_2[process - always_zero];
			check_password_3(userpw[userpw[always_zero] - 49], user_index - 1 + always_zero);
			if (check_password_4(userpw, user_index - 1)) {
				check_password_5(userpw[4], user_index - 1);
				process = 7;
				check_password_6(userpw[5], user_index - 1);
				check_password_7(userpw[6], user_index - 1);
				auto last_part = get_last_part(userpw, process);
				if (std::strncmp(last_part.c_str(), last_password[user_index-1], 123) == 0) {
					return true;
				}
				get_user_index_next(always_zero);
			}
			else {
				get_user_index_next(always_zero);
				main(1);
			}
		}
		
	}
}
