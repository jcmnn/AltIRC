local servers = {
    -- {"hostname", port, "Nickname", "Username", "Real name", {"#channel1", "#channel2"}};
    {"irc.esper.net", 6667, "AltBot", "AltBot", "AltBot", {"#altenius", "#V"}};
}
























local conns = {}
for _, info in ipairs(servers) do
    conns[AltIrc:get():connectionHandler():newConnection(info[1], info[2], info[3], info[4], info[5])] = info[6]
end

registerEvent("auth", "config_auth", function(conn)
    if conns[conn] then
        local proto = conn:protocolHandler()
        for _, channel in ipairs(conns[conn]) do
            proto:join(channel)
        end
    end
end)