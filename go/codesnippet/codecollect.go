f, err := os.Open("test.txt")
// input := bufio.NewScanner(f)
input := bufio.NewScanner(os.Stdin)
for input.Scan() {
	fmt.Println(input.Text())
}

data, err := ioutil.ReadFile("test.txt")  // 返回字节切片, 需要转换为字符串
for _, line := range strings.Split(string(data), "\n") {}

// 获取网页信息
resp, err := http.Get(url)
b, err := ioutil.ReadAll(resp.Body)  // 读取所有的数据内容
fmt.Println(resp.Status)  // 获取状态码
n, err := io.Copy(os.Stdout, resp.Body)  // 读取数据到os.Stdout, 返回读取的字节数
n, err := io.Copy(ioutil.Discard, resp.Body) // 将数据读取到/dev/null中, 即丢弃
resp.Body.Close()

ch := make(chan string)
// 会启动一个新的goroutine运行该函数
go fetchurl("http://www.baidu.com", ch)  // 可以传递一个双向通道, go会进行自动转换
fmt.Println(<-ch)  // 从ch中读取数据
// 函数定义了一个只能发送的通道
func fetchurl(url string, ch chan<-string) {
	// ...
	ch <- "fetch success"
}

// 只用于接受通道
func receiveChan(ch <-chan string) {
	fmt.Println(<-ch)
}


// 最简单的Web服务
var mu sync.Mutex
var count int
func main() {
	http.HandleFunc("/", handler)  // 定义路由
	http.HandleFunc("/lissajous", func(w http.ResponseWriter, r *http.Request{}))
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
	mu.Lock()  // 加锁, 防止竞态条件发生
	count++
	mu.Unlock()
	fmt.Fprintf(w, "URL.Path=%q, count %d\n", r.URL.Path, count)
	// w.Header().Set("Content-Type", "image/svg+xml")  // 设置响应头信息
	for k,v := range r.Header {}  // 读取头信息
	err := r.ParseForm()  // 在读取信息前需要先parse, 否则无法读取到数据
	for k, v := range r.Form {}
}

// 第一个参数: 命令行标志参数的名字, 默认值, 帮组信息
var n = flag.Bool("n", false, "omit trailing newline")
flag.Parse()  // 解析命令行参数
fmt.Println(*n)
fmt.Println(flag.Args())  // 访问非标志参数的普通命令行参数.

var buf bytes.Buffer
buf.WriteByte('[')
buf.WriteRune('你')

var a int
fmt.Scanf("%d", &a)  // 从标准输入中读取数据

// slice内存技巧, 公用同一个底层数组
// 1. 翻转
func reverse(data []string) []string {
	for i, j := 0, len(data)-1; i < j; i, j = i+1, j-1 {
		data[i], data[j] = data[j], data[i]
	}
}

// 2. 去空
func noempty1(data []string) []string {
	i := 0
	for _, s := range data {
		if s != "" {
			data[i] = s
			i++
		}
	}
	return data[:i]
}
func noempty2(data []string) []string {
	out := strings[:0] // zero-length slice
	for _, s := range strings {
		if s != "" {
			out = append(out, s)
		}
	}
	return out
}

// 删除slice中间某个元素, 并保证顺序不变
func remove(slice []int, idx int) []int {
	copy(slice[i:] slice[i+1:])
	return slice[:len(slice)-1]
}

// 删除slice中间某个元素, 不保证顺序
func remove(slice []int, idx int) []int {
	slice[idx] = slice[len(slice)-1]  // 用最后一个元素替换删除的元素.
	return slice[:len(slice)-1]
}

in := bufio.NewReader(os.Stdin)
for {
	r, n, err := in.ReadRune()  // return rune, nbytes, error
	if r == unicode.ReplacementChar && n == 1 {
		fmt.Println("read a invalid character")
	}
}

// 使用深度优先搜索完成前置课程的排序
package main

import (
	"fmt"
	"sort"
)

var prereqs = map[string][]string{
	"algorithms": {"data structures"},
	"calculus":   {"linear algebra"},
	"compilers": {
		"data structures",
		"formal languages",
		"computer organization",
	},
	"data structures":       {"discrete math"},
	"databases":             {"data structures"},
	"discrete math":         {"intro to programming"},
	"formal languages":      {"discrete math"},
	"networks":              {"operating systems"},
	"operating systems":     {"data structures", "computer organization"},
	"programming languages": {"data structures", "computer organization"},
}

func topoSort(m map[string][]string) []string {
	var order []string

	seen := make(map[string]bool)
	var visitAll func(items []string)

	visitAll = func(items []string) {
		for _, item := range items {
			if !seen[item] {
				seen[item] = true
				visitAll(m[item])
				order = append(order, item)
			}
		}
	}

	var keys []string
	for key := range m {
		keys = append(keys, key)
	}
	sort.Strings(keys)
	visitAll(keys)
	return order
}

func main() {
	for i, course := range topoSort(prereqs) {
		fmt.Printf("%d: %s\n", i+1, course)
	}
}

// 遍历目录
func walkDir(dir string) {
	entries, err := ioutil.ReadDir(dir)  // 返回一个os.FileInfo类型的slice
	// os.State函数也会返回这个值.
	if err != nil {
		fmt.Println("Error")
		return
	}

	for _, entry := range entries {
		if entry.IsDir() {
			walkDir(filepath.Join(dir, entry.Name()))
		} else {
			fmt.Println(filepath.Join(dir, entry.Name()))
		}
	}
	
}

