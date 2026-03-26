class Solution:
    # Assuming values in height can't be negative 
    def maxArea(self, height: List[int]) -> int:
        max_area = 0
        height_len = len(height)

        for i, h0 in enumerate(height):
            # Must avoid division by zero. max_area won't
            # be found with a 0 height anyway.
            if h0 == 0:
                continue

            skip = int(max_area / h0)
            # Given the remaining indices. Is it possible 
            # to get a bigger result with the current value of h0?
            if i + skip >= height_len:
                continue

            # Skip combination that can't produce larger areas 
            # than previously found
            for j, h1 in enumerate(height[i+skip:]):
                min_h = min(h0, h1)
                # Due to skip j if a smaller value 
                # than if we iterated from i
                area = min_h * (j + skip)
                if area > max_area:
                    max_area = area

        return max_area 
