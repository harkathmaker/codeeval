-- https://www.codeeval.com/open_challenges/8/

import System.IO
import System.Environment
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
            if null line
                then
                    return ()
                else
                    putStrLn (reverseWords line)
            processFile handle
  
reverseWords :: String -> String
reverseWords l = unwords (reverse (words l))
