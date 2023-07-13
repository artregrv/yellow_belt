#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
public:
	Matrix() : 
		_rows(0),
		_cols(0)
	{}

	Matrix(int rows, int cols)
	{
		if (rows < 0 || cols < 0) {
			throw std::out_of_range("Rows and cols should be >= 0");
		}

		if (rows == 0 || cols == 0) {
			rows = 0;
			cols = 0;
		}

		_rows = rows;
		_cols = cols;

		_matrix.resize(rows);
		for (auto &row : _matrix) {
			row.resize(cols);
		}
	}
	
	void Reset(int rows, int cols)
	{
		if (rows < 0 || cols < 0) {
			throw std::out_of_range("Rows and cols should be >= 0");
		}

		if (rows == 0 || cols == 0) {
			rows = 0;
			cols = 0;
		}

		_rows = rows;
		_cols = cols;

		_matrix.resize(rows);

		for (int i = 0; i < rows; ++i) {
			_matrix[i].resize(cols);
			
			for (int j = 0; j < cols; ++j) {
				_matrix[i][j] = 0;
			}
		}
	}

	int At(int row, int col) const
	{
		if (row < 0 || col < 0 || row >= _rows || col >= _cols) {
			throw std::out_of_range("Rows and cols should be >= 0");
		}

		return _matrix.at(row).at(col);
	}

	int &At(int row, int col)
	{
		if (row < 0 || col < 0 || row >= _rows || col >= _cols) {
			throw std::out_of_range("Rows and cols should be >= 0");
		}

		return _matrix[row][col];
	}

	int GetNumRows() const
	{
		return _rows;
	}

	int GetNumColumns() const
	{
		return _cols;
	}

private:
	std::vector<std::vector<int>> _matrix;
	int _rows { 0 };
	int _cols { 0 };
};

std::istream &operator>>(std::istream &stream, Matrix &matrix)
{
	int rows;
	int cols;
	
	stream >> rows >> cols;

	matrix.Reset(rows, cols);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			stream >> matrix.At(i, j);
		}
	}

	return stream;
}

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix)
{
	int rows = matrix.GetNumRows();
	int cols = matrix.GetNumColumns();

	stream << rows << ' ' << cols << '\n';

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			stream << matrix.At(i, j) << ' ';
		}
		stream << '\n';
	}

	return stream;
}

bool operator==(const Matrix &lhs, const Matrix &rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows()
		|| lhs.GetNumColumns() != rhs.GetNumColumns()) {
		return false;
	}
	
	int rows = lhs.GetNumRows();
	int cols = lhs.GetNumColumns();

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (lhs.At(i, j) != rhs.At(i, j)) {
				return false;
			}
		}
	}

	return true;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{
	if (lhs.GetNumRows() != rhs.GetNumRows()
		|| lhs.GetNumColumns() != rhs.GetNumColumns()) {
		throw std::invalid_argument("Matrices should be the same size!");
	}

	int rows = lhs.GetNumRows();
	int cols = lhs.GetNumColumns();

	Matrix result(rows, cols);

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}

	return result;
}

int main()
{
	Matrix m1;
	std::cin >> m1;
	std::cout << m1;

	Matrix m2;
	std::cin >> m2;
	std::cout << m2;

	if (m1 == m2) {
		std::cout << "equal\n";
	} else {
		std::cout << "not equal\n";
	}

	Matrix m3 = m1 + m2;

	std::cout << m3;

	return 0;
}
