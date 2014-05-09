-- https://www.codeeval.com/open_challenges/20/

import System.IO
import System.Environment
import Data.Char
import System.Exit
      
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
            putStrLn (map toLower line)
            processFile handle
