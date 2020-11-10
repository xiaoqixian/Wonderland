### 链表的新奇写法

我以前写链表的时候总是习惯这样写：

```c
struct Example {
    int e;
    double d;
};

struct list_node {
    struct list_node* prev;
    struct Example* data;
    struct list_node* next;
};
```

不知道有没有人和我一样。这种方式写链表，我们可以根据链表头很快找到某个`data`，但是无法根据一个`data` 找到这个链表。

但是最近发现了另一种方式写链表，可以使得两种被双向找到。

```c
struct Example {
    int e;
    double d;
    struct list_node* list;
};

struct list_node {
    struct list_node* prev;
    struct list_node* next;
};
```

显然，要根据一个 `struct Example` 找到整条链表是非常容易的。那要怎么根据一个链表结点找到其所属的 `struct Example` 呢？

答案是根据结构体内的各个成员的偏移量，我们知道一个链表结点的地址 `node` ，那么只要用这个地址减去其在结构体内的偏移量不就是 `struct Example` 的地址了吗？

因此我们可以定义一个宏函数：

```c
#include <stddef.h>
#define CONTAINER_OF(ptr, type, member)\
    ((type*)((char*)ptr - offsetof(type, member)))
```

这个宏函数的三个参数分别表示链表结点的指针，相应的要找到的结构体类型，这里是 `struct Example`，以及链表结点在该结构体中的名字。

`offsetof` 同样是一个宏函数，其返回一个 `type` 的成员变量 `member` 在其内的偏移量。

通过这个宏函数，我们就可以这样找到相应的结构体了：

```c
struct list_node* node;
struct Example* e = CONTAINER_OF(node, struct Example, list);
```

这样虽然并不能节省空间，但是链表与其对应的结构体绑定更加紧密了。我看到很多开源项目如果有链表的话都倾向于这种写法，说明还是有其优势的。