import sklearn
from sklearn import datasets
from sklearn import svm
from sklearn import metrics

#can load datasets from the sklearn library
cancer_data = datasets.load_breast_cancer()

#how to view the features and target of the dataset from sklearn.
# print(cancer_data.feature_names)
# print(cancer_data.target_names)


x = cancer_data.data
y = cancer_data.target

x_train , x_test , y_train , y_test = sklearn.model_selection.train_test_split(x,y,test_size=0.2)


#parameters help make it more accurate

#kernel is linear poly rbf or sigmoid

#C is referred to softmarging , if c=0 hard margin

model = svm.SVC(kernel="linear", C=2)

model.fit(x_train,y_train)

predictions = model.predict(x_test)

accuracy = metrics.accuracy_score(y_test,predictions)

print(accuracy)
