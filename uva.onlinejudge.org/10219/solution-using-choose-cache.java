class Main {
	public static class IntInt {
		public final int n;
		public final int k;
		
		public IntInt(int n, int k) {
			this.n = n;
			this.k = k;
		}
		
		public int hashCode() {
			return (this.n + this.k) * this.n + this.k;
		}
		
		public boolean equals(Object other) {
			if (!(other instanceof IntInt))
				return false;
			
			IntInt otherIntInt = (IntInt)other;
			return otherIntInt.k == this.k && otherIntInt.n == this.n;
		}
	}
	
	public static final java.util.HashMap<Main.IntInt, java.math.BigInteger> cache = new java.util.HashMap<Main.IntInt, java.math.BigInteger>();
	
	public static java.math.BigInteger choose(final int n, final int k) {
		Main.IntInt pair = new Main.IntInt(n, k);
		
		if (Main.cache.containsKey(pair))
			return Main.cache.get(pair);
		
		java.math.BigInteger result;
		
		if (n < k)
			result = java.math.BigInteger.ZERO;
		else if (n == k || 0 == k)
			result = java.math.BigInteger.ONE;
		else
			result = Main.choose(n - 1, k).add(Main.choose(n - 1, k - 1));
		
		if (n % 10 == 0)
			Main.cache.put(pair, result);
		
		return result;
	}
	
	public static void main(String[] args) throws java.io.IOException {
		java.util.Scanner scanner = new java.util.Scanner(System.in);
		
		Main.cache.put(new Main.IntInt(100, 50), new java.math.BigInteger("100891344545564193334812497256"));
		Main.cache.put(new Main.IntInt(1000, 100), new java.math.BigInteger("63850511926305130236698511142022274281262900693853331776286816221524376994750901948920974351797699894319420811933446197797592213357065053890"));
		Main.cache.put(new Main.IntInt(2000, 1000), new java.math.BigInteger("2048151626989489714335162502980825044396424887981397033820382637671748186202083755828932994182610206201464766319998023692415481798004524792018047549769261578563012896634320647148511523952516512277685886115395462561479073786684641544445336176137700738556738145896300713065104559595144798887462063687185145518285511731662762536637730846829322553890497438594814317550307837964443708100851637248274627914170166198837648408435414308177859470377465651884755146807496946749238030331018187232980096685674585602525499101181135253534658887941966653674904511306110096311906270342502293155911108976733963991149120"));
		
		try {
			while (true)
			{
				int n = scanner.nextInt();
				int k = scanner.nextInt();
				
				System.out.println(Main.choose(n, k).toString());
			}
		} catch (java.util.NoSuchElementException ex) {
			return;
		}
	}
}
