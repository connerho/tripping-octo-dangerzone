SLASH_ROLLCALL1 = "/rollcall"
SLASH_WORLDBUFF1 = "/addwb"

local DEBUG = true

-- Let's define our buffs that we care about here
local buffs_we_care_about = {
    ["Elixir of the Mongoose"]      = 1,
    ["Elixir of the Giants"]        = 1,
    ["Greater Armor"]               = 1,
    ["Regneration"]                 = 1,
    ["Health II"]                   = 1,
    ["Arcane Elixir"]               = 1,
    ["Shadow Power"]                = 1,
    ["Frost Power"]                 = 1,
    ["Fire Power"]                  = 1,
    ["Minor Mana Oil"]              = 1,
    ["Lesser Wizard Oil"]           = 1,
    ["Gift of Arthas"]              = 1,
    ["Winterfall Firewater"]        = 1,
    ["Rumsey Rum Black Label"]      = 1,
    ["Dense Sharpening Stone"]      = 1,
    ["Mana Regeneration"]           = 1,
    ["Health Regeneration"]         = 1,
    ["Dragonbreath Chili"]          = 1,
    ["Increased Agility"]           = 1,
    ["Well Fed"]                    = 1  -- Will need to do some extra for this because there are different levels of being "fed"
}

-- And define world buffs that we care about too 
local world_buffs = {
    ["Boon of Blackfathom"]             = 1,
    ["Spark of Inspiration"]            = 1,
    ["Fervor of the Temple Explorer"]   = 1
}

local function loopThroughMembersAddPoints(table)
    -- This is how we loop through all of the buff list
    -- Loop through all members in the raid
    if EPBuffCountLog_Herp == nil then
        EPBuffCountLog_Herp = {}
    end
    local numGroupMembers = GetNumGroupMembers();
    for i = 1, numGroupMembers do
        local total_ep = 0
        name, rank, subgroup = GetRaidRosterInfo(i);
        -- Loop through all of the buffs that we care about
        for k, v in pairs(table) do
            local return_val = AuraUtil.FindAuraByName(k, name)
            if( return_val == nil ) then
                if( DEBUG ) then
                    print(name,"does not have buff",k)
                end
            else
                -- Player does have the buff, let's keep track of additional EP
                if( DEBUG ) then
                    print(name,"does have buff", k, "adding EP")
                end
                total_ep = total_ep + v
                tinsert(EPBuffCountLog_Herp, strjoin(";",name,k,v,time()))
            end
        end
        print(name,"gets", total_ep, "for having buffs")
    end
end

SlashCmdList.WORLDBUFF = function(msg, editBox)
    loopThroughMembersAddPoints(world_buffs)
end

-- define the corresponding slash command handler
SlashCmdList.ROLLCALL = function(msg, editBox)
    loopThroughMembersAddPoints(buffs_we_care_about)
end