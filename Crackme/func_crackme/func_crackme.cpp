#include <iostream>
#include <string>

uint32_t* read_address(const std::string& input) {
	return reinterpret_cast<uint32_t*>(static_cast<uint64_t>(std::stoull(input, 0, 16)));
}

int read_data(uint8_t* address) {
	return static_cast<int>(*address);
}

void check_address(uint32_t* address) {
	uint8_t* byte_addr = reinterpret_cast<uint8_t*>(address);
	int prev_byte = read_data(byte_addr - 1);
	int next_byte = read_data(byte_addr + 4);
	if (*address == 0xC318418B
		&& prev_byte == 0xCC
		&& next_byte == prev_byte) {
		std::cout << "congrat!";
	}
	else {
		std::cout << "try again..";
	}
}

int main() {
	std::string input;
	std::cout << "type something: ";
	std::cin >> input;
	auto user_password = read_address(input);
	check_address(user_password);
}