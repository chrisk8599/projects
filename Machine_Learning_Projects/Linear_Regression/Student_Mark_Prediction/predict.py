import pandas as pd
import numpy as np
import sklearn
import matplotlib.pyplot as pyplot
import pickle
from sklearn import linear_model
from sklearn.utils import shuffle
from matplotlib import style

data = pd.read_csv("student-mat.csv", sep=";")

# These are attributes we are going to use to get the label
data = data[
    ["G1", "G2", "G3", "studytime", "failures", "absences", "famrel", "freetime", "goout", "Dalc", "Walc", "health"]]

#Use this if you want to translate categorical attributes to numerical.
# data[["internet"]]=data[["internet"]].replace("yes", 1)
# data[["internet"]]=data[["internet"]].replace("no", 0)


# This is a label, what we want to predict
predict = "G3"

x = np.array(data.drop([predict], 1))
y = np.array(data[predict])
x_train, x_test, y_train, y_test = sklearn.model_selection.train_test_split(x, y, test_size=0.1)

#
# best_accuracy = 0
#
# while best_accuracy<0.97:
#     x_train, x_test, y_train, y_test = sklearn.model_selection.train_test_split(x, y, test_size=0.1)
#
#     model = linear_model.LinearRegression()
#     model.fit(x_train, y_train)
#     accuracy = model.score(x_test, y_test)
#     print("The accuracy is %f " % accuracy )
#
#     if accuracy > best_accuracy:
#         best_accuracy = accuracy
#
#         # Pickle will save the model so that we can keep one with a good accuracy.
#         with open("model.pickle", "wb") as f:
#             pickle.dump(model, f)
#


saved_model = open("model.pickle","rb")
model = pickle.load(saved_model )



# The Predictions

predictions = model.predict(x_test)

for x in range(len(predictions)):
    print("The prediction is %f for these attributes %s , the actual value is %d" % (
        predictions[x], x_test[x], y_test[x]))



#Use pyplot to visualise the plot in a graph

style.use("ggplot")
pyplot.scatter(data['G1'],data['G3'])
pyplot.xlabel("G1 grade")
pyplot.ylabel("Final grade")
pyplot.show()