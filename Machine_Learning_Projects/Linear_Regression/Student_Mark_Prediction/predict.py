import pandas as pd
import numpy as np
import sklearn
from sklearn import linear_model
from sklearn.utils import shuffle

data = pd.read_csv("student-mat.csv", sep=";")

# These are attributes we are going to use to get the label
data = data[
    ["G1", "G2", "G3", "studytime", "failures", "absences", "famrel", "freetime", "goout", "Dalc", "Walc", "health"]]

# This is a label, what we want to predict
predict = "G3"

x = np.array(data.drop([predict], 1))
y = np.array(data[predict])

x_train, x_test, y_train, y_test = sklearn.model_selection.train_test_split(x, y, test_size=0.1)

model = linear_model.LinearRegression()
model.fit(x_train, y_train)
accuracy = model.score(x_test, y_test)

print("The accuracy is %f " % accuracy)

# The Predictions

predictions = model.predict(x_test)

for x in range(len(predictions)):
    print("The prediction is %f for these attributes %s , the actual value is %d" % (
        predictions[x], x_test[x], y_test[x]))
