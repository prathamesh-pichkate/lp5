# Fashion MNIST CNN Classifier
# Import Required Libraries

import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import matplotlib.pyplot as plt

# Load Dataset
data = pd.read_csv("fashion-mnist_test.csv")

# Display first 5 rows
print(data.head())

# Separate labels and image pixels
y = data['label']
X = data.drop('label', axis=1)

# Normalize pixel values
X = X / 255.0

# Convert into numpy arrays
X = np.array(X)
y = np.array(y)

# Reshape images for CNN
X = X.reshape(-1, 28, 28, 1)

# Class Names
class_names = [
    'T-shirt',
    'Trouser',
    'Pullover',
    'Dress',
    'Coat',
    'Sandal',
    'Shirt',
    'Sneaker',
    'Bag',
    'Ankle Boot'
]

# Build CNN Model
model = keras.Sequential([

    # Input Layer
    keras.Input(shape=(28, 28, 1)),

    # First Convolution Layer
    layers.Conv2D(
        32,
        (3,3),
        activation='relu'
    ),

    # First Pooling Layer
    layers.MaxPooling2D((2,2)),

    # Second Convolution Layer
    layers.Conv2D(
        64,
        (3,3),
        activation='relu'
    ),

    # Second Pooling Layer
    layers.MaxPooling2D((2,2)),

    # Flatten Layer
    layers.Flatten(),

    # Dense Layer
    layers.Dense(
        128,
        activation='relu'
    ),

    # Output Layer
    layers.Dense(
        10,
        activation='softmax'
    )
])

# Compile Model
model.compile(
    optimizer='adam',
    loss='sparse_categorical_crossentropy',
    metrics=['accuracy']
)

# Train Model
model.fit(
    X,
    y,
    epochs=5
)

# Evaluate Model
loss, accuracy = model.evaluate(X, y)

# Print Accuracy
print("\nAccuracy:", accuracy)

# Predict Images
prediction = model.predict(X)

# Get First Image Prediction
predicted_class = class_names[
    np.argmax(prediction[0])
]

print("\nPredicted Class:",
      predicted_class)

# Display First Image
plt.imshow(
    X[0].reshape(28,28),
    cmap='gray'
)

plt.title(
    "Predicted: " +
    predicted_class
)

plt.show()