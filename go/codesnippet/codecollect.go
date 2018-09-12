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

