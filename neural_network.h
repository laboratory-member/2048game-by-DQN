#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <cassert>

// 张量类（Tensor）
class Tensor {
public:
    std::vector<std::vector<double>> data; // 二维张量
    size_t rows, cols;

    Tensor();
    Tensor(size_t rows, size_t cols);

    Tensor matmul(const Tensor& other) const;
    Tensor add(const Tensor& other) const;
    Tensor subtract(const Tensor& other) const;
    Tensor transpose() const;
    Tensor multiply(const Tensor& other) const;

    void print() const;
};

// ReLU 激活函数及其导数
Tensor relu(const Tensor& input);
Tensor relu_derivative(const Tensor& input);

// Sigmoid 激活函数及其导数
Tensor sigmoid(const Tensor& input);
Tensor sigmoid_derivative(const Tensor& input);

// 全连接层（Linear Layer）
class LinearLayer {
public:
    Tensor weights;
    Tensor biases;
    Tensor input;

    LinearLayer(size_t input_dim, size_t output_dim);

    Tensor forward(const Tensor& input);
    Tensor backward(const Tensor& grad_output, double learning_rate);
};

// 损失函数
double mse_loss(const Tensor& predictions, const Tensor& targets);
double cross_entropy_loss(const Tensor& predictions, const Tensor& targets);

#endif // NEURAL_NETWORK_H
