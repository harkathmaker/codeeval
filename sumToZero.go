// https://www.codeeval.com/open_challenges/81/

package main

import "fmt"
import "log"
import "bufio"
import "os"
import "strings"
import "strconv"

func getZeroSums(line string) int {
    rawElements := strings.Split(line,",")
    elements := make([]int, len(rawElements))
    for i:=0; i<len(rawElements); i++ {
        elements[i],_ = strconv.Atoi(rawElements[i])
    }
    return combinations(elements,4)
}

func sum(elements []int) int {
    s := 0
    for _,e := range elements {
        s += e
    }
    return s
}

// Modified from code found at http://play.golang.org/p/JEgfXR2zSH
func combinations(iterable []int, r int) (zeroSums int) {
    zeroSums = 0
    pool := iterable
    n := len(pool)

    if r > n {
        return
    }

    indices := make([]int, r)
    for i := range indices {
        indices[i] = i
    }

    result := make([]int, r)
    for i, el := range indices {
        result[i] = pool[el]
    }

    if sum(result) == 0 {
        zeroSums += 1
    }

    for {
        i := r - 1
        for ; i >= 0 && indices[i] == i+n-r; i -= 1 {
        }

        if i < 0 {
            return
        }

        indices[i] += 1
        for j := i + 1; j < r; j += 1 {
            indices[j] = indices[j-1] + 1
        }

        for ; i < len(indices); i += 1 {
            result[i] = pool[indices[i]]
        }
        if sum(result) == 0 {
            zeroSums += 1
        }

    }

    return
}

func main() {
    file, err := os.Open(os.Args[1])
    if err != nil {
        log.Fatal(err)
    }   
    defer file.Close()
    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        fmt.Println(getZeroSums(scanner.Text()))
    }   
}
