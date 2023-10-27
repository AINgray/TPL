const int N = 20005;
int n, V, m;
int v[N], w[N], dp[1005][N], s[N];
int q[200005];
int rear, front;
int main()
{
	int i, j, k;
	cin >> n >> V;
	for (i = 1; i <= n; i++)
		cin >> v[i] >> w[i] >> s[i];
	// 利用单调队列
	for (i = 1; i <= n; i++)
		for (j = 0; j < v[i]; j++)
		{
			rear = front = 0;
			for (k = j; k <= V; k += v[i])
			{
				dp[i][k] = dp[i - 1][k];
				if ((k - q[front]) v[i] > s[i] && rear != front)
					front++;
				if (front != rear)
					dp[i][k] = max(dp[i][k], dp[i - 1][q[front]] + (k - q[front]) v[i] * w[i]);
				// 单调队列中直接维护dp[i][k]的值
				while (rear != front && dp[i - 1][q[rear - 1]] + (k - q[rear - 1]) v[i] * w[i] <= dp[i - 1][k])
					rear--;
				q[rear++] = k;
			}
		}
	cout << dp[n][V] << endl;
	return 0;
}