// https://www.codeeval.com/open_challenges/45/
package main

import "fmt"
import "log"
import "bufio"
import "os"
import "strconv"

func getReverseNum(n int) (reverse int) {
    reverse = 0
    for n > 0 {
        reverse *= 10
        reverse += n % 10
        n /= 10
    }
    return
}

func isPalindrome(n int) bool {
    return n == getReverseNum(n)
}

func main() {
    file, err := os.Open(os.Args[1])
    if err != nil {
        log.Fatal(err)
    }   
    defer file.Close()
    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        n,_ := strconv.Atoi(scanner.Text())
        iterations := 0
        for !isPalindrome(n) {
            n = n + getReverseNum(n)
            iterations++
        }
        fmt.Printf("%d %d\n",iterations,n)
    }
}
