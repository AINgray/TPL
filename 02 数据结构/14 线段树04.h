/*
线段树04
区间覆盖 区间查询F值
NUL_LAZY:空LAZY值
NUL_QRY:空查询值 F=max时NUL_QRY=-INF F=min时NUL_QRY=INF
F(lh,rh):F可以是max/min
sz:当前大小
dt[1 ~ sz]:初始数据容器
Init(sz):O(N)初始化
Build():O(NlogN)建树
Cov(l,r,v):O(logN)使a[l ~ r]=v
Qry(l,r):O(logN)查询F(l ~ r)
*/
template <ll SZ>
struct SGT
{
#define LS (id << 1)
#define RS (id << 1 | 1)
public:
	static constexpr ll NUL_LAZY = -114514;
	static constexpr ll NUL_QRY = -INF;
	ll F(const ll &lh, const ll &rh) const { return std::max(lh, rh); }
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
	void Cov(ll l, ll r, ll v) { Cov(l, r, v, 1, 1, sz); }
	ll Qry(ll l, ll r) { return Qry(l, r, 1, 1, sz); }

protected:
	ll f[SZ << 2 | 1];
	ll lz[SZ << 2 | 1];
	void PushUp(ll id) { f[id] = F(f[LS], f[RS]); }
	void PushDw(ll id, ll l, ll r)
	{
		if (lz[id] == NUL_LAZY)
			return;
		ll md = (l + r) >> 1;
		lz[LS] = lz[RS] = lz[id];
		f[LS] = f[RS] = lz[id];
		lz[id] = NUL_LAZY;
		return;
	}
	void Build(ll id, ll l, ll r)
	{
		lz[id] = NUL_LAZY;
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
	void Cov(ll l, ll r, ll v, ll id, ll id_l, ll id_r)
	{
		if (l <= id_l and id_r <= r)
		{
			lz[id] = v;
			f[id] = v;
			return;
		}
		PushDw(id, id_l, id_r);
		ll md = (id_l + id_r) >> 1;
		if (l <= md)
			Cov(l, r, v, LS, id_l, md);
		if (md < r)
			Cov(l, r, v, RS, md + 1, id_r);
		PushUp(id);
		return;
	}
	ll Qry(ll l, ll r, ll id, ll id_l, ll id_r)
	{
		if (l <= id_l and id_r <= r)
			return f[id];
		PushDw(id, id_l, id_r);
		ll res = NUL_QRY;
		ll md = (id_l + id_r) >> 1;
		if (l <= md)
			res = F(res, Qry(l, r, LS, id_l, md));
		if (md < r)
			res = F(res, Qry(l, r, RS, md + 1, id_r));
		return res;
	}
#undef LS
#undef RS
};
SGT<SZ> sgt;