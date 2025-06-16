use std::cmp::Ord;
use std::fmt::Debug;

#[derive(Debug)]
struct Node<T: Ord + Copy> {
    value: T,
    left: Option<Box<Node<T>>>,
    right: Option<Box<Node<T>>>,
}

#[derive(Debug)]
struct BinarySearchTree<T: Ord + Copy> {
    root: Option<Box<Node<T>>>,
}

impl<T: Ord + Copy> BinarySearchTree<T> {
    fn new() -> Self {
        BinarySearchTree { root: None }
    }

    fn storeInorderTraversalRecursive(&self, node: Option<&Box<Node<T>>>, values: &mut Vec<T>) {
        if let Some(node) = node {
            self.storeInorderTraversalRecursive(node.left.as_ref(), values);
            values.push(node.value);
            self.storeInorderTraversalRecursive(node.right.as_ref(), values);
        }
    }

    fn storeInorderTraversal(&self) -> Vec<T> {
        let mut values = Vec::new();
        self.storeInorderTraversalRecursive(self.root.as_ref(), &mut values);
        values
    }

    fn insert(&mut self, value: T) {
        // Take ownership of root first, then pass it to insert_recursive
        let root = self.root.take();
        self.root = Self::insert_recursive(root, value);
    }

    // Static method that doesn't borrow self
    fn insert_recursive(node: Option<Box<Node<T>>>, value: T) -> Option<Box<Node<T>>> {
        match node {
            None => Some(Box::new(Node {
                value,
                left: None,
                right: None,
            })),
            Some(mut boxed_node) => {
                if value < boxed_node.value {
                    boxed_node.left = Self::insert_recursive(boxed_node.left, value);
                } else if value > boxed_node.value {
                    boxed_node.right = Self::insert_recursive(boxed_node.right, value);
                }
                // If equal, do nothing (no duplicates)
                Some(boxed_node)
            }
        }
    }

    // Search for a value in the tree, returns true if found
    fn search(&self, value: T) -> bool {
        Self::search_recursive(self.root.as_ref(), value)
    }

    // Static method for searching
    fn search_recursive(node: Option<&Box<Node<T>>>, value: T) -> bool {
        match node {
            None => false,
            Some(boxed_node) => {
                if value == boxed_node.value {
                    true
                } else if value < boxed_node.value {
                    Self::search_recursive(boxed_node.left.as_ref(), value)
                } else {
                    Self::search_recursive(boxed_node.right.as_ref(), value)
                }
            }
        }
    }

    // Delete a value from the tree
    fn delete(&mut self, value: T) {
        let root = self.root.take();
        self.root = Self::delete_recursive(root, value);
    }

    // Find the minimum value in a subtree
    fn min_value_node(node: &Box<Node<T>>) -> T {
        let mut current = node;
        while let Some(left) = &current.left {
            current = left;
        }
        current.value
    }

    // Static method for deletion
    fn delete_recursive(node: Option<Box<Node<T>>>, value: T) -> Option<Box<Node<T>>> {
        if node.is_none() {
            return None;
        }

        let mut boxed_node = node.unwrap();

        if value < boxed_node.value {
            boxed_node.left = Self::delete_recursive(boxed_node.left, value);
        } else if value > boxed_node.value {
            boxed_node.right = Self::delete_recursive(boxed_node.right, value);
        } else {
            // Node with only one child or no child
            if boxed_node.left.is_none() {
                return boxed_node.right;
            } else if boxed_node.right.is_none() {
                return boxed_node.left;
            }

            // Node with two children: Get the inorder successor
            let min_value = Self::min_value_node(boxed_node.right.as_ref().unwrap());
            boxed_node.value = min_value;

            // Delete the inorder successor
            boxed_node.right = Self::delete_recursive(boxed_node.right, min_value);
        }

        Some(boxed_node)
    }

    // Get the height of the tree
    fn height(&self) -> usize {
        Self::height_recursive(self.root.as_ref())
    }

    fn height_recursive(node: Option<&Box<Node<T>>>) -> usize {
        match node {
            None => 0,
            Some(boxed_node) => {
                let left_height = Self::height_recursive(boxed_node.left.as_ref());
                let right_height = Self::height_recursive(boxed_node.right.as_ref());
                1 + std::cmp::max(left_height, right_height)
            }
        }
    }

    // Check if the tree is balanced
    fn is_balanced(&self) -> bool {
        Self::is_balanced_recursive(self.root.as_ref())
    }

    fn is_balanced_recursive(node: Option<&Box<Node<T>>>) -> bool {
        match node {
            None => true,
            Some(boxed_node) => {
                let left_height = Self::height_recursive(boxed_node.left.as_ref());
                let right_height = Self::height_recursive(boxed_node.right.as_ref());

                let height_diff = if left_height > right_height {
                    left_height - right_height
                } else {
                    right_height - left_height
                };

                height_diff <= 1
                    && Self::is_balanced_recursive(boxed_node.left.as_ref())
                    && Self::is_balanced_recursive(boxed_node.right.as_ref())
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_new() {
        let bst = BinarySearchTree::<i32>::new();
        assert!(bst.root.is_none());
    }

    #[test]
    fn test_insert_and_search() {
        let mut bst = BinarySearchTree::<i32>::new();

        // Insert and search for values
        bst.insert(50);
        assert!(bst.search(50));
        assert!(!bst.search(30));

        bst.insert(30);
        bst.insert(70);
        assert!(bst.search(30));
        assert!(bst.search(70));
        assert!(!bst.search(20));

        // Test tree structure
        let root = bst.root.as_ref().unwrap();
        assert_eq!(root.value, 50);
        assert_eq!(root.left.as_ref().unwrap().value, 30);
        assert_eq!(root.right.as_ref().unwrap().value, 70);
    }

    #[test]
    fn test_store_inorder_traversal() {
        let mut bst = BinarySearchTree::<i32>::new();

        // Empty tree should return empty vector
        let empty_result = bst.storeInorderTraversal();
        assert_eq!(empty_result, Vec::<i32>::new());

        // Insert some values
        // The tree will look like:
        //      50
        //     /  \
        //    30   70
        //   /  \
        //  20  40
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);

        // Get inorder traversal (should be sorted)
        let result = bst.storeInorderTraversal();

        // Check the result
        assert_eq!(result, vec![20, 30, 40, 50, 70]);

        // Insert more values
        bst.insert(60);
        bst.insert(80);

        // Check updated traversal
        let updated_result = bst.storeInorderTraversal();
        assert_eq!(updated_result, vec![20, 30, 40, 50, 60, 70, 80]);
    }

    #[test]
    fn test_duplicates() {
        let mut bst = BinarySearchTree::<i32>::new();

        // Insert values with duplicates
        bst.insert(50);
        bst.insert(30);
        bst.insert(30); // Duplicate
        bst.insert(20);

        // Get inorder traversal
        let result = bst.storeInorderTraversal();

        // Check the result (duplicates are ignored in this implementation)
        assert_eq!(result, vec![20, 30, 50]);
    }

    #[test]
    fn test_delete() {
        let mut bst = BinarySearchTree::<i32>::new();

        // Delete from empty tree
        bst.delete(10);
        assert!(bst.root.is_none());

        // Setup tree
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);

        // Delete leaf node
        bst.delete(20);
        assert!(!bst.search(20));
        assert_eq!(bst.storeInorderTraversal(), vec![30, 40, 50, 60, 70, 80]);

        // Delete node with one child
        bst.delete(30);
        assert!(!bst.search(30));
        assert_eq!(bst.storeInorderTraversal(), vec![40, 50, 60, 70, 80]);

        // Delete node with two children
        bst.delete(50);
        assert!(!bst.search(50));
        assert_eq!(bst.storeInorderTraversal(), vec![40, 60, 70, 80]);

        // Delete non-existent node
        bst.delete(100);
        assert_eq!(bst.storeInorderTraversal(), vec![40, 60, 70, 80]);
    }

    #[test]
    fn test_height() {
        let mut bst = BinarySearchTree::<i32>::new();

        // Empty tree
        assert_eq!(bst.height(), 0);

        // Single node
        bst.insert(50);
        assert_eq!(bst.height(), 1);

        // Two levels
        bst.insert(30);
        bst.insert(70);
        assert_eq!(bst.height(), 2);

        // Three levels
        bst.insert(20);
        assert_eq!(bst.height(), 3);

        // Unbalanced tree
        bst.insert(10);
        assert_eq!(bst.height(), 4);
    }

    #[test]
    fn test_is_balanced() {
        let mut bst = BinarySearchTree::<i32>::new();

        // Empty tree is balanced
        assert!(bst.is_balanced());

        // Single node is balanced
        bst.insert(50);
        assert!(bst.is_balanced());

        // Balanced tree with multiple levels
        bst.insert(30);
        bst.insert(70);
        assert!(bst.is_balanced());

        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);
        assert!(bst.is_balanced());

        // Create unbalanced tree
        let mut unbalanced_bst = BinarySearchTree::<i32>::new();
        unbalanced_bst.insert(50);
        unbalanced_bst.insert(40);
        unbalanced_bst.insert(30);
        unbalanced_bst.insert(20);
        unbalanced_bst.insert(10);

        assert!(!unbalanced_bst.is_balanced());
    }
}

// Simple main function for running the code
fn main() {
    let mut bst = BinarySearchTree::<i32>::new();

    println!("Inserting values: 50, 30, 70, 20, 40, 60, 80");
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    println!("Inorder traversal: {:?}", bst.storeInorderTraversal());
    println!("Tree height: {}", bst.height());
    println!("Is balanced: {}", bst.is_balanced());

    println!("Deleting 30...");
    bst.delete(30);
    println!(
        "Inorder traversal after deletion: {:?}",
        bst.storeInorderTraversal()
    );
}
