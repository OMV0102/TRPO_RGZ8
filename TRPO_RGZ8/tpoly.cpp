#include "tmember.cpp"

class TPoly 
{
	private:
		std::map<int, TMember> members;

		void RemoveZero()  // Удаление нулевых одночленов
		{
			for (int i = 0; i < this->Count() - 1;)
				if (this->members[i].Coeff() == 0 && this->members[i].Degree() == 0)
					this->members.erase(i); // убрала begin
				else
					i++;
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

		int Count() const 
		{
			return this->members.size();
		}

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

		bool reg()
		{
			int i = 0;
			bool f = true;
			while (i < this->Count() - 1)
			{
				if (this->members[i].Degree() < this->members[i+1].Degree())
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


			
			/*int indmaxDeg = 0;
			bool indCnange = false;
			TMember *m = new TMember();
			for (int i = 0; i < this->Count(); i++)
			{
				for (int j = i; j < this->Count()-1; j++)
				{

					if (this->members[j].Degree() > this->members[indmaxDeg].Degree())
					{
						indmaxDeg = j;
						indCnange = true;
					}
				}
				if (indCnange)
				{
					m->SetDeg(this->members[i].Degree());
					m->SetCoeff(this->members[i].Coeff());
					this->members[i].SetDeg(this->members[indmaxDeg].Degree());
					this->members[i].SetCoeff(this->members[indmaxDeg].Coeff());
					this->members[indmaxDeg].SetDeg(m->Degree());
					this->members[indmaxDeg].SetCoeff(m->Coeff());
					indCnange = false;
				}
			}*/
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

		// оператор МИНУС РАВНО
		void operator-=(TMember& q)
		{
			TMember *cur = this->FindIndByDeg(q.Degree());
			if (cur)
				*cur -= q;
			else
				this->members.insert(std::pair<int, TMember>(this->members.size(), TMember(q)));
		}

		// оператор ПЛЮС
		TPoly* operator+(TPoly& T) 
		{
			TPoly *res = new TPoly(*this);
			for (int i = 0; i < T.Count(); i++)
				*res += *T[i];
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
			std::map<int,TPoly> cont;
			for (int i = 0; i < B.Count(); i++) {
				cont.insert(std::pair<int, TPoly>(cont.size(), *this));
				cont[i] *= *B[i];
			}
			TPoly *res = new TPoly();
			for (int i = 0; i < cont.size(); i++)
				res = *res + cont[i];
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