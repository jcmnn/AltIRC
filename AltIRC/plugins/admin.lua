local admins = {
    ["Altenius"] = "password";
}

local registered = {}

function checkAdmin(prefix, reply)
    if not admins[prefix:name()] then
        reply("you are not authorized")
        return false
    end
    if not registered[prefix:name()] then
        reply("you are unregistered")
        return false
    end
    return true
end

registerCommand("reload", "admin_reload", function(conn, prefix, reply, args)
    if checkAdmin(prefix, reply) then
        _reload = true
        reply("scheduled reload")
    end
end)

registerCommand("join", "admin_join", function(conn, prefix, reply, args)
    if checkAdmin(prefix, reply) then
        conn:protocolHandler():join(parseArgs(args))
        reply("joining channel(s)")
    end
end)

registerCommand("part", "admin_part", function(conn, prefix, reply, args)
    if checkAdmin(prefix, reply) then
        conn:protocolHandler():part(parseArgs(args))
        reply("parting channel(s)")
    end
end)

registerCommand("register", "admin_register", function(conn, prefix, reply, args)
    if admins[prefix:name()] and admins[prefix:name()] == args then
        registered[prefix:name()] = true
        reply("registered")
    else
        reply("failed to register")
    end
end)
