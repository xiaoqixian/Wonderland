# B+ Tree Deletion

首先，可以使用一个[可视化工具](https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html)来帮助理解.

本文从数据库应用的角度来讲解一下B+树的删除。

相信找到相应节点和节点中的key的过程不复杂，略过。

为了实现key的删除，我们采用一种类似回溯的操作。首先从根节点开始调用删除函数，删除函数会首先找到要进入的下一层的节点，然后递归调用删除函数。直到达到某个叶子节点。在完成下一层节点的删除操作后，会返回一些表征删除情况的变量，本节点再根据删除情况进行一些更新操作，然后再返回同类型的变量到上一层，直到返回到最顶层。

#### 叶子节点删除

当我们一路寻找要删除的key到达某个叶子节点后，在删除这个key后，我们还需要考虑两个问题：

- 如果这个key是这个节点中最小的一个key, 则需要更新父节点中的key, 因为父节点中对应这个节点的key就是这个节点中最小的key.

- 如果这个节点中的key的数量小于最大数量的一半，则要考虑向其两个兄弟节点借一个key（如果是边界的叶子节点则只有一个兄弟节点）。如果其兄弟节点有超过一半的节点，则可以借出，任务完成。

  如果两个兄弟节点都没有富余key, 则需要考虑节点的融合。如果需要进行节点的融合，则涉及到节点的删除，同样需要进行父节点相应的key的删除。

#### 考虑中间节点

首先，中间节点同样需要顾虑上述叶子节点的两个问题。只是中间节点的兄弟节点就不是像链表一样链接起来的prev和next两个节点，而是同属于同一个父节点的所有节点。如果没有其它的兄弟节点，则即使少于最大数量一般的key数也不要进行任何操作。

要想实现上面提到的父节点的key的更新和删除，站在父节点的角度来看，下一层节点在完成删除操作后会返回第一个key的下一个key以及删除标志，这两个变量并不共同作用。

如果有删除标志，表明下一层的节点因为在完成删除后少于最大数量一半的key, 又借不到其它key, 只能与兄弟节点完成合并操作。