class Solution:
    # Assuming values in height can't be negative 
    def maxArea(self, height: List[int]) -> int:
        max_area = 0

        i = 0
        j = len(height) - 1
        while i < j:
            i_h = height[i]
            j_h = height[j]
            d = j - i
            h = min(i_h, j_h)
            area = d * h
            
            if max_area < area:
                max_area = area
            
            # This is fine since the minimum of the height is always used
            if i_h > j_h:
                j -= 1
            else:
                i += 1
            
        return max_area

