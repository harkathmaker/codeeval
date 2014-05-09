// https://www.codeeval.com/open_challenges/33/
package main

import "fmt"
import "log"
import "bufio"
import "os"
import "math"
import "strconv"

func doubleSquareCount(n int) int {
    ceil := int(math.Sqrt(float64(n)))
    floor := 0
    count := 0
    for floor <= ceil {
        total := ceil*ceil + floor*floor
        if total > n {
            ceil--
        } else if total < n {
            floor++
        } else {
            count++
            ceil--
        }
    }
    return count
}

func main() {
    file, err := os.Open(os.Args[1])
    if err != nil {
        log.Fatal(err)
    }   
    defer file.Close()
    scanner := bufio.NewScanner(file)
    var lines int
    if scanner.Scan() {
        lines,_ = strconv.Atoi(scanner.Text())
    }
    for i := 0; i < lines; i++ {
        scanner.Scan()
        n,_ := strconv.Atoi(scanner.Text())
        fmt.Println(doubleSquareCount(n))
    }
}
