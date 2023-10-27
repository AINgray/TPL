// 字符串s(0,n-1)查询Ever(l,r)使得s[l,r]是回文串
// d1[i]：以位置i为中心长度为奇数的回文串个数/最长回文串的半径长度
// d2[i]：同上，但为偶数
vector<int> d1(n);
for (int i = 0, l = 0, r = -1; i < n; i++)
{
	int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
	while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
		k++;
	d1[i] = k--;
	if (i + k > r)
	{
		l = i - k;
		r = i + k;
	}
}
vector<int> d2(n);
for (int i = 0, l = 0, r = -1; i < n; i++)
{
	int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
	while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
		k++;
	d2[i] = k--;
	if (i + k > r)
	{
		l = i - k - 1;
		r = i + k;
	}
}