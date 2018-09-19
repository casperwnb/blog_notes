// quicksort
func quicksort(a []int, start, end int) []int {
	if start > end {
		return a
	}

	pvoit := a[start]
	i, j := start, end
	for i < j {
		for i < j && a[j] >= pvoit {
			j--
		}
		for i < j && a[i] <= pvoit {
			i++
		}

		if i < j {
			a[i], a[j] = a[j], a[i]
		}
	}
	a[i], a[start] = a[start], a[i]
	quicksort(a, 0, i-1)
	quicksort(a, i+1, end)
	return a
}
// quicksort end

// 二叉树插入排序
type tree struct {
	value int
	left, right *tree
}

func sort(values []int) {
	var root *tree
	for _, v := range values {
		root = add(root, v)
	}

	appendValues(values[:0], root)
}

func add(t *tree, v int) *tree {
	if t == nil {
		t = new(tree)
		t.value = v
		return t
	}

	if value < t.value {
		t.left = add(t.left, v)
	} else {
		t.right = add(t.right, v)
	}
	return t
}

func appendValues(values []int, t *tree) []int {
	if t != nil {  // 树的前序遍历
		values = appendValues(values, t.left)
		values = append(values, t.value)
		values = appendValues(values, t.right)
	}
	return values
}
// 插入排序end
