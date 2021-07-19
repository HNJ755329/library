# Typical DP Contest (Atcoder) をすべて解く

- [Typical DP Contest](https://atcoder.jp/contests/tdpc)

動的計画法 (Dynamic Programming, DP) の練習をすることを目的として作られたTypical DP Contestを解いていく.すべて解くと書いてるけど,すべて解きません.(今はまだ解けません)
解けた問題にチェックを入れていく.

- [x] A.コンテスト
- [x] B.ゲーム
- [x] C.トーナメント
- [x] D.サイコロ
- [x] E.数
- [x] F.準急
- [x] G.辞書順
- [x] H.ナップザック
- [x] I.イウィ
- [x] J.ボール
- [x] K.ターゲット
- [x] L.猫
- [x] M.家
- [ ] N.木
- [ ] O.文字列
- [ ] P.うなぎ
- [ ] Q.連結
- [ ] R.グラフ
- [ ] S.マス目
- [x] T.フィボナッチ

本質的と思われる部分以外のコードは省略しているので,そのままコピペしても動かないので注意. ~~C++14に準拠.~~ C++17に準拠.
DPコンテストなのにDP使用してない率高い気がする.結局,再帰メモ化に頼ってしまう.

## 2020/11/25 追記

- G,Kの解説を追加.

## TODO(open)

- 解いてない問題を解く.
- 解いた問題も推敲する.

## A.コンテスト

$N$問の問題があるコンテストがあり,$i$問目の問題の配点は$p_i$点.解いた問題の配点の合計が得点となる.
得点は何通り考えられるか.

### A.制約

```math
1 \leq N \leq 100\\
1 \leq p_i \leq 100
```

### A.解説

あまりにも有名な部分和問題.簡単なので省略.

## B.ゲーム

二人がゲームをしている.2つの山がある.

- 左の山には$A$個のものが積まれており,上から$i$番目のものの価値は$a_i$.
- 右の山には$B$個のものが積まれており,上から$i$番目のものの価値は$b_i$.

次の操作を交互に繰り返す.

- 両方の山が空であれば,ゲームを終了する.
- 片方の山が空であれば,空でないほうの山の一番上のものをとる.
- 両方の山が空でなければ,好きな方の山を選び,一番上のものをとる.

両者が最善を尽くしたとき,先攻がとるものの価値の合計を求めよ.

### B.制約

```math
1 \leq A, B \leq 100\\
1 \leq a_i, b_i \leq 100
```

### B.解説

左の山から$i$個,右の山から$j$個取ったあとから先攻,後攻の獲得できるものの価値を表す再帰関数を作る.
いい感じに条件を分岐させれば作れる.計算量が気になるのでメモ化する.
$i+j$の偶奇で条件を分岐させ,一つの再帰関数することもできたが,関数内の分岐がわちゃわちゃするので二つに分けた.
（DPを直接計算するにはループの順番が気になりすぎて怖い.）

```cpp
pair<int, int> recF(int i=0, int j=0);
pair<int, int> recS(int i=0, int j=0);

pair<int, int> recF(int i, int j){
    if(used[i][j]) return memo[i][j];
    used[i][j] = true;
    pair<int, int> ret;
    if(i>=a && j>=b) return {0,0};
    else if(i>=a){
        ret = recS(i,j+1);
        ret.first += B[j];
    }
    else if(j>=b){
        ret = recS(i+1,j);
        ret.first += A[i];
    }
    else{
        pair<int, int> la = recS(i+1,j);
        la.first += A[i];
        pair<int, int> rb = recS(i,j+1);
        rb.first += B[j];
        if(la.first>rb.first) ret=la;
        else ret=rb;
        }
    return memo[i][j] = ret;
}

pair<int, int> recS(int i, int j){
    if(used[i][j]) return memo[i][j];
    used[i][j] = true;
    pair<int, int> ret;
    if(i>=a && j>=b) return {0,0};
    else if(i>=a){
        ret = recF(i,j+1);
        ret.second += B[j];
    }
    else if(j>=b){
        ret = recF(i+1,j);
        ret.second += A[i];
    }
    else{
        pair<int, int> la = recF(i+1,j);
        la.second += A[i];
        pair<int, int> rb = recF(i,j+1);
        rb.second += B[j];
        if(la.second>rb.second) ret=la;
        else ret=rb;
        }
    return memo[i][j] = ret;
}

int ans = recF().first;
```

「後攻の手番では,先攻の得点を最小化する」とかの読み替えをしてない分,愚直な,長いコードになった.それぞれの再帰関数内では先攻,後攻ともに自らの得点を最大化している.

## C.トーナメント

$2^K$人が参加するトーナメントがある.人$i$の優勝確率を求めよ.
ただし,レートが$R_i$の人$i$がレート$R_j$の人$j$に勝つ確率は$1/(1+10^{(R_i-R_j)/400})$とする.

### C.制約

```math
1 \leq K \leq 10\\
1 \leq R_i \leq 4000
```

### C.解説・コメント

勝率の計算をミスってWA.原因究明に時間ロス.小数点の扱いはホンマ注意せんと.

```math
Win(i,k) = (人iが第kラウンドで勝つ確率)
```

とする.

```math
「人iが第kラウンドで勝つ\Leftrightarrow人iが第k-1ラウンドまで勝ちすすめ,さらに第kラウンドで勝つ」
```

と読み替えると,次の再帰関係が成り立つ.

```math
Win(i,k) = (人iが第kラウンドで勝つ確率) \\
= (人iが第(k-1)ラウンドで勝つ確率)\times \sum_j(人iが人jに勝つ確率)\times(人jが第(k-1)ラウンドで勝つ確率) \\
= Win(i,k-1)\sum_j p_{ij}Win(j,k-1);
```

ただし,$p_{ij}$は人$i$が人$j$に勝つ確率,人$j$は人$i$が第$k$ラウンドで戦う可能性のある人すべて,とする.

```cpp
// 答えがあわなくて30分ぐらいまよった.結局(double)のつけ忘れ.
double Pij(int p, int q){
    return 1.0/(1+pow(10,(double)(R[q]-R[p])/400) );
}

// iがk回戦目までで当たる可能性のある人物すべて
vector<int> AllMatcedhMemo[2000][20];
vector<int> AllMatched(int i, int k){
    if(k==0) return {i};
    if(!AllMatcedhMemo[i][k].empty()) return AllMatcedhMemo[i][k];
    int j=0;
    vector<int> ret;
    while(!(j<=i && i<(j+(1<<k)) )) j+=(1<<k);
    for (int mat = j; mat < (j+(1<<k)); mat++) ret.push_back(mat);
    return AllMatcedhMemo[i][k] = ret;
}

// iがちょうどk回戦目で当たる可能性のある人物すべて
vector<int> MatchMemo[2000][20];
vector<int> Match(int i, int k){
    if(k==0) return {i};
    if(!MatchMemo[i][k].empty()) return MatchMemo[i][k];
    int j=0;
    vector<int> ret;
    vector<int> Match = AllMatched(i,k);
    vector<int> alreadyMatched = AllMatched(i,k-1);
    int idx_init = Match[0];
    int idx_last = Match.back();
    int already_left = alreadyMatched[0];
    int already_right = alreadyMatched.back();
    for (int mat = idx_init; mat <= idx_last; mat++)
    {
        if(already_left<=mat && mat<=already_right) continue;
        if(mat==i) continue;
        ret.push_back(mat);
    }
    return MatchMemo[i][k] = ret;
}

double Win(int i, int k){
    if(seen[i][k]) return winMemo[i][k];
    if(k==0) return winMemo[i][k] = 1;
    double ret = 0;
    auto v = Match(i,k);
    for(int j:v) ret += Win(j,k-1)*Pij(i,j);
    ret *= Win(i,k-1);
    seen[i][k] = true;
    return winMemo[i][k] = ret;
}

for (int i = 0; i < (1<<K); i++)
{
    cout << fixed << setprecision(10) << Win(i,K) << endl;
}
```

ただし,

```math
(人iがちょうど第kラウンドで戦う可能性のある人) \\
=(人iが第kラウンドまでで戦う可能性のある人)-(人iが第k-1ラウンドまでで戦う可能性のある人)
```

の関係を利用して求めた.

## D.サイコロ

サイコロを $N$ 回振ったとき,出た目の積が $D$ の倍数となる確率を求めよ.

### D.制約

```math
1 \leq N \leq 100\\
1 \leq D \leq 10^{18}
```

### D.解説・コメント

まず,Dを素因数分解して7以上の素数を持つ場合,1〜6の積で表せないので,Dの倍数となる確率は0.
かけた数たちを保存していくと大きな数になりすぎるので,mod D上で考える.mod D上で積が0になる確率を求めれば良い.

```math
dp[i][d] = (サイコロをi回振って積がdとなる確率)
```

としてDPを解く.

```cpp
bool isDividedDice(ll n) {
  for(int i = 6; i >= 2; i--) {
    while(n % i == 0) {n /= i;}
  }
  if(n!=1) return false;
  return true;
}

int solve(){
  if(!isDividedDice(D)){cout << 0 << endl; return 0;}
  vector<unordered_map<ll,double> > dp(N+10);
  dp[0][1] = 1.0;
  for (int i = 0; i < N; i++)
  {
    for(auto dice:dp[i]){
      ll d = dice.first;
      if(d==0) {dp[i+1][0] += dice.second; continue;}
      else{
        for (int k = 1; k <= 6; k++)
        {
          dp[i+1][(d*k)%D] += (double)dice.second/6.0;
        }
      }
    }
    dp[i].clear();
  }
  cout << fixed << setprecision(10) << dp[N][0] << endl;
  
  return 0;
}
```

## E.数

$N$ 以下の正整数であって,十進法表記した時の各桁の和が $D$ の倍数であるものの個数をmod $(10^9+7)$ で求めよ.

### E.制約

```math
1 \leq N \leq 10^{10000} \\
1 \leq D \leq 100
```

### E.解説・コメント

桁DP. $N$ は文字列として受け取る.典型的すぎるので解説はしない.

```cpp
int m = N.length();
vector<vector<vector<modint> > > dp(m+1,vector<vector<modint>>(D+1,vector<modint>(3,0)));
dp[0][0][0] = 1;
for (int i = 0; i < m; i++)
  for (int d = 0; d < D; d++)
  {
      dp[i+1][(d+N[i]-'0')%D][0] += dp[i][d][0];
      for (int k = 0; k < 10; k++)
      {
          if(k<N[i]-'0') dp[i+1][(d+k)%D][1] += dp[i][d][0];
          dp[i+1][(d+k)%D][1] += dp[i][d][1];
      }
  }
int Remainder = 0;
modint ans = dp[m][Remainder][false] + dp[m][Remainder][true] - 1;
```

## F.準急

ある路線には $N$ 個の駅がある.この路線に準急を走らせる.

- 駅 $1$ に止まり,駅 $2$ 〜駅 $(N-1)$ の部分集合に止まり,駅 $N$ に止まる
- 連続する $K$ 個以上の駅には止まらない.

準急の停車駅の組み合わせとして何通り考えられるか.mod $10^9+7$で求めよ.

### F.制約

```math
2 \leq K \leq N \leq 10^6
```

### F.解説・コメント

駅 $i$ までで連続何個の駅に止まったかを管理しながらループを回せばいい.

```math
dp[i][k] = 駅iから左に連続するk個の駅に止まる組み合わせ.ただしk=0は駅iには止まらないことを表す.
```

とすると次の漸化式を満たす.

```math
dp[i+1][k+1] = dp[i][k] \\
dp[i+1][0] = \sum_{j=0}^{K-1} dp[i][j];
```

ただこれだと $O(KN)$ かかりそうなのでもう少し構造をみる.
$d[i][0]$ の更新に必要な合計は別途取り出して,dequeを使えば $O(1)$ で計算できそう.

dequeを使った更新のイメージ.
sumをdequeの先頭にpushする.停車数K-1の組み合わせをpopして,sumから引く.
各更新が$O(1)$でできるので,$O(N)$で答えが求まる.
最終的な$sum-dp[N][0]$が求める答え.

|停車駅数＼駅|  1   | 2 | $\cdots$ | N |
| :----:   |:----:|:----: |:----: |:----: |
|  0       |   0  | $\nearrow$ 1=sum |  $\cdots$ | dp[N][0] |
|  1       |   1  | $\searrow$ 0=dp[0][0] |  $\cdots$ | dp[N][1] |
|  2       |   0  | $\searrow$ 1=dp[0][1] |  $\cdots$ | dp[N][2] |
|$\vdots$  |$\vdots$  | $\vdots$ |  $\ddots$ | $\vdots$ |
|  K-1     |   0  | $\searrow$ 0=dp[0][K-2] |  $\cdots$ | dp[N][K-1] |
|  SUM     |   1  | $\searrow$ 2(=2*1-0)  |  $\cdots$ | sum=2sum-dp[N-1][K-1] |

```cpp
deque<modint> dq(K,0);
dq[1] = 1;
modint sum = 1;
modint out;
for (int i = 2; i <= N; i++)
{
  out = dq.back();
  dq.pop_back();
  dq.push_front(sum);
  sum = sum+sum-out;
}
cout << sum-dq.front() << endl;
```

## G.辞書順

文字列 $s$ の空でない部分列のうち,辞書順で $K$ 番目のものを求めよ.
そのようなものが存在しない場合は"Eel"と出力せよ.

### G.制約

```math
1 \leq |s| \leq 10^6 \\
1 \leq K \leq 10^{18}
```

### G.解説・コメント

~~くそムズなので飛ばす.~~

prefixが $s$ となる部分列の個数が分かれば $K$ 番目の部分列を先頭から決定していける.
わかりにくいので簡単な例で説明する.

'a'から始まる部分列の個数がK以上の場合,求める文字列の先頭は'a'である.

'a'から始まる部分列の個数がK未満の場合,求める文字列の先頭は'a'にはなりえない.
次に'b'から始まるかをチェックする.

この考えに従って疑似コードを書く.

```cpp
string ans = "";
while(K > 0){
  for(char c='a'; c<='z';c++){
    if(cnt[ans+c] >= K) ans += c, K--,  break;
    else K -= cnt[ans+c];
  }
}
cout << ans << endl;
```

あとは部分列の個数 $cnt[s]$ をdpで求める.次のdpを考える.

$dp[i][c] = i文字目以降で頭文字がcから始まる部分列の個数$

このdpをつかって1文字目を決める際にはdp[0][c]を使う.2文字目以降を決める際には
indexを適切に右に移動させながらdp[i][c]を使う.

sample 2

- s = lexicographical
- K = 100
- output = capal

例えば,問題サンプル2において1文字目が'c'と決まったとき,
2文字目は'o'以降から選ぶので'o'以降で頭文字がa~zから始まる部分列の個数をつかって
2文字目を決定する.
また2文字目を'a'と決定する際,'a'の候補が2つあるが,'c'から一番近い'a'を選ぶ.
そうすることによって3文字目以降の候補をより増やせる.

コードに落とす時の注意点

- dp[i][c]は逆順で求めること
- 事前に各cに対するindexを計算しておくこと
- オーバーフローに注意すること
- 条件を満たす文字列が存在しない場合を最初に求めておくこと
- ループの順番は必ずaからzへ

```cpp

string solve(string S, ll K){
    int N = S.length();
    vector<vector<ll>> dp(N+1,vector<ll>(26,0LL));
    vector<vector<int>> Index(26);
    for (int i = N-1; i >= 0; i--)
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            if(S[i]==c){
                for (char x = 'a'; x<= 'z'; x++)
                {
                    dp[i][c-'a'] += dp[i+1][x-'a'];
                    // オーバーフロー対策
                    chmin(dp[i][c-'a'], K);
                }
                dp[i][c-'a'] += 1;
            }
            else{
                dp[i][c-'a'] = dp[i+1][c-'a']; 
            }
            // オーバーフロー対策
            chmin(dp[i][c-'a'], K);
        }
    }
    // indexを前計算
    for (int i = 0; i < N; i++) Index[S[i]-'a'].push_back(i);

    string ans = "";
    ll max = 0LL;
    for (char c = 'a'; c <= 'z'; c++)
    {
        max += dp[0][c-'a'];
        chmin(max,K);
    }
    if(K > max) return "Eel";

    int idx = -1;
    while(K > 0LL){
        for (char c = 'a'; c <= 'z'; c++)
        {
            if(K <= dp[idx+1][c-'a']){
                ans += c;
                K--;
                idx = *upper_bound(Index[c-'a'].begin(),Index[c-'a'].end(),idx);
                break;
            }
            else{
                K -= dp[idx+1][c-'a'];
            }
        }
    }
    return ans;
}
```

## H.ナップサック

$N$ 個のものがあり, $i$ 番目のものの重さ,価値,色はそれぞれ $w_i, v_i, c_i$である.
ナップサックにいくつかものを入れることにした.
ただしものの重さの合計は $W$ 以下であり,色は $C$ 種類以下でなければならない.
ナップサックに入れられるものの価値の合計の最大値を求めよ.

### H.制約

```math
1 \leq N \leq 100 \\
1 \leq W \leq 10000\\
1 \leq C \leq 50\\
1 \leq w_i, v_i \leq 10000\\
1 \leq c_i \leq 50\\
```

### H.解説・コメント

ふつうのナップサック問題に色の制約が追加された問題. $C$ が大きいときはふつうのナップサック問題とかわらない.
色についてソートする.ソートした順にものを見ていく.このとき次のDPを考えればよい.

```math
dp[i][w][cnum][clast] \\
= (i番目のものまで見た後,ナップサックに重さの合計w,色の種類cnum,\\
最後に入れた色clastとしたときの価値の合計の最大値)
```

$i+1$ 番目に入れるものの色が $clast$ と同じ場合, $cnum$ はそのまま.
違う場合 $cnum+1$ となり $clast$ も更新.

というふうにdpを書けば良い.
ただし,コードに落とすときはループの順番に注意して $i$ を消す.

```cpp
sort(Objs.begin(),Objs.end(),[](obj a, obj b){return a.c < b.c;});
vector<vector<vector<ll> > > dp(W+1,vector<vector<ll>>(C+1,vector<ll>(51,-1)));
dp[0][0][0] = 0;
ll ans = 0;
for (int i = 0; i < N; i++)
for (int w=W-Objs[i].w;w>=0;w--)
for (int cnum=C;cnum>=0;cnum--)
for (int lastc=50;lastc>=0;lastc--)
{
    if(dp[w][cnum][lastc]==-1) continue;
    if(lastc==Objs[i].c) {
    chmax(dp[w+Objs[i].w][cnum][lastc], dp[w][cnum][lastc]+Objs[i].v);
    chmax(ans,dp[w+Objs[i].w][cnum][lastc]);
    }
    else {
    if((cnum+1)>C) continue;
    chmax(dp[w+Objs[i].w][cnum+1][Objs[i].c], dp[w][cnum][lastc]+Objs[i].v);
    chmax(ans,dp[w+Objs[i].w][cnum+1][Objs[i].c]);
    }
}
cout << ans << endl;
```

$O(NWC^2)$ でなんとか間に合った.ループの順番を考えない,unorderd_mapを使ったもうちょっと雑なコードだとTLEになり間に合わなかった.
雑なコードで間に合わなかった場合,ループの順番を考えて,メモリ使用量・計算量を減らしてあげることが有用.

## I.iwi

文字列sはiとwのみからなる.連続する3文字が"iwi"となってる部分を取り除ける.操作を行うことのできる回数の最大値を求めよ.

### I.制約

```math
1 \leq |s| \leq 300
```

### I.解説・コメント

取り除ける場所をすべて分岐して取り除くdfsを考えたらTLE.
よくよく考えると貪欲法で解ける.この問題はなんだったんだ・・・？

"iwii"か"iiwi"となっていたらこの中の"iwi"は取り除いても全体に影響を及ぼさない.
よってこの２つを先に取り除けるだけ取り除き,のこった"iwi"については重複してる部分もあるが,左から数えて取り除けばよい.

## J.ボール

N個のものがある.i番目のものは座標$x_i$に置かれている.座標xの点を目指してボールを投げると$x-1,x,x+1$のうちのいずれかに$1/3$ずつの確率で飛んでいき,そこに物が置いてあった場合は倒れる.最適な戦略でボールを投げたとき,すべての物を倒すのに必要なボールを投げる回数の期待値を求めよ.
ただし,ボールを投げる場所は,前に投げたボールのとんだ場所を見た後に決めることができる.

### J.制約

```math
1 \leq N \leq 16 \\
0 \leq x_i \leq 15 \\
x_i はすべて異なる.
```

### J.解説・コメント

~~左から順番に倒していけば良い.例えば,一番左の物の座標が$x$のとき,その物が倒れるまで$x+1$に向かってボールを投げ続けるのが最適な戦略である.~~

また,ボールの投げる場所は$1 \sim 14$だけを考えれば良い.

左から貪欲に消していくのはウソ解法である.例えば,OOOXOのようにものが並んでいたとき,最初にXに向かってボールを投げるべきである.(これもホントか怪しい.)
結局,物の並びと投げる順番のアルゴリズムについてはよくわからないので全探索する.貪欲にやるのはウソ解法になりやすいのでよくわからないときは避ける.幸い$N$が小さいのでなんとか間に合いそう.

再帰関数で計算する.ボールを投げても何も物を倒さなかった場合についてはそのまま実装すると無限にループするので事前に次のように式変形をして影響がでない形で計算する.結果,場合分けが多くなる.

残ってる物の集合を$S$とする.$i-1,i$に物が残った状態で$i$にボールを投げる時の,回数の期待値を求める式$dfs(S)$を書くと

```math
dfs(S) = \frac{1}{3}dfs(S-\{i-1\})+\frac{1}{3}dfs(S-\{i\})+\frac{1}{3}dfs(S)+1
```

$dfs(S)$を移行して$dfs(S)$についてまとめると,

```math
dfs(S) = \frac{1}{2}dfs(S-\{i-1\})+\frac{1}{2}dfs(S-\{i\})+\frac{3}{2}
```

物が1つ,３つ残ってる場合についても同じように式を解いてから再帰式のなかに埋め込む.
また,残ってる物の集合をbitで管理する.

```cpp
// 残ってる物たちbitを与えて,ボールを投げたときに物が倒れうる座標と,倒れうる物の個数のペアの集合を返す.
vector<pii> next_idx(int bit){
  vector<pii> container;
  int mask = 1|2|4;
  for (int i = 1; i < 15; i++)
  {
    int num = __builtin_popcount(bit&mask);
    if(num) container.emplace_back(num, i);
    mask<<=1;
  }
  return container;
}

bool ok(int bit, int i){
  if(i<0) return false;
  return (bit>>(i))&1;
}

// メモ化再帰.
unordered_map<int ,double> memo;
double dfs(int bit){
  if(bit==0) return 0;
  if(memo[bit]!=0) return memo[bit];
  double res = 1e8;
  auto idxs = next_idx(bit);
  for(auto idx:idxs){
    double ret = 0;
    // i;ボールを投げる場所,
    // cnt_one:i-1,i,i+1に物が何個あるか.1(0)〜3の値をとる.
    int cnt_one = idx.first;
    int i = idx.second;
    if(cnt_one==3){
      if(i) ret += dfs(bit&~(1<<(i-1)))/3.0;
      ret += dfs(bit&~(1<<i))/3.0;
      ret += dfs(bit&~(1<<(i+1)))/3.0;
      ret += 1;
    }
    else if(cnt_one==2){
      if(ok(bit,i-1)) ret += dfs(bit&~(1<<(i-1)))/2.0;
      if(ok(bit,i  )) ret += dfs(bit&~(1<<i    ))/2.0;
      if(ok(bit,i+1)) ret += dfs(bit&~(1<<(i+1)))/2.0;
      ret += 1.5;
    }
    else if(cnt_one==1){
      if(ok(bit,i-1)) ret += dfs(bit&~(1<<(i-1)));
      if(ok(bit,i  )) ret += dfs(bit&~(1<<i    ));
      if(ok(bit,i+1)) ret += dfs(bit&~(1<<(i+1)));
      ret += 3.0;
    }
    else{
      ret = 1e8;
    }
    res = min(res,ret);
  }
  return memo[bit] = res;
}

```

あとは初期値を代入してやれば良い.

```cpp
int bit = 0;
for(int x:X) bit |= (1<<x);
double ans = dfs(bit);
```

## K.ターゲット

円の列 $C_1,C_2,\ldots,C_K$ は各 $i$ に対し $C_{i + 1}$ が $C_i$ の strictly に内部にあるときサイズ $K$ のターゲットであるという. すぬけ君は,円を $N$ 個描いた. $i$ 番目の円は中心が $( x_i , 0 )$ であり,半径が $r_i$ である.この中から円をいくつか選んでターゲットを作るとき,ターゲットの最大サイズを求めよ.

### K.制約

```math
1 \leq N \leq 100000 \\
0 \leq x_i \leq 100,000,000 \\
1 \leq r_i \leq 100,000,000 \\
```

### K.解説・コメント

適切にソートすればLIS(最長増加部分列)を求める問題に帰着される.

すべての円の中心がx軸上にあるので,「円の包含関係」を「円とx軸の交点の関係」に言い換えることができる.

```math
C_{i + 1} が C_i の strictly に内部にある
\Leftrightarrow
(x_i - r_i < x_{i+1} - r_{i+1} ) \&\& (x_{i+1} + r_{i+1} < x_i + r_i)
```

したがって, $\{x_i - r_i \}$ で円を降順にソートした後, $\{x_i + r_i \}$ のLISを求めればそれが答えになる.
ただしstrictlyの条件を達成するために,$x_i-r_i = x_j-r_j$ となるものについては $\{x_i + r_i \}$が降順になるようにする.

## L.猫

$N$匹の猫を飼っている.猫$i$と猫$j$の仲の良さは$f_{i,j}$である.
猫の幸福度は,その猫から距離$1$以内にいる猫との仲の良さの総和.
猫$1$から猫$N$をこの順に1次元上に配置することにした.
猫の幸福度の総和の最大値を求めよ.

### L.制約

```math
1 \leq N \leq 1000 \\
-1000 \leq f_{i,j} \leq 1000 \\
f_{i,i} = 0 \\
f_{i,j} = f_{j,i} \\
```

### L.解説・コメント

最初,猫の順番も自分で決めると誤読していたせいで全く別の問題を解いていた.

左から順に位置を決めていくことを考える.本質的には距離が1以内というのは意味がなく,すでに配置している猫とどれだけおなじグループ属するかどうかだけを管理すれば良い.

```math
dp[i][k] = (猫iの左にk匹,猫iとの距離が1以内になるように猫i-1,i-2,\cdots i-kがいるときの猫たちの幸福度の総和)
```

とする.
$k$の取りうる値の範囲は猫$i-1$までの位置に依存している.
例えば猫$i-1$の左1以内に2匹しか猫が居なかったら,猫iの左1以内には最大で3匹までしか猫が存在し得ない.
それに注意してループを回せばいい.
また,幸福度の計算は事前に累積和を計算しておくことによりTime complexityを$O(1)$まで落としておく.

```cpp
int solve(){
  vector<vector<int> > dp(N+1,vector<int>(N+1,-1e8));
  dp[0][0] = 0;
  for (int i = 0; i < N; i++)
  {
    // 猫iの左1以内に何匹いるかをkで表す.
    for (int k = 0; k <= i; k++)
    {
      if(dp[i][k]==-1e8) continue;
    // 猫i+1の左1以内に何匹いるかをlで表す.
      for (int l = 0; l <= k+1; l++)
      {
        int happiness = 0;
        int j = max(0,i-l);
        // 累積和にすることによってTLEを回避.
        happiness += 2*(FS[i][i]-FS[i][j]);
        chmax(dp[i+1][l], dp[i][k] + happiness);
      }
    }
    dp[i].clear();
  }
  int ans = 0;
  for (int i = 0; i <= N; i++) chmax(ans, dp[N][i]);
  cout << ans << endl;
  return 0;
}
```

## M.家

$H$階建ての家があり,どの階も同じ構造をしている.
各階には$R$個の部屋があり,部屋$i$と部屋$j$は$g_{i,j}=1$であるとき,通路で繋がっている.
また,$h$階の部屋$r$から$h-1$階の部屋$r$に階段を使って降りることができる.
（$h$,$r$は任意の整数.登ることはできない.）
$H$階の部屋$1$から$1$階の部屋$1$に同じ部屋を通らずに行く通路の個数を mod $10^9+7$で求めよ.

### M.制約

```math
2 \leq H \leq 10^9 \\
1 \leq R \leq 16 \\
g_{i,j} = 0 or 1 \\
g_{i,i} = 0 \\
g_{i,j} = g_{j,i}
```

### M.解説・コメント

```math
A_{i,j} = ある階で部屋iから部屋jへ,同じ部屋を通らずに行く通路の個数
```

とする.

たとえば$H=2$の場合を考えると,求める答えは,$2$階で部屋$1$から部屋$j$に行った後,$1$階に降りて,部屋$j$から部屋$1$に行く通路の総数になる.次が答え.

```math
\sum_j A_{1,j}\times A_{j,1}
```

$H=3$の場合,

```math
\sum_{j,k} A_{1,j} \times A_{j,k} \times A_{k,1}
```

一般の$H$の場合,$A_{i,j}$を$(i,j)$成分に持つ行列$A$を用いて$A^H$の$(1,1)$成分に一致する.
行列の累乗計算はダブリング的に求めて$O(R^3logH)$で行える.

あとは行列$A$を求めれば良い.

$dfs$で部屋$i$から部屋$j$への通路の個数を求める.すでに通った部屋の集合の管理を$bit$で行う.$R \leq 16$なのでなんとかなりそう.

```cpp
modint dfs(int i, int j, ll seen){
    if(i==j) return memo[i][j][seen] = 1;
    if(memo[i][j][seen]!=0) return memo[i][j][seen];
    seen |= (1<<i);
    modint ret = 0;
    for (int k = 0; k < R; k++)
    {
        if(G[i][k]==0) continue;
        if((seen>>k)&1) continue;
        ret += dfs(k,j,(seen|(1<<k)));
    }
    return memo[i][j][seen] = ret;
}

for (int i = 0; i < R; i++)
{
    A[i][i] = 1;
    for (int j = i+1; j < R; j++) A[i][j] = A[j][i] = dfs(i,j,0);
}

auto ansmat = matPow(A,H);
cout << ansmat[0][0] << endl;
```

行列の掛け算,累乗計算のコードは本質的ではないので省略.

## T.フィボナッチ

数列$\{ a_i \}$を次のように定義する.

```math
a_1 = a_2 = \cdots = a_K = 1\\
a_i = a_{i-1} + \cdots +a_{i-K} (i>K)
```

$a_N$を mod $10^9+7$で求めよ.

### T.制約

```math
2 \leq K \leq 1000 \\
1 \leq N \leq 10^9
```

### T.解説・コメント

$N \leq K$のときは明らかに$a_N = 1$.

行列でフィボナッチ数列を表して行列の累乗計算に持ち込んだ.
しかし,$O(K^3logN)$かかるのでTLE.
どうやら,きたまさ法というものを使うらしい.そうすると$O(K^2logN)$で抑えられて間に合うってわけ.

本質的には行列の掛け算$O(K^3)$の代わりに行列計算の一部を抜き出して,タブリング的に$a_m$を$O(K^2)$で計算するというもの.
以下のリンクを参考にした.
ただ,ググってもきたまさ法自体が記載されているものがないのが不安.
ちゃんとした数学の言葉で書かれてるものが少なかったので,ちゃんと書く.

問題において,与えられたフィボナッチ数列はK次元ベクトル空間をなす.ただし,1-indexから0-indexに書き直す.
このベクトル空間の基底は初項$(a_0, \cdots , a_{K-1})$で表わせる.

いま,

```math
a_m = x_{m,0} a_0 + \cdots + x_{m,K-1} a_{K-1}
```

で表されてるとする.適切な同型写像を用いることにより$a_m$と$\{x_{m,0}, \cdots , x_{m,K-1}\}$を同一視できる.
ここで$a_m$に対して,その次の値$a_{m+1}$を返す写像$f$を考えると,次の写像と同じとみなせる.

```math
f : V^K \rightarrow V^K \\
\{ x_0,\cdots ,x_K \} \rightarrowtail f(\{ x_0,\cdots ,x_K \})
```

この$f$を具体的に求める.数列の項を1つだけずらす操作は線形写像になる.
(これの理解に苦しんだ.結局,フィボナッチ数列を次にすすめる操作が行列で書ける＝線形であるという理解.線形だと係数と和を分解して操作できる.)
よって,

```math
a_m = x_{m,0} a_0 + \cdots + x_{m,K-1} a_{K-1}
```

たちのすべての項を1つずらして,

```math
a_{m+1} = x_{m,0} a_1 + \cdots + x_{m,K-1} a_{K} \\
= x_{m,0} a_1 + \cdots + x_{m,K-1} (a_0 + \cdots + a_{K-1}) \\
= x_{m,K-1} a_0 + ( x_{m,0} + x_{m,K-1}) a_1 + \cdots + (x_{m,K-2} + x_{m,K-1} )a_{K-1} \\
```

したがって写像$f$は次のように表せる.

```math
f(\{ x_0,\cdots ,x_{K-1} \}) = \{x_{K-1}, x_0+x_{K-1}, \cdots,x_{K-2} + x_{K-1} \}
```

あとはダブリング的に$f^2,f^4,f^8,\cdots$と求めていくことで$f^N$を$O(logN)$で計算できる.
と,思ったけど合成関数がプログラムで素朴に書けないのか...単純に関数を合成するだけなら計算量減ってないし.$f^2(\{x_0 , \cdots , x_{K-1} \}), f^4(\{x_0 , \cdots , x_{K-1} \}), \cdots$を計算するしかなさそう.

この$f$を使うと,ベクトル空間の元と数列を同一視することにより,$a_{m+1} = f(a_m)$と表せる.
特に分ける必要がないので同じ$f$で表記する.
この$f$を利用して新たに$a_{2m} = g(a_m)$なる関数$g$を考えたい.この$f,g$によってダブリング的に解く.

$a_m$の両辺を$m$ステップすすめて,

```math
a_{2m} = x_{m,0}a_m + x_{m,1}a_{m+1} +\cdots + x_{m,K-1}a_{m+K-1} \\
= x_{m,0}a_m + x_{m,1}f(a_{m}) +\cdots + x_{m,K-1}f^{K-1}(a_{m}) \\
```

予め$f^i(a_m)(1 \leq i \leq K-1)$を求めておき,$f^i(a_m)$の$a_j$の係数を$f_j^i(a_m)$で表すと,

```math
a_{2m} = x_{m,0}\sum_j f^0_j(a_m)a_j + x_{m,1}\sum_j f^1_j(a_m)a_j +\cdots + x_{m,K-1}\sum_j f^{K-1}_j(a_m)a_j \\
= \sum_j\{ \sum_i x_{m,i} f_j^i(a_m)\} a_j \\
= \sum_j\ x_{2m,j} a_j \\
```

したがって

```math
g(\{x_{m,0}, \cdots, x_{m,K-1} \}) = \{ \sum_i x_{m,i} f_j^i(a_m)\}_j
```

ひとつの$f^i$が$O(K)$で求められるので,$a_{m}$から$a_{2m}$が$O(K^2)$で求められた.
よって,これを繰り返して$a_N$が$O(K^2logN)$で求められる.

```cpp
// fをone_foward, gをdouble_fowardで表す.
// fの操作を簡単に表すため,コンテナとしてdequeを用いた.
deque<modint> one_foward(deque<modint> x){
  deque<modint> ret = x;
  modint xK = ret.back();
  ret.pop_back();
  ret.push_front(0);
  for (int i = 0; i < ret.size(); i++) ret[i] += xK;
  return ret;
}

deque<modint> double_foward(deque<modint> x){
  vector<deque<modint> > k_foward(K);
  k_foward[0] = x;
  for (int i = 0; i < K-1; i++) k_foward[i+1] = one_foward(k_foward[i]);
  deque<modint> ret(K,0);
  for (int j = 0; j < K; j++)
  {
    for (int i = 0; i < K; i++)
    {
      ret[j] += x[i]*k_foward[i][j];
    }
  }
  return ret;
}

// Nを二進数で表し,上から計算してく.
deque<modint> pow_poly(deque<modint> a, ll n){
  deque<modint> ret = a;
  string x = bitset<64>(n).to_string();
  int i=0;
  while(x[i]=='0' && i<x.size()) i++;
  for (int j = i; j < x.size(); j++)
  {
    if(x[j]=='1') {ret = one_foward(ret);}
    if(j < (x.size()-1)) ret = double_foward(ret);
  }
  return ret;
}

int solve(){
  deque<modint> d(K,0);
  d[0] = 1; // m=0に相当.
  auto ret = pow_poly(d, N-1);
  modint ans = 0;
  for (int i = 0; i < K; i++) ans += ret[i];
  cout << ans << endl;
  return 0;
}
```

線形代数の復習にもなる面白い問題だった.
ただかなり理解に時間がかかった.

- [きたまさ法メモ](https://yosupo.hatenablog.com/entry/2015/03/27/025132)
- [漸化式（フィボナッチ数列）を線形代数（線形空間,固有ベクトル）で解く方法を解説](https://math-fun.net/20191216/4098/)
