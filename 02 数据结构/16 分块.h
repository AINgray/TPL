template <ll SZ>
struct DivBlk
{
	ll sz;
	ll dt[SZ];
	ll blk_siz, blk_cnt, blk_rem;
	ll blk_sz[SZ];
	void Init(ll sz) { this->sz = sz; }
	void Build(void)
	{
		blk_siz = sqrt(sz + 1);
		blk_cnt = sz / blk_siz;
		blk_rem = sz % blk_siz;
		FOR(i, 1, blk_cnt)
		{
			blk_sz[i] = blk_siz;
			// 初始化blk[i]
		}
		blk_sz[++blk_cnt] = blk_rem;
		// 初始化blk[i]
		FOR(i, 1, sz)
		{
			ll id = AidToBLKid(i);
			// 维护blk[i]
		}
		return;
	}
	void Mdf(ll l, ll r, ll d)
	{
		ll l_id = AidToBLKid(l);
		ll r_id = AidToBLKid(r);
		// 暴力维护blk[l_id]
		FOR(i, l_id + 1, r_id - 1)
		// 整块维护blk[i]
		// 暴力维护blk[r_id]
		return;
	}
	void Qry(ll l, ll r)
	{
		ll l_id = AidToBLKid(l);
		ll r_id = AidToBLKid(r);
		// 暴力查询blk[l_id]
		FOR(i, l_id + 1, r_id - 1)
		// 整块查询blk[i]
		// 暴力查询blk[r_id]
		return;
	}
	ll AidToBLKid(ll id) { return (id + blk_siz - 1) / blk_siz; }
	PLL BLKidToARange(ll id)
	{
		PLL res;
		res.fi = (id - 1) * blk_siz + 1;
		res.se = res.fi + blk_sz[id] - 1;
		return res;
	}
};
DivBlk<SZ> divBlk;