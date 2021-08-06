# Panda

kaggle micro course on pandas.

## Creating, Reading, Writing, Indexing, Selecting & Assigning
```python
import pandas as pd

# read

wine_reviews = pd.read_csv("../input/wine-reviews/winemag-data-130k-v2.csv")
wine_reviews.shape
wine_reviews.head()

## creat

animals = pd.DataFrame({'Cows': [12, 20], 'Goats': [22, 19]}, index=['Year 1', 'Year 2'])

## save

animals.to_csv('cows_and_goats.csv')

## set_index

reviews.set_index("title")

## イタリアかつポイントが90以上

reviews.loc[(reviews.country == 'Italy') & (reviews.points >= 90)]

## priceがNaNでないものすべて．

eviews.loc[reviews.price.notnull()]

## すべてのデータの変更

reviews['critic'] = 'everyone'
```
## Function and Map
```python
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
```
mapとapplyでやりたいことはほぼ同じだが使用法が異なる．

## Grouping and Sorting

groupby は SQL の GROUP BY とだいたい同じ．また，エクセルのピポット機能とだいたい同じ．

```python
## value_counts()とおなじ

reviews.groupby('points').points.count()

## グループ化してその中での特徴値を抽出する．

reviews.groupby('points').price.min()
reviews.groupby('winery').apply(lambda df: df.title.iloc[0]) # 代表元の抽出．
reviews.groupby(['country', 'province']).apply(lambda df: df.loc[df.points.idxmax()])
reviews.groupby(['country']).price.agg([len, min, max])

## Multi-indexes

countries_reviewed = reviews.groupby(['country', 'province']).description.agg([len])
countries_reviewed = countries_reviewed.reset_index()

## sort. multi-indexesの場合はreset_index()する．

countries_reviewed.sort_values(by='len')
countries_reviewed.sort_values(by='len', ascending=False)
countries_reviewed.sort_values(by=['country', 'len'])
```

## Renaming and Combining

```python
## rename

reviews.rename(columns={'points': 'score'})

## 上下に連結

pd.concat([up_data,down_data])

## 左右に連結

left = canadian_youtube.set_index(['title', 'trending_date'])
right = british_youtube.set_index(['title', 'trending_date'])

left.join(right, lsuffix='_CAN', rsuffix='_UK')
```