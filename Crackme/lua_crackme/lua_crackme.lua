print("type password: ")
local pw = io.read()
local f = load(pw)
local password
if f then
    local r = f(function() password = PASSWORD() end)
    if r == "load_pw" then
        if password then
            print("password: " .. password)
        else
            print("password is not set")
        end
    else
        print("wrong input data")
    end
else
    print("wrong input type")
end