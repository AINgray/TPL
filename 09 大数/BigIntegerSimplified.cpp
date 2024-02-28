namespace BigIntegerSimplified
{
	template <ll SZ>
	struct BigInt
	{
		int num[SZ];
		int l;
		int sig;
		BigInt(long long n = 0)
		{
			memset(num, 0, sizeof(num));
			if (n)
			{
				l = 0;
				if (n < 0)
				{
					sig = 1;
					n *= -1;
				}
				else
					sig = 0;
				while (n)
				{
					num[++l] = n % 10;
					n /= 10;
				}
			}
			else
			{
				l = 1;
				sig = 0;
			}
		}
		BigInt(char s[])
		{
			char stk[SZ];
			int top = 0;
			int ls = strlen(s);
			int i = 0;
			l = 0;
			for (int i = 0; i < SZ; ++i)
				num[i] = 0;
			if (s[i] == '-')
			{
				sig = 1;
				++i;
			}
			else if (s[i] == '+')
			{
				sig = 0;
				++i;
			}
			else
				sig = 0;
			for (; i < ls; ++i)
				stk[++top] = s[i];
			while (top)
				num[++l] = stk[top--] - '0';
			while (num[l] == 0 && l > 1)
				--l;
		}
	};

	bool operator<(BigInt a, BigInt b);
	bool operator>(BigInt a, BigInt b);
	bool operator==(BigInt a, BigInt b);
	bool operator!=(BigInt a, BigInt b);
	bool operator>=(BigInt a, BigInt b);
	bool operator<=(BigInt a, BigInt b);
	BigInt operator+(BigInt a, BigInt b);
	BigInt operator-(BigInt a, BigInt b);
	BigInt operator*(BigInt a, BigInt b);
	BigInt operator/(BigInt a, BigInt b);
	BigInt operator%(BigInt a, BigInt b);
	BigInt bigabs(BigInt a);
	istream &operator>>(istream &in, BigInt &a);
	ostream &operator<<(ostream &in, BigInt a);

	bool operator<(BigInt a, BigInt b)
	{
		if (a.sig ^ b.sig)
			return a.sig ? true : false;
		if (a.sig)
			return bigabs(a) > bigabs(b);
		if (a.l != b.l)
			return a.l < b.l;
		for (int i = a.l; i; --i)
			if (a.num[i] != b.num[i])
				return a.num[i] < b.num[i];
		return false;
	}
	bool operator>(BigInt a, BigInt b)
	{
		if (a.sig ^ b.sig)
			return a.sig ? false : true;
		if (a.sig)
			return bigabs(a) < bigabs(b);
		if (a.l != b.l)
			return a.l > b.l;
		for (int i = a.l; i; --i)
			if (a.num[i] != b.num[i])
				return a.num[i] > b.num[i];
		return false;
	}
	bool operator>=(BigInt a, BigInt b) { return !(a < b); }
	bool operator<=(BigInt a, BigInt b) { return !(a > b); }
	bool operator==(BigInt a, BigInt b)
	{
		if (a.sig != b.sig || a.l != b.l)
			return false;
		for (int i = a.l; i; --i)
			if (a.num[i] != b.num[i])
				return false;
		return true;
	}
	bool operator!=(BigInt a, BigInt b) { return !(a == b); }
	BigInt operator+(BigInt a, BigInt b)
	{
		if (a.sig ^ b.sig)
		{
			if (a.sig)
			{
				a.sig ^= 1;
				return b - a;
			}
			else
			{
				b.sig ^= 1;
				return a - b;
			}
		}
		a.l = max(a.l, b.l) + 1;
		for (int i = 1; i <= a.l; i++)
		{
			a.num[i] += b.num[i];
			if (a.num[i] >= 10)
			{
				a.num[i + 1] += a.num[i] / 10;
				a.num[i] %= 10;
			}
		}
		while (a.num[a.l] == 0 && a.l > 1)
			--a.l;
		return a;
	}
	BigInt operator-(BigInt a, BigInt b)
	{
		if (a.sig ^ b.sig)
		{
			b.sig ^= 1;
			return a + b;
		}
		if (bigabs(b) > bigabs(a))
		{
			BigInt c = b - a;
			c.sig ^= 1;
			return c;
		}
		a.l = max(a.l, b.l);
		for (int i = 1; i <= a.l; i++)
		{
			a.num[i] -= b.num[i];
			if (a.num[i] < 0)
			{
				a.num[i] += 10;
				a.num[i + 1] -= 1;
			}
		}
		while (a.num[a.l] == 0 && a.l > 1)
			--a.l;
		if (a.l == 1 && a.num[1] == 0)
			a.sig = 0;
		return a;
	}
	BigInt operator*(BigInt a, BigInt b)
	{
		BigInt c;
		c.l = a.l + b.l;
		c.sig = a.sig ^ b.sig;
		for (int i = 1; i <= a.l; ++i)
			for (int j = 1; j <= b.l; ++j)
				c.num[i + j - 1] += a.num[i] * b.num[j];
		for (int i = 1; i <= c.l; ++i)
			if (c.num[i] >= 10)
			{
				c.num[i + 1] += c.num[i] / 10;
				c.num[i] %= 10;
			}
		while (c.num[c.l] == 0 && c.l > 1)
			--c.l;
		if (c.l == 1 && c.num[1] == 0)
			c.sig = 0;
		return c;
	}
	BigInt operator/(BigInt a, BigInt b)
	{
		BigInt c, d, ten = BigInt(10LL);
		c.sig = a.sig ^ b.sig;
		b.sig = 0;
		c.l = a.l;
		for (int i = a.l; i >= 1; --i)
		{
			d = d * ten;
			d.num[1] = a.num[i];
			while (d >= b)
			{
				d = d - b;
				++c.num[i];
			}
		}
		while (c.num[c.l] == 0 && c.l > 1)
			--c.l;
		if (c.l == 1 && c.num[1] == 0)
			c.sig = 0;
		return c;
	}
	BigInt operator%(BigInt a, BigInt b)
	{
		BigInt c, d, ten = BigInt(10LL);
		b.sig = 0;
		c.l = a.l;
		for (int i = a.l; i >= 1; --i)
		{
			d = d * ten;
			d.num[1] = a.num[i];
			while (d >= b)
			{
				d = d - b;
				++c.num[i];
			}
		}
		d.sig = a.sig;
		while (d.num[d.l] == 0 && d.l > 1)
			--d.l;
		if (d.l == 1 && d.num[1] == 0)
			d.sig = 0;
		return d;
	}
	BigInt bigabs(BigInt a)
	{
		a.sig = 0;
		return a;
	}
	ostream &operator<<(ostream &o, BigInt a)
	{
		if (a.sig)
			o << '-';
		std::string s;
		for (int i = a.l; i; --i)
			s += a.num[i] + '0';
		o << s;
		return o;
	}
	istream &operator>>(istream &i, BigInt &a)
	{
		std::string s;
		i >> s;
		a = BigInt(s.data());
		if (a.l == 1 && a.num[1] == 0)
			a.sig = 0;
		return i;
	}
}
using namespace BigIntegerSimplified;