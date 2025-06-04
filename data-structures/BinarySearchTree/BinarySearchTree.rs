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
}

#[cfg(test)]
mod tests {
    use super::*;

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
    fn test_store_inorder_traversal_with_duplicates() {
        let mut bst = BinarySearchTree::<i32>::new();

        // Insert values with duplicates (if your BST handles duplicates)
        bst.insert(50);
        bst.insert(30);
        bst.insert(30); // Duplicate
        bst.insert(20);

        // Get inorder traversal
        let result = bst.storeInorderTraversal();

        // Check the result (depends on how your BST handles duplicates)
        // If duplicates are ignored:
        assert_eq!(result, vec![20, 30, 50]);
        // If duplicates are allowed (uncomment if your BST allows duplicates):
        // assert_eq!(result, vec![20, 30, 30, 50]);
    }
}
