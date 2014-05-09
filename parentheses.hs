-- https://www.codeeval.com/open_challenges/68/

import System.IO
import System.Environment
import Data.Char
import System.Exit
import Data.Text
      
main = do
    args <- getArgs
    handle <- openFile (args !! 0) ReadMode
    processFile handle
    hClose handle

processFile handle = do
    eof <- (hIsEOF handle)
    if eof
        then
            exitWith ExitSuccess
        else do
            line <- hGetLine handle
            putStrLn (show (parentheses line ""))
            processFile handle

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
