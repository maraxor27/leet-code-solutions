class Solution:
    roman_lookup_table = [
        ["", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"],
        ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"],
        ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"],
        ["", "M", "MM", "MMM", None, None, None, None, None, None, None],
    ]

    def intToRoman(self, num: int) -> str:
        roman_buffer = ""

        num_s = str(num)

        i = len(num_s) - 1
        for c in num_s:
            d = int(c)
            digits = self.roman_lookup_table[i]
            roman_buffer += digits[int(c)]
            i -= 1

        return roman_buffer


        
