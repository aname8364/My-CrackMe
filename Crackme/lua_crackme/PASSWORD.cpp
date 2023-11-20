int get_password(lua_State* L) {
    std::array<int, 8> arr = { 208, 208, 209, 190, 192, 218, 169, 130 };
    std::string password;
    for (int i = 0; i <= 8; ++i) {
        password += 255 - arr[i];
    }
    lua_pushstring(L, password.c_str());
    return 1;
}