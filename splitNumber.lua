-- https://www.codeeval.com/open_challenges/131/

for line in io.lines(arg[1]) do
    a,b = line:find(" ")
    nums = line:sub(1,a)
    expr = string.sub(line,b+1)

    final_expr = ''
    num_index = 1

    for i = 1,#expr do
        c = expr:sub(i,i)
        if c == '+' or c == '*' or c == '-' or c == '/' then
            final_expr = final_expr .. c
        else
            final_expr = final_expr .. nums:sub(num_index,num_index)
            num_index = num_index+1
        end
    end

    -- The problem could be solved by constructing parse trees. For lua,
    -- however, evaluating the string seems like a simpler solution.
    f = loadstring("result = " .. final_expr)
    f()
    print(result)
end
