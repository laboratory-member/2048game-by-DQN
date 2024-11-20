#include "neural_network.h"

// 张量类实现
Tensor::Tensor() : rows(0), cols(0) {}

Tensor::Tensor(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows, std::vector<double>(cols, 0)) {}

Tensor Tensor::matmul(const Tensor& other) const {
    assert(cols == other.rows);
    Tensor result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            for (size_t k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Tensor Tensor::add(const Tensor& other) const {
    assert(rows == other.rows && cols == other.cols);
    Tensor result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Tensor Tensor::subtract(const Tensor& other) const {
    assert(rows == other.rows && cols == other.cols);
    Tensor result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Tensor Tensor::transpose() const {
    Tensor result(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

Tensor Tensor::multiply(const Tensor& other) const {
    assert(rows == other.rows && cols == other.cols);
    Tensor result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] * other.data[i][j];
        }
    }
    return result;
}

void Tensor::print() const {
    for (const auto& row : data) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

// ReLU 激活函数及其导数实现
Tensor relu(const Tensor& input) {
    Tensor output(input.rows, input.cols);
    for (size_t i = 0; i < input.rows; ++i) {
        for (size_t j = 0; j < input.cols; ++j) {
            output.data[i][j] = std::max(0.0, input.data[i][j]);
        }
    }
    return output;
}

Tensor relu_derivative(const Tensor& input) {
    Tensor output(input.rows, input.cols);
    for (size_t i = 0; i < input.rows; ++i) {
        for (size_t j = 0; j < input.cols; ++j) {
            output.data[i][j] = (input.data[i][j] > 0) ? 1.0 : 0.0;
        }
    }
    return output;
}

// Sigmoid 激活函数及其导数实现
Tensor sigmoid(const Tensor& input) {
    Tensor output(input.rows, input.cols);
    for (size_t i = 0; i < input.rows; ++i) {
        for (size_t j = 0; j < input.cols; ++j) {
            output.data[i][j] = 1.0 / (1.0 + std::exp(-input.data[i][j]));
        }
    }
    return output;
}

Tensor sigmoid_derivative(const Tensor& input) {
    Tensor output(input.rows, input.cols);
    Tensor sig = sigmoid(input);
    for (size_t i = 0; i < input.rows; ++i) {
        for (size_t j = 0; j < input.cols; ++j) {
            output.data[i][j] = sig.data[i][j] * (1.0 - sig.data[i][j]);
        }
    }
    return output;
}

// LinearLayer 类实现
LinearLayer::LinearLayer(size_t input_dim, size_t output_dim)
    : weights(input_dim, output_dim), biases(1, output_dim) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.1, 0.1);
    for (auto& row : weights.data) {
        for (auto& val : row) {
            val = dis(gen);
        }
    }
    for (auto& val : biases.data[0]) {
        val = dis(gen);
    }
}

Tensor LinearLayer::forward(const Tensor& input) {
    this->input = input;
    return input.matmul(weights).add(biases);
}

Tensor LinearLayer::backward(const Tensor& grad_output, double learning_rate) {
    Tensor grad_weights = input.transpose().matmul(grad_output);
    Tensor grad_biases = grad_output;

    for (size_t i = 0; i < weights.rows; ++i) {
        for (size_t j = 0; j < weights.cols; ++j) {
            weights.data[i][j] -= learning_rate * grad_weights.data[i][j];
        }
    }
    for (size_t j = 0; j < biases.cols; ++j) {
        biases.data[0][j] -= learning_rate * grad_biases.data[0][j];
    }

    return grad_output.matmul(weights.transpose());
}

// 损失函数实现
double mse_loss(const Tensor& predictions, const Tensor& targets) {
    double loss = 0.0;
    for (size_t i = 0; i < predictions.rows; ++i) {
        for (size_t j = 0; j < predictions.cols; ++j) {
            double diff = predictions.data[i][j] - targets.data[i][j];
            loss += diff * diff;
        }
    }
    return loss / predictions.rows;
}

double cross_entropy_loss(const Tensor& predictions, const Tensor& targets) {
    double loss = 0.0;
    for (size_t i = 0; i < predictions.rows; ++i) {
        for (size_t j = 0; j < predictions.cols; ++j) {
            if (targets.data[i][j] == 1.0) {
                loss -= std::log(predictions.data[i][j]);
            }
        }
    }
    return loss / predictions.rows;
}
