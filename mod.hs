-- https://www.codeeval.com/open_challenges/62/

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
            let params = (stringListToIntList (Prelude.map unpack (splitOn (pack ",") (pack line))))
            putStrLn (show (Main.mod (params!!0) (params!!1)))
            processFile handle

stringListToIntList :: [String] -> [Int]
stringListToIntList = Prelude.map read

mod :: Int -> Int -> Int
mod n m | n >= m = Main.mod (n-m) m
        | otherwise = n
