#include <iostream>
#include "tpoly.cpp"

int main(int argc, char *argv[]) {
	TPoly *p1, *p2, *p3, *p4, *res;

	p1 = new TPoly(3, 2);
	p2 = new TPoly(4, 2);
	p3 = new TPoly(3, 0);
	p4 = new TPoly(5, 3);


	std::cout << "=============== TEST 1 =================" << std::endl; // сложение с 2
	res = *p1 - *p2;
	std::cout << "(" << p1->toString() << ") - (" << p2->toString() << ") = " << res->toString() << std::endl << std::endl;

	/*std::cout << "=============== TEST 2 =================" << std::endl;	// сложение с 3
	res = *p1 - *p2;
	res = *res - *p3;
	std::cout << "(" << p1->toString() << ") - (" << p2->toString() << ") - ("<< p3->toString() << ") = "<< res->toString() << std::endl << std::endl;*/

	//std::cout << "=============== TEST 3 =================" << std::endl;// умножение с 2
	//res = *p1 * *p2;
	//std::cout << "(" << p1->toString() << ") * (" << p2->toString() << ") = " << res->toString() << std::endl << std::endl;

	/*std::cout << "=============== TEST 4 =================" << std::endl;// умножение с 3
	res = *p1 * *p2;
	res = *res * *p3;
	std::cout << "(" << p1->toString() << ") 8 (" << p2->toString() << ") 8 (" << p3->toString() << ") = " << res->toString() << std::endl << std::endl;*/

	/*std::cout << "=============== TEST 5 =================" << std::endl;  // дифференцирование
	res = *p1 * *p2;
	std::cout << "(" << p1->toString() << ") * (" << p2->toString() << ") = " << res->toString() << std::endl << std::endl;
	*res->Diff();
	std::cout << "Diff(p1 * p2) = " << res->toString() << std::endl << std::endl;*/

	/*std::cout << "================ TEST 6 =================" << std::endl;
	std::cout << "f(x) = (" << p1->toString() << "), f(1) = " << p1->Eval(1) << std::endl;*/



	system("pause");
	return 0;
}