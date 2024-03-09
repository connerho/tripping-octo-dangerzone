SLASH_ROLLCALL1 = "/rollcall"
SLASH_HELLOW1 = "/helloworld"
SLASH_HELLOW2 = "/hw"

-- define the corresponding slash command handler
SlashCmdList.ROLLCALL = function(msg, editBox)
    AuraUtil.ForEachAura("player", "HELPFUL", nil, function(name, icon, ...)
        print(name, icon, ...)
    end)
end

-- define the corresponding slash command handler
SlashCmdList.HELLOW = function(msg, editBox)
	local name1, name2 = strsplit(" ", msg)
	if #name1 > 0 then -- check for empty string
		print(format("hello %s and also %s", name1, name2 or "Carol"))
	else
		print("Please give at least one name")
	end
end

local function buffCallback(name, icon, _, _, _, _, _, _, _, spellId, ...)
    -- Check to see if any of the buffs matches the ones we care about
    
end

local function read_yaml_file(filename)
    local file = io.open(filename, "r")
    if not file then
        return nil, "Failed to open file: " .. filename
    end
    local data = {}
    for line in file:lines() do
        local key, value = line:match("(%w+):%s*(.+)")
        if key and value then
            data[key] = value
        end
    end
    file:close()
    return data
end

--[[ Loop through all of the players int he raid ]]
local function loop_through_raid_members()
    local buffFound = 0
    BUFF_VALUE_PAIRING = read_yaml_file('buffs.yaml')
    for i = 1, MAX_RAID_MEMBERS do
        local unit = format("%s%i", 'raid', i)
        AuraUtil.ForEachAura(unit, "HELPFUL", nil, buffCallback)
    end
end

read_yaml_file('buffvalues.yaml')

AuraUtil.ForEachAura("player", "HELPFUL", nil, function(name, icon, ...)
    print(name, icon, ...)
end)