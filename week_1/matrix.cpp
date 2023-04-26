#include <iostream>
#include <vector>

class Matrix
{
public:
	Matrix() : 
		_rows(0),
		_cols(0)
	{}

	Matrix(int rows, int cols) :
		_rows(rows),
		_cols(cols)
	{}
	
	void Reset(int rows, int cols)
	{
		
	}

	int At(int row, int col) const
	{
		return _matrix.at(row).at(col);
	}

	int &At(int row, int col)
	{
		return _matrix[row][col];
	}

	int GetNumRows() const
	{
		return _rows;
	}

	int GetNumCols() const
	{
		return _cols;
	}

private:
	std::vector<std::vector<int>> _matrix;
	int _rows { 0 };
	int _cols { 0 };
};

int main()
{
	return 0;
}
