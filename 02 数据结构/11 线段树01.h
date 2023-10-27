/*
线段树01
区间修改 区间查询和
NUL:空Lazy值
sz:当前大小
dt[1 ~ sz]:初始数据容器
Init(sz):O(N)初始化
Build():O(NlogN)建树
Mdf(l,r,d):O(logN)使a[l ~ r]+=d
Qry(l,r):O(logN)查询Sum(l ~ r)
*/
template <ll SZ>
struct SGT
{
#define LS (id << 1)
#define RS (id << 1 | 1)
public:
	static constexpr ll NUL = 0;
	ll sz;
	ll dt[SZ + 1];
	void Init(ll sz)
	{
		this->sz = sz;
		FOR(i, 0, sz)
		dt[i] = 0;
		return;
	}
	void Build(void) { Build(1, 1, sz); }
	void Mdf(ll l, ll r, ll d) { Mdf(l, r, d, 1, 1, sz); }
	ll Qry(ll l, ll r) { return Qry(l, r, 1, 1, sz); }

protected:
	ll f[SZ << 2 | 1];
	ll lz[SZ << 2 | 1];
	void PushUp(ll id) { f[id] = f[LS] + f[RS]; }
	void PushDw(ll id, ll l, ll r)
	{
		if (lz[id] == NUL)
			return;
		ll md = (l + r) >> 1;
		lz[LS] += lz[id];
		lz[RS] += lz[id];
		f[LS] += (md - l + 1) * lz[id];
		f[RS] += (r - md) * lz[id];
		lz[id] = NUL;
		return;
	}
	void Build(ll id, ll l, ll r)
	{
		lz[id] = NUL;
		if (l == r)
		{
			f[id] = dt[l];
			return;
		}
		ll md = (l + r) >> 1;
		Build(LS, l, md);
		Build(RS, md + 1, r);
		PushUp(id);
		return;
	}
	void Mdf(ll l, ll r, ll d, ll id, ll id_l, ll id_r)
	{
		if (l <= id_l and id_r <= r)
		{
			lz[id] += d;
			f[id] += (id_r - id_l + 1) * d;
			return;
		}
		PushDw(id, id_l, id_r);
		ll md = (id_l + id_r) >> 1;
		if (l <= md)
			Mdf(l, r, d, LS, id_l, md);
		if (md < r)
			Mdf(l, r, d, RS, md + 1, id_r);
		PushUp(id);
		return;
	}
	ll Qry(ll l, ll r, ll id, ll id_l, ll id_r)
	{
		if (l <= id_l and id_r <= r)
			return f[id];
		PushDw(id, id_l, id_r);
		ll res = 0;
		ll md = (id_l + id_r) >> 1;
		if (l <= md)
			res += Qry(l, r, LS, id_l, md);
		if (md < r)
			res += Qry(l, r, RS, md + 1, id_r);
		return res;
	}
#undef LS
#undef RS
};
SGT<SZ> sgt;