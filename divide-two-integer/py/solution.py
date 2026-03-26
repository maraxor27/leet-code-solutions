class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        result = 0
        sign = 1
        
        if dividend < 0:
            dividend = -dividend
            sign = -sign
        
        if divisor < 0:
            divisor = -divisor
            sign = -sign

        while dividend >= divisor:
            multiple = 0
            while dividend >= (divisor << multiple + 1):
                multiple += 1
        
            dividend -= (divisor << multiple)
            result += (1 << multiple)
        
        result = result * sign

        if result > 2**31 - 1:
            result = 2**31 - 1
        elif result < -(2**31):
            result = -(2**31)

        return result
