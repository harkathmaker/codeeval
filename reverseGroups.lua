-- https://www.codeeval.com/open_challenges/71/

-- Split code taken from http://lua-users.org/wiki/SplitJoin
function string:split(sSeparator, nMax, bRegexp)
    assert(sSeparator ~= '')
    assert(nMax == nil or nMax >= 1)

    local aRecord = {}

    if self:len() > 0 then
        local bPlain = not bRegexp
        nMax = nMax or -1

        local nField=1 nStart=1
        local nFirst,nLast = self:find(sSeparator, nStart, bPlain)
        while nFirst and nMax ~= 0 do
            aRecord[nField] = self:sub(nStart, nFirst-1)
            nField = nField+1
            nStart = nLast+1
            nFirst,nLast = self:find(sSeparator, nStart, bPlain)
            nMax = nMax-1
        end
        aRecord[nField] = self:sub(nStart)
    end

    return aRecord
end

for line in io.lines(arg[1]) do
    splitLine = line:split(";")
    reverseInterval = tonumber(splitLine[2])
    numStr = splitLine[1]
    nums = numStr:split(",")

    reversedList = {}

    for i = 1,#nums-#nums % reverseInterval do
        idx = (math.floor((i-1)/reverseInterval)+1)*reverseInterval-((i-1) % reverseInterval)
        table.insert(reversedList,nums[idx])
    end
    for i = #nums-#nums % reverseInterval+1,#nums do
        table.insert(reversedList,nums[i])
    end

    print(table.concat(reversedList,","))
end
