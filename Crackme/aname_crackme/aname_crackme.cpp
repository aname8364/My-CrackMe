#include <iostream>
#include <vector>

void first_calculation(std::string& password) {
	for (int i = 0; i < 23; ++i) {
		password[i] += 6;
	}
}

void second_calculation(std::string& password) {
	const std::vector<int> key{ 11, 33, 22, 44 };
	for (int i = 0; i < 22; ++i) {
		password[i] ^= password[i + 1] ^ key[i % 4];
	}
}

void last_calculation(std::string& password, int n) {
	for (int i = 0; i < 23; ++i) {
		if (n & 1) {
			password[i] ^= i;
		}
		else {
			password[i] -= 7;
		}
	}
}

void calculate_password(std::string& password) {
	for (int i = 0; i < 16; ++i) {
		first_calculation(password);
		second_calculation(password);
		last_calculation(password, i);
	}
}

bool check_password(std::string& user_password) {
	const std::string password{ "pa_s_sw_or_d" };
	const std::vector<int> good_password{ 38, 16, 28, 74, 28, -104, -91, 44, 87, 71, -63, -113, -117, -121, -118, 28, -9, -115, 72, -80, -41, 89, 60 };
	const int correct_length = 23;

	if (user_password.length() != correct_length) { return false; }

	calculate_password(user_password);

	for (int i = 0; i < user_password.length(); ++i) {
		if (user_password[i] != good_password[i]) { return false; }
	}
	return true;
}

int main() {
	std::string str;
	std::cin >> str;
	if (check_password(str)) { std::cout << "Correct!"; }
	else { std::cout << "Try again."; }
	return 0;
}