// https://www.codeeval.com/open_challenges/7/

package main

import "fmt"
import "log"
import "bufio"
import "os"
import "strings"
import "strconv"

type Node struct {
    left *Node
    right *Node
    parent *Node
    value string
}

// round value - convert to int64
func Round(value float64) int64 {
    if value < 0.0 {
        value -= 0.5
    } else {
        value += 0.5
    }
    return int64(value)
}

func parseInput(line string) *Node {
    symbols := strings.Split(line," ")
    tree,_ := parseNode(symbols, 0)
    return tree
}

func parseNode(symbols []string, offset int) (*Node, int) {
    tree := new(Node)
    s := symbols[offset]
    if s == "*" || s == "/" || s == "+" {
        tree.value = s
        offset++
        tree.left, offset = parseNode(symbols, offset)
        tree.right, offset = parseNode(symbols, offset)
    } else {
        tree.value = s
        offset++
    }
    return tree, offset
}

func evalParseTree(tree *Node) (val float64) {
    if tree.value == "*" {
        val = evalParseTree(tree.left) * evalParseTree(tree.right)
    } else if tree.value == "/" {
        val = evalParseTree(tree.left) / evalParseTree(tree.right)
    } else if tree.value == "+" {
        val = evalParseTree(tree.left) + evalParseTree(tree.right)
    } else {
        i,err := strconv.Atoi(tree.value)
        if err != nil {
            // handle error
            fmt.Println(err)
        }
        val = float64(i)
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
        tree := parseInput(scanner.Text())
        fmt.Println(Round(evalParseTree(tree)))
    }   
}
