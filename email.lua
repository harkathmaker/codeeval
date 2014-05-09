-- https://www.codeeval.com/open_challenges/35/

for line in io.lines(arg[1]) do
    if #line > 0 then
        regexp = "^[%w(%w[%.%-]%w)]+@[%w]+%.[%w]+$"
        if line:find(regexp) ~= nil then
            print("true")
        else
            print("false")
        end
    end
end
