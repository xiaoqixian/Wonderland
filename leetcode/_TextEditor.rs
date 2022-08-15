/**********************************************
  > File Name		: _TextEditor.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Aug 14 11:52:27 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::cell::{RefCell, Ref};
use std::rc::Rc;
use std::fmt::Debug;

trait NodeMove {
    type Output;
    
    fn prev(&self) -> Self::Output;

    fn next(&self) -> Self::Output;
}

struct Node<T> {
    prev: RefCell<Option<Rc<Node<T>>>>,
    next: RefCell<Option<Rc<Node<T>>>>,
    inner: T
}

struct SafeNode<T> {
    inner: RefCell<Option<Rc<Node<T>>>>
}

struct LinkedList<T> {
    head: SafeNode<T>,
    tail: SafeNode<T>
}

struct TextEditor {
    editor: LinkedList<String>,
    cursor: SafeNode<String>,
    offset: usize
}

impl<T> Clone for SafeNode<T> {
    fn clone(&self) -> Self {
        Self {
            inner: self.inner.clone()
        }
    }
}

impl<T> PartialEq for SafeNode<T> {
    fn eq(&self, other: &Self) -> bool {
        if self.is_none() ^ other.is_none() {
            return false;
        }

        let p1 = Rc::as_ptr(self.inner.borrow().as_ref().unwrap());
        let p2 = Rc::as_ptr(other.inner.borrow().as_ref().unwrap());
        return p1 == p2;
    }
}

impl<T> Node<T> {
    fn new(inner: T) -> Self {
        Self {
            prev: RefCell::new(None),
            next: RefCell::new(None),
            inner
        }
    }

    fn set_prev(&self, node: Option<Rc<Node<T>>>) {
        *self.prev.borrow_mut() = node;
    }

    fn set_next(&self, node: Option<Rc<Node<T>>>) {
        *self.next.borrow_mut() = node;
    }
}

impl<T> SafeNode<T> {
    fn new(inner: T) -> Self {
        Self {
            inner: RefCell::new(Some(Rc::new(Node::new(inner))))
        }
    }

    fn new_none() -> Self {
        Self {
            inner: RefCell::new(None)
        }
    }

    fn clone_node(&self) -> Option<Rc<Node<T>>> {
        self.inner.borrow().clone()
    }

    fn set_prev(&self, node: Option<Rc<Node<T>>>) {
        self.inner.borrow().as_ref().unwrap().set_prev(node);
    }

    fn set_next(&self, node: Option<Rc<Node<T>>>) {
        self.inner.borrow().as_ref().unwrap().set_next(node);
    }

    #[inline]
    fn is_none(&self) -> bool {
        self.inner.borrow().is_none()
    }

    #[inline]
    fn is_some(&self) -> bool {
        self.inner.borrow().is_some()
    }

    fn next(&self) -> Self {
        Self {
            inner: self.inner.borrow().as_ref().unwrap().next.clone()
        }
    }

    fn prev(&self) -> Self {
        Self {
            inner: self.inner.borrow().as_ref().unwrap().prev.clone()
        }
    }
}

impl SafeNode<String> {
    fn len(&self) -> usize {
        self.inner.borrow().as_ref().unwrap().inner.len()
    }

    fn as_str(&self) -> &str {
        self.inner.borrow().as_ref().unwrap().inner.as_str()
    }
}

impl<T> LinkedList<T> {
    fn new() -> Self {
        Self {
            head: SafeNode::new_none(),
            tail: SafeNode::new_none()
        }
    }

    #[inline]
    fn is_empty(&self) -> bool {
        self.head.is_none()
    }

    fn link_before(&self, pos: &SafeNode<T>, node: SafeNode<T>) {
        let prev = pos.prev();
        pos.set_prev(node.clone_node());
        node.set_next(pos.clone_node());
        if prev.is_some() {
            prev.set_next(node.clone_node());
            node.set_prev(prev.clone_node());
        }
    }

    fn unlink_before(&mut self, pos: SafeNode<T>) {
        assert!(pos.is_some());

        let prev = pos.prev();
        if prev.is_none() {return;}

        let prev_prev = prev.prev();
        
        if prev_prev.is_none() {
            pos.set_prev(None);
            self.head = pos;
        } else {
            prev_prev.set_next(pos.clone_node());
            pos.set_prev(prev_prev.clone_node());
        }
    }

    fn unlink_range(&mut self, begin: SafeNode<T>, end: SafeNode<T>) {
        assert!(begin.is_some());

        let begin_prev = begin.prev();

        if begin_prev.is_none() {
            end.set_prev(None);
            if end.is_none() {
                self.tail = end.clone();
            }
            self.head = end;
        } else {
            begin_prev.set_next(end.clone_node());
            if end.is_none() {
                self.tail = begin_prev;
            }
        }
    }

    #[inline]
    fn push_back_node(&mut self, node: SafeNode<T>) {
        if self.head.is_none() {
            assert!(self.tail.is_none());
            self.head = node.clone();
            self.tail = node;
        } else {
            self.tail.set_next(node.clone_node());
            node.set_prev(self.tail.clone_node());
            self.tail = node;
        }
    }

    #[inline]
    fn push_front_node(&mut self, node: SafeNode<T>) {
        if self.head.is_none() {
            assert!(self.tail.is_none());
            self.head = node.clone();
            self.tail = node;
        } else {
            self.head.set_prev(node.clone_node());
            node.set_next(self.head.clone_node());
            self.head = node;
        }
    }

    fn push_front(&mut self, element: T) {
        self.push_front_node(SafeNode::new(element));
    }

    fn push_back(&mut self, element: T) {
        self.push_back_node(SafeNode::new(element));
    }
}

impl TextEditor {
    fn new() -> Self {
        Self {
            editor: LinkedList::new(),
            cursor: SafeNode::new_none(),
            offset: 0
        }
    }

    fn add_text(&mut self, text: String) {
        if self.editor.is_empty() {
            self.offset = text.len();
            self.editor.push_back(text);
            self.cursor = self.editor.head.clone();
            return;
        }

        assert!(self.cursor.is_some());

        if self.offset == self.cursor.len() {
            self.offset = text.len();
            if self.cursor.next().is_none() {
                self.editor.push_back(text);
                self.cursor = self.editor.tail.clone();
            } else {
                self.cursor = self.cursor.next();
                self.editor.link_before(&self.cursor, SafeNode::new(text));
                self.cursor = self.cursor.prev();
            }
            return;
        }

        
    }
}

impl<T: Debug> Debug for Node<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{:?}", self.inner)
    }
}

impl<T: Debug> Debug for SafeNode<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{:?}", &self)
    }
}

fn main() {
}
