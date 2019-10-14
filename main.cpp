
#include <iomanip>
#include "test/tester.h"

int main(int argc, char *argv[]) {

    Tester::execute_test1();
    Tester::execute_test2();

// #Test variables: Descomentar para probar expresiones con variables
    /*auto exp = new ExpressTree();
    string infixExpression = "";

    cout << "Input the infixExpression :";
    getline(cin, infixExpression);
    exp->generateFromInfixExp(infixExpression);
    exp->askvalueVariables();
    auto result = exp->evaluate();
    cout << " \nResult = " << result << endl;
    //exp->printPostFix();*/

    return EXIT_SUCCESS;
}
