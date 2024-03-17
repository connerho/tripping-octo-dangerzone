# Parse the input LUA file to get player name, buff to reward
# reward points, and time awarded
# LUA file contents look like this "Herpcurse;Demon Skin;5;1710620120", -- [1]

$file = "C:\Program Files (x86)\World of Warcraft\_classic_era_\WTF\Account\53668689#2\SavedVariables\HerpsCoolAddon.lua"
$pattern = "^\s+.(?<char_name>\w+);(?<buff>.+);(?<points>\d+);(?<time>\d+)"

# extracting captured groups
$csv_obj = Get-ChildItem $file |
    Select-String -Pattern $pattern |
    Foreach-Object {
        $char_name, $buff, $points, $time = $_.Matches[0].Groups[1..4].Value   # this is a common way of getting the groups of a call to select-string
        [PSCustomObject] @{
            CharName = $char_name
            Buff = $buff
            Points = [int] $points
            Time = [int] $time
        }
    }

$csv_obj | Export-Csv -NoTypeInformation .\BuffList.csv