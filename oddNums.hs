-- https://www.codeeval.com/open_challenges/25/

import System.IO
import System.Environment
import Data.Char
import System.Exit
import Data.Text
      
main = do
    let odd = oddNums 1 99
    printValues odd

oddNums :: Int -> Int -> [Int]
oddNums s e | s <= e = [s] ++ (oddNums (s+2) e)
            | otherwise = []

listValues :: [Int] -> [String]
listValues = Prelude.map Prelude.show

printValues :: [Int] -> IO ()
printValues l = putStr (Prelude.unlines (listValues l))
