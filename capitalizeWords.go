// https://www.codeeval.com/open_challenges/93/
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
        //'scanner.Text()' represents the test case, do something with it
        s := scanner.Text()
        for i:=0; i<len(s);i++ {
            if s[i] >= 'a' && s[i] <= 'z' && (i == 0 || s[i-1] == ' ') {
                fmt.Printf("%c",s[i]+'A'-'a')
            } else {
                fmt.Printf("%c",s[i])
            }
        }
        fmt.Printf("\n")
    }
}
