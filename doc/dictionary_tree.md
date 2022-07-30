## **字典树**

字典树又称为前缀树，是一种通过字符串的字符从上往下构建的树，相同前缀字符越多的两个字符串在字典树上相隔越近。

字典树的根节点通常不存放字符，根节点的子节点存放着目前所有字符串的首字母。每个字符具有某种编号，这些字符串的子节点则是相应字符串的第二个字符。以此类推。

这里采用链表来表示一颗字典树。

### **链表法**

链表法比较简单，其数据结构为：

```c
typedef struct Node_s {
    char c;
    int state;
    struct Node_s* nexts[26];
} Node;
```

结构体中c表示相应的字符，state表示当前节点的状态，为0表示不是任何字符串的前缀，为1表示为一个前缀，为2表示不但是一个前缀，还是某个字符串的最后一个字符。一般这样一个结构体被创建出来，就表明是要成为一个前缀了。所以一般不为0。nexts则用26个同类型结构体指针指向下一个结构体指针，为了防止出现乱指针，应该在初始化的时候就置零。

#### **插入字符串**

首先创建一棵字典树，根节点不作为前缀，用字符'.'表示。

```c
Node root;
memset(&root, 0, sizeof(root));
root.c = '.';
```

则插入代码为：

```c
void insert(char* str, Node* root) {
	Node* tmp = root;
    int i;
    for (i = 0; i < strlen(str); i++) {
        if (tmp->nexts[str[i] - 'a'] == 0) { //说明还没有此前缀
            Node* new = (Node*)malloc(sizeof(Node));
            memset(new, 0, sizeof(Node));
            new->c = str[i];
            new->state = 1;
            nexts[str[i] - 'a'] = new;
            tmp = new;
        }
        else {
            if (i == strlen(str) - 1) {//如果是最后一个字符
            	tmp->nexts[str[i] - 'a']->state = 2;
            }
            else {
                tmp = nexts[str[i] - 'a'];
            }
        }
    }
}
```

代码中遍历插入字符串的所有字符，有相应前缀的就继续下一个字符，没有的话就创建。很好懂。在字符串结尾处还要记得将相应节点的state改为2

#### **查找**

查找非常容易，不讲。

字典树一般不需要执行删除操作，也不讲。
