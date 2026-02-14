#include<core/classes/compute/invert_matrix.hpp>

std::vector<std::vector<double>> invertComponentMatrix(
    const std::vector<std::vector<std::function<double(const std::vector<double>&)>>>& componentMatrix,
    const std::vector<double>& point) {
    
    size_t n = componentMatrix.size();
    if (n == 0) {
        throw std::invalid_argument("Matrix is empty");
    }
    
    // Проверка, что матрица квадратная
    for (const auto& row : componentMatrix) {
        if (row.size() != n) {
            throw std::invalid_argument("Component matrix must be square");
        }
    }
    
    // 1. Вычисляем значения всех функций в заданной точке
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            A[i][j] = componentMatrix[i][j](point);
        }
    }
    
    // 2. Создаем копию матрицы для LU-разложения и матрицу перестановок
    std::vector<std::vector<double>> LU = A;
    std::vector<int> permutations(n);
    for (size_t i = 0; i < n; ++i) {
        permutations[i] = i;
    }
    
    // 3. LU-разложение с частичным выбором главного элемента
    for (size_t k = 0; k < n; ++k) {
        // Поиск максимального элемента в столбце k
        double maxElement = std::abs(LU[k][k]);
        size_t maxRow = k;
        for (size_t i = k + 1; i < n; ++i) {
            if (std::abs(LU[i][k]) > maxElement) {
                maxElement = std::abs(LU[i][k]);
                maxRow = i;
            }
        }
        
        // Проверка на вырожденность матрицы
        if (maxElement < 1e-12) {
            throw std::runtime_error("Matrix is singular or nearly singular at given point");
        }
        
        // Перестановка строк
        if (maxRow != k) {
            std::swap(LU[k], LU[maxRow]);
            std::swap(permutations[k], permutations[maxRow]);
        }
        
        // LU-разложение
        for (size_t i = k + 1; i < n; ++i) {
            LU[i][k] /= LU[k][k];
            for (size_t j = k + 1; j < n; ++j) {
                LU[i][j] -= LU[i][k] * LU[k][j];
            }
        }
    }
    
    // 4. Создаем единичную матрицу для обратной
    std::vector<std::vector<double>> inverse(n, std::vector<double>(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        inverse[i][i] = 1.0;
    }
    
    // 5. Применяем перестановки к единичной матрице
    std::vector<std::vector<double>> permutedIdentity(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        permutedIdentity[i] = inverse[permutations[i]];
    }
    
    // 6. Решаем систему LU * X = permutedIdentity для каждого столбца
    for (size_t col = 0; col < n; ++col) {
        // Прямая подстановка (решаем L * y = b)
        std::vector<double> y(n);
        for (size_t i = 0; i < n; ++i) {
            double sum = 0.0;
            for (size_t j = 0; j < i; ++j) {
                sum += LU[i][j] * y[j];
            }
            y[i] = permutedIdentity[i][col] - sum;
        }
        
        // Обратная подстановка (решаем U * x = y)
        for (int i = n - 1; i >= 0; --i) {
            double sum = 0.0;
            for (size_t j = i + 1; j < n; ++j) {
                sum += LU[i][j] * inverse[j][col];
            }
            inverse[i][col] = (y[i] - sum) / LU[i][i];
        }
    }
    
    return inverse;
}