/**********************************************
  > File Name		: TextEditor.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri Aug 12 23:33:35 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::ptr::NonNull;
use std::marker::PhantomData;

trait NodeMove {
    type Output;
    fn next(&self) -> Self::Output;

    fn prev(&self) -> Self::Output;
}

trait Len {
    fn len(&self) -> usize;
}

struct LinkedList<T> {
    head: Option<NonNull<Node<T>>>,
    tail: Option<NonNull<Node<T>>>,
    marker: PhantomData<Box<Node<T>>>
}

struct Node<T> {
    prev: Option<NonNull<Node<T>>>,
    next: Option<NonNull<Node<T>>>,
    inner: T
}

struct TextEditor {
    editor: LinkedList<String>,
    cursor: Option<NonNull<Node<String>>>,
    offset: usize
}

type Iter<T> = Option<NonNull<Node<T>>>;

impl TextEditor {
    fn move_left(&self, mut k: usize) -> (Iter<String>, usize, usize) {
        if let None = self.editor.head {
            assert!(self.editor.tail.is_none());
            return (None, 0, 0);
        }

        let (mut start, head) = (self.cursor.unwrap(), self.editor.head.unwrap());
        let (mut offset, target) = (self.offset, k);

        while k != 0 && start != head {
            if k < offset {
                offset -= k;
                k = 0;
            } else {
                k -= offset;
                start = start.prev().unwrap();
                offset = unsafe {start.as_ref().len()};
            }
        }
        
        if k != 0 {
            if offset >= k {
                offset -= k;
                k = 0;
            } else {
                k -= offset;
                offset = 0;
            }
        }

        if offset == 0 && start != head {
            start = start.prev().unwrap();
            offset = unsafe {start.as_ref().len()};
        }

        (Some(start), offset, target-k)
    }

    fn move_right(&self, mut k: usize) -> (Iter<String>, usize, usize) {
        if let None = self.editor.head {
            assert!(self.editor.tail.is_none());
            return (None, 0, 0);
        }

        let (mut stop, tail) = (self.cursor, self.editor.tail.unwrap());
        let (mut offset, target) = (self.offset, k);

        while k != 0 && stop.is_some() {
            let size = unsafe {stop.as_ref().unwrap().as_ref().len()};
            if offset + k > size {
                k -= size - offset;
                stop = stop.next();
                offset = 0;
            } else {
                offset += k;
                k = 0;
            }
        }

        if stop.is_none() {
            stop = self.editor.tail;
            offset = unsafe {stop.as_ref().unwrap().as_ref().len()};
        } 
        else if offset == 0 && stop.unwrap() != self.editor.head.unwrap() {
            stop = stop.prev();
            offset = unsafe {stop.as_ref().unwrap().as_ref().len()};
        }

        assert!(stop.is_some());
        
        (stop, offset, target-k)
    }

    fn get_left(&self) -> String {
        if self.cursor.is_none() || (self.offset == 0 && self.cursor.unwrap() == self.editor.head.unwrap()) {return String::from("");}

        let (start, mut offset, _) = self.move_left(10);
        assert!(start.is_some());
        let mut cursor = start.unwrap();

        if cursor == self.cursor.unwrap() {
            assert!(offset <= self.offset);
            let mut res = String::new();
            unsafe {res.push_str(&cursor.as_ref().as_str()[offset..self.offset]);}
            return res;
        }

        let mut res = String::new();

        let curr_cursor = self.cursor.unwrap();
        while cursor != curr_cursor {
            unsafe {
                res.push_str(&cursor.as_ref().as_str()[offset..]);
            }
            offset = 0;
            cursor = cursor.next().unwrap();
        }

        unsafe {res.push_str(&cursor.as_ref().as_str()[0..self.offset]);}
        return res;
    }

    fn at_end(&self) -> bool {
        match self.cursor {
            Some(c) => self.cursor.unwrap() == self.editor.tail.unwrap(),
            None => true
        }
    }

    fn new() -> Self {
        Self {
            editor: LinkedList::<String>::new(),
            cursor: None,
            offset: 0
        }
    }

    fn add_text(&mut self, text: String) {
        if self.cursor.is_none() {
            self.offset = text.len();
            self.editor.push_back(text);
            self.cursor = self.editor.tail;
            return;
        }

        if self.cursor == self.editor.head && self.offset == 0 {
            assert!(self.cursor.prev().is_none());
            self.offset = text.len();
            self.editor.push_front(text);
            self.cursor = self.editor.head;
            return;
        }

        assert_ne!(self.offset, 0);

        if self.offset == unsafe {self.cursor.unwrap().as_ref().len()} {
            self.offset = text.len();
            match self.cursor.next() {
                None => {
                    self.editor.push_back(text);
                    self.cursor = self.editor.tail;
                },
                Some(mut next) => {
                    unsafe {
                        self.editor.link_before(next, Box::new(Node::new(text)));
                    }
                    self.cursor = next.prev();
                }
            }
            return;
        }

        let remain = {
            let cursor = unsafe {self.cursor.unwrap().as_mut()};
            let mut res = String::new();
            res.push_str(&cursor.inner.as_str()[self.offset..]);
            //let res = String::from(cursor.inner.split_at(self.offset).1);
            cursor.inner.truncate(self.offset);
            res
        };


        if self.cursor.next().is_none() {
            self.offset = text.len();
            self.editor.push_back(text);
            self.cursor = self.editor.tail;
            self.editor.push_back(remain);
            return;
        }

        let mut next = self.cursor.next().unwrap();
        self.offset = text.len();
        unsafe {
            self.editor.link_before(next, Box::new(Node::new(text)));
            self.editor.link_before(next, Box::new(Node::new(remain)));
        }
        self.cursor = self.cursor.next();
        assert_eq!(self.offset, self.cursor.unwrap().len());
    }

    fn delete_text(&mut self, mut k: i32) -> i32 {
        let (mut cursor, mut offset, walk_len) = self.move_left(k as usize);
        println!("res: ({:?}, {}, {})", unsafe {cursor.unwrap().as_ref()}, offset, walk_len);
        if walk_len == 0 {return 0;}

        let mut remain = String::new();
        unsafe {
            remain.push_str(&cursor.unwrap().as_ref().as_str()[0..offset]);
            remain.push_str(&self.cursor.unwrap().as_ref().as_str()[self.offset..]);
        }

        let mut link_after = false;
        self.cursor = match self.cursor.unwrap().next() {
            None => {
                unsafe {self.editor.unlink_range(cursor, None);}
                link_after = true;
                self.editor.tail
            },
            Some(next) => {
                unsafe {self.editor.unlink_range(cursor, Some(next));}
                Some(next)
            }
        };
        self.offset = 0;

        if remain.len() > 0 {
            self.offset = offset;
            match self.cursor {
                Some(c) if !link_after => {
                    unsafe {self.editor.link_before(c, Box::new(Node::new(remain)));}
                    self.cursor = c.prev();
                },
                _ => {
                    self.editor.push_back(remain);
                    self.cursor = self.editor.tail;
                }
            }
        } else if self.editor.head.is_some() && self.cursor.unwrap() != self.editor.head.unwrap() {
            self.cursor = self.cursor.unwrap().prev();
            self.offset = unsafe {self.cursor.unwrap().as_ref().len()};
        }

        return walk_len as i32;
    }

    fn cursor_left(&mut self, k: i32) -> String {
        let (cursor, offset, walk_len) = self.move_left(k as usize);
        if k > 0 && walk_len == 0 {return String::new();}

        self.cursor = cursor;
        self.offset = offset;

        self.get_left()
    }

    fn cursor_right(&mut self, k: i32) -> String {
        let (cursor, offset, _) = self.move_right(k as usize);
        //println!("move_right res: ({:?}, {},)", unsafe {cursor.unwrap().as_ref()}, offset);

        self.cursor = cursor;
        self.offset = offset;

        self.get_left()
    }
}

impl<T> Node<T> {
    fn new(inner: T) -> Self {
        Self {
            prev: None,
            next: None,
            inner
        }
    }

    fn into_element(self: Box<Self>) -> T {
        self.inner
    }

}

impl<T> NodeMove for NonNull<Node<T>> {
    type Output = Option<Self>;
    fn next(&self) -> Self::Output {
        unsafe {self.as_ref().next}
    }

    fn prev(&self) -> Self::Output {
        unsafe {self.as_ref().prev}
    }
}

impl<T> NodeMove for Option<NonNull<Node<T>>> {
    type Output = Self;
    fn next(&self) -> Self::Output {
        unsafe {self.unwrap().as_ref().next}
    }

    fn prev(&self) -> Self::Output {
        unsafe {self.unwrap().as_ref().prev}
    }
}

impl Len for NonNull<Node<String>> {
    fn len(&self) -> usize {
        unsafe {
            self.as_ref().inner.len()
        }
    }
}

impl<T> std::ops::Deref for Node<T> {
    type Target = T;
    fn deref(&self) -> &Self::Target {
        &self.inner
    }
}

impl<T> AsRef<T> for Node<T> {
    fn as_ref(&self) -> &T {
        &self.inner
    }
}

impl<T> std::ops::DerefMut for Node<T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.inner
    }
}

impl<T> LinkedList<T> {
    fn new() -> Self {
        Self {
            head: None,
            tail: None,
            marker: PhantomData
        }
    }

    /// Adds the given node to the front of the list.
    #[inline]
    fn push_front_node(&mut self, mut node: Box<Node<T>>) {
        // This method takes care not to create mutable references to whole nodes,
        // to maintain validity of aliasing pointers into `element`.
        unsafe {
            node.next = self.head;
            node.prev = None;
            let node = Some(Box::leak(node).into());

            match self.head {
                None => self.tail = node,
                // Not creating new mutable (unique!) references overlapping `element`.
                Some(head) => (*head.as_ptr()).prev = node,
            }

            self.head = node;
        }
    }

    /// Removes and returns the node at the front of the list.
    #[inline]
    fn pop_front_node(&mut self) -> Option<Box<Node<T>>> {
        // This method takes care not to create mutable references to whole nodes,
        // to maintain validity of aliasing pointers into `element`.
        self.head.map(|node| unsafe {
            let node = Box::from_raw(node.as_ptr());
            self.head = node.next;

            match self.head {
                None => self.tail = None,
                // Not creating new mutable (unique!) references overlapping `element`.
                Some(head) => (*head.as_ptr()).prev = None,
            }

            node
        })
    }

    /// Adds the given node to the back of the list.
    #[inline]
    fn push_back_node(&mut self, mut node: Box<Node<T>>) {
        // This method takes care not to create mutable references to whole nodes,
        // to maintain validity of aliasing pointers into `element`.
        unsafe {
            node.next = None;
            node.prev = self.tail;
            let node = Some(Box::leak(node).into());

            match self.tail {
                None => self.head = node,
                // Not creating new mutable (unique!) references overlapping `element`.
                Some(tail) => (*tail.as_ptr()).next = node,
            }

            self.tail = node;
        }
    }

    /// Removes and returns the node at the back of the list.
    #[inline]
    fn pop_back_node(&mut self) -> Option<Box<Node<T>>> {
        // This method takes care not to create mutable references to whole nodes,
        // to maintain validity of aliasing pointers into `element`.
        self.tail.map(|node| unsafe {
            let node = Box::from_raw(node.as_ptr());
            self.tail = node.prev;

            match self.tail {
                None => self.head = None,
                // Not creating new mutable (unique!) references overlapping `element`.
                Some(tail) => (*tail.as_ptr()).next = None,
            }

            node
        })
    }

    /// Unlinks the specified node from the current list.
    ///
    /// Warning: this will not check that the provided node belongs to the current list.
    ///
    /// This method takes care not to create mutable references to `element`, to
    /// maintain validity of aliasing pointers.
    #[inline]
    unsafe fn unlink_node(&mut self, mut node: NonNull<Node<T>>) {
        let node = unsafe { node.as_mut() }; // this one is ours now, we can create an &mut.

        // Not creating new mutable (unique!) references overlapping `element`.
        match node.prev {
            Some(prev) => unsafe { (*prev.as_ptr()).next = node.next },
            // this node is the head node
            None => self.head = node.next,
        };

        match node.next {
            Some(next) => unsafe { (*next.as_ptr()).prev = node.prev },
            // this node is the tail node
            None => self.tail = node.prev,
        };

    }

    /// Unlinks a range of nodes from the current list.
    #[inline]
    unsafe fn unlink_range(&mut self, begin: Option<NonNull<Node<T>>>, mut end: Option<NonNull<Node<T>>>) {
        if let None = begin {return;}

        if let Some(end) = end {
            if begin.unwrap().as_ptr() == end.as_ptr() {
                return;
            }
        }

        let begin = begin.unwrap().as_mut();
        
        match end {
            None => {//delete to the end.
                match begin.prev {
                    None => {
                        self.head = None;
                        self.tail = None;
                    },
                    Some(mut prev) => {
                        (*prev.as_mut()).next = None;
                        self.tail = Some(prev);
                    }
                }
            },
            Some(mut end) => {
                match begin.prev {
                    None => {
                        (*end.as_mut()).prev = None;
                        self.head = Some(end);
                    },
                    Some(mut prev) => {
                        (*prev.as_mut()).next = Some(end);
                        (*end.as_mut()).prev = Some(prev);
                    }
                }
            }
        }
    }

    #[inline]
    unsafe fn link_before(&mut self, mut pos: NonNull<Node<T>>, mut node: Box<Node<T>>) {
        match pos.as_mut().prev {
            None => {
                node.next = Some(pos);
                (*pos.as_mut()).prev = NonNull::new(Box::into_raw(node));
                self.head = pos.as_ref().prev;
            },
            Some(mut prev) => {
                node.next = Some(pos);
                node.prev = Some(prev);
                let node = NonNull::new(Box::into_raw(node));
                (*pos.as_mut()).prev = node;
                (*prev.as_mut()).next = node;
            }
        }
    }

    fn push_back(&mut self, element: T) {
        self.push_back_node(Box::new(Node::new(element)));
    }

    fn push_front(&mut self, element: T) {
        self.push_front_node(Box::new(Node::new(element)));
    }

    fn pop_back(&mut self) -> Option<T> {
        self.pop_back_node().map(Node::into_element)
    }

    fn pop_front(&mut self) -> Option<T> {
        self.pop_front_node().map(Node::into_element)
    }
}

impl std::fmt::Debug for TextEditor {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "list: [")?;
        
        let mut cursor = self.editor.head;
        while let Some(c) = cursor {
            unsafe {write!(f, "{}, ", c.as_ref().as_ref())?;}
            cursor = cursor.next();
        }

        let empty = String::new();
        write!(f, "], cursor: {}, offset: {}", match self.cursor {
            Some(c) => unsafe {c.as_ref().as_ref()},
            None => &empty
        }, self.offset)
    }
}

impl std::fmt::Debug for Node<String> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", &self.inner)
    }
}


fn main() {
//["TextEditor","addText","deleteText","addText","cursorLeft","addText","deleteText","addText","cursorLeft","deleteText"]
//[[],["arnvmumatgmyw"],[5],["zrlufuifuy"],[2],["unh"],[20],["kwwp"],[6],[9]]
    let mut te = TextEditor::new();

    println!("add arnvmumatgmyw"); te.add_text(String::from("arnvmumatgmyw")); println!("{:?}\n", te);
    println!("delete 5: {}", te.delete_text(5)); println!("{:?}\n", te);
    println!("add zrlufuifuy"); te.add_text(String::from("zrlufuifuy")); println!("{:?}\n", te);
    println!("cursor_left 2: {}", te.cursor_left(2)); println!("{:?}\n", te);
    println!("add unh"); te.add_text(String::from("unh")); println!("{:?}\n", te);
    println!("delete 20: {}", te.delete_text(20)); println!("{:?}\n", te);
    println!("add kwwp"); te.add_text(String::from("kwwp")); println!("{:?}\n", te);
    println!("cursor_left 6: {}", te.cursor_left(6)); println!("{:?}\n", te);
    println!("delete 9: {}", te.delete_text(9)); println!("{:?}\n", te);
}
