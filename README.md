AltIRC
======
A generic IRC bot written in C++ with a Lua plugin system.

Configuration
-------------

AltIRC's configuration system is currently part of the plugin system but there are plans to change it to a dedicated configuration format.

### Adding servers
To add servers and channels, open AltIRC/plugins/config.lua and follow the format:  
```
local servers = {
  -- {"hostname", port, "Nickname", "Username", "Real name", {"#channel1", "#channel2"}};
  {"irc.example.org", 6667, "AltBot", "AltBot", "AltBot", {"#channel1", "#channel2", "#channel3", "#channelN"}};
} 
```

### Adding administrators
To add admins, open AltIRC/plugins/admin.lua and follow the format:
```
local admins = {
    -- Format: ["Nickname"] = "password";
    ["Altenius"] = "password";
    ["UnsecureJoe"] = "12345";
}
```
To register with the bot, use the command `$register <password>`

Usage
-----
AltIRC currently has 5 commands preinstalled:
  * `reload` (admin only) - Reloads plugins
  * `join <channel(s)> [password(s)]` (admin only) - Joins a channel/channels
  * `part <channel(s)>` (admin only) - Leaves a channel/channels
  * `register <password>` - Registers as an admin. This is required in order to use admin only commands
  * `echo <message>` - Replies with `message`

Commands can be issued by sending a message to a channel the bot is active in or by sending a private message to the bot.

Commands are used by prefixing your message with `$` (e.g. `$join #channel`)

Contributors: [Altenius](https://github.com/Altenius)
