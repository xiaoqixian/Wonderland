---
title: 红黑树
date: 2020-04-26
mathjax: true
tags:
- DataStructure
- BinaryTree
categories:
- DataStructure
---

### **红黑树(R-B Tree)**

> 本文属于半转载：是根据多篇介绍文章加上自己的理解写成。文章地址：   https://www.cnblogs.com/skywang12345/p/3245399.html
>
> https://www.jianshu.com/p/e136ec79235c

#### **红黑树的特性**

1. 每个节点或者是黑色，或者是红色
2. 根节点是黑色
3. 每个为空的叶子结点为黑色
4. 如果一个节点是红色的，则子节点必须是黑色的
5. 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点。这一点可以确保红黑树不会一条路径过长，保证是一个相对平衡的树

#### **红黑树的应用**

红黑树的应用比较广泛，主要是用它来存储有序的数据，它的时间复杂度是O(lgn)，效率非常之高。
例如，Java集合中的[TreeSet](http://www.cnblogs.com/skywang12345/p/3311268.html)和[TreeMap](http://www.cnblogs.com/skywang12345/p/3310928.html)，C++ STL中的set、map，以及Linux虚拟内存的管理，都是通过红黑树去实现的。

而红黑树快的根本就在于它通过一系列的规则使得这棵二叉查找树编程一棵自平衡的二叉查找树，不会出现某一个分支过长的情况。

#### **左旋与右旋**

红黑树需要经常进行添加或删除的操作，但是由于红黑树的要求非常高，在经过添加或删除的操作后就不是红黑树了，需要通过旋转来保持红黑树的特性。

1. **左旋**

   ![](https://images0.cnblogs.com/i/497634/201403/251733282013849.jpg)

   操作步骤：

   * 将Y的左节点$\beta$设为X的右节点并将$\beta$节点的父节点更改为X
   * 将Y的父节点设为X的父节点，进行判断，如果X的父节点是空节点，则将Y节点设为root节点。如果不为空，则将对应父节点的子节点设为Y
   * 将X设为Y的左节点
   * 将X的父节点设为Y

   事实上不一定要按照这种步骤，要实现图中的效果，可以由多种实现方法。

   ![](https://images0.cnblogs.com/i/497634/201403/251734577643655.jpg)

2. **右旋**

   ![](https://images0.cnblogs.com/i/497634/201403/251735527958942.jpg)

   与左旋类似，略

   ![](https://images0.cnblogs.com/i/497634/201403/251737465769614.jpg)

总结来说：左旋的操作可以使得当前节点与左子节点交换位置，使得自己成为左子节点；右旋的操作可以使得当前节点（父节点的右节点）与父节点交换位置，使得自己成为父节点并使父节点成为自己的左节点。

#### **添加节点**

核心思想：**将红色节点移到根节点，将根节点涂黑**

为了使添加节点后违背的红黑树的特性条数最少，我们考虑将新添加的节点颜色设为红色，这样只会有可能违背特性4。

然后开始插入新节点，由于**红黑树首先是一棵二叉查找树**，所以先根据要插入的节点的值的大小找到要插入的位置。

插入节点后有三种情况：

* 插入后父节点是根节点，则将插入节点涂成黑色。
* 插入后父节点不是根节点，但是是黑色节点，不需要任何操作此树依旧是一棵红黑树。
* 插入后父节点是红色节点。需要再进行分情况。

**插入后父节点是红色节点**

* **叔叔节点是红色**

  处理策略：

  * 将父节点设为黑色
  * 叔叔节点设为黑色
  * 祖父节点设为红色
  * 将祖父节点作为当前节点进行递归

  首先，若父节点是红色的，则直接违背了特性3。于是将父节点涂成黑色的，这样就违背了特性5。因为在插入新节点之前，该树已经是一棵红黑树，说明父节点及以上的节点到负节点和到叔叔节点的黑色节点是一样的，现在父节点变黑了，到父节点的路径就多了一个黑节点，需要将叔叔节点也涂黑。

  但是这样变换会带来新的问题，虽然到父节点和到叔叔节点的路径黑节点数量平衡了，但是对于祖父节点及以上的节点来说，走祖父节点的这条路径的黑色节点多了一个，所以需要将祖父节点涂红平衡。为什么祖父节点一定是黑色呢？因为父节点和叔叔节点都是红色的，祖父不可能是红色的。

  但是这样对于祖父节点以上的节点又不平衡了，所以需要将祖父节点作为当前节点继续进行等效的插入操作。直到递归到根节点，而前面提到，如果祖父节点就是根节点的话，直接将祖父节点涂黑便可。

* **叔叔节点是黑色，且当前节点是右节点**

  处理策略：

  * 将父节点作为新的当前节点
  * 以新的当前节点作为支点进行左旋

  這樣的處理策略可以使得紅黑樹變成情景3的結構，所以轉到情景3.

  示意图：

  ![](https://images0.cnblogs.com/i/497634/201403/251801031546918.jpg)

* 叔叔节点是黑色，且当前节点是左节点

  处理策略：

  * 将父节点设为黑色
  * 将祖父节点设为红色
  * 以祖父节点为支点进行右旋

  經過這樣的處理後就變成了情景1的狀況。再將祖父節點作為當前節點後就可以逐漸將紅色節點移動到根節點，再直接塗黑。這就體現了紅黑樹添加節點的核心思想：**將紅色節點通過塗顏色和旋轉的方式移動到根節點後直接塗黑**。

  示意图：
  
  ![](https://images0.cnblogs.com/i/497634/201404/170945094945387.jpg)


#### **删除节点**

删除节点是红黑树操作最难的部分。

首先通过查找操作找到要删除的节点，这个不难操作。

先不考虑红黑树的平衡问题，只先考慮如何删除一个节点。

* 情景1：如果要删除的节点没有子节点，则直接删除

* 情景2：如果要删除的节点只有一个子节点，则用子节点替换删除的节点

* 情景3：若删除节点有两个子节点，用后继节点（大于删除节点的最小节点）替换删除节点

  大于删除节点的最小节点即删除节点的右子树的最左节点

  把二叉树的所有节点投射在X轴上，所有节点都是从左到右排好序的，所有目标节点的前后节点就是对应前继和后继节点。

  ![](https://upload-images.jianshu.io/upload_images/2392382-dc4f0ab5d111ff96.png?imageMogr2/auto-orient/strip|imageView2/2/w/806/format/webp)

一个删除节点的重要思想：**删除节点被替代后，对于树来说，可以认为删除的是替代节点**。

![](https://upload-images.jianshu.io/upload_images/2392382-f45799daa674d0ad.png?imageMogr2/auto-orient/strip|imageView2/2/w/1200/format/webp)

根据这个思想，可以将三种情景都转换为情景1。

* 情景2：删除结点用其唯一的子结点替换，子结点替换为删除结点后，可以认为删除的是子结点，若子结点又有两个子结点，那么相当于转换为情景3，一直自顶向下转换，总是能转换为情景1。（对于红黑树来说，只存在一个子结点的结点肯定在树末了）
* 情景3：删除结点用后继结点（肯定不存在左结点，因为后继节点为大于删除节点的最左节点），如果后继结点有右子结点，那么相当于转换为情景2，否则转为为情景1。

总结：**删除操作删除的结点可以看作删除替代结点，而替代结点最后总是在树末**。這裡說的刪除替代節點並不是真的將替代節點刪除，而是將需要被刪除的節點刪除，將替代節點移動到被刪除節點的位置，二叉查找樹（不考慮顏色）依舊保持穩定。

接下來就只需考慮刪除節點後的紅黑樹的自平衡問題。

**红黑树删除场景**

提示：裡面列出的許多場景在正常的紅黑樹可能不會遇到，但是在其他場景中經過變換後可能得到那些場景，所以加上了處理情況。

![](https://upload-images.jianshu.io/upload_images/2392382-edaf96e55f08c198.png?imageMogr2/auto-orient/strip|imageView2/2/format/webp)

* 場景1：替換節點是紅色節點

  由於替換節點是紅色，即使刪除了也不會影響紅黑樹的平衡，所以直接將替換節點的顏色設為刪除節點的顏色就可以保持紅黑樹的平衡。

* 場景2：替換節點是黑節點

  需要根據不同的場景進行不同的旋轉操作

  * 場景2.1：替換節點是其父節點的左子節點

    * 場景2.1.1：替換節點的兄弟節點是紅節點

      **處理**：

      將兄弟節點設為黑色，父節點設為紅色，對父節點進行左旋。

    * 場景2.1.2：替換節點的兄弟節點是黑節點

      * 場景2.1.2.1：替換節點的兄弟節點的右子節點是紅節點，左子節點為任意顏色。

        處理：

        * 將兄弟節點的顏色設為父節點的顏色
        * 將父節點涂為黑色
        * 將兄弟節點的右節點設為黑色
        * 對父節點進行左旋

      * 場景2.1.2.2：替換節點的兄弟節點的右子節點為黑節點，左子節點為紅節點。

        處理：

        * 將兄弟節點設為紅節點
        * 兄弟節點左節點設為黑節點
        * 對兄弟節點右旋，可得到2.1.2.1的場景，繼續進行處理

      * 場景2.1.2.3：替換節點的兄弟節點的子節點都為黑節點

        處理：

        * 將兄弟節點設為紅色
        * 將父節點作為新的替換節點進行考慮

        等於是讓父節點的兩棵子樹強行平衡，然後自己作為新的替換節點到上層去“想辦法”。

  * 場景2.2：替換節點是父節點的右節點

    * 場景2.2.1：兄弟節點是紅節點

      處理：

      * 兄弟節點設為父節點的顏色
      * 父節點設為紅色
      * 對父節點進行右旋，得到場景2.2.2.3
      * 進行場景2.2.2.3的處理

    * 場景2.2.2：兄弟節點是黑節點

      * 場景2.2.2.1：兄弟節點的左自子節點是紅節點，右子節點任意顏色

        處理：

        * 兄弟節點設為父節點的顏色
        * 父節點設為黑色
        * 兄弟節點的左子節點設為黑色
        * 對父節點進行右旋

      * 場景2.2.2.2：兄弟節點的左子節點為黑節點，右子節點為紅節點

        處理：

        * 兄弟節點設為紅色
        * 兄弟節點的右子節點設為黑色
        * 對兄弟節點進行左旋，得到場景2.2.2.1
        * 進行場景2.2.2.1的處理

      * 場景2.2.2.3：替換節點的兄弟節點的子節點均為黑節點

        處理：

        * 兄弟節點設為黑色
        * 將父節點作為新的替換節點重新進行場景處理

---

#### **Visualization**

我認為學習數據結構，可視化是一個很大的幫助。前幾天找到一篇大神寫的紅黑樹可視化的前端代碼，分享給大家。大神博客在源碼中有

```html

<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>在线生成红黑树（含变形步骤）</title>
</head>
<body>
    <div>
        <ul>
            <li>增加节点</li>
            <li>方式一：<input type="button" value="随机增加一个节点" title="随机增加一个节点" onclick="AddRandom()" /></li>
            <li>方式二：<input id="numbertext" title="" placeholder="请用,(单字节)分割数字,0-999之间的数字" value="" /><input type="button" value="一个一个节点增加" title="增加一个节点" onclick="AddOneNumber()" /></li>
            <li></li>
            <li>删除节点</li>
            <li><input id="deleteNumberText" type="text" placeholder="请输入需要删除的节点" /><input type="button" value="删除" onclick="DeleteNumber()" /> </li>
            <li></li>
            <li>参考：  http://www.cnblogs.com/skywang12345/p/3603935.html </li>
        </ul>
    </div>
    <form>
        <fieldset>
            <legend>红黑树</legend>
            <div id="currentView"></div>
        </fieldset>
    </form>
    <form id="stepView"></form>
 <!--我的博客： http://www.cnblogs.com/bbvi/ --> 
    
    <script>
        var NodeColor = { Black: "black", Red: "red" };

        var RBNode = function (_date, _paret, _color) {
            this.Data = _date;
            this.Parent = _paret;
            this.Color = _color;
            this.LeftNode = null;
            this.RightNode = null;
        }

        var RedBlackBinaryTree = function () {
            this.RootNode = null;//根节点

            this.Insert = function (insertValue) {
                if (this.RootNode == null) {
                    this.RootNode = new RBNode(insertValue, null, NodeColor.Black);
                } else {
                    var newNode = insert.call(this, insertValue);
                    insertFixUp.call(this, newNode);
                }
            }

            function insert(key) {
                ClearStepView();//清空分解步骤
                var node = this.RootNode;

                var newNode = new RBNode(key, null, NodeColor.Red);
                while (true) {
                    if (key > node.Data) {
                        if (node.RightNode == null) {
                            newNode.Parent = node;
                            node.RightNode = newNode;
                            break;
                        }
                        node = node.RightNode;
                    } else if (key < node.Data) {
                        if (node.LeftNode == null) {
                            newNode.Parent = node;
                            node.LeftNode = newNode;
                            break;
                        }
                        node = node.LeftNode;
                    } else {
                        break;
                    }
                }
                return newNode;
            }

            function insertFixUp(node) {
                var parentNode = node.Parent;
                if (parentNode != null && NodeColor.Red == parentNode.Color) {
                    var gprentNode = parentNode.Parent;
                    if (parentNode == gprentNode.LeftNode) {
                        var uncleNode = gprentNode.RightNode;
                        if (uncleNode != null && NodeColor.Red == uncleNode.Color) {
                            CreateStepView(this.RootNode, "insertCaseA1", node.Data);//记录分解步骤
                            parentNode.Color = NodeColor.Black;
                            uncleNode.Color = NodeColor.Black;
                            gprentNode.Color = NodeColor.Red;
                            CreateStepView(this.RootNode, "insertSolutionA1");//记录分解步骤
                            insertFixUp.call(this, gprentNode);
                        } else {
                            if (parentNode.RightNode == node) {
                                CreateStepView(this.RootNode, "insertCaseB1", node.Data);//记录分解步骤
                                leftRotation.call(this, parentNode);
                                CreateStepView(this.RootNode, "insertSolutionB1");//记录分解步骤
                                insertFixUp.call(this, parentNode);
                            } else if (parentNode.LeftNode == node) {
                                CreateStepView(this.RootNode, "insertCase3", node.Data);//记录分解步骤
                                parentNode.Color = NodeColor.Black;
                                gprentNode.Color = NodeColor.Red;
                                rightRotation.call(this, gprentNode);
                                CreateStepView(this.RootNode, "insertSolution3");//记录分解步骤
                            }
                        }
                    } else {
                        var uncleNode = gprentNode.LeftNode;
                        if (uncleNode != null && NodeColor.Red == uncleNode.Color) {
                            CreateStepView(this.RootNode, "insertCaseA1", node.Data);//记录分解步骤
                            parentNode.Color = NodeColor.Black;
                            uncleNode.Color = NodeColor.Black;
                            gprentNode.Color = NodeColor.Red;
                            CreateStepView(this.RootNode, "insertSolutionA1");//记录分解步骤
                            insertFixUp.call(this, gprentNode);
                        } else {
                            if (parentNode.LeftNode == node) {
                                CreateStepView(this.RootNode, "insertCase4", node.Data);//记录分解步骤
                                rightRotation.call(this, parentNode);
                                CreateStepView(this.RootNode, "insertSolution4");//记录分解步骤
                                insertFixUp.call(this, parentNode);
                            } else if (parentNode.RightNode == node) {
                                CreateStepView(this.RootNode, "insertCase5", node.Data);//记录分解步骤
                                parentNode.Color = NodeColor.Black;
                                gprentNode.Color = NodeColor.Red;
                                leftRotation.call(this, gprentNode);
                                CreateStepView(this.RootNode, "insertSolution5");//记录分解步骤
                            }
                        }
                    }
                }
                this.RootNode.Color = NodeColor.Black;
            }

            function leftRotation(node) {
                var temp = node.RightNode;

                node.RightNode = temp.LeftNode;
                if (temp.LeftNode != null) {
                    temp.LeftNode.Parent = node;
                }

                temp.Parent = node.Parent;

                if (node.Parent == null) {
                    this.RootNode = temp;
                }
                else {
                    if (node.Parent.LeftNode == node) {
                        node.Parent.LeftNode = temp;
                    } else {
                        node.Parent.RightNode = temp;
                    }
                }
                temp.LeftNode = node;
                node.Parent = temp;
            }

            function rightRotation(node) {
                var temp = node.LeftNode;

                node.LeftNode = temp.RightNode;
                if (temp.RightNode != null) {
                    temp.RightNode.Parent = node;
                }

                temp.Parent = node.Parent;

                if (node.Parent == null) {
                    this.RootNode = temp;
                } else {
                    if (node == node.Parent.RightNode) {
                        node.Parent.RightNode = temp;
                    } else {
                        node.Parent.LeftNode = temp;
                    }
                }
                temp.RightNode = node;
                node.Parent = temp;
            }

            this.Remove = function (key) {
                var node = search.call(this, this.RootNode, key);
                if (node == null) {
                    return;
                } else {
                    remove.call(this, node);
                }
            }

            function remove(node) {
                ClearStepView();//清空分解步骤
                
                var child, parent, nodeColor;
                if (node.LeftNode != null && node.RightNode != null) {
                    CreateStepView(this.RootNode, "deleteCase8", node.Data);//记录分解步骤
                    var tempNode = findMin(node.RightNode);
                    if (node.Parent == null) {
                        this.RootNode = tempNode;
                    } else {
                        if (node.Parent.LeftNode == node) {
                            node.Parent.LeftNode = tempNode;
                        } else {
                            node.Parent.RightNode = tempNode;
                        }
                    }

                    child = tempNode.RightNode;
                    parent = tempNode.Parent;
                    nodeColor = tempNode.Color;

                    if (parent.Data == node.Data) {
                        parent = tempNode;
                    } else {
                        if (child != null) {
                            child.Parent = parent;
                        }
                        parent.LeftNode = child;

                        tempNode.RightNode = node.RightNode;
                        node.RightNode.Parent = tempNode;
                    }

                    tempNode.Parent = node.Parent;
                    tempNode.Color = node.Color;
                    tempNode.LeftNode = node.LeftNode
                    node.LeftNode.Parent = tempNode;
                    
                    CreateStepView(this.RootNode, "deleteSolution8");//记录分解步骤

                    if (nodeColor == NodeColor.Black) {
                        removeFixUp.call(this, child, parent);
                    }
                } else {
                    CreateStepView(this.RootNode, "deleteCase9", node.Data);//记录分解步骤
                    if (node.LeftNode != null) {
                        child = node.LeftNode;
                    } else {
                        child = node.RightNode;
                    }

                    parent = node.Parent;
                    nodeColor = node.Color;

                    if (child != null) {
                        child.Parent = parent;
                    }

                    if (parent != null) {
                        if (parent.LeftNode != null && parent.LeftNode.Data == node.Data) {
                            parent.LeftNode = child;
                        } else {
                            parent.RightNode = child;
                        }
                    } else {
                        this.RootNode = child;
                    }

                    CreateStepView(this.RootNode, "deleteSolution9");//记录分解步骤

                    if (nodeColor == NodeColor.Black) {
                        removeFixUp.call(this, child, parent)
                    }
                }
                node = null;
            }

            function removeFixUp(node, parentNode) {
                
                var otherNode;
                while ((node == null || node.Color == NodeColor.Black) && (node != this.RootNode)) {
                    if (parentNode.LeftNode == node) {
                        otherNode = parentNode.RightNode;
                        if (otherNode.Color == NodeColor.Red) {
                            CreateStepView(this.RootNode, "deleteCase1");//记录分解步骤
                            otherNode.Color = NodeColor.Black;
                            parentNode.Color = NodeColor.Red;
                            leftRotation.call(this, parentNode);
                            otherNode = parentNode.RightNode;
                            CreateStepView(this.RootNode, "deleteSolution1");//记录分解步骤
                        }

                        if ((otherNode.LeftNode == null || otherNode.LeftNode.Color == NodeColor.Black) &&
                           (otherNode.RightNode == null || otherNode.RightNode.Color == NodeColor.Black)) {
                            CreateStepView(this.RootNode, "deleteCase3");//记录分解步骤
                            otherNode.Color = NodeColor.Red;
                            node = parentNode;
                            parentNode = node.Parent;
                            CreateStepView(this.RootNode, "deleteSolution3");//记录分解步骤
                        } else {
                            if (otherNode.RightNode == null || otherNode.RightNode.Color == NodeColor.Black) {
                                CreateStepView(this.RootNode, "deleteCase4");//记录分解步骤
                                otherNode.LeftNode.Color == NodeColor.Black;
                                otherNode.Color = NodeColor.Red;
                                rightRotation.call(this, otherNode);
                                otherNode = parentNode.RightNode;
                                CreateStepView(this.RootNode, "deleteSolution4");//记录分解步骤
                            }

                            CreateStepView(this.RootNode, "deleteCase6");//记录分解步骤
                            otherNode.Color = parentNode.Color;
                            parentNode.Color = NodeColor.Black;
                            otherNode.RightNode.Color = NodeColor.Black;
                            leftRotation.call(this, parentNode);
                            node = this.RootNode;
                            CreateStepView(this.RootNode, "deleteSolution6");//记录分解步骤
                            break;
                        }
                    } else {
                        otherNode = parentNode.LeftNode;
                        if (otherNode.Color == NodeColor.Red) {
                            CreateStepView(this.RootNode, "deleteCase2");//记录分解步骤
                            otherNode.Color = NodeColor.Black;
                            parentNode.Color = NodeColor.Red;
                            rightRotation.call(this, parentNode);
                            otherNode = parentNode.LeftNode;
                            CreateStepView(this.RootNode, "deleteSolution2");//记录分解步骤
                        }

                        if ((otherNode.LeftNode == null || otherNode.LeftNode.Color == NodeColor.Black) &&
                            (otherNode.RightNode == null || otherNode.RightNode.Color == NodeColor.Black)) {
                            CreateStepView(this.RootNode, "deleteCase3");//记录分解步骤
                            otherNode.Color = NodeColor.Red;
                            node = parentNode;
                            parentNode = node.parent;
                            CreateStepView(this.RootNode, "deleteSolution3");//记录分解步骤
                        } else {
                            if (otherNode.LeftNode == null || otherNode.LeftNode.Color == NodeColor.Black) {
                                CreateStepView(this.RootNode, "deleteCase5");//记录分解步骤
                                otherNode.RightNode.Color = NodeColor.Black;
                                otherNode.Color = NodeColor.Red;
                                leftRotation.call(this, otherNode);
                                otherNode = parentNode.LeftNode;
                                CreateStepView(this.RootNode, "deleteSolution5");//记录分解步骤
                            }
                            CreateStepView(this.RootNode, "deleteCase7");//记录分解步骤
                            otherNode.Color = parentNode.Color;
                            parentNode.Color = NodeColor.Black;
                            otherNode.LeftNode.Color = NodeColor.Black;
                            rightRotation.call(this, parentNode);
                            node = this.RootNode;
                            CreateStepView(this.RootNode, "deleteSolution7");//记录分解步骤
                            break;
                        }
                    }
                }
                if (node != null) {
                    node.Color = NodeColor.Black;
                }
            }

            this.Search = function (key) {
                return search.call(this, this.RootNode, key);
            }

            function search(node, key) {
                if (node == null) {
                    return null;
                }

                if (node.Data > key) {
                    return search(node.LeftNode, key);
                } else if (node.Data < key) {
                    return search(node.RightNode, key);
                } else {
                    return node;
                }
            }

            this.FindMin = function () {
                return findMin(this.RootNode);
            }

            function findMin(node) {
                if (node.LeftNode == null) {
                    return node;
                }
                return findMin(node.LeftNode);
            }

            this.FindMax = function () {
                return findMax(this.RootNode)
            }

            function findMax(node) {
                if (node.RightNode == null) {
                    return node;
                }
                return findMax(node.RightNode);
            }


            this.SearchRange = function (minKey, maxKey) {
                return searchRange(minKey, maxKey, this.RootNode, []);
            }

            function searchRange(minKey, maxKey, node, nodeList) {
                if (node == null) {
                    return nodeList;
                }

                if (node.Data > minKey) {
                    searchRange(minKey, maxKey, node.LeftNode, nodeList);
                }

                if (node.Data >= minKey && node.Data < maxKey) {
                    nodeList.push(node.Data);
                }

                if (node.Data < maxKey) {
                    searchRange(minKey, maxKey, node.RightNode, nodeList);
                }

                return nodeList;
            }

            this.LevelOrder = function (action) {
                levelOrder(this.RootNode, action);
            }

            function levelOrder(node, action) {
                var stack = [];
                stack.push(node);

                while (stack.length > 0) {
                    var temp = stack.pop();

                    action(temp);

                    if (temp.LeftNode != null) {
                        stack.push(temp.LeftNode);
                    }

                    if (temp.RightNode != null) {
                        stack.push(temp.RightNode);
                    }
                }
            }


            this.PreOrder = function (action) {
                treeOrder(this.RootNode, action, null, null);
            }

            this.InOrder = function (action) {
                treeOrder(this.RootNode, null, action, null);
            }

            this.PostOrder = function (action) {
                treeOrder(this.RootNode, null, null, action);
            }

            function treeOrder(node, preOrderAction, inOrderAction, postOrderAction) {
                if (preOrderAction) {
                    preOrderAction(node);
                }

                if (node.LeftNode != null) {
                    treeOrder(node.LeftNode, preOrderAction, inOrderAction, postOrderAction);
                }

                if (inOrderAction) {
                    inOrderAction(node);
                }

                if (node.RightNode != null) {
                    treeOrder(node.RightNode, preOrderAction, inOrderAction, postOrderAction);
                }

                if (postOrderAction) {
                    postOrderAction(node);
                }
            }
        }
    </script>

    <script>
        var height = 50;//节点之间的高
        var width = 15;//节点之间的宽
        var tops = 40;//根节点离顶部的距离
        var foot = 40;//树离底部距离
        var spacing = 30;//树分别离两边的间距

        var tree = new RedBlackBinaryTree();

        function AddOneNumber() {
            var numbertext = document.getElementById("numbertext").value;

            var oneNums = numbertext.match(/[1-9][0-9]{0,2}\,?/);
            document.getElementById("numbertext").value = numbertext.replace(/[1-9][0-9]{0,2}\,?/, "");

            var num = (oneNums + "").match(/[1-9][0-9]{0,2}/);

            if (!!num) {
                AddNumber(parseInt(num));
            }
        }

        function AddRandom() {
            AddNumber(Math.floor(Math.random() * (1000)));
        }

        function AddAllNumber() {
            while (true) {
                AddOneNumber();
                var numbertext = document.getElementById("numbertext").value;
                if (!/[1-9][0-9]{0,2}/.test(numbertext)) {
                    break;
                }
            }
        }

        function AddNumber(number) {
            tree.Insert(number);
            RenewView(tree);
        }

        function DeleteNumber() {
            var deleteNumberText = document.getElementById("deleteNumberText").value;
            if (!deleteNumberText.match(/^[1-9][0-9]{0,2}$/)) {
                alert("请正确输入1-999的整数");
                return false;
            }
            var number = parseInt(deleteNumberText);
            var isExist = tree.Search(number);
            if (!isExist)
            {
                alert("不存在此节点");
                return false;
            }
            tree.Remove(number);
            document.getElementById("deleteNumberText").value = '';
            RenewView(tree);
        }

        function RenewView(_tree) {
            var currentView = document.getElementById("currentView");
            currentView.innerHTML = '';
            CreateTreeView(_tree.RootNode, currentView);
        }


        function CreateTreeView(rootNode, hostDocument) {
            var size = SetCanvasWidthHeight(rootNode);

            var canvas = document.createElement("canvas");
            canvas.style.backgroundColor = "antiquewhite";
            canvas.style.display = "block";
            canvas.height = size.height;
            canvas.width = size.width;

            var context = canvas.getContext("2d");

            hostDocument.appendChild(canvas);
            SetPoint(rootNode);
            PreOrder(rootNode, SetPreOrder, context, canvas.width);
        }


        function PreOrder(node, action, context, canvasWidth) {
            action(node, context, canvasWidth);

            if (node.LeftNode != null) {
                PreOrder(node.LeftNode, action, context, canvasWidth);
            }

            if (node.RightNode != null) {
                PreOrder(node.RightNode, action, context, canvasWidth);
            }
        }


        function SetCanvasWidthHeight(rootNode) {
            var level = Level(rootNode);
            return {
                height: height * level + tops + foot,
                width: Math.pow(2, level + 1) * width + spacing * 2
            };
        }

        function SetPreOrder(node, context, canvasWidth) {
            var container = drawArc(
                context,
                node.Data,
                canvasWidth / 2 + width * node.nodePoint,
                (node.nodeLevel * height + parseInt(tops)),
                node.Color);

            if (node.Parent != null) {
                var line = linkNode(
                    context,
                    (canvasWidth / 2 + width * node.Parent.nodePoint),
                    (node.Parent.nodeLevel * height + parseInt(tops)),
                    (node.Data, canvasWidth / 2 + width * node.nodePoint),
                    (node.nodeLevel * height + parseInt(tops)));
            }
        }

        //生产节点
        function drawArc(context, number, x, y, color) {
            //圆
            context.beginPath();
            context.fillStyle = color;
            context.arc(x, y, 15, (Math.PI / 180) * 0, (Math.PI / 180) * 360, false);
            context.fill();
            context.closePath();

            //数字
            var textX = x;
            var textY = y + 5;
            if (number < 10) {
                textX -= 5;
            } else if (number > 9 && number < 100) {
                textX -= 8;
            } else {
                textX -= 12;
            }

            context.fillStyle = "white";
            context.font = "bold 15px Arial";
            context.fillText(number + "", textX, textY);
        }

        //链接节点
        function linkNode(context, fatherNodeX, fatherNodeY, childrenNodeX, childrenNodeY) {
            drawLine(context, fatherNodeX, fatherNodeY + 15, childrenNodeX, childrenNodeY - 15);
        }

        //生产线
        function drawLine(context, x, y, toX, toY) {
            context.moveTo(x, y);
            context.lineTo(x, y);
            context.lineTo(toX, toY);
            context.stroke();
        }



        var maxLevel;
        var level;
        function Level(rootNode) {
            maxLevel = 0;
            level = 0;
            return levels(rootNode);
        }

        function levels(node) {
            if (node.LeftNode != null) {
                level++;
                levels(node.LeftNode);
            }
            maxLevel = Math.max(maxLevel, level);

            if (node.RightNode != null) {
                level++;
                levels(node.RightNode);
            }
            level--;
            return maxLevel;
        }

        function SetPoint(rootNode) {
            var thisMaxLevel = Level(rootNode);
            var childQuanty = Math.pow(2, thisMaxLevel);

            rootNode.nodeLevel = 0;
            rootNode.nodePoint = 0;

            if (rootNode.LeftNode != null) {
                setPointsLeft(rootNode.LeftNode, -1 * childQuanty / 2, 0, thisMaxLevel - 1);
            }

            if (rootNode.RightNode != null) {
                setPointsRight(rootNode.RightNode, childQuanty / 2, 0, thisMaxLevel - 1);
            }
        }

        function setPointsLeft(node, point, levels, thisMaxLevel) {
            ++levels;
            node.nodeLevel = levels;
            node.nodePoint = point;

            if (node.LeftNode != null) {
                setPointsLeft(node.LeftNode, point - Math.pow(2, thisMaxLevel - levels), levels, thisMaxLevel);
            }

            if (node.RightNode != null) {
                setPointsLeft(node.RightNode, point + Math.pow(2, thisMaxLevel - levels), levels, thisMaxLevel);
            }
        }

        function setPointsRight(node, point, levels, thisMaxLevel) {
            ++levels;
            node.nodeLevel = levels;
            node.nodePoint = point;

            if (node.LeftNode != null) {
                setPointsRight(node.LeftNode, point - Math.pow(2, thisMaxLevel - levels), levels, thisMaxLevel);
            }

            if (node.RightNode != null) {
                setPointsRight(node.RightNode, point + Math.pow(2, thisMaxLevel - levels), levels, thisMaxLevel);
            }
        }


        var stepRemark = {
            "insertCaseA1": {
                "title": "插入节点情况A1",
                "remark": [
                    "当前节点的父节点是红色，且当前节点的祖父节点的另一个子节点（叔叔节点）也是红色"
                ]
            },
            "insertSolutionA1": {
                "title": "插入节点情况A1的解决方案",
                "remark": [
                        "(01) 将“父节点”设为黑色",
                        "(02) 将“叔叔节点”设为黑色",
                        "(03) 将“祖父节点”设为“红色",
                        "(04) 将“祖父节点”设为“当前节点”(红色节点)；即，之后继续对“当前节点”进行操作"
                ]
            },
            "insertCaseB1": {
                "title": "插入节点情况2",
                "remark": [
                    "当前节点的父节点是红色，叔叔节点是黑色，且当前节点是其父节点的右孩子"
                ]
            },
            "insertSolutionB1": {
                "title": "插入节点情况2的解决方案",
                "remark": [
                        "(01) 将“父节点”作为“新的当前节点”",
                        "(02) 以“新的当前节点”为支点进行左旋",
                ]
            },
            "insertCase3": {
                "title": "插入节点情况3",
                "remark": [
                    "当前节点的父节点是红色，叔叔节点是黑色，且当前节点是其父节点的左孩子"
                ]
            },
            "insertSolution3": {
                "title": "插入节点情况3的解决方案",
                "remark": [
                        "(01) 将“父节点”设为“黑色”",
                        "(02) 将“祖父节点”设为“红色”",
                        "(03) 以“祖父节点”为支点进行右旋"
                ]
            },
            "insertCase4": {
                "title": "插入节点情况4",
                "remark": [
                    "当前节点的父节点是红色，叔叔节点是黑色，且当前节点是其父节点的左孩子"
                ]
            },
            "insertSolution4": {
                "title": "插入节点情况4的解决方案",
                "remark": [
                        "(01) 将“父节点”作为“新的当前节点”",
                        "(02) 以“新的当前节点”为支点进行右旋",
                ]
            },
            "insertCase5": {
                "title": "插入节点情况5",
                "remark": [
                    "当前节点的父节点是红色，叔叔节点是黑色，且当前节点是其父节点的右孩子"
                ]
            },
            "insertSolution5": {
                "title": "插入节点情况5的解决方案",
                "remark": [
                        "(01) 将“父节点”设为“黑色”",
                        "(02) 将“祖父节点”设为“红色”",
                        "(03) 以“祖父节点”为支点进行左旋"
                ]
            },
            "deleteCase1": {
                "title": "删除节点情况1",
                "remark": [
                    "被删节点是“黑+黑”节点，被删除的节点是左节点，被删节点的兄弟节点是红色。(此时被删节点的父节点和x的兄弟节点的子节点都是黑节点)。"
                ]
            },
            "deleteSolution1": {
                "title": "删除节点情况1解决方案",
                "remark": [
                    "(01) 将x的兄弟节点设为“黑色”。",
                    "(02) 将x的父节点设为“红色”。",
                    "(03) 对x的父节点进行左旋。",
                    "(04) 左旋后，重新设置x的兄弟节点。"
                ]
            },
            "deleteCase2": {
                "title": "删除节点情况2",
                "remark": [
                    "被删节点是“黑+黑”节点，被删除的节点是右节点，被删节点的兄弟节点是红色。(此时被删节点的父节点和x的兄弟节点的子节点都是黑节点)。"
                ]
            },
            "deleteSolution2": {
                "title": "删除节点情况2解决方案",
                "remark": [
                    "(01) 将被删节点的兄弟节点设为“黑色”。",
                    "(02) 将被删节点的父节点设为“红色”。",
                    "(03) 对被删节点的父节点进行右旋。",
                    "(04) 右旋后，重新设置x的兄弟节点。"
                ]
            },
            "deleteCase3": {
                "title": "删除节点情况3",
                "remark": [
                    "被删节点是“黑+黑”节点，被删节点的兄弟节点是黑色，被删节点的兄弟节点的两个孩子都是黑色。"
                ]
            },
            "deleteSolution3": {
                "title": "删除节点情况3解决方案",
                "remark": [
                    "(01) 将被删节点的兄弟节点设为“红色”。",
                    "(02) 设置“被删节点的父节点”为“新的被删节点节点”。"
                ]
            },
            "deleteCase4": {
                "title": "删除节点情况4",
                "remark": [
                    "将被删节点是“黑+黑”节点，被删节点的兄弟节点是黑色；将被删节点的兄弟节点的左孩子是红色，右孩子是黑色的。"
                ]
            },
            "deleteSolution4": {
                "title": "删除节点情况4解决方案",
                "remark": [
                    "(01) 将被删节点兄弟节点的左孩子设为“黑色”。",
                    "(02) 将被删节点兄弟节点设为“红色”。",
                    "(03) 对被删节点的兄弟节点进行右旋。",
                    "(04) 右旋后，重新设置被删节点的兄弟节点。",
                ]
            },
            "deleteCase5": {
                "title": "删除节点情况5",
                "remark": [
                    "被删节点是“黑+黑”节点，被删节点的兄弟节点是黑色；被删节点的兄弟节点的左孩子是黑色，右孩子是红色的。"
                ]
            },
            "deleteSolution5": {
                "title": "删除节点情况5解决方案",
                "remark": [
                    "(01) 将被删节点兄弟节点的右孩子设为“黑色”。",
                    "(02) 将被删节点兄弟节点设为“红色”。",
                    "(03) 对被删节点的兄弟节点进行左旋。",
                    "(04) 左旋后，重新设置被删节点的兄弟节点。",
                ]
            },
            "deleteCase6": {
                "title": "删除节点情况6",
                "remark": [
                    "被删节点是“黑+黑”节点，被删节点的兄弟节点是黑色；被删节点的兄弟节点的右孩子是红色的，被删节点的兄弟节点的左孩子任意颜色。"
                ]
            },
            "deleteSolution6": {
                "title": "删除节点情况6解决方案",
                "remark": [
                    "(01) 将被删节点父节点颜色 赋值给 被删节点的兄弟节点。",
                    "(02) 将被删节点父节点设为“黑色”。",
                    "(03) 将被删节点兄弟节点的右子节点设为“黑色”。",
                    "(04) 对被删节点的父节点进行左旋。",
                    "(05) 设置“被删节点”为“根节点”。"
                ]
            },
            "deleteCase7": {
                "title": "删除节点情况7",
                "remark": [
                    "被删节点是“黑+黑”节点，被删节点的兄弟节点是黑色；被删节点的兄弟节点的左孩子是红色的，被删节点的兄弟节点的右孩子任意颜色。"
                ]
            },
            "deleteSolution7": {
                "title": "删除节点情况7解决方案",
                "remark": [
                    "(01) 将被删节点父节点颜色 赋值给 被删节点的兄弟节点。",
                    "(02) 将被删节点父节点设为“黑色”。",
                    "(03) 将被删节点兄弟节点的左子节设为“黑色”。",
                    "(04) 对被删节点的父节点进行右旋。",
                    "(05) 设置“被删节点”为“根节点”。"
                ]
            },
            "deleteCase8": {
                "title": "删除节点情况8",
                "remark": [
                    "被删节点有两个子节点"
                ]
            },
            "deleteSolution8": {
                "title": "删除节点情况8解决方案",
                "remark": [
                    "(01) 将被删节点右节点的子孙节点中找出小的节点，替换被删节点。",
                ]
            },
            "deleteCase9": {
                "title": "删除节点情况9",
                "remark": [
                    "被删节点只有一个子节点或无子节点"
                ]
            },
            "deleteSolution9": {
                "title": "删除节点情况9解决方案",
                "remark": [
                    "(01) 将唯一的子节点替换被删节点。",
                ]
            }
                
        };

        function ClearStepView() {
            var stepView = document.getElementById("stepView");
            stepView.innerHTML = '';
        }

        function CreateStepView(_tree, step, currentNumber) {
            var fieldset = document.createElement("fieldset");
            var legend = document.createElement("legend");
            var ul = document.createElement("ul");
            var canvas = document.createElement("canvas");

            legend.innerHTML = stepRemark[step].title;

            if (!!currentNumber) {
                var li = document.createElement("li");
                li.innerHTML = "当前节点：" + currentNumber;
                ul.appendChild(li);
            }


            for (var i = 0; i < stepRemark[step].remark.length; i++) {
                var li = document.createElement("li");
                li.innerHTML = stepRemark[step].remark[i];
                ul.appendChild(li);
            }

            fieldset.appendChild(legend);
            fieldset.appendChild(ul);
            fieldset.appendChild(canvas);

            var stepView = document.getElementById("stepView");
            stepView.appendChild(fieldset);

            CreateStepTreeView(_tree, canvas);
        }

        function CreateStepTreeView(rootNode, canvas) {
            var size = SetCanvasWidthHeight(rootNode);

            canvas.style.backgroundColor = "antiquewhite";
            canvas.style.display = "block";
            canvas.height = size.height;
            canvas.width = size.width;

            var context = canvas.getContext("2d");

            SetPoint(rootNode);
            PreOrder(rootNode, SetPreOrder, context, canvas.width);
        }
    </script>
</body>
</html>
```









