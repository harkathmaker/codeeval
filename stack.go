// https://www.codeeval.com/open_challenges/9/
package main

import "fmt"
import "log"
import "bufio"
import "os"
import "strings"

type StrStack struct {
    vals []string
}

func (st *StrStack) push(val string) {
    st.vals = append(st.vals,val)
}
func (st *StrStack) pop() (element string) {
    element = st.vals[len(st.vals)-1]
    st.vals = st.vals[:len(st.vals)-1]
    return
}
func (st *StrStack) empty() (bool) {
    return (len(st.vals) < 1)
}

func main() {
    file, err := os.Open(os.Args[1])
    if err != nil {
        log.Fatal(err)
    }   
    defer file.Close()
    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        nums := strings.Split(scanner.Text(), " ")
        st := new(StrStack)
        for s := range nums {
            if nums[s] != "\n" {
                st.push(nums[s])
            }
        }
        alternate := true
        for !st.empty() {
            s := st.pop()
            if alternate {
                fmt.Printf("%s ",s)
            }
            alternate = !alternate
        }
        fmt.Printf("\n")
    }
}
