class Solution:
    class Result:
        OFFSET = 10**5
        def __init__(self, x, y, z):
            self.values = [x, y, z]
            self.values.sort()
            e_0 = self.values[0] + self.OFFSET
            e_1 = self.values[1] + self.OFFSET
            e_2 = self.values[2] + self.OFFSET
            self.encoded = e_0 + (e_1 << 18) + (e_2 << 36)
        
        def __eq__(self, other):
            return self.encoded == other.encoded

        def __hash__(self):
            return self.encoded

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        results: set[self.Result] = set()
        lookup_dictionary: dict[int, int] = {}

        for num in nums:
            if lookup_dictionary.get(num) != None:
                lookup_dictionary[num] += 1
            else:
                lookup_dictionary[num] = 1
        
        for x, count_x in lookup_dictionary.items():

            if x == 0 and count_x >= 3:
                results.add(self.Result(0, 0, 0))
            
            # Lets find combination where all number are different
            for y, count_y in lookup_dictionary.items():
                if x == y:
                    continue

                z = -(x + y)
                if count_z := lookup_dictionary.get(z):
                    if z == x or z == y:
                        continue

                    results.add(self.Result(x, y, z))

            # Lets find combination where two numbers are the same               
            if count_x >= 2:
                y = x
                z = -(x + y)

                if lookup_dictionary.get(z) != None:
                    if z == x:
                        continue
                    
                    results.add(self.Result(x, y, z))
    
        return [ result.values for result in results ]       
