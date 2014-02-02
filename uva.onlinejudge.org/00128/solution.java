class Main {
	public static void main(String[] args) throws java.io.IOException {
		java.io.BufferedReader in = new java.io.BufferedReader(new java.io.InputStreamReader(System.in));
		
		int divisor = 34943;
		java.math.BigInteger bigDivisor = java.math.BigInteger.valueOf(divisor);
		
		while (true)
		{
			String line = in.readLine();
			if (null == line || line.length() > 0 && '#' == line.charAt(0))
				break;
			
			int remainder = new java.math.BigInteger(1, line.getBytes()).shiftLeft(2 * 8).remainder(bigDivisor).intValue();
			int crc = 0 == remainder ? 0 : divisor - remainder;
			System.out.println(String.format("%02X %02X", (crc & 0xFF00) >> 8, crc & 0xFF));
		}
	}
}
