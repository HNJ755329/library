# Visualize

```python
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
pd.plotting.register_matplotlib_converters()
%matplotlib inline

fifa_data = pd.read_csv(fifa_filepath, index_col="Date", parse_dates=True)
# Line
sns.lineplot(data=fifa_data)
# Bar chart showing average arrival delay for Spirit Airlines flights by month
sns.barplot(x=flight_data.index, y=flight_data['NK'])

# Heatmap showing average arrival delay for each airline by month
sns.heatmap(data=flight_data, annot=True)

# Scatter
sns.scatterplot(x=insurance_data['bmi'], y=insurance_data['charges'])
## you might like to add a regression line
sns.regplot(x=insurance_data['bmi'], y=insurance_data['charges'])
#histogram
sns.displot(df_train['SalePrice'])

#skewness and kurtosis
print("Skewness: %f" % df_train['SalePrice'].skew())
print("Kurtosis: %f" % df_train['SalePrice'].kurt())
```