import unittest
import time

# Sample functions that should return the same result
class Solution1:
    # Some computation...
    def shortestCommonSupersequence(self, str1: str, str2: str) -> str:
        # recusive function
        def recursion(str1: str, str2: str) -> str:
            if len(str1) == 0:
                return str2

            if len(str2) == 0:
                return str1

            if str1[0] == str2[0]:
                return str1[0] + recursion(str1[1:], str2[1:])
            else:
                tmp1 = str1[0] + recursion(str1[1:], str2)
                tmp2 = str2[0] + recursion(str1, str2[1:])
                return tmp1 if len(tmp1) < len(tmp2) else tmp2

        return recursion(str1, str2)

class Solution2:
    # Another implementation...
    def shortestCommonSupersequence(self, str1: str, str2: str) -> str:
        memo = {}

        # recusive function
        def recursion(str1: str, str2: str, memo: dict) -> str:
            memo_key = str1 + " " + str2
            if memo.get(memo_key) != None:
                return memo.get(memo_key)

            if len(str1) == 0:
                return str2

            if len(str2) == 0:
                return str1

            if str1[0] == str2[0]:
                result = str1[0] + recursion(str1[1:], str2[1:], memo)
                memo[memo_key] = result
                return result
            else:
                tmp1 = str1[0] + recursion(str1[1:], str2, memo)
                tmp2 = str2[0] + recursion(str1, str2[1:], memo)
                result = tmp1 if len(tmp1) < len(tmp2) else tmp2
                memo[memo_key] = result
                return result

        return recursion(str1, str2, memo)

class Solution3:
    # Yet another implementation...
    def shortestCommonSupersequence(self, str1: str, str2: str) -> str:

        return

class TestFunctions(unittest.TestCase):
    def setUp(self):
        # Dictionary of functions to test: keys are function names.
        self.classes = {
            'Solution 1': Solution1,
            'Solution 2': Solution2
        }

    def _test_helper(self, str1: str, str2: str, expected_result: str) -> str:
        # Loop over each function and test its output and measure execution time.
        for name, cl in self.classes.items():
            with self.subTest(func=name):
                start_time = time.time()
                solution = cl()
                result = solution.shortestCommonSupersequence(str1, str2)
                end_time = time.time()
                execution_time = end_time - start_time
                print(f"\n{name} execution time: {execution_time:.6f} seconds")
                self.assertEqual(result, expected_result)

    def test_leetcode_testcases_case_1(self):
        str1 = "abac"
        str2 = "cab"
        expected_result = "cabac"
        self._test_helper(str1, str2, expected_result)

    def test_leetcode_testcases_case_2(self):
        str1 = "aaaaaaaa"
        str2 = "aaaaaaaa"
        expected_result = "aaaaaaaa"
        self._test_helper(str1, str2, expected_result)

if __name__ == '__main__':
    unittest.main()
