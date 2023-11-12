#include <iostream>
#include <vector>

std::string user_password;

static const std::vector<int> im = {
2, 1, 0, 1, 2, 0, 3, 1, 2, 1, 2, 1, 4, 1, 2, 6, 102, 2, 1, 1, 3, 2, 1, 1, 3, 2, 4, 2, 3,
6, 88, 2, 2, 2, 1, 1, 3, 4, 2, 1, 6, 77, 2, 1, 3, 2, 2, 4, 2, 3, 5, 2, 4, 6, 1, 0, 4, 4,
1, 0, 6, 57, 1, 0, 5, 3, 1, 2, 3, 1, 4, 4, 0, 1, 6, 43, 2, 4, 6, 3, 3, 4, 1, 4, 6, 4, 3,
4, 6, 29, 2, 1, 3, 2, 2, 4, 2, 3, 5, 2, 4, 6, 3, 4, 1, 3, 4, 2, 3, 4, 3, 1, 1, 7, 4, 4,
1, 5, 1, 8, 9, 7, 6, -5, 7
};

static const std::vector<int> constants = {
	77, 4, 73, 95, 71, 76, 11, 3
//  0   1  2   3   4   5   6   7
};

static bool flag_compare = false;

std::vector<int> data(100, 0);

std::size_t pc = 0;

enum opcode {
	OPCODE_MOVE = 1,
	OPCODE_INPUT,
	OPCODE_XOR,
	OPCODE_EQ,
	OPCODE_JE,
	OPCODE_JNE,
	OPCODE_GOOD,
	OPCODE_BAD,
	OPCODE_CHECKLENGTH
};

int get_arg() {
	return im[++pc];
}

void read_im() {
	opcode op = static_cast<opcode>(im[pc]);
	switch (op) {
	case OPCODE_MOVE: // move(index, value) { data[index] = const[value]; }
	{
		std::size_t index = get_arg();
		int value = get_arg();
		data[index] = constants[value];
		break;
	}
	case OPCODE_XOR: // xor(index_1, index_2) { data[index_1] ^= data[index_2]; }
	{
		std::size_t index_1 = get_arg();
		std::size_t index_2 = get_arg();
		data[index_1] ^= data[index_2];
		break;
	}
	case OPCODE_EQ: // eq(index_1, index_2) { CF = data[index_1] == data[index_2]; }
	{
		std::size_t index_1 = get_arg();
		std::size_t index_2 = get_arg();
		//std::cout << data[index_1] << " " <<   data[index_2] << "\n";
		flag_compare = data[index_1] == data[index_2];
		//std::cout << "[EQ-CHECK] " << (flag_compare ? "TRUE" : "FALSE") << "\n";
		break;
	}
	case OPCODE_JE: // je(offset) {}
	{
		int offset = get_arg();
		if (flag_compare) {
			pc += offset;
		}
		break;
	}
	case OPCODE_JNE: // jne(offset) {}
	{
		int offset = get_arg();
		if (!flag_compare) {
			pc += offset;
		}
		break;
	}
	case OPCODE_GOOD: // print good
		std::cout << "congrat!";
		pc = INT_MAX;
		break;
	case OPCODE_INPUT: // input(index_1, index_2) { data[index_1] = input[index_2] }
	{
		std::size_t index_1 = get_arg();
		std::size_t index_2 = get_arg();
		if (index_2 < user_password.length()) {
			data[index_1] = user_password[index_2];
			break;
		}
	}
	case OPCODE_BAD: // print bad
		std::cout << "try again..";
		pc = INT_MAX;
		break;
	case OPCODE_CHECKLENGTH: // for check {password}{anyletter}
		std::size_t length = get_arg();
		flag_compare = length == user_password.length();
		//std::cout << length << " " << user_password.length();
		break;
	}

}

int main() {
	std::cout << "type password: ";
	std::cin >> user_password;

	for (; pc < im.size(); ++pc) {
		read_im();
	}
}