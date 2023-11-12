#include <iostream>
#include <vector>

void reverse_last_calculation(std::vector<int>& password, int n) {
    for (int i = 0; i < 23; ++i) {
        if (n & 1) {
            password[i] ^= i;
        }
        else {
            password[i] += 7;
        }
    }
}

void reverse_second_calculation(std::vector<int>& password) {
    const std::vector<int> key{ 11, 33, 22, 44 };
    for (int i = 21; i >= 0; --i) {
        password[i] ^= password[i + 1] ^ key[i % 4];
    }
}

void reverse_first_calculation(std::vector<int>& password) {
    for (int i = 22; i >= 0; --i) {
        password[i] -= 6;
    }
}

void reverse_password_calculation(std::vector<int>& password) {
    for (int i = 15; i >= 0; --i) {
        reverse_last_calculation(password, i);
        reverse_second_calculation(password);
        reverse_first_calculation(password);
    }
}

int main() {
    std::vector<int> good_password{ 38, 16, 28, 74, 28, -104, -91, 44, 87, 71, -63, -113, -117, -121, -118, 28, -9, -115, 72, -80, -41, 89, 60 };
    reverse_password_calculation(good_password);

    for (int i = 0; i < good_password.size(); ++i) {
        std::cout << (char)good_password[i];
    }
    std::cout << std::endl;

    return 0;
}

