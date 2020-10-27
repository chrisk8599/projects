#!/usr/bin/env python
# coding: utf-8

# In[1]:


from pyspark.context import SparkContext
from pyspark.sql.session import SparkSession
sc = SparkContext('local')
spark = SparkSession(sc)


# In[2]:


df = spark.read.csv("letter-recognition.data", inferSchema=True).toDF("letter", "xboxhoriz", "yboxvert", "widthbox", "heightbox","onpix","xbar",
     "ybar","meanxvariance","meanyvariance","meanxycorr","meanx*x*y","meanx*y*y","x-ege","xegvy","y-ege","yegvx")


# In[3]:


from pyspark.ml.linalg import Vectors
from pyspark.ml.feature import VectorAssembler


# In[4]:


vector_assembler = VectorAssembler(inputCols=["xboxhoriz", "yboxvert", "widthbox", "heightbox","onpix","xbar",
     "ybar","meanxvariance","meanyvariance","meanxycorr","meanx*x*y","meanx*y*y","x-ege","xegvy","y-ege","yegvx"],\
outputCol="features")
df_temp = vector_assembler.transform(df)


# In[5]:


df = df_temp.drop("xboxhoriz", "yboxvert", "widthbox", "heightbox","onpix","xbar",
     "ybar","meanxvariance","meanyvariance","meanxycorr","meanx*x*y","meanx*y*y","x-ege","xegvy","y-ege","yegvx")


# In[6]:


from pyspark.ml.feature import StringIndexer
l_indexer = StringIndexer(inputCol="letter", outputCol="LetterNumber")
df = l_indexer.fit(df).transform(df)


# In[13]:


(trainingData, testData) = df.randomSplit([0.7, 0.3])


# In[8]:


from pyspark.ml.classification import DecisionTreeClassifier
from pyspark.ml.evaluation import MulticlassClassificationEvaluator


# In[9]:


dt = DecisionTreeClassifier(labelCol="LetterNumber", featuresCol="features")
model = dt.fit(trainingData)


# In[10]:


predictions = model.transform(testData)


# In[15]:


predictions.select("prediction", "LetterNumber").show(2000)


# In[16]:


evaluator = MulticlassClassificationEvaluator(labelCol="LetterNumber", predictionCol="prediction",metricName="accuracy")
accuracy = evaluator.evaluate(predictions)
print(accuracy)


# In[ ]:




