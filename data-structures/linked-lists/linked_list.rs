use std::fmt::{self, Display, Formatter};

// Define a Node structure that will hold our data and a pointer to the next node
struct Node<T> {
    data: T,
    next: Option<Box<Node<T>>>,
}

// Define our LinkedList structure
pub struct LinkedList<T> {
    head: Option<Box<Node<T>>>,
    size: usize,
}

impl<T> LinkedList<T> {
    // Create a new empty linked list
    pub fn new() -> Self {
        LinkedList {
            head: None,
            size: 0,
        }
    }

    // Check if the list is empty
    pub fn is_empty(&self) -> bool {
        self.head.is_none()
    }

    // Get the size of the list
    pub fn len(&self) -> usize {
        self.size
    }

    // Add an element to the front of the list
    pub fn push_front(&mut self, data: T) {
        let new_node = Box::new(Node {
            data,
            next: self.head.take(),
        });
        self.head = Some(new_node);
        self.size += 1;
    }

    // Remove an element from the front of the list
    pub fn pop_front(&mut self) -> Option<T> {
        self.head.take().map(|node| {
            self.head = node.next;
            self.size -= 1;
            node.data
        })
    }

    // Peek at the front element without removing it
    pub fn peek_front(&self) -> Option<&T> {
        self.head.as_ref().map(|node| &node.data)
    }

    // Add an element to the back of the list
    pub fn push_back(&mut self, data: T) {
        let new_node = Box::new(Node { data, next: None });

        if self.head.is_none() {
            self.head = Some(new_node);
        } else {
            let mut current = &mut self.head;
            while let Some(ref mut node) = current {
                if node.next.is_none() {
                    node.next = Some(new_node);
                    break;
                }
                current = &mut node.next;
            }
        }
        self.size += 1;
    }

    // Create an iterator over the list
    pub fn iter(&self) -> Iter<T> {
        Iter {
            next: self.head.as_deref(),
        }
    }
}

// Implement Display for LinkedList if T implements Display
impl<T: Display> Display for LinkedList<T> {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        write!(f, "[")?;
        let mut current = &self.head;
        while let Some(node) = current {
            write!(f, "{}", node.data)?;
            current = &node.next;
            if current.is_some() {
                write!(f, ", ")?;
            }
        }
        write!(f, "]")
    }
}

// Drop implementation to avoid stack overflow on recursive destruction
impl<T> Drop for LinkedList<T> {
    fn drop(&mut self) {
        let mut current = self.head.take();
        while let Some(mut node) = current {
            current = node.next.take();
        }
    }
}

// Define an iterator for our LinkedList
pub struct Iter<'a, T> {
    next: Option<&'a Node<T>>,
}

impl<'a, T> Iterator for Iter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        self.next.map(|node| {
            self.next = node.next.as_deref();
            &node.data
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_push_and_pop_front() {
        let mut list = LinkedList::new();
        assert_eq!(list.len(), 0);
        assert_eq!(list.pop_front(), None);

        list.push_front(1);
        list.push_front(2);
        list.push_front(3);

        assert_eq!(list.len(), 3);
        assert_eq!(list.pop_front(), Some(3));
        assert_eq!(list.pop_front(), Some(2));
        assert_eq!(list.len(), 1);
        assert_eq!(list.pop_front(), Some(1));
        assert_eq!(list.pop_front(), None);
        assert_eq!(list.len(), 0);
    }

    #[test]
    fn test_peek_front() {
        let mut list = LinkedList::new();
        assert_eq!(list.peek_front(), None);

        list.push_front(1);
        assert_eq!(list.peek_front(), Some(&1));

        list.push_front(2);
        assert_eq!(list.peek_front(), Some(&2));

        list.pop_front();
        assert_eq!(list.peek_front(), Some(&1));
    }

    #[test]
    fn test_push_back() {
        let mut list = LinkedList::new();
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        assert_eq!(list.len(), 3);
        assert_eq!(list.pop_front(), Some(1));
        assert_eq!(list.pop_front(), Some(2));
        assert_eq!(list.pop_front(), Some(3));
    }

    #[test]
    fn test_iter() {
        let mut list = LinkedList::new();
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        let mut iter = list.iter();
        assert_eq!(iter.next(), Some(&1));
        assert_eq!(iter.next(), Some(&2));
        assert_eq!(iter.next(), Some(&3));
        assert_eq!(iter.next(), None);
    }
}
