import sklearn
from sklearn.utils import shuffle
from sklearn.neighbors import KNeighborsClassifier
import pandas as pd
import numpy as np
from sklearn import linear_model, preprocessing

data = pd.read_csv("car.data")

# helps convert categroical to numerical data.
le = preprocessing.LabelEncoder()
buying = le.fit_transform(list(data["buying"]))
maintenance = le.fit_transform(list(data["maint"]))
doors = le.fit_transform(list(data["door"]))
persons = le.fit_transform(list(data["persons"]))
lug = le.fit_transform(list(data["lug_boot"]))
safety = le.fit_transform(list(data["safety"]))
classification = le.fit_transform(list(data["class"]))

predict = "class"

x = list(zip(buying, maintenance, doors, persons, lug, safety))
y = list(classification)

x_train, x_test, y_train, y_test = sklearn.model_selection.train_test_split(x, y, test_size=0.1)

model = KNeighborsClassifier(n_neighbors=7)
model.fit(x_train,y_train)
accuracy = model.score(x_test,y_test)
print(accuracy)

classification_type = ["unacc","acc","good","vgood"]

predictions = model.predict(x_test)


for i in range(len(x_test)):
    print("Prediction of safety is %s , the data given is %s and the actual safety value is %s"
          %(classification_type[predictions[i]],x_test[i],classification_type[y_test[i]]))








