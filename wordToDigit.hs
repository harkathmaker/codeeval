-- https://www.codeeval.com/open_challenges/104/

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
            putStrLn (wordToDigit (Prelude.map unpack (splitOn (pack ";") (pack line))) "")
            processFile handle

wordToDigit :: [String] -> String -> String
wordToDigit [] s = s
wordToDigit (t:ts) s | t == "zero" = wordToDigit ts (s ++ "0")
                     | t == "one" = wordToDigit ts (s ++ "1")
                     | t == "two" = wordToDigit ts (s ++ "2")
                     | t == "three" = wordToDigit ts (s ++ "3")
                     | t == "four" = wordToDigit ts (s ++ "4")
                     | t == "five" = wordToDigit ts (s ++ "5")
                     | t == "six" = wordToDigit ts (s ++ "6")
                     | t == "seven" = wordToDigit ts (s ++ "7")
                     | t == "eight" = wordToDigit ts (s ++ "8")
                     | t == "nine" = wordToDigit ts (s ++ "9")
