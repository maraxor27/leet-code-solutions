class Solution:
    def isValid(self, s: str) -> bool:
        state = []
        for c in s:
            match c:
                case '[' | '{' | '(':
                    state.append(c)
                case ']':
                    if len(state) == 0 or state.pop() != '[':
                        return False
                case '}':
                    if len(state) == 0 or state.pop() != '{':
                        return False
                case ')':
                    if len(state) == 0 or state.pop() != '(':
                        return False
        return len(state) == 0
