/*
二维零一背包
共kind_sz种物品 最多花费cost1_sz and cost2_sz
第i种物品花费cost1[i] and cost2[i] 贡献val[i] 最多拿1次
花费cost1[i] and cost2[j]最多得到f[i][j]的贡献
kind_sz:共kind_sz种物品
cost1_sz:第一种花费最多花费cost1_sz
cost2_sz:第二种花费最多花费cost2_sz
val[i]:第i件的贡献
f[i][j]:花费第一种i第二种j最多得到的贡献
Init(kind_sz,cost1_sz,cost2_sz):O(cost1_sz * cost2_sz)初始化
Build():O(kind_sz * cost1_sz * cost2_sz)跑DP得到f[][]
*/
template <ll KIND_SZ, ll COST1_SZ, ll COST2_SZ>
struct Pack
{
	ll kind_sz, cost1_sz, cost2_sz;
	ll cost1[KIND_SZ + 1], cost2[KIND_SZ + 1], val[KIND_SZ + 1];
	ll f[COST1_SZ + 1][COST2_SZ + 1];

	void Init(ll kind_sz, ll cost1_sz, ll cost2_sz)
	{
		this->kind_sz = kind_sz;
		this->cost1_sz = cost1_sz;
		this->cost2_sz = cost2_sz;
		FOR(i, 0, cost1_sz)
		FOR(j, 0, cost2_sz)
		f[i][j] = 0;
		return;
	}
	void Build(void)
	{
		FOR(i, 1, kind_sz)
		ROF(j, cost1_sz, cost1[i])
		ROF(k, cost2_sz, cost2[i])
		f[j][k] = max(f[j][k], f[j - cost1[i]][k - cost2[i]] + val[i]);
		return;
	}
};
Pack<SZ, SZ, SZ> pack;