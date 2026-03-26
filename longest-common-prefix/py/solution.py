class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        reference = strs[0]
        common = len(strs[0])

        for s in strs[1:]:
            i = 0
            
            min_common = min(common, len(s))

            if min_common < common:
                common = min_common

            for cr in reference[:common]:
                if cr != s[i]:
                    common = i
                    break
                i += 1
        
        return reference[:common]
        
