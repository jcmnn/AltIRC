local commands = {}

function checkArg(arg, pos, types)
    if type(types) == "string" then
        types = {types }
    elseif type(types ~= "table") then
        error("bad argument #3 (string, table expected, got " .. type(types) .. ")")
    end
    
    if type(pos) ~= "number" then
        error("bad argument #2 (string, table expected, got " .. type(pos) .. ")")
    end
    
    for _, t in ipairs(types) do
        if type(arg) == t then
            return
        end
    end

    error("bad argument #" .. pos .. " (" .. table.concat(types, ", ") .. " expected, got " .. type(arg) .. ")", 3)
end

function registerCommand(command, id, func)
    checkArg(command, 1, "string")
    checkArg(id, 2, "string")
    checkArg(func, 3, "function")
    
    command = command:lower()
    if not commands[command] then
        commands[command] = {[id] = func }
    else
        commands[command][id] = func
    end
end

function unregisterCommand(command, id)
    checkArg(command, 1, "string")
    checkArg(id, 2, "string")
    
    command = command:lower()
    if commands[command] then
        commands[command][id] = nil
    end
end

function parseArgs(string)
    checkArg(string, 1, "string")
    local args = {}
    for arg in string:gmatch("[^ ]+") do
        table.insert(args, arg)
    end
    
    return unpack(args)
end

registerEvent("message", "command_handler", function(conn, prefix, target, message)
    if not prefix then
        return
    end
    print(prefix:name() .. ": " .. message)
    if message:sub(1, 1) == "$" and #message ~= 1 then
        message = message:sub(2)
        local command, args
        if message:find(" ") then
            command, args = message:match("(.-) (.*)")
        else
            command = message
            args = ""
        end
        
        local replytgt
        if target == conn:nick() then
            replytgt = prefix:name()
        else
            replytgt = target
        end
        
        local function reply(message)
            conn:protocolHandler():sendNotice(replytgt, prefix:name() .. ", " .. message)
        end
        
        if commands[command] then
            for _, func in pairs(commands[command]) do
                local success, err = pcall(func, conn, prefix, reply, args)
                if not success then
                    print("Error running command handler for command " .. command .. ": " .. err)
                end
            end
        end
    end
end)