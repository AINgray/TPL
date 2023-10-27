/*
完全背包
共kind_sz种物品 最多花费cost_sz
第i种物品花费cost[i] 贡献val[i] 可无限拿
花费i最多得到f[i]的贡献
kind_sz:共kind_sz种物品
cost_sz:最多花费cost_sz
cost[i]:第i件的花费
val[i]:第i件的贡献
f[i]:花费i最多得到的贡献
Init(kind_sz,cost_sz):O(cost_sz)初始化
Build():O(kind_sz * cost_sz)跑DP得到f[]
*/
template <ll KIND_SZ, ll COST_SZ>
struct Pack
{
	ll kind_sz, cost_sz;
	ll cost[KIND_SZ + 1], val[KIND_SZ + 1];
	ll f[COST_SZ + 1];
	void Init(ll kind_sz, ll cost_sz)
	{
		this->kind_sz = kind_sz;
		this->cost_sz = cost_sz;
		FOR(i, 0, cost_sz)
		f[i] = 0;
		return;
	}
	void Build(void)
	{
		FOR(i, 1, kind_sz)
		FOR(j, cost[i], cost_sz)
		f[j] = max(f[j], f[j - cost[i]] + val[i]);
		return;
	}
};
Pack<SZ, SZ> pack;