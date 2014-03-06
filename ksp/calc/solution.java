import java.util.Scanner;

public class calc {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		
		for (int i = 0; i < n; ++i)
		{
			int a = scan.nextInt();
			String op = scan.next();
			int b = scan.nextInt();
			int result = 0;
			
			if ("+".equals(op))
					result = a + b;
			else if ("-".equals(op))
				result = a - b;
			else if ("*".equals(op))
				result = a * b;
			
			System.out.println(result);
		}
	}
}
