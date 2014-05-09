// https://www.codeeval.com/open_challenges/21/
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
        sum := 0
        for i:=0; i<len(str); i++ {
            sum += int(str[i]) - '0'
        }
        fmt.Printf("%d\n",sum)
    }
}
