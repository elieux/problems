import java.util.Scanner;

public class calc {
	private static int compute(int a, String op, int b) {
		if ("+".equals(op))
			return a + b;
		if ("-".equals(op))
			return a - b;
		if ("*".equals(op))
			return a * b;
		
		throw new RuntimeException();
	}
	
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		
		for (int i = 0; i < n; ++i)
		{
			int a = scan.nextInt();
			String op = scan.next();
			int b = scan.nextInt();
			
			System.out.println(compute(a, op, b));
		}
	}
}
