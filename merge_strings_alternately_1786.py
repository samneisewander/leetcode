class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        word1 = list(word1)
        word2 = list(word2)
        combined = []
        while len(word1) > 0 and len(word2) > 0:
            combined += word1.pop(0) + word2.pop(0)
        combined += word1 if len(word1) > 0 else word2

        return ''.join(combined)

# best solution
class Solution:
    def mergeAlternately(self, word1: str, word2: str) -> str:
        merged = ""
        smallerLength = min(len(word1), len(word2))
        for i in range(smallerLength):
            merged = merged + word1[i]
            merged = merged + word2[i]
        # By slicing both strings, you only take the part you dont have from either string. clever!
        merged = merged + word1[smallerLength::]
        merged = merged + word2[smallerLength::]
        
        return merged