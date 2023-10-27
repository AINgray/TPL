int id[N], scc_cnt, sz[N];
int dfn[N], low[N], timestamp;
int n, m;
int cnt[N];
void tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++timestamp;
	int child = 0;
	for (int i = h[u]; ~i; i = ne[i])
	{
		int j = e[i];
		if (!dfn[j])
		{
			tarjan(j, u);
			low[u] = min(low[u], low[j]);
			if (low[j] >= dfn[u] && u != fa)
				cnt[u] = 1;
			if (u == fa)
				child++;
		}
		else
			low[u] = min(low[u], dfn[j]);
	}
	if (child >= 2 && u == fa)
		cnt[u] = 1;
	//    if(cnt[i]) 是割点
}