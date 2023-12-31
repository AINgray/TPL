/*
	z[i]=s[0,n-1] and s[i,n-1]的LCP(最长公共前缀）的长度
	z[0]=0
*/
vector<int> z_function(string s)
{
	int n = (int)s.length();
	vector<int> z(n);
	for (int i = 1, l = 0, r = 0; i < n; ++i)
	{
		if (i <= r && z[i - l] < r - i + 1)
			z[i] = z[i - l];
		else
		{
			z[i] = max(0, r - i + 1);
			while (i + z[i] < n && s[z[i]] == s[i + z[i]])
				++z[i];
		}
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}