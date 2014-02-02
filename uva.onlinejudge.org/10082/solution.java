import java.util.Map;
import java.util.HashMap;

class Main {
	public static void main(String[] args) throws java.io.IOException {
		java.io.BufferedReader in = new java.io.BufferedReader(new java.io.InputStreamReader(System.in));
		
		while (true)
		{
			String line = in.readLine();
			if (null == line)
				break;
			
			int len = line.length();
			for (int p = 0; p < len; p++)
				System.out.print(table.get(line.charAt(p)));
			System.out.println();
		}
	}
	
	private static Map<Character, Character> table = new HashMap<Character, Character>() { {
		this.put(' ',  ' ');
		this.put('`',  null);
		this.put('1',  '`');
		this.put('2',  '1');
		this.put('3',  '2');
		this.put('4',  '3');
		this.put('5',  '4');
		this.put('6',  '5');
		this.put('7',  '6');
		this.put('8',  '7');
		this.put('9',  '8');
		this.put('0',  '9');
		this.put('-',  '0');
		this.put('=',  '-');
		this.put('Q',  null);
		this.put('W',  'Q');
		this.put('E',  'W');
		this.put('R',  'E');
		this.put('T',  'R');
		this.put('Y',  'T');
		this.put('U',  'Y');
		this.put('I',  'U');
		this.put('O',  'I');
		this.put('P',  'O');
		this.put('[',  'P');
		this.put(']',  '[');
		this.put('\\', ']');
		this.put('A',  null);
		this.put('S',  'A');
		this.put('D',  'S');
		this.put('F',  'D');
		this.put('G',  'F');
		this.put('H',  'G');
		this.put('J',  'H');
		this.put('K',  'J');
		this.put('L',  'K');
		this.put(';',  'L');
		this.put('\'', ';');
		this.put('Z',  null);
		this.put('X',  'Z');
		this.put('C',  'X');
		this.put('V',  'C');
		this.put('B',  'V');
		this.put('N',  'B');
		this.put('M',  'N');
		this.put(',',  'M');
		this.put('.',  ',');
		this.put('/',  '.');
	} };
}
