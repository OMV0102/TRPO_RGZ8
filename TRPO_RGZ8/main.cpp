#include <iostream>
#include "tpoly.cpp"

int main(int argc, char *argv[]) {
	TPoly *p1, *p2, *p3 , *p4, *res, *res2, *res3;
	
	p1 = new TPoly(5, 0);
	p2 = new TPoly(5, 1);
	p3 = new TPoly(5, 2);
	p4 = new TPoly(5, 3);
	
	std::cout << "TEST 0" << std::endl;
	res = *p1 + *p2;
	res2 = *p3 + *p4;
	res3 = *res + *res2;
	res3->Norm();
	std::cout << res3->toString() << std::endl;

	std::cout << "TEST 1" << std::endl;			// TEST 1: 2x^0 + 3x^0
	p1 = new TPoly(2, 0); p2 = new TPoly(3, 0);
	res = *p1 + *p2;
	std::cout << "(" << p1->toString() << ") + (" << p2->toString() << ") = " << res->toString() << std::endl << std::endl;

	p1 = new TPoly(5, 1);
	p2 = new TPoly(3, 0);
	res = *p1 - *p2;
	std::cout << "(" << p1->toString() << ") - (" << p2->toString() << ") = " << res->toString() << std::endl;

	//===================================================================================================

	
	
	std::cout << "TEST 3" << std::endl;			// TEST 3: (5x^1 - 3x^0) * 2x^1
	p1 = res; p2 = new TPoly(2, 1);
	res = *p1 * *p2;
	//std::cout << "(" << p1->toString() << ") * (" << p2->toString() << ") = " << res->toString() << std::endl;
	std::cout << "(" << p1->toString() << ") *"  << std::endl;
	std::cout << "(" << p2->toString() << ") =" << std::endl;
	std::cout  << res->toString() << std::endl;

	//===================================================================================================

	std::cout << "TEST 4" << std::endl;			// TEST 4: (10x^2 - 6x^1)'
	p1 = res;
	res = p1->Diff();
	std::cout << "(" << p1->toString() << ")' = " << res->toString() << std::endl;

	//===================================================================================================

	std::cout << "TEST 5" << std::endl;			// TEST 5: -(20x^1 - 6x^0)
	p1 = res;
	std::cout << "-(" << p1->toString() << ") = ";
	-*p1;
	std::cout << p1->toString() << std::endl;

	//===================================================================================================

	std::cout << "TEST 6" << std::endl;			// TEST 6: f(x) = (-20x^1 + 6x^0), x = 0.5;
	p1 = res;
	std::cout << "f(x) = (" << p1->toString() << ")', f(0.5) = " << p1->Eval(0.5) << std::endl;
	system("pause");
	return 0;
}