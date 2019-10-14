# Solver
> El árbol de expresiones sirve para resolver operaciones combinadas de tipo 7/4*((3+1)*3)+3. 

## Diagrama de Clases:
![](class.png)
 
## Resultados
> Las pruebas se realizan invocando a los métodos execute_test1 y execute_test2 de la clase Tester.
```cpp
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
```
> Para probar las expresiones con variables como ((7*A)/A+6*(3^B)/2) solo es necesario descomentar las líneas y comentar los test. El resultado es similar al siguiente:
![](with_variables.png)