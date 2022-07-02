/**********************************************
  > File Name		: CalculatorTool.java
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 22 Apr 2022 05:40:35 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class CalculatorTool {
    public static void main(String[] args) throws Exception {
        IntegerCalculator ic = new IntegerCalculator();
        System.out.println(ic.calculate(args[0]));
    }
}

interface Calculator<T> {
    public T calculate(String expression) throws Exception;
}

class IntegerCalculator implements Calculator<Integer> {
    private static final Map<Character, Integer> operatorPriority;
    private Stack<Integer> numbers;
    private Stack<Character> operators;

    static {
        operatorPriority = new HashMap<>();
        operatorPriority.put('+', 3);
        operatorPriority.put('-', 3);
        operatorPriority.put('*', 2);
        operatorPriority.put('/', 2);
    }

    {
        this.numbers = new Stack<>();
        this.operators = new Stack<>();
    }

    @Override
    public Integer calculate(String expression) throws Exception {
        char[] chars = expression.toCharArray();
        int number = 0;
        boolean numberFlag = false;

        for (char c: expression.toCharArray()) {
            print("c = " + c);
            if (Character.isDigit(c)) {
                number *= 10;
                number += c - '0';
                numberFlag = true;
                continue;
            }

            if (numberFlag) {
                this.numbers.push(number);
                number = 0;
                numberFlag = false;
            }

            switch (c) {
                case '(':
                    this.operators.push(c);
                    break;
                case ')':
                    while (this.operators.peek() != '(') {
                        this.numbers.push(operate(this.numbers.pop(), this.numbers.pop(), this.operators.pop()));
                    }
                    this.operators.pop(); //pop (
                    break;
                case '-':
                    if (this.operators.isEmpty() || this.operators.peek() == '(') {
                        this.numbers.push(0);
                    }
                default:
                    while (!this.operators.isEmpty() && this.operators.peek() != '(' 
                            && operatorPriority.get(c) >= operatorPriority.
                            get(this.operators.peek())) {
                        this.numbers.push(operate(this.numbers.pop(), this.numbers.pop(), this.operators.pop()));
                    }
                    this.operators.push(c);
                    break;
            }
        }

        if (numberFlag) {
            this.numbers.push(number);
        }

        while (!this.operators.isEmpty()) {
            this.numbers.push(operate(this.numbers.pop(), this.numbers.pop(), this.operators.pop()));
        }
        return this.numbers.pop();
    }

    public static Integer operate(Integer rhs, Integer lhs, Character operator) throws Exception {
        switch (operator) {
            case '+':
                return lhs + rhs;
            case '-':
                return lhs - rhs;
            case '*':
                return lhs * rhs;
            case '/':
                return lhs / rhs;
            default:
                throw new Exception("Invalid operator" + operator);
        }
    }

    public static <T> void print(T t) {
        System.out.println(t);
    }
}

