#include <iostream>

template <class T>
class Table {
private:
	T** table;
	int rows;
	int cols;
	int size;

public:

	Table(int rowsСount, int colsCount) : rows(rowsСount), cols(colsCount)
	{
		table = new T * [rows] {};
		for (int i = 0; i < rows;i++)
		{
			table[i] = new T[cols]{};
		}
		std::cout << "Конструктор " << this << std::endl;
	};

	Table(const Table& other)
	{
		this->rows = other.rows;
		this->cols = other.cols;

		table = new T * [this ->rows] {};

		for (int i = 0; i < this->rows;i++)
		{
			table[i] = new T[this->cols]{};
		}
		std::cout << "Конструктор" << this << std::endl;

		for (int i = 0;i < other.rows;i++)
		{
			for (int j = 0;j < other.cols;j++)
			{
				this->table[i][j] = other.table[i][j];
			}
		}
		std::cout << this << "Конструктор копирования Table" << std::endl;
	};

	T& operator()(int i, int j)
	{
		if (i >= rows || i < 0)
			throw std::out_of_range("Выход за пределы (i)");

		if (j >= cols || j < 0)
			throw std::out_of_range("Выход за пределы (j)");

		return table[i][j];
	};

	class Array
	{
	public:
			Array(T* arr_rows, const int colsCount) : arr_rows(arr_rows), cols(colsCount){}

			T& operator[](int i)
			{
				if (i >= cols || i < 0)
					throw std::out_of_range("Выход за пределы (j)");
				return arr_rows[i];
			}

	private:
		T* arr_rows;
		int cols = 0;
	};

	

	Array operator[](const int i) const
	{
		if (i >= rows || i < 0)
			throw std::out_of_range("Выход за пределы (i)");
		return Array(table[i], cols);
	};

	Table& operator = (const Table& other)
	{
		if (this != &other)
		{
			this->cols = other.cols;
			this->rows = other.rows;

			this->~Table();

			table = new T * [rows] {};

			for (int i = 0; i < rows;i++)
			{
				table[i] = new T[cols]{};
			}
			std::cout << "Конструктор" << this << std::endl;

			for (int i = 0; i < other.rows;i++)
			{
				for (int j = 0;j < other.cols;j++)
				{
					this->table[i][j] = other.table[i][j];
				}
			}
			std::cout << this << std::endl;
			return *this;
		};
	};

	void getSize()
	{
		std::cout << "Рзамер массива: " << rows << "x" << cols << std::endl;
	};

	void print()
	{
		for (int i = 0;i < rows;i++)
		{
			for (int j = 0;j < cols;j++)
			{
				std::cout << table[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	};

	~Table()
	{
		for (int j = 0;j < this->rows;j++)
		{
			delete[] this->table[j];
		}
		delete[] this->table;
		this->table = nullptr;
		std::cout << this << std::endl;
	}
};



int main(int argc, char** argv) 
{

	setlocale(LC_ALL, "Rus");

	Table<double> T1(7, 7);

	T1.print();
	T1.getSize();

	try 
	{
		T1(0, 0) = 5.5;
		T1(1, 1) = 7.9;
		T1(2, 2) = 9.5;
		T1(5, 4) = 11.8;
		T1[5][5] = 199;
		T1[5][6] = 255;

		T1.print();

		std::cout << T1(1, 1) << "\n";
		std::cout << T1[5][5] << "\n";

		Table<double> t1(2, 3);
		Table<double> t2(2, 3);


		t2(0, 0) = 999.99;
		t2(1, 2) = 888.88;
		t2(1, 1) = 777.77;

		std::cout << "\nОбъект t1\n";
		t1.print();

		std::cout << "\nОбъект t2\n";
		t2.print();

		t1 = t2;

		std::cout << "\nОбъект t1\n";
		t1.print();

		std::cout << "\nОбъект t2\n";
		t2.print();

		Table<double> t3(t1);
		std::cout << "\nОбъект t3\n";
		t3.print();
	}

	catch (const std::exception& ex) 
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}