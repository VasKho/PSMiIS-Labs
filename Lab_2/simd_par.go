package main

import (
    "fmt"
    "math/rand"
    "time"
    con "strconv"
    "sync"
)

var A, B, E, G [][]int

func count_c_par() [][]int {
    var m sync.Mutex
    var wg sync.WaitGroup
    rows := len(G)
    cols := len(G[0])
    k := len(E[0])
    C := make([][]int, rows)
    for row := range C {
        C[row] = make([]int, cols)
    }
    for i := 0; i < rows; i++ {
        for j := 0; j < cols; j++ {
            go c_par(&C, i, j, k, &m, &wg)
        }
    }
    wg.Wait()
    return C
}

func c_par(C *[][]int, i, j, k int, m *sync.Mutex, wg *sync.WaitGroup) {
    defer wg.Done()
    wg.Add(1)
    cha0 := make(chan int)
    go op2(f, i, j, k, cha0)
    cha1 := make(chan int)
    go d(i, j, k, cha1)
    cha2 := make(chan int)
    op2_val := <-cha0
    d_val := <-cha1
    go op3(op2_val, d_val, cha2)
    m.Lock()
    (*C)[i][j] = op2_val*(3*G[i][j]-2)*G[i][j]+(1 - G[i][j])*(d_val+(4*<-cha2-3*d_val)*G[i][j])
    m.Unlock()
    close(cha0)
    close(cha1)
    close(cha2)
}

func f(i, j, k int) int {
    return impl(A[i][k], B[k][j]) * (2*E[0][k] - 1) * E[0][k] + impl(B[k][j], A[i][k]) * (1 + (4 * impl(A[i][k], B[k][j]) - 2) * E[0][k]) * (1 - E[0][k])
}

func d(i, j, k int, cha chan int) {
    res := 1
    for k1 := 0; k1 < k; k1++ {
        res *= A[i][k1] * B[k1][j]
    }
    cha <- res
}

// /~\
func op2(x func(int, int, int) int, i, j, k int, cha chan int) {
    res := 1
    for k1 := 0; k1 < k; k1++ {
        res *= x(i, j, k1)
    }
    cha <- res
}

// (~)
func op3(x, y int, cha chan int) {
    sl := [2]int{x+y-1, 0}
    max := sl[0]
    for _, elem := range sl {
        if elem > max { max = elem }
    }
    cha <- max
}

// x~>y
func impl(x, y int) int {
    d := [3]int{-1, 0, 1}
    sl := []int{}
    for _, z := range d {
        if (1-x*z) <= y { sl = append(sl, z) }
    }
    if len(sl) == 0 { return -1 }
    max := sl[0]
    for _, elem := range sl {
        if elem > max { max = elem }
    }
    return max
}

func gen_matrix(rows, cols int) [][]int {
    rand.Seed(time.Now().UnixNano())
    matrix := make([][]int, rows)
    for row := range matrix {
        matrix[row] = make([]int, cols)
    }

    for row := range matrix {
        for col := range matrix[row] {
            matrix[row][col] = rand.Intn(3) - 1
        }
    }
    return matrix
}

func main() {
    var p, m, q string
    fmt.Print("Enter p: ")
    fmt.Scanln(&p)
    p_int, _ := con.Atoi(p)
    fmt.Print("Enter m: ")
    fmt.Scanln(&m)
    m_int, _ := con.Atoi(m)
    fmt.Print("Enter q: ")
    fmt.Scanln(&q)
    q_int, _ := con.Atoi(q)
    A = gen_matrix(p_int, m_int)
    B = gen_matrix(m_int, q_int)
    E = gen_matrix(1, m_int)
    G = gen_matrix(p_int, q_int)
    C := count_c_par()
    for row := range C {
        for _, col := range C[row] {
            fmt.Printf("%4d", col)
        }
        fmt.Println()
    }
}
