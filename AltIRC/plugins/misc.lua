registerCommand("echo", "misc_echo", function(conn, prefix, reply, args)
    reply(args)
end)

registerCommand("source", "misc_source", function(conn, prefix, reply, args)
    reply("https://github.com/Altenius/AltIRC")
end)