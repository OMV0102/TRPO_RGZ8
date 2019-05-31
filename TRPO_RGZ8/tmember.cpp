#include <map>
const short size = 10;
class TMember
{
private:
	// ============================
	int c; // Коэффициент одночлена 
	int d; // Степень одночлена


	// ============================
public:
	// ============================================
	// Конструктор
	TMember(int nc = 0, int nd = 0)
	{
		this->c = nc;
		this->d = nd;
	}

	//Конструктор копирования
	TMember(const TMember& P)
	{
		this->c = P.Coeff();
		this->d = P.Degree();
	}

	// оператор СРАВНЕНИЕ одночленов
	bool operator==(TMember& T)
	{
		return (this->c == T.Coeff() && this->d == T.Degree());
	}

	// ПРОТИВОПОЛОЖНЫЙ ЗНАК одночлена
	void operator - (void)
	{
		this->c = -this->c;
	}

	// Дифференцирование одночлена
	void Diff()
	{
		this->c *= this->d;
		this->d--;
		if (this->c != 0)
		{
			this->c *= this->d;
			this->d--;

		}
	}

	//Вычисление значения одночлена
	double Eval(double r)
	{
		return (this->c * pow(r, this->d));
	}

	// Преобразование к string
	char *toString()
	{
		char *str = new char[size];
		memset(str, 0, size);
		if (this->Coeff() < 0)
		{
			sprintf_s(str, size, "%d*X^%d", this->Coeff(), this->Degree());
		}
		else
		{
			sprintf_s(str, size, "+%d*X^%d", this->Coeff(), this->Degree());
		}
		return str;
	}

	// прочитать степень одночлена
	int Degree() const
	{
		return (this->d);
	}

	// записать степень одночлена
	void SetDeg(int deg)
	{
		this->d = deg;
	}

	// прочитать коэффициент одночлена
	int Coeff() const
	{
		return (this->c);
	}

	// записать степень
	void SetCoeff(int cof)
	{
		this->c = cof;
	}

	// Сложение одночлена с одночленом
	void operator += (TMember& q)
	{
		if (this->d == q.Degree())
			this->c += q.Coeff();
	}

	// Вычитание одночлена с одночленом
	void operator -= (TMember& q)
	{
		if (this->d == q.Degree())
			this->c -= q.Coeff();
	}

	// Умножение одночлена на одночлен
	void operator *= (TMember& q)
	{
		this->c *= q.Coeff();
		this->d += q.Degree();
	}
};