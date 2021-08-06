# Panda

kaggle micro course on pandas.

```python
import pandas as pd

# csvからデータを読み出し形を確認．
wine_reviews = pd.read_csv("../input/wine-reviews/winemag-data-130k-v2.csv")
wine_reviews.shape
wine_reviews.head()
## set_index
reviews.set_index("title")
## イタリアかつポイントが９０以上
reviews.loc[(reviews.country == 'Italy') & (reviews.points >= 90)]
## priceがNaNでないものすべて．
eviews.loc[reviews.price.notnull()]
## すべてのデータの変更
reviews['critic'] = 'everyone'

## よく使うmethod
reviews.points.mean()
reviews.taster_name.unique()
reviews.taster_name.value_counts()
review_points_mean = reviews.points.mean()
## map:Series の method
reviews.points.map(lambda p: p - review_points_mean)
## apply:DataFrame の method
def remean_points(row):
    row.points = row.points - review_points_mean
    return row

reviews.apply(remean_points, axis='columns')
## mapとapplyでやりたいことはほぼ同じだが使用法が異なる．

```
