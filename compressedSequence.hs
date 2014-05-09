-- https://www.codeeval.com/open_challenges/128/

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
            putStrLn (compressedStr (compressNums (splitOn (pack " ") (pack line)) []))
            processFile handle

compressNums :: [Text] -> [Integer] -> [Integer]
compressNums [] l = l
compressNums (t:ts) [] = compressNums ts [i,1]
                        where i = read $ unpack t :: Integer
compressNums (t:ts) (x:n:xn) | i == x = compressNums ts [x,n+1] ++ xn
                             | otherwise = compressNums ts [i,1] ++ (x:n:xn)
                             where i = read $ unpack t :: Integer

compressedStr :: [Integer] -> String
compressedStr [] = ""
compressedStr (x:n:xn) = compressedStr xn ++ (show n) ++ " " ++ (show x) ++ " "
