contains :: String -> Char -> Bool
contains (x:xs) c | c == x = True
                  | otherwise = contains xs c
contains [] c = False

parentheses :: String -> String -> Bool
parentheses [] [] = True
parentheses [] x = False
parentheses (x:xs) [] | (contains "([{" x) = parentheses xs [x]
                      | otherwise = False
parentheses (x:xs) (s:ss) | (contains "([{" x) = parentheses xs ([x,s] ++ ss)
                          | x == ')' && s == '(' = parentheses xs ss
                          | x == '}' && s == '{' = parentheses xs ss
                          | x == ']' && s == '[' = parentheses xs ss
                          | otherwise = False
