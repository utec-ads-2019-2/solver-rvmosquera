
#include <iomanip>
#include <cctype>

#include "test/tester.h"

int main(int argc, char *argv[]) {

   // Tester::execute_test1();

// #Test variables: Descomentar para probar expresiones con variables
 auto exp = new ExpressTree();
    string infixExpression = "";

    cout << "Input the infixExpression :";
    getline(cin, infixExpression);
    exp->generateFromInfixExp(infixExpression);
    exp->askvalueVariables();
    cout << " \nResult = " << exp->evaluate() << endl;
    exp->printPostFix();

    return EXIT_SUCCESS;
}
