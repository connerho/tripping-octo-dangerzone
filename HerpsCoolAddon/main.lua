SLASH_ROLLCALL1 = "/rollcall"
SLASH_WORLDBUFF1 = "/addwb"

-- Let's define our buffs that we care about here
local buffs_we_care_about = {
    ["Elixir of Agility"]           = 5,
    ["Elixir of Ogre Strength"]     = 5,
    ["Elixir of Greater Defense"]   = 5,
    ["Elixir of Frost Power"]       = 5,
    ["Elixir of Firepower"]         = 5,
    ["Elixir of Fortitude"]         = 5,
    ["Demon Skin"]                  = 5,
    ["Blood Pact"]                  = 5,
}

-- And define world buffs that we care about too 
local world_buffs = {
    ["Boon of Blackfathom"]         = 5,
    ["Spark of Inspiration"]        = 5,
}

local function loopThroughMembersAddPoints(table)
    -- This is how we loop through all of the buff list
    -- Loop through all members in the raid
    local numGroupMembers = GetNumGroupMembers();
    for i = 1, MAX_RAID_MEMBERS do
        if (i <= numGroupMembers) then
            local total_ep = 0
            name, rank, subgroup = GetRaidRosterInfo(i);
            -- Loop through all of the buffs that we care about
            for k, v in pairs(table) do
                local return_val = AuraUtil.FindAuraByName(k, name)
                if( return_val == nil ) then
                    print(name,"does not have buff",k)
                else
                    -- Player does have the buff, let's keep track of additional EP
                    print(name,"does have buff", k, "adding EP")
                    total_ep = total_ep + v
                end
            end
            print(name,"gets", total_ep, "for having buffs")
        end
    end
end

SlashCmdList.WORLDBUFF = function(msg, editBox)
    loopThroughMembersAddPoints(world_buffs)
end

-- define the corresponding slash command handler
SlashCmdList.ROLLCALL = function(msg, editBox)
    -- This is how we loop through all of the buff list
    -- Loop through all members in the raid
    local numGroupMembers = GetNumGroupMembers();
    for i = 1, MAX_RAID_MEMBERS do
        if (i <= numGroupMembers) then
            local total_ep = 0
            name, rank, subgroup = GetRaidRosterInfo(i);
            -- Loop through all of the buffs that we care about
            for k, v in pairs(buffs_we_care_about) do
                local return_val = AuraUtil.FindAuraByName(k, name)
                if( return_val == nil ) then
                    print(name,"does not have buff",k)
                else
                    -- Player does have the buff, let's keep track of additional EP
                    print(name,"does have buff", k, "adding EP")
                    total_ep = total_ep + v
                end
            end
            print(name,"gets", total_ep, "for having buffs")
        end
    end
end

--[[ Loop through all of the players int he raid ]]
local function loop_through_raid_members()
    local buffFound = 0
    for i = 1, MAX_RAID_MEMBERS do
        local unit = format("%s%i", 'raid', i)
        AuraUtil.ForEachAura(unit, "HELPFUL", nil, buffCallback)
    end
end