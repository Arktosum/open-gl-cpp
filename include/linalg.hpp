#include <iostream>
#include <vector>
#define M_PI 3.14159265358979323846264338327950288
class Matrix {
public:
    std::vector<std::vector<double>> data;
    int rows, cols;


    // Constructor
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<double>(cols, 0.0)) {}

    // Getter methods
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Matrix addition
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions do not match for addition.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    // Matrix subtraction
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions do not match for subtraction.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return result;
    }

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Invalid matrix dimensions for multiplication.");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    // Scaling (scalar multiplication)
    Matrix operator*(double scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = scalar * data[i][j];
            }
        }

        return result;
    }

    // Matrix transpose
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }

        return result;
    }

    // Print the matrix
    void print() const {
        std::cout <<"---------------------------"<<std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout <<"---------------------------"<<std::endl;
    }
};
#include <cmath>

class Matrix4x4 : public Matrix {
public:
    // Constructor
    Matrix4x4() : Matrix(4, 4) {
        for(int i = 0; i < 4; ++i){
            data[i][i] = 1.0f;
        }
    }
    static double degreesToRadians(double degrees) {
        return (degrees * M_PI) / 180.0;
    }
    // Rotation around X-axis
    static Matrix4x4 rotateX(double angleDegrees) {
        double angle = degreesToRadians(angleDegrees);
        Matrix4x4 rotationMatrix;
        double cosTheta = cos(angle);
        double sinTheta = sin(angle);

        rotationMatrix.data[1][1] = cosTheta;
        rotationMatrix.data[1][2] = -sinTheta;
        rotationMatrix.data[2][1] = sinTheta;
        rotationMatrix.data[2][2] = cosTheta;

        return rotationMatrix;
    }

    // Rotation around Y-axis
    static Matrix4x4 rotateY(double angleDegrees) {
        double angle = degreesToRadians(angleDegrees);

        Matrix4x4 rotationMatrix;
        double cosTheta = cos(angle);
        double sinTheta = sin(angle);

        rotationMatrix.data[0][0] = cosTheta;
        rotationMatrix.data[0][2] = sinTheta;
        rotationMatrix.data[2][0] = -sinTheta;
        rotationMatrix.data[2][2] = cosTheta;

        return rotationMatrix;
    }

    // Rotation around Z-axis
    static Matrix4x4 rotateZ(double angleDegrees) {
        double angle = degreesToRadians(angleDegrees);

        Matrix4x4 rotationMatrix;
        double cosTheta = cos(angle);
        double sinTheta = sin(angle);

        rotationMatrix.data[0][0] = cosTheta;
        rotationMatrix.data[0][1] = -sinTheta;
        rotationMatrix.data[1][0] = sinTheta;
        rotationMatrix.data[1][1] = cosTheta;

        return rotationMatrix;
    }

    // Translation
    static Matrix4x4 translate(double dx, double dy, double dz) {
        Matrix4x4 translationMatrix;

        translationMatrix.data[0][3] = dx;
        translationMatrix.data[1][3] = dy;
        translationMatrix.data[2][3] = dz;

        return translationMatrix;
    }

    static Matrix4x4 orthogonalProjection(){
        Matrix4x4 orthogonalMatrix;
        float left = -1, right = 1, bottom = -1, top = 1, near = -1, far = 1;
        orthogonalMatrix.data[0][0] = 1 / (right - left);
        orthogonalMatrix.data[0][3] = - (right + left) / (right - left);
        orthogonalMatrix.data[1][1] =  1 / (top - bottom);
        orthogonalMatrix.data[1][3] = - (top + bottom) / (top - bottom);
        orthogonalMatrix.data[2][2] = -2 / (far - near);
        orthogonalMatrix.data[2][3] = - (far + near) / (far - near);
        return orthogonalMatrix;
    }
    // Matrix multiplication with a 4x4 matrix (without modifying the current matrix)
    Matrix4x4 operator*(const Matrix& other) const {
        const Matrix& base = *this;
        const Matrix& derived = other;
        Matrix result = base * derived;
        return static_cast<const Matrix4x4&>(result);
    }

    float* toFloatArray(){
        float* floatArray = new float[4 * 4];
        size_t index = 0;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                floatArray[index++] = static_cast<float>(data[i][j]);
            }
        }

        return floatArray;
    }



};