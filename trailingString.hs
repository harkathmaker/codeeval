-- https://www.codeeval.com/open_challenges/32/

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
            let strs = (splitOn (pack ",") (pack line))
            if (trailing (strs !! 0) (strs !! 1))
                then putStrLn "1"
                else putStrLn "0"
            processFile handle

trailing :: Text -> Text -> Bool
trailing s t | Data.Text.length t == Data.Text.length s = s == t
             | Data.Text.length t > Data.Text.length s = False
             | Data.Text.length t < Data.Text.length s = trailing (Data.Text.tail s) t
