// https://www.codeeval.com/open_challenges/121/
package main

import "fmt"
import "log"
import "bufio"
import "os"

func main() {
    file, err := os.Open(os.Args[1])
    if err != nil {
        log.Fatal(err)
    }   
    defer file.Close()
    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        str := scanner.Text()
        m := map[rune]rune{
            ' ':' ',
            'a':'y',
            'b':'h',
            'c':'e',
            'd':'s',
            'e':'o',
            'f':'c',
            'g':'v',
            'h':'x',
            'i':'d',
            'j':'u',
            'k':'i',
            'l':'g',
            'm':'l',
            'n':'b',
            'o':'k',
            'p':'r',
            'q':'z',
            'r':'t',
            's':'n',
            't':'w',
            'u':'j',
            'v':'p',
            'w':'f',
            'x':'m',
            'y':'a',
            'z':'q',
        }
        for _,c := range str {
            fmt.Printf("%c",m[c])
        }
        fmt.Printf("\n")
    }
}
