import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn.preprocessing import MinMaxScaler
from sklearn import metrics
from sklearn.metrics import confusion_matrix
import itertools

# activation functions to be used at the output of each layer.
def Sigmoid(Z):
    return 1 / (1 + np.exp(-Z))


def Relu(Z):
    return np.maximum(0, Z)

#Derivatives of the activation functions

def dRelu(x):
    x[x<=0] = 0
    x[x>0] = 1
    return x
def dSigmoid(Z):
    s = 1/(1+np.exp(-Z))
    dZ = s * (1-s)
    return dZ


class dlnet:
    def __init__(self, x, y):
        # X is the input layer, the data we give to the network
        # X is a matrix which has as many rows as features of the data
        # and as many columns as samples we have available to train the network

        self.X = x

        # The output, used to train the network
        self.Y = y

        # Holds the output the network produces. Has same dimensions as Y.

        self.Yh = np.zeros((1, self.Y.shape[1]))

        # The number of layers of the network.
        self.L = 2

        # The number of neurons in each layer. 9 features, 15 hidden neurons , 1 output neuron
        self.dims = [9, 15, 1]

        # A python dict which will hold W and B parameters of each of the layers of the network
        self.param = {}

        # The cache which holds some calculations needed for backpropagation
        self.ch = {}

        self.grad = {}

        # An array where the loss value of the network every x iterations is stored.
        # Loss value expresses the difference between predicted and actual output.
        self.loss = []

        # Learning rate, the speed at which the network will learn
        self.lr = 0.003

        # The number of training samples.
        self.sam = self.Y.shape[1]

    # Intiialise the network with random values for the parameters
    def nInit(self):
        np.random.seed(1)

        # When we do the matrix multiplications, the products must be the right size
        # W1: Rows = number of hidden units of that layer, dims[1]
        # W1: Columns = number of features, rows of previous layer
        # b1 : Same number of rows as W1 and a single column
        # W2 : Rows = number of hidden units of that layer ie alyer 2.
        # W2 : Columns = number of rows of the input to that layer
        # b2 : Same number of rows as W2 and a single column

        self.param['W1'] = np.random.randn(self.dims[1], self.dims[0]) / np.sqrt(self.dims[0])
        self.param['b1'] = np.zeros((self.dims[1], 1))
        self.param['W2'] = np.random.randn(self.dims[2], self.dims[1]) / np.sqrt(self.dims[1])
        self.param['b2'] = np.zeros((self.dims[2], 1))
        return

    # Function that will perform computation at each unit of each layer in the network.
    # Takes input and pass it forwards through its deifferent layers.

    def forward(self):
        Z1 = self.param['W1'].dot(self.X) + self.param['b1']
        A1 = Relu(Z1)
        self.ch['Z1'], self.ch['A1'] = Z1, A1

        Z2 = self.param['W2'].dot(A1) + self.param['b2']
        A2 = Sigmoid(Z2)
        self.ch['Z2'], self.ch['A2'] = Z2, A2
        self.Yh = A2
        loss = self.nloss(A2)
        return self.Yh, loss


    #Objective of the loss function  is to express how far from the intended
    #target the result was.

    #CROSS ENTROPY LOSS FUNCTION IS USED FOR CLASSIFICATION CHALLENGES'
    def nloss(self, Yh):
        loss = (1. / self.sam) * (-np.dot(self.Y, np.log(Yh).T) - np.dot(1 - self.Y, np.log(1 - Yh).T))
        return loss


    #Up to here is the end of forward propogation
    # we have achieved 2 outputs of loss and yh
    #Loss is the distance bw Yh and Y
    # We want to minimise the loss.


    #Essentially, the process is like this.
    #1. we initially set weights and biases to random values
    #2. We run the input data forwards through the network and produce a result Yh
    #3. Calculate the loss, the distance bw Yh and Y
    #4. if not good enough, change weights and baises and run again, to see if loss
    #has improved. and repeat till satisfied.

    #To ensure we know whether to increase or decrease the biases we need to use calculus
    #derivatives wil ltell us what impact a small change in a parameter has on on the final loss

    #If the derivative of the loss in relation to a weight is positive
    #this means that increasing the weight will make the loss increase.
    #if this happens then decrease the weight to make the loss decrease

    #if the derivative is negative, it means that increasing the weight will
    #make the loss decrease which is what we want.



    #Theres a final obstacle. The network is made up of layers.
    #it could have 2 such as this one or many more
    #We need to understand how changes to each of the parameters
    #impacts the loss at the end of the network.
    #THe way to connect the different derivatives and the loss of the networks is
    #by using chainrule.


    #an Example to illustrate chain rule
    #To understand how small changes to W1 will impact the loss.
    #Start from the loss and go back until u get to W1

    #The equation of the loss
    # Loss = -(YLog(Yh) + (1-Y)Log(1-Yh))
    #by differentiaing we get dloss wrt Yh

    #dLoss_Yh = -(Y/Yh - (1-Y)/(1-Yh))

    #Before that how did we get Yh? from the sigmoid function

    #Yh = sigmoid(Z2)

    #the derivative of the sigmoid is
    #dSigmoid = sigmoid(x) * (1 - sigmoid(x))

    #thus dYh_Z2 = dSigmoid(Z2)

    #Therefore with chain rule we can say
    #dLoss_Z2 = dLoss_Yh * dSigmoid(z2)

    #Next step is z2

    #Z2 = W2A1 + b2

    #dZ2_A1 = W2

    #thus dLoss_A1 = W2 * dLoss_Z2

    # A1  = Relu(Z1)
    #dA1_Z1 = dRelu(z1)

    #dLoss_Z1 = dLoss_A1 * dRelu(z1)

    #z1 = W1x + b1

    #Finally we found w1
    #dZ1_W1 = x

    #threfore
    #dLoss_W1 = X*dloss_Z1

    def backward(self):
        dLoss_Yh = - (np.divide(self.Y, self.Yh) - np.divide(1 - self.Y, 1 - self.Yh))

        dLoss_Z2 = dLoss_Yh * dSigmoid(self.ch['Z2'])
        dLoss_A1 = np.dot(self.param["W2"].T, dLoss_Z2)
        dLoss_W2 = 1. / self.ch['A1'].shape[1] * np.dot(dLoss_Z2, self.ch['A1'].T)
        dLoss_b2 = 1. / self.ch['A1'].shape[1] * np.dot(dLoss_Z2, np.ones([dLoss_Z2.shape[1], 1]))

        dLoss_Z1 = dLoss_A1 * dRelu(self.ch['Z1'])
        dLoss_A0 = np.dot(self.param["W1"].T, dLoss_Z1)
        dLoss_W1 = 1. / self.X.shape[1] * np.dot(dLoss_Z1, self.X.T)
        dLoss_b1 = 1. / self.X.shape[1] * np.dot(dLoss_Z1, np.ones([dLoss_Z1.shape[1], 1]))

        self.param["W1"] = self.param["W1"] - self.lr * dLoss_W1
        self.param["b1"] = self.param["b1"] - self.lr * dLoss_b1
        self.param["W2"] = self.param["W2"] - self.lr * dLoss_W2
        self.param["b2"] = self.param["b2"] - self.lr * dLoss_b2



    def gd(self, X, Y, iter=3000):
        np.random.seed(1)

        self.nInit()

        for i in range(0, iter):
            Yh, loss = self.forward()
            self.backward()

            if i % 500 == 0:
                print("Cost after iteration %i: %f" % (i, loss))
                self.loss.append(loss)

        return

    def pred(self, x, y):
        self.X = x
        self.Y = y
        comp = np.zeros((1, x.shape[1]))
        pred, loss = self.forward()

        for i in range(0, pred.shape[1]):
            if pred[0, i] > 0.5:
                comp[0, i] = 1
            else:
                comp[0, i] = 0

        print("Acc: " + str(np.sum((comp == y) / x.shape[1])))

        return comp

df = pd.read_csv('breast-cancer-wisconsin.csv',header=None)
df.head(5)

#Replace the class values of 2 and 4 to 0 and 1
df.iloc[:,10].replace(2, 0,inplace=True)
df.iloc[:,10].replace(4, 1,inplace=True)

#Eliminate all rows that hold missing values at column 6
df = df[~df[6].isin(['?'])]

df = df.astype(float)


#Applied normalisation
names = df.columns[0:10]
scaler = MinMaxScaler()
scaled_df = scaler.fit_transform(df.iloc[:,0:10])
scaled_df = pd.DataFrame(scaled_df, columns=names)


x=scaled_df.iloc[0:500,1:10].values.transpose()
y=df.iloc[0:500,10:].values.transpose()
xval=scaled_df.iloc[501:683,1:10].values.transpose()
yval=df.iloc[501:683,10:].values.transpose()



nn = dlnet(x, y)
nn.lr = 0.01
nn.dims = [9,15,1]
nn.gd(x, y, iter=15000)

pred_train = nn.pred(x, y)
pred_test = nn.pred(xval, yval)