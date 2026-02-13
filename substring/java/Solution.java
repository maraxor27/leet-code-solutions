public class Solution {
	public static void main(String[] args) {
		switch (args[0]) {
		case "1":
			String test = "abac"; 
			System.out.println(test + ": " + solve(test));
		}

	}	

	public static int solve(String s) {
		boolean[] bitmap = new boolean[96];
		int start = 0, end = 0, best = 0;
		while (end < s.length()) {
			int end_c = ((int) s.charAt(end++)) - 32;
			if (!bitmap[end_c]) {
				bitmap[end_c] = true;
			} else {
				while (true) {
					int start_c = ((int) s.charAt(start++)) - 32;
					if (start_c != end_c) {
						bitmap[start_c] = false;
					} else {
						break;
					}
				}
			}

			if (end - start > best) {
				best = end - start;
			}
		} 
		return best;
	}
}