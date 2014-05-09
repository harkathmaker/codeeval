-- https://www.codeeval.com/open_challenges/92/

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
            putStrLn (penultimate (Prelude.map unpack (splitOn (pack " ") (pack line))))
            processFile handle

penultimate :: [String] -> String
penultimate [] = ""
penultimate [t] = ""
penultimate (t:t2:ts) | ts == [] = t
                      | otherwise = penultimate (t2:ts)
