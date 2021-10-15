# Typical 90

間違って消してしまった．
解けなかった問題たちの振り返りコメント．

## 001	Yokan Party(★4)
## 002	Encyclopedia of Parentheses(★3)
## 003	Longest Circular Road(★4)
## 004	Cross Sum(★2)
## 005	Restricted Digits(★7)

ダブリング．

## 006	Smallest Subsequence(★5)
## 007	CP Classes(★3)
## 008	AtCounter(★4)
## 009	Three Point Angle(★6)

偏角ソート．

## 010	Score Sum Queries(★2)
## 011	Gravy Jobs(★6)

スケジューリング問題の発展．DP

## 012	Red Painting(★4)
## 013	Passing(★5)
## 014	We Used to Sing a Song Together(★3)
## 015	Don't be too close(★6)

調和級数．

## 016	Minimum Coins(★3)
## 017	Crossing Segments(★7)
## 018	Statue of Chokudai(★3)
## 019	Pick Two(★6)

区間DP

## 020	Log Inequality(★3)
## 021	Come Back in One Piece(★5)
## 022	Cubic Cake(★2)
## 023	Avoid War(★7)
## 024	Select +／- One(★2)
## 025	Digit Product Equation(★7)
## 026	Independent Set on a Tree(★4)
## 027	Sign Up Requests (★2)
## 028	Cluttered Paper(★4)
## 029	Long Bricks(★5)
## 030	K Factors(★5)
## 031	VS AtCoder(★6)
## 032	AtCoder Ekiden(★3)
## 033	Not Too Bright(★2)

コーナーケースに注意．

## 034	There are few types of elements(★4)
## 035	Preserve Connectivity(★7)

DFS順に距離を測る．部分点がちゃんとヒントになってる．

## 036	Max Manhattan Distance(★5)
## 037	Don't Leave the Spice(★5)
## 038	Large LCM(★3)
## 039	Tree Distance(★5)

辺に注目して何回足されるか数えればいい．
それか全方位木DP．
## 040	Get More Money(★7)

埋める燃やす問題．最小カットを求めたいので
現金はすべて回収できると考えてそこからいくら損するかを考える．
## 041	Piles in AtCoder Farm(★7)

convex hull.幾何ライブラリの整備が必要な問題．
ピックの定理．

## 042	Multiple of 9(★4)
## 043	Maze Challenge with Lack of Sleep(★4)
## 044	Shift and Swapping(★3)
## 045	Simple Grouping(★6)

もともとのグループ，新規グループのO(2^N)二乗ループが
O(3^N)になるやつ．

## 046	I Love 46(★3)
## 047	Monochromatic Diagonal(★7)

ローリングハッシュ．RGBを012に変換するのは基本．

## 048	I will not drop out(★3)
## 049	Flip Digits 2(★6)
## 050	Stair Jump(★3)
## 051	Typical Shop(★5)
## 052	Dice Product(★3)
## 053	Discrete Dowsing(★7)

三分探索の発展として黄金比率探索を行う．
実装がかなり難しい．Nがフィボナッチ数のときに
整数でもうまく行くようになる．

## 054	Takahashi Number(★6)
## 055	Select 5(★2)
## 056	Lucky Bag(★5)
## 057	Flip Flap(★6)
## 058	Original Calculator(★4)
## 059	Many Graph Queries(★7)

true/falseの判定を64個まとめて行うことで64倍高速化を行う．

## 060	Chimera(★5)
## 061	Deck(★2)
## 062	Paint All(★6)
## 063	Monochromatic Subgrid(★4)
## 064	Uplift(★3)
## 065	RGB Balls 2(★7)
## 066	Various Arrays(★5)
## 067	Base 8 to 9(★2)
## 068	Paired Information(★5)

交代和．同じクエリを無視しなかったことによるケアレスミス．

## 069	Colorful Blocks 2(★3)
## 070	Plant Planning(★4)

45度回転しない普通のマンハッタン距離．
## 071	Fuzzy Priority(★7)

DFSによる探索の効率化．
K個で打ち切る実装がビームサーチに近い．

## 072	Loop Railway Plan(★4)
## 073	We Need Both a and b(★5)
## 074	ABC String 2(★6)
## 075	Magic For Balls(★3)
## 076	Cake Cut(★3)
## 077	Planes on a 2D Plane(★7)

最大流による二部グラフ組み合わせ．

## 078	Easy Graph Problem(★2)
## 079	Two by Two(★3)
## 080	Let's Share Bit(★6)
## 081	Friendly Group(★5)

二次元累積和．
ソートしてセグ木に乗せる．

## 082	Counting Numbers(★3)
## 083	Colorful Graph(★6)
## 084	There are two types of characters(★3)
## 085	Multiplication 085(★4)
## 086	Snuke's Favorite Arrays(★5)
## 087	Chokudai's Demand(★5)
## 088	Similar but Different Ways(★6)

鳩の巣原理．DFSによる探索の効率化．

## 089	Partitions and Inversions(★7)
## 090	Tenkei90's Last Problem(★7)

激ムズ．本番で出たら部分点を積極的に取りに行く問題．
値を決める順番を降順（昇順）にすることによって
DPできまる範囲を決めている．