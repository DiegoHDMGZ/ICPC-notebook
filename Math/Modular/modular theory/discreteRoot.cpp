	
	
	(x ^ k) % mod = r
	Suppose we know primitve root of mod = g
	( (g ^ y ) ^ k )  % mod = r
	( (g ^ k ) ^ y ) % mod = r
	We find y by discreteLog and then answer is g ^ y
