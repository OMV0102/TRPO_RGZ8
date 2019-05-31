#include "tmember.cpp"

class TPoly
{
private:
	std::map <int, TMember> members;

	void RemoveZero()  // Удаление нулевых одночленов
	{
		if (this->Count() > 1)
		{
			for (int i = 0; i < this->Count() && this->Count() > 1;)
				if (this->members[i].Coeff() == 0)
					this->members.erase(i);
				else
					i++;
		}
	}

public:
	// Конструктор
	TPoly(int nc = 0, int nd = 0)
	{
		this->members.insert(std::pair<int, TMember>(this->members.size(), TMember(nc, nd)));
	}

	// Копирующий конструктор
	TPoly(const TPoly& P)
	{
		for (int i = 0; i < P.Count(); i++)
			this->members.insert(std::pair<int, TMember>(this->members.size(), TMember(P.members.at(i))));
	}

	// подсчет количества одночленов в полиноме
	int Count() const
	{
		return this->members.size();
	}

	// поиск идекса полинома по степени
	TMember* FindIndByDeg(int n)
	{
		TMember *res;
		for (int i = 0; i < this->Count(); i++)
		{
			res = &(this->members[i]);
			if (res->Degree() == n)
				return res;
		}
		return NULL;
	}

	// В СТРОКУ
	char *toString()
	{
		this->RemoveZero();
		int len = this->Count();
		char *out = new char[len * size];
		memset(out, 0, len * size);
		for (int i = 0; i < len; i++)
			strcat_s(out, len * size, this->members[i].toString());
		return out;
	}

	// ОЧИСТИТЬ
	void Clear()
	{
		this->members.clear();
		this->members.insert(std::pair<int, TMember>(this->members.size(), TMember()));
	}

	// проверка для нормализации полинома
	bool reg()
	{
		int i = 0;
		bool f = true;
		while (i < this->Count() - 1)
		{
			if (this->members[i].Degree() < this->members[i + 1].Degree())
			{
				f = false;
				break;
			}
			i++;
		}
		return f;
	}

	// НОРМАЛИЗОВАННЫЙ ПОЛИНОМ
	void Norm()
	{
		while (!reg())
		{
			int i = 0;
			while (i < this->Count() - 1)
			{
				if (this->members[i].Degree() < this->members[i + 1].Degree())
				{
					TMember buf = this->members[i + 1];
					this->members[i + 1] = this->members[i];
					this->members[i] = buf;
				}
				i++;
			}
		}
	}

	// ПРИВЕДЕНИЕ ПОДОБНЫХ
	void similar()
	{
		TPoly *buf = new TPoly(0, 0);
		for (int i = 0; i < this->Count();)
		{
			TMember mem;
			mem.SetCoeff(this->members[i].Coeff());
			mem.SetDeg(this->members[i].Degree());

			int s = 0;
			for (int j = i + 1; j < this->Count(); j++)
				if (mem.Degree() == this->members[j].Degree())
				{
					mem += this->members[j];
					s++;
				}
			buf->members.insert(std::pair<int, TMember>(this->members.size(), mem));
			i += s + 1;
		}
		*this = *buf;
	}

	// оператор СКОБКИ
	TMember* operator[](int i)
	{
		if (i < this->Count())
			return &(this->members[i]);
		else
			return NULL;
	}

	// оператор ПЛЮС РАВНО
	void operator += (TMember& q)
	{
		TMember *cur = this->FindIndByDeg(q.Degree());
		if (cur)
			*cur += q;
		else
			this->members.insert(std::pair<int, TMember>(this->members.size(), TMember(q)));
	}

	// оператор ПЛЮС
	TPoly* operator+(TPoly& T)
	{
		TPoly *res = new TPoly(*this);
		for (int i = 0; i < T.Count(); i++)
			*res += *T[i];
		res->RemoveZero();
		res->Norm();
		return res;
	}

	// оператор УМНОЖИТЬ РАВНО
	void operator*=(TMember& q)
	{
		for (int i = 0; i < this->Count(); i++)
			this->members[i] *= q;
	}

	// оператор УМНОЖИТЬ
	TPoly* operator*(TPoly& B)
	{
		TPoly *res = new TPoly(0, 0);
		for (int i = 0; i < this->Count(); i++)
			for (int j = 0; j < B.Count(); j++)
			{
				TMember mem;
				mem.SetCoeff(this->members[i].Coeff());
				mem.SetDeg(this->members[i].Degree());
				mem *= B.members[j];
				res->members.insert(std::pair<int, TMember>(this->members.size(), mem));
			}
		res->RemoveZero();
		res->Norm();
		return res;

	}

	// оператор МИНУС
	TPoly* operator - (TPoly& q)
	{
		TPoly *res = new TPoly(*this);
		for (int i = 0; i < q.Count(); i++)
		{
			-q;
			*res += *q[i];
			-q;
		}
		res->RemoveZero();
		res->Norm();
		return res;
	}

	// оператор СРАВНЕНИЕ
	bool operator==(TPoly& q)
	{
		if (this->Count() != q.Count())
			return false;
		for (int i = 0; i < this->Count(); i++)
			if (!(this->members[i] == *q.FindIndByDeg(this->members[i].Degree())))
				return false;
		return true;
	}

	// оператор ПРОТИВОПОЛОЖНЫЙ ЗНАК
	void operator -()
	{
		for (int i = 0; i < this->Count(); i++)
		{
			this->members[i].SetCoeff(-this->members[i].Coeff());
		}
	}

	// ДИФФЕРЕНЦИРОВАНИЕ
	TPoly* Diff()
	{
		TPoly *res = new TPoly(*this);
		for (int i = 0; i < res->Count(); i++)
			res->members[i].Diff();
		return res;
	}

	// ЗНАЧЕНИЕ
	double Eval(double x)
	{
		double res = 0.0;
		for (int i = 0; i < this->Count(); i++)
			res += this->members[i].Eval(x);
		return res;
	}
};