import numpy
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten, BatchNormalization, Activation
from keras.layers.convolutional import Conv2D, MaxPooling2D
from keras.constraints import maxnorm
from keras.utils import np_utils
from keras.datasets import cifar10

(x_train, y_train), (x_test, y_test) = cifar10.load_data()

# normalise the data so that it is a value between 0 and 255
x_train = x_train.astype('float32')
x_test = x_test.astype('float32')
x_train = x_train / 255.0
x_test = x_test / 255.0

# one hot encode the outputs so that it classifies  only one potential output.
y_train = np_utils.to_categorical(y_train)
y_test = np_utils.to_categorical(y_test)

# number of potential outputs
num_classes = y_test.shape[1]

model = Sequential()

# Need to specify the number of filters ie 32 and the size of filter.
# input shape is when creating the first layer
# padding = same means not changing anything
# relu is most common activation

model.add(Conv2D(32, (3, 3), input_shape=x_train.shape[1:], padding='same'))
model.add(Activation('relu'))
# Create the dropout layer to prevent overfitting.
# randomly eliminates connections between layers

model.add(Dropout(0.1))

# Batch normalisation normalises the inputs heading into the next layers
model.add(BatchNormalization())

# Add another convolutional layer, notice the filter size increases so that more complex representations can be
# learnt
model.add(Conv2D(64, (3, 3), padding='same'))
model.add(Activation('relu'))

#The pooling layer is added to make the classifier more robust so it can learn relevant patterns.
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Dropout(0.1))
model.add(BatchNormalization())

#adding another layer.
model.add(Conv2D(128, (3, 3), padding='same'))
model.add(Activation('relu'))
model.add(Dropout(0.1))
model.add(BatchNormalization())

#Flatten the data after convulational layers.
model.add(Flatten())
model.add(Dropout(0.1))

#Create the first densely connected layer, we specify the number of neurons in this layer
model.add(Dense(256, kernel_constraint=maxnorm(3)))
model.add(Activation('relu'))
model.add(Dropout(0.1))
model.add(BatchNormalization())

model.add(Dense(128, kernel_constraint=maxnorm(3)))
model.add(Activation('relu'))
model.add(Dropout(0.1))
model.add(BatchNormalization())

#Create the final layer with neurons= to the number of potential classes. softmax chooses the class with
#highest probability.
model.add(Dense(num_classes))
model.add(Activation('softmax'))


epochs = 25
#most common optimiser is adam. an optimiser tunes the weights in the network to approach the point of least loss.
optimiser = 'adam'


model.compile(loss='categorical_crossentropy', optimizer=optimiser, metrics=['accuracy'])

print(model.summary())

numpy.random.seed(10)
model.fit(x_train, y_train, validation_data=(x_test, y_test), epochs=epochs, batch_size=128)

scores = model.evaluate(x_test, y_test, verbose=0)
print("Accuracy: %.2f%%" % (scores[1]*100))